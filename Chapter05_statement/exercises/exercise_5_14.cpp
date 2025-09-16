#include <iostream>
#include <vector>
#include <string>

using std::cout; 
using std::cin;
using std::endl; 
using std::vector; 
using std::string;  

/*
* Exercise 5.14: 
* Write a program to read strings from standard input
* looking for duplicated words. The program should find places in the input
* where one word is followed immediately by itself. Keep track of the largest
* number of times a single repetition occurs and which word is repeated. Print
* the maximum number of duplicates, or else print a message saying that no
* word was repeated. For example, if the input is
* how now now now brown cow cow
* the output should indicate that the word now occurred three times.
*/

int main(void){

    vector<string> words;
    vector<int> freq; 
    string word;

    //载入到words方便处理
    //每次载入的时候检查是否有重复如果有重复我们会在freq加上一次重复次数来记录
    while( cin >> word ) {
        //遍历查找是否在words里面已经出现过了该单词
        decltype(words.size()) i = 0; 

        while( (!words.empty()) && (i != words.size()) && (words[i] != word) ) ++i;

        if( i == words.size() ){
            //如果遍历到尾后位置的话就是新的元素，添加
            words.push_back(word);
            freq.push_back(1);

        }else{
            //不是尾后位置， 说明已经是老元素， 那么freq相应位置加一代表frequency加一
            ++ freq[i];

        }

    } 

    //打印出来重复的结果， 没有重复的则输出警告提示
    cout << "Print out outcome ... " << endl; 
    bool is_repeated = false; 
    for ( decltype(words.size()) index = 0; index != words.size(); ++index){

        if( freq[index] != 1 ){
            //出现了重复元素我们不用打印警告
            is_repeated = true; 
            cout << words[index] << " has been repeated " <<
            freq[index] << " times ..." << endl; 

        } 
        
    }

    if( !is_repeated ){
        //没有任何元素重复过
        cout << "There is no any word repeated ..." << endl; 
        
    }

}