#include <iostream>
#include <memory>
#include <vector>
#include "X.h"

using namespace std; 

/*
* Exercise 13.13:
* Add the copy-assignment operator and destructor to X and write a program using
* X objects in various ways: 
* Pass them as nonreference and reference parameters;
* dynamically allocate them; 
* put them in containers; and so forth. 
* Study the output until you are certain you understand when and why each copy-control member is
* used. As you read the output, remember that the compiler can omit calls to the
* copy constructor.
*/

int main(){

    //直接初始化
    X x1(114514); 
    X x3(1919);
    //值初始化，其中的成员不可用
    X x4; 

    cout << x1.getValue() << " "
    << x3.getValue() << " " 
    << endl;

    //赋值操作
    x3 = x1; 
    //赋值初始化
    X x2(x1); 

    cout << x1.getValue() << " "
    << x2.getValue() << " "
    << x3.getValue() << " " 
    << endl;

    //动态分配内存
    X *xp = new X(272); 
    shared_ptr<X> sxp = make_shared<X>(114);
    x4 = *xp; 
    cout << x4.getValue() << endl; 
    x4 = *sxp; 
    cout << x4.getValue() << endl; 
    
    
    cout << xp->getValue() << " "
    << sxp->getValue() << " "
    << endl; 

    delete xp; 
    xp = nullptr; 

    //使用容器的
    vector<X> vec(10, X(2002)); 
    for (const auto &e : vec) cout << e.getValue() << endl; 

}