//
// Created by pengwei on 2018/6/28.
//

#ifndef JAVASCRIPTCORESTUDY_EXAMPLE_H
#define JAVASCRIPTCORESTUDY_EXAMPLE_H


class Example {
public:
    Example();

    virtual ~Example();

    void TestStatic();

    void TestDynamic();

    int num();

    void set_num(int num);

    JSValueRef runScript(const char * buffer);

    int numValue;
    JSContextRef context;
    JSObjectRef global;

private:
    void Initialize();
};


#endif //JAVASCRIPTCORESTUDY_EXAMPLE_H
