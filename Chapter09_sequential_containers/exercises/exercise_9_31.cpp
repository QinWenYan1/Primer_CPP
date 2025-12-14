#include <list>
#include <forward_list>
#include <iostream>

using namespace std; 

/*
* Exercise 9.31: 
* The program on page 354 to remove even-valued elements
* and duplicate odd ones will not work on a list or forward_list. Why?
* Revise the program so that it works on these types as well.


vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
auto iter = vi.begin(); 
while (iter != vi.end()) {
    if (*iter % 2) {
        iter = vi.insert(iter, *iter); 
        iter += 2; 
    } else iter = vi.erase(iter); 
}

Answer: 

在list和forward_list都不可以运行的原因是

- list和forward_list不支持随机访问， 不能使用+=运算符号
- forward_list不能使用insert和erase而是由自己的版本insert_after, erase_after版本实现
- 并且forward_list还需要维护前驱来实现
*
*/



int main(){
    list<int> li = {0,1,2,3,4,5,6,7,8,9};
    forward_list<int> fli = {0,1,2,3,4,5,6,7,8,9};

    auto iter = li.begin(); 
    while(iter != li.end()) {
        if (*iter % 2) {
            iter = li.insert(iter, *iter); 
            ++ iter; 
            ++ iter; 
        } else iter = li.erase(iter); 
    }

    /*----------------------------------*/
    auto prev = fli.before_begin();
    auto curr = fli.begin(); 

    while(curr != fli.end()) {
        if (*curr % 2) {
            prev = fli.insert_after(prev, *curr);  
            ++ prev;  
            ++curr;  
        } else {
            curr = fli.erase_after(prev); 
        }; 
    }

    for (const auto e:li) cout << e << " "; 
    cout << endl; 
    for (const auto e:fli) cout << e << " "; 
    cout << endl; 

}
