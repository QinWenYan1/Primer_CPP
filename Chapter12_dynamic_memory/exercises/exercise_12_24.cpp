/*
* Exercise 12.24: 
* Write a program that reads a string from the standard input
* into a dynamically allocated character array. Describe how your program
* handles varying size inputs. Test your program by giving it a string of data
* that is longer than the array size you’ve allocated.
*/
#include <iostream>
#include <string>
#include <memory>
#include <cstring>    // for strncpy
#include <algorithm>  // for copy_n

using namespace std;

int main() {
    // 策略1：动态适应大小（你的当前方法，修正版）
    cout << "=== Strategy 1: Dynamic size ===" << endl;
    string temp;
    if (!(cin >> temp)) return 0;  // 检查输入是否成功
    
    // +1 留给 null 终止符
    unique_ptr<char[]> strPtr(new char[temp.size() + 1]);
    
    // 方法A：使用标准库算法（推荐）
    copy(temp.begin(), temp.end(), strPtr.get());
    strPtr[temp.size()] = '\0';  // 手动添加终止符！
    
    // 方法B：或者直接用 c_str() 复制（更简单）
    // strcpy(strPtr.get(), temp.c_str());
    
    cout << "Dynamic result: " << strPtr.get() << endl;
    
    // ========================================
    // 策略2：固定大小，测试超长输入（题目要求的测试）
    cout << "\n=== Strategy 2: Fixed size (testing overflow) ===" << endl;
    constexpr size_t FIXED_SIZE = 8;  // 固定小数组
    
    unique_ptr<char[]> fixedPtr(new char[FIXED_SIZE]);
    string longInput;
    cin >> longInput;
    
    // 安全复制：最多复制 FIXED_SIZE-1 个字符，确保留一个位置给 \0
    size_t copyLen = min(longInput.size(), FIXED_SIZE - 1);
    copy_n(longInput.begin(), copyLen, fixedPtr.get());
    fixedPtr[copyLen] = '\0';  // 确保终止
    
    cout << "Fixed buffer result (truncated): " << fixedPtr.get() << endl;
    if (longInput.size() >= FIXED_SIZE) {
        cout << "Warning: Input was truncated from " << longInput.size() 
             << " to " << FIXED_SIZE - 1 << " chars" << endl;
    }
    
    return 0;
}