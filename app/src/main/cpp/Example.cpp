//
// Created by pengwei on 2018/6/28.
// https://juejin.im/post/5ad420656fb9a028bc2e359a
//

#include "Example.h"
#include "JavaScriptCore/JavaScript.h"
#include "Log.h"

// example.test() 调用时对应的 c++ 函数钩子
static JSValueRef
TestStaticCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef object, size_t argumentCount,
                   const JSValueRef arguments[], JSValueRef *exception) {
    // 获取 JS 引擎对象中持有的 c++ 对象
    Example *example = static_cast<Example *>(JSObjectGetPrivate(object));
    example->TestStatic();
}

// example.testDynamic() 调用时对应的 c++ 函数钩子
static JSValueRef TestDynamicCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef object,
                                      size_t argumentCount, const JSValueRef arguments[],
                                      JSValueRef *exception) {
    Example *example = static_cast<Example *>(JSObjectGetPrivate(object));
    example->TestDynamic();
}

// console.log(example.num) 调用时对应触发的 c++ 钩子函数
static JSValueRef GetNumCallback(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName,
                                 JSValueRef *exception) {
    Example *example = static_cast<Example *>(JSObjectGetPrivate(object));
    int num = example->num();
    return JSValueMakeNumber(ctx, num);
}

// example.num = 99 时会触发该的 c++ 函数钩子
static bool
SetNumCallback(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value,
               JSValueRef *exception) {
    Example *example = static_cast<Example *>(JSObjectGetPrivate(object));
    example->set_num(JSValueToNumber(ctx, value, NULL));
}

// 定义将要 Extension 的静态方法，其中包含函数钩子
static JSStaticFunction s_examplle_function_[] = {
        {"testStatic", TestStaticCallback, kJSClassAttributeNone},
        {0,            0,                  0}
};

// 定义将要 Extension 的变量，其中包含 get 和 set 函数钩子
static JSStaticValue s_example_values_[] = {
        {"num", GetNumCallback, SetNumCallback,
                                   kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
        {0,     0,              0, 0}
};

void Example::Initialize() {
    // 初始化 JSC 引擎
    JSContextGroupRef context_group = JSContextGroupCreate();

    // 创建全局 global 类的定义
    JSClassDefinition global_class_definition = kJSClassDefinitionEmpty;
    // 创建 global 对象的类
    JSClassRef global_class = JSClassCreate(&global_class_definition);
    // 根据 global 类创建上下文，从上下文获取 global 对象
    context = JSGlobalContextCreateInGroup(context_group, global_class);
    global = JSContextGetGlobalObject(context);

    // 创建 example 类的定义
    JSClassDefinition example_class_definition = kJSClassDefinitionEmpty;
    // 设置类的对应函数名和参数名的钩子
    example_class_definition.staticFunctions = s_examplle_function_;
    example_class_definition.staticValues = s_example_values_;
    // 设置类的名称
    example_class_definition.className = "Example";
    // 创建 JS 引擎的类
    JSClassRef example_class_ref = JSClassCreate(&example_class_definition);
    JSObjectRef example = JSObjectMake(context, example_class_ref, NULL);
    // 关联 c++ 对象和 JS 引擎对象
    JSObjectSetPrivate(example, this);
    JSClassRelease(example_class_ref);
    // 动态注册函数钩子
    JSStringRef dynamic_test_func_name = JSStringCreateWithUTF8CString("testDynamic");
    JSObjectRef dynamic_test_func = JSObjectMakeFunctionWithCallback(context,
                                                                     dynamic_test_func_name,
                                                                     TestDynamicCallback);
    JSObjectSetProperty(context, example, dynamic_test_func_name, dynamic_test_func,
                        kJSPropertyAttributeDontDelete, NULL);
    JSStringRelease(dynamic_test_func_name);
    // 向 global 对象中设置 example 属性
    JSStringRef example_str_ref = JSStringCreateWithUTF8CString("example");
    JSObjectSetProperty(context, global, example_str_ref, example, kJSPropertyAttributeDontDelete,
                        NULL);
    JSStringRelease(example_str_ref);
}


Example::Example() {
    LOGD("Example");
    Initialize();
}

Example::~Example() {
    LOGD("~Example");
}

void Example::TestStatic() {
    LOGD("call TestStatic");
}

void Example::TestDynamic() {
    LOGD("call TestDynamic!");
}

int Example::num() {
    LOGD("call num: %d", numValue);
    return numValue;
}

void Example::set_num(int num) {
    numValue = num;
    LOGD("call set_num: %d", num);
}

JSValueRef Example::runScript(const char *buffer) {
    JSStringRef script = ::JSStringCreateWithUTF8CString(buffer);
    JSValueRef exception = nullptr;
    JSValueRef ret = JSEvaluateScript(context, script, global, 0, 0, &exception);
    JSStringRelease(script);
    if (nullptr != exception) {
        JSStringRef errorStr = ::JSValueToStringCopy(
                context, exception, nullptr);
        // 输出错误内容
        if (nullptr != errorStr) {
            std::string lineError = "";
            lineError.resize(::JSStringGetMaximumUTF8CStringSize(errorStr));
            lineError.resize(::JSStringGetUTF8CString(
                    errorStr, &lineError[0], lineError.length()));
            ::JSStringRelease(errorStr);
            LOGE("runScript error: %s", lineError.c_str());
        }
    }
    return ret;
}
