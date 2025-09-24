#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string; 
using std::vector; 

/*
* Exercise 6.17: 
* Write a function to determine whether a string contains
* any capital letters. Write a function to change a string to all lowercase. Do
* the parameters you used in these functions have the same type? If so, why?
* If not, why not?
* Answer: 两个函数使用的形参用的类型并不同，一个是const string&, 一个是string&, 
* 因为一个是检查而不会去改动字符串， 为了安全使用const 
* 另一个会改动字符串， 无法使用const 
*/

/*
* Exercise 6.18: Write declarations for each of the following functions. When
* you write these declarations, use the name of the function to indicate what
* the function does.
* (a) A function named compare that returns a bool and has two parameters
* that are references to a class named matrix.
* (b) A function named change_val that returns a vector<int> iterator
* and takes two parameters: One is an int and the other is an iterator for a
* vector<int>
*/

struct matrix {}; 
bool compare(const matrix &, const matrix &);
vector<int>::iterator change_val(const int, vector<int>::iterator);

//检查输入字符串是否有大写字母， 有则返回true, 没有则返回false
//返回类：bool
//输入类: const string& 
bool contain_capital(const string & str){

    bool is_capital = false;

    for (auto & e : str){

        if ( isupper(e) ){

            is_capital = true; 

        }

    }

    return is_capital; 
    
}

//将目标字符串里的大写字母全部转换为小写， 如果转换发生那么返回true, 反之返回false
//返回类：bool
//输入类: const string& 
bool convert_lower(string & str ){

    bool is_converted = false;

    for (auto & e : str){

        if ( isupper(e) ){

            is_converted = true; 
            e = tolower(e); 

        }

    }

    return is_converted; 

}

int main(){

    //创造一个string测试
    string test = "Hello, this is Qinwen Speaking"; 
    cout << "Testing starting ... \n"
         << "Original string is: " << test 
         << endl; 

    cout << "does it contains captials? " << contain_capital(test) << endl;

    if( contain_capital(test)) convert_lower(test);

    cout << "Now, the string is: " << test << endl; 



}