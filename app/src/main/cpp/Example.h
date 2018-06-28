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

    int numValue;

private:
    void Initialize();

    void runScript(JSContextRef context_group);
};


#endif //JAVASCRIPTCORESTUDY_EXAMPLE_H
