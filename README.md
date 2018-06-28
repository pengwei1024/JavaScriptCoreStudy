# JavaScriptCoreStudy
JavaScriptCore study

### 简单的四则运算
```c++
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
```
