#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector; 

int main(void){

    //默认初始化，这个我用的最多，因为更灵活， 在大部分时间不知道元素具体值
    vector<int> v; 
    //列表初始化
    vector<int> v1 = {1 ,2 ,3};
    vector<int> v5{1,2,3};
    //直接初始化
    vector<int> v2(10, 12);
    //拷贝初始化
    vector<int> v3 = v1; 
    vector<int> v4(v3); 

}