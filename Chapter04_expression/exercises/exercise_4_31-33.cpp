#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl; 
using std::vector; 

/*
* Exercise 4.31: 
* The program in this section used the prefix increment and
* decrement operators. Explain why we used prefix and not postfix. What
* changes would have to be made to use the postfix versions? Rewrite the
* program using postfix operators.
* vector<int>::size_type cnt = ivec.size();
* // assign values from size... 1 to the elements in ivec
* for(vector<int>::size_type ix = 0;
* ix != ivec.size(); ++ix, --cnt)
* ivec[ix] = cnt;
* answer: 在这个版本的for-loop中， 我们用不到ix和cnt的副本， 因此考虑到程序效率， 
* 我们选择 prefix ++ 这样就不会产生副本, 但我们注意到cnt可以修改为postfix ++ 来使用
* 其副本赋值
*/

/*
* Exercise 4.32: 
* Explain the following loop.
* constexpr int size = 5;
* int ia[size] = {1,2,3,4,5};
* for (int *ptr = ia, ix = 0;
*   ix != size && ptr != ia+size;
*   ++ix, ++ptr) {  }
*/

/*
* Exercise 4.33: 
* Using Table 4.12 (p. 166) explain what the following
* expression does:
* someValue ? ++x, ++y : --x, --y
*/

int main(void){

    // exercise 31
    vector<int> ivec(10); 
    vector<int>::size_type cnt = ivec.size();

    // assign values from size... 1 to the elements in ivec
    for(vector<int>::size_type ix = 0; ix != ivec.size();   ivec[ix] = cnt--, ++ix);
    
    //let's print the vector out 
    cout << "Print it out ..." << endl;
    for (const int e:ivec){

        cout << e << endl; 

    }

    //exercise 32
    cout << "Print out the outcome ... " << endl; 
    constexpr int size = 5;
    int ia[size] = {1,2,3,4,5};
    for (int *ptr = ia, ix = 0; ix != size && ptr != ia+size; ++ix, ++ptr) { 

        cout << "element: " << *ptr << endl;
        cout << "ix: " << ix << endl; 

    }
/* 
* 解释：这个循环使用两种不同的方式遍历数组：

* 使用索引 ix 从 0 到 size-1

* 使用指针 ptr 从数组开头 ia 到结尾 ia+size

* 条件部分使用了两种检查方式，但实际上它们是等价的。这是一种教学示例，展示了数组遍历的两种方法。
*/ 

    //exercise 33
    int x = 114, y= 514, someValue = 1; 
    someValue ? ++x, ++y : --x, --y; 
    // 解释：根据C++运算符优先级，这个表达式被解析为：
    // (someValue ? (++x, ++y) : --x), --y; 
    // 因为comma优先级别非常低， 并且都是从左向右结合
    cout << "Testing outcome ..." << endl; 
    cout << "x: " << x << " y: " << y << endl; 

}
