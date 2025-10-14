#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl; 

/*
* Exercise 6.42: 
* Give the second parameter of make_plural (§ 6.3.2, p.
* 224) a default argument of 's'. Test your program by printing singular and
* plural versions of the words success and failure.
*/


// 更合理的方案：给第三个参数ending提供默认值"s"
string make_plural(size_t ctr, const string &word, const string &ending = "s") {
    return (ctr > 1) ? word + ending : word;
}

// 测试程序
int main() {
    // 测试单数形式
    cout << "Singular:" << endl;
    cout << make_plural(1, "success") << endl;  // 输出: success
    cout << make_plural(1, "failure") << endl;  // 输出: failure
    
    // 测试复数形式  
    cout << "\nPlural:" << endl;
    cout << make_plural(2, "success") << endl;  // 输出: successes
    cout << make_plural(2, "failure") << endl;  // 输出: failures
    
    // 测试特殊情况：使用自定义复数形式
    cout << "\nCustom plural:" << endl;
    cout << make_plural(2, "child", "ren") << endl;  // 输出: children
    cout << make_plural(2, "ox", "en") << endl;      // 输出: oxen
    
    return 0;
}