/*
* Exercise 12.23: 
* Write a program to concatenate two string literals, putting
* the result in a dynamically allocated array of char. Write a program to
* concatenate two library strings. 
*/
#include <iostream>
#include <string>
#include <memory>
#include <cstring>  // for strlen and strcpy

using namespace std;

int main() {
    // ========== Part 1: C风格字符串（使用动态数组）==========
    const char str1[] = "Hello";
    const char str2[] = ", world";
    
    // 使用strlen计算实际所需空间（+1 给 null终止符）
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t total_len = len1 + len2 + 1;
    
    // C++14 及以上建议用 make_unique，但数组不支持初始化列表，所以这里仍用 new
    unique_ptr<char[]> conStrPtr(new char[total_len]);
    
    // 使用C标准库函数复制（更简洁且不易出错）
    strcpy(conStrPtr.get(), str1);      // 先复制第一个
    strcat(conStrPtr.get(), str2);      // 追加第二个
    
    cout << "C-style result: " << conStrPtr.get() << endl;
    
    // ========== Part 2: 库字符串（std::string）==========
    // 这是现代C++推荐的方式，无需手动管理内存
    string s1 = "Hello";
    string s2 = ", world";
    string result = s1 + s2;  // 直接拼接
    
    cout << "std::string result: " << result << endl;
    
    return 0;
    
}