#include <iostream>

/* Exercise 1.6: 
*  Explain whether the following program fragment is legal. 
*/

/* answer: this program is illegal 
* 段代码是非法的。因为只有第一行以 std::cout 开头，后续两行直接以 << 开头，
* 缺少左操作数，违反了语法规则。
* 正确写法应将整条输出语句写成一行或连续使用不加分号的链式写法。
*/

int main(void){

    int v1 = 12; 
    int v2 = 13;

    std::cout << "The sum of " << v1
            << " and " << v2
            << " is " << v1 + v2 << std::endl; 
}