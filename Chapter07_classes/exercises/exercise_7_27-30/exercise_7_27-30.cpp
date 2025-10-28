#include "Screen.h"
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl; 

/*
* Exercise 7.27: 
* Add the move, set, and display operations to your
* version of Screen. Test your class by executing the following code: 
* 
* Screen myScreen(5, 5, 'X');
* myScreen.move(4,0).set('#').display(cout);
* cout << "\n";
* myScreen.display(cout);
* cout << "\n";
*/

/*
* Exercise 7.28: 
* What would happen in the previous exercise if the return
* type of move, set, and display was Screen rather than Screen&?
*
* Answer: 如过这样的话，那么Screen类只会支持单一行为，函数的调用
* 而不是链式调用， 否则后续连续的链式调用不会有任何作用， 或者说，相当于没有调用
*/

/*
* Exercise 7.29: 
* Revise your Screen class so that move, set, and display
* functions return Screen and check your prediction from the previous
* exercise.
* 
* Answer: 可以发现第一个display可以支持并看到到：
* myScreen.move(4,0).set('#').display(cout);
* 这整个操作
* 但是第二次display后发现并没有执行.set('#')这个操作
* 根据这个现象我们可知， 对象本体只能收到第一个函数调用的影响， 后续的链式函数调用
* 不会影响到本体， 而是影响到其副本， 第一个display就是display的副本
*/

/*
* Exercise 7.30: 
* It is legal but redundant to refer to members through the
* this pointer. Discuss the pros and cons of explicitly using the this pointer
* to access members.
* 
* Answer:
* Pros: 
* 1. 直接，快捷地使用或者访问到本对象地内部数据，支持到接口的操作
* 2. 这种隐式传参可以减少函数传参数的问题检查， 比如类型匹配等
* 3. 可以通过this这个参数来实现overload, 支持到对非const和const对象的不同操作
*
* cons 
* 1. this对于使用者有一些抽象
* 2. 如果使用不当， 可能会无意将对象数据改动
*/

int main(){

    Screen myScreen(5, 5, 'X');
    myScreen.move(4,0).set('#').display(cout);
    cout << "\n" << "------------" << "\n";
    myScreen.display(cout);
    cout << "\n";

}
