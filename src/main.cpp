#include "function.h"
#include <iostream>
#include <string>

using namespace std;

struct TestFunctor
{
    void operator()(int i, double d)
    {
        cout << "TestFunctor::operator()(" << i << ", " << d << ") called.\n" << endl;
    }
};

void functionPointer(int i, int d)
{
    cout << "functionPointer (" << i << "," << d << ") called." << endl;
}

const char *TestFunction(double, double)
{
    static const char buffer[] = "Hello, world!";
    return buffer;
}

int main()
{
    TestFunctor f;
    Functor<void, TYPELIST_2(int, double) > cmd(f);
    cmd(4, 4.5);

    typedef void(*TF)(int, int);
    TF pf = functionPointer;

    Functor<void, TYPELIST_2(int, int) > cmd2(pf);
    cmd2(1, 2);

    typedef const char*(*M)(double, double);
    M m = TestFunction;

    Functor<const char*, TYPELIST_2(double, double) > cmd3(m);
    cmd3(1.0, 2.0);
    return 0;
}


