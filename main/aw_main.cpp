/*
 * Copyright 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "aw"

//#define NDEBUG 0

#include <android-base/strings.h>
#include <binder/IPCThreadState.h>
#include <signal.h>
#include <string.h>
#include <utils/Errors.h>
#include <utils/Log.h>
#include "aw.h"

using namespace android::base;
using namespace std;
using namespace android;

int main(int argc, char* const argv[]) {
    ALOGE("android work test ..., argc:%d argv:%s\n", argc, argv[0]);
    ProcessState::self()->startThreadPool();  //启动线程池
    IPCThreadState::self()->joinThreadPool(); //把主线程加入线程池
    while(1) {
        ;
    }
    return 0;
}