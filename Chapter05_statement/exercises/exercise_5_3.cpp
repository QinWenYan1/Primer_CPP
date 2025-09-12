#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

/*
* Exercise 5.3: 
* Use the comma operator (§ 4.10, p. 157) to rewrite the
* while loop from § 1.4.1 (p. 11) so that it no longer requires a block. Explain
* whether this rewrite improves or diminishes the readability of this code.
* Answer: 
* 这种改写实际上降低了代码的可读性，原因如下：
* 1. 逗号运算符不如花括号直观，容易让人忽略这是循环体的一部分
* 2. 违背了常见的编码惯例，大多数程序员期望看到循环体用花括号明确界定
* 3. 增加了出错的风险，如果以后需要添加更多语句，很容易忘记添加花括号
* 4. 代码的意图不如使用块时明确，降低了可维护性
*/

int main(void){

    int sum = 0 ,val = 1; 

    while(val <= 10 )
        sum += val, ++val; 
    
    cout << "The sum is : " << sum << endl; 

}