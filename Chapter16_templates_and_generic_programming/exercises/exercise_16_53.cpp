/*
* Exercise 16.53: 
* Write your own version of the print functions and test
* them by printing one, two, and five arguments, each of which should have
* different types.
*/

#include <string>
#include <iostream>

using namespace std;
template<typename T>
void print(const T& obj){
    cout << " " << obj << endl; 
}

template <typename T, typename... Args>
void print(const T& obj, const Args  ...rest){
    cout << " " << obj << " " << sizeof...(rest)<<endl; 
    print(rest...); 
}

int main(){

    print(1145, "Hello", 'Y', 50.05); 

}


