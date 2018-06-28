#include <jni.h>
#include <string>
#include "JavaScriptCore/JavaScript.h"
#include "Example.cpp"
#include "Log.h"

extern "C" JNIEXPORT jstring
JNICALL
Java_com_apkfuns_javascriptcorestudy_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jdouble
JNICALL
Java_com_apkfuns_javascriptcorestudy_MainActivity_calculation(
        JNIEnv *env, jobject obj, jstring jsValue) {
    const char *buffer = (env)->GetStringUTFChars(jsValue, 0);
    JSValueRef exception = nullptr;
    JSGlobalContextRef executor_context_ = ::JSGlobalContextCreate(nullptr);
    JSStringRef script = ::JSStringCreateWithUTF8CString(buffer);
    JSValueRef value = ::JSEvaluateScript(executor_context_, script, 0, 0, 0, &exception);
    if (JSValueIsNumber(executor_context_, value)) {
        double result = JSValueToNumber(executor_context_, value, nullptr);
        LOGD("JSValueIsNumber: %f", result);
        return result;
    }
    ::JSStringRelease(script);
    return -1;
}


extern "C" JNIEXPORT void JNICALL
Java_com_apkfuns_javascriptcorestudy_MainActivity_callObject(
        JNIEnv *env, jobject obj) {
    LOGD("callObject!!");
    Example example = Example();
}
