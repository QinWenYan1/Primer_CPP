/*
* Exercise 12.26: 
* Rewrite the program on page 481 using an allocator.
*/
#include <iostream>
#include <string>
#include <memory> //allocator

using namespace std;

int main() {
    
    allocator<string> allStr;
    string *strPtr = allStr.allocate(1); 

    string temp;
    if (!(cin >> temp)) return 0;  // 检查输入是否成功

    allStr.construct(strPtr, temp); //构造

    cout << *strPtr << endl; //打印

    allStr.destroy(strPtr);  //销毁
    allStr.deallocate(strPtr, 1);  //释放

    
}