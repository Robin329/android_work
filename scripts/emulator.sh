#!/bin/bash

export ANDROID_ROOT=/Volumes/android/android11 
EMULATOR=/Users/renbinjiang/Library/Android/sdk/emulator/emulator
echo -e
echo -e "/Users/renbinjiang/Library/Android/sdk/emulator/emulator "
echo -e "-netdelay none -netspeed full -avd Pixel_3_XL_API_30"
$EMULATOR -netdelay none \
    -netspeed full \
    -avd Pixel_3_XL_API_30 \
    -writable-system \
    -shell \
    -no-boot-anim\
   # -gpu host \
    -selinux disabled \
    -skip-adb-auth \
    -sysdir ${ANDROID_ROOT}/out/target/product/crosshatch/  \
    -kernel ${ANDROID_ROOT}/prebuilts/qemu-kernel/arm64/5.4/kernel-qemu2
echo -e
echo -e
