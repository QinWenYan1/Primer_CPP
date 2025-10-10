#include <iostream>
#include <string>
#include <cstdlib>

using std::string; 
using std::cout;
using std::cin;
using std::endl;

/* 
* Exercise 6.30: Compile the version of str_subrange as presented on
* page 223 to see what your compiler does with the indicated errors.
*/

/*
* Answer: 
*  exercise_6_30.cpp:25:13: error: non-void function 'str_subrange' should return a value [-Wreturn-type]
*   25 |             return; // error #1: no return value; compiler should detect this error
*      |             ^
* 1 error generated.
*
* exercise_6_30.cpp:38:1: warning: non-void function does not return a value in all control paths [-Wreturn-type]
*    38 | }
*       | ^
* 1 warning generated.
*/

bool str_subrange(const string &str1, const string &str2)
{
    // same sizes: return normal equality test
    if (str1.size() == str2.size())
        return str1 == str2; // ok: == returns bool
    // find the size of the smaller string; conditional operator, see § 4.7 (p. 151)
    auto size = (str1.size() < str2.size())? str1.size() : str2.size();
    // look at each element up to the size of the smaller string
    for (decltype(size) i = 0; i != size; ++i) {
        if (str1[i] != str2[i])
            return false; // error #1: no return value; compiler should detect this error
    }
    // error #2: control might flow off the end of the function without a return 
    //the compiler might not detect this error

}

int main(void){

    string str1 = "hello", str2 = "hi"; 
    cout << str_subrange(str1, str2) << endl; 

}