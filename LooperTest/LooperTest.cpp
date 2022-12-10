//
// Copyright 2010 The Android Open Source Project
//
#define LOG_NDEBUG 0
#define LOG_TAG "LooperTest"

#include <time.h>
#include <unistd.h>
#include <utils/Log.h>
#include <utils/Looper.h>
#include <utils/Timers.h>
#include <utils/threads.h>

// # of milliseconds to fudge stopwatch measurements
#define TIMING_TOLERANCE_MS 25

using namespace android;
using namespace std;

class StubMessageHandler : public MessageHandler {
 public:
  Vector<Message> messages;

  virtual void handleMessage(const Message& message) {
    ALOGD("[Thread=%d] %s message.what=%d \n", gettid(), __func__,
          message.what);
    messages.push(message);
  }
};

struct LooperThread : public Thread {
 public:
  LooperThread(Looper* looper) : mLooper(looper) {}

  virtual bool threadLoop() {
    if (mLooper == NULL) return false;
    int32_t ret = mLooper->pollOnce(-1);
    switch (ret) {
      case Looper::POLL_WAKE:
      case Looper::POLL_CALLBACK:
        return true;
      case Looper::POLL_ERROR:
        ALOGE("Looper::POLL_ERROR");
        return true;
      case Looper::POLL_TIMEOUT:
        // timeout (should not happen)
        return true;
      default:
        // should not happen
        ALOGE("Looper::pollOnce() returned unknown status %d", ret);
        return true;
    }
  }

 protected:
  virtual ~LooperThread() {}

 private:
  Looper* mLooper;
};

class CallbackHandler {
 public:
  CallbackHandler() : callbackCount(0) {}
  void setCallback(const sp<Looper>& looper, int fd, int events) {
    looper->addFd(fd, 0, events, staticHandler, this);
  }

 protected:
  int handler(int fd, int events) {
    callbackCount++;
    ALOGD("[Thread=%d] %s fd=%d, events=%d, callbackCount=%d\n", gettid(),
          __func__, fd, events, callbackCount);
    return 0;
  }

 private:
  static int staticHandler(int fd, int events, void* data) {
    return static_cast<CallbackHandler*>(data)->handler(fd, events);
  }
  int callbackCount;
};

class Pipe {
 public:
  int sendFd;
  int receiveFd;

  Pipe() {
    int fds[2];
    ::pipe(fds);

    receiveFd = fds[0];
    sendFd = fds[1];
  }

  ~Pipe() {
    if (sendFd != -1) {
      ::close(sendFd);
    }

    if (receiveFd != -1) {
      ::close(receiveFd);
    }
  }

  status_t writeSignal() {
    ssize_t nWritten = ::write(sendFd, "*", 1);
    return nWritten == 1 ? 0 : -errno;
  }

  status_t readSignal() {
    char buf[1];
    ssize_t nRead = ::read(receiveFd, buf, 1);
    return nRead == 1 ? 0 : nRead == 0 ? -EPIPE : -errno;
  }
};

int main(void) {
  // Looper的轮询处理工作在新线程中
  sp<Looper> mLooper = new Looper(true);
  sp<LooperThread> mLooperThread = new LooperThread(mLooper.get());
  mLooperThread->run("LooperThread");

  // 测试消息的发送与处理
  sp<StubMessageHandler> handler = new StubMessageHandler();
  ALOGD("[Thread=%d] sendMessage message.what=%d \n", gettid(), 1);
  mLooper->sendMessage(handler, Message(1));
  ALOGD("[Thread=%d] sendMessage message.what=%d \n", gettid(), 2);
  mLooper->sendMessage(handler, Message(2));

  sleep(1);

  // 测试监测fd与回调callback
  Pipe pipe;
  CallbackHandler mCallbackHandler;
  mCallbackHandler.setCallback(mLooper, pipe.receiveFd, Looper::EVENT_INPUT);
  ALOGD("[Thread=%d] writeSignal 1\n", gettid());
  pipe.writeSignal();  // would cause FD to be considered signalled
  sleep(1);
  mCallbackHandler.setCallback(mLooper, pipe.receiveFd, Looper::EVENT_INPUT);
  ALOGD("[Thread=%d] writeSignal 2\n", gettid());
  ALOGI("ALOGI test!");
  ALOGV("ALOGV test@");
  pipe.writeSignal();

  sleep(1);
  mLooperThread->requestExit();
  mLooper.clear();
}