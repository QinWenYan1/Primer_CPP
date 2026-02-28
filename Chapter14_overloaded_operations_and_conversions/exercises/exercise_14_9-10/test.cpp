#include "Sales_data.h"
#include <string> 

/*
* 并不会报错
* 按目标类型的语法规则解析输入，读到非法字符即停，而非读到空格为止。
*/

int main(){
    Sales_data item1, item2; 
    std::cin >> item1 >> item2; 
    std::cout << item1 << std::endl; 
    std::cout << item2 << std::endl; 
}