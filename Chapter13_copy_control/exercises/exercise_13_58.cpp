/*
* Exercise 13.58: 
* Write versions of class Foo with print statements in their
* sorted functions to test your answers to the previous two exercises.
*/
#include <iostream>

using namespace std; 

struct Foo{
    int value; 
    Foo(int arg = 0): value(arg) {}; //默认构造函数也有了
    Foo(Foo &&rhs): value(rhs.value) {}
    Foo(Foo &rhs): value(rhs.value) {} 
    Foo &operator=(Foo &&rhs) & { 
        value = rhs.value; 
        return *this; 
    }
    Foo &operator=(Foo &rhs){
        value = rhs.value; 
        return *this; 
    }

    Foo &minus(int &&num) && {
        cout << "executing rvalue reference version" << endl;
        value -= num; 
        return *this; 
    }
    Foo &minus(int &&num) & {
        cout << "executing lvalue reference version" << endl;
        value -= num; 
        return *this; 
    }
}; 


int main(){
    Foo f1(114); 
    Foo f2(510); 
    Foo f3; 
    cout << f1.value << f2.value << f3.value << endl;
    f3 = Foo(191).minus(100); 
    f2.minus(100);
    f1 = std::move(f2); 
    cout << f1.value << f2.value << f3.value << endl;

}