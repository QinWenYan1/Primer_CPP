/*
* Exercise 14.38: 
* Write a class that tests whether the length of a given
* string matches a given bound. Use that object to write a program to report
* how many words in an input file are of sizes 1 through 10 inclusive.
* 
* Exercise 14.39: 
* Revise the previous program to report the count of words
* that are sizes 1 through 9 and 10 or more.
* 
*/

/*
* Exercise 14.40: 
* Rewrite the biggies function from § 10.3.2 (p. 391) to
* use function-object classes in place of lambdas.
*
* Answer: 略
*/

#include <iostream>
#include <string>
#include <fstream>

class TestStrLength{

    size_t desLength; 

public:
    //构造函数: 默认 + 自定义
    TestStrLength(const unsigned &size = 0): desLength(size) {}

    //函数调用操作符: 检查单词是否为小于设定长度的
    bool operator()(const std::string &word){ return word.size() <= desLength; }

};

using namespace std; 

int main(){

    ifstream ifs("text.txt");
    istream_iterator<string> ifsItertor(ifs), end; //头尾迭代器都有了
    unsigned counter = 0; //记录满足条件单词的数量
    unsigned desSize = 0; 
    unsigned totalSize = 0;
    cout << "please input the size you wanna test ..." << endl; 
    cin >> desSize; 
    TestStrLength tester(desSize); 

    while (ifsItertor != end){
        ++totalSize; 
        counter += (tester(*ifsItertor++))? 1 : 0; 
    }

    cout << "After examination ... " << endl; 
    cout << "The count of word that less or equal to length " 
    << desSize << " is " 
    << counter 
    << "/" << totalSize << endl; 
    
}
