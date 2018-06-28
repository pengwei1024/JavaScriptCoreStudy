//
// Created by pengwei on 2018/6/28.
//

#ifndef JAVASCRIPTCORESTUDY_LOG_H
#define JAVASCRIPTCORESTUDY_LOG_H

#include<android/log.h>

#define TAG "NativeTag"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


#endif //JAVASCRIPTCORESTUDY_LOG_H
