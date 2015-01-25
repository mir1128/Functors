#include "function.h"
#include <iostream>

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

int main()
{
    TestFunctor f;
    Functor<void, TYPELIST_2(int, double) > cmd(f);
    cmd(4, 4.5);

    typedef void(*TF)(int, int);
    TF pf = functionPointer;

    Functor<void, TYPELIST_2(int, int) > cmd2(pf);
    cmd2(1, 2);
    return 0;
}


