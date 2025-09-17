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
    string pre_word;  

    //载入到words方便处理
    //每次载入的时候检查是否有重复如果有重复我们会在freq加上一次重复次数来记录
    cin >> pre_word;
    words.push_back(pre_word); 
    freq.push_back(1);
    //index用于追踪words和freq
    decltype(words.size()) i = 0;
    while( cin >> word ) {

        if( pre_word == word ){

            //说明已经是老元素 
            //如果上一个元素相同，那么freq相应位置加一代表frequency加一
            ++ freq[i];

        }else{

            //添加元素和这个元素的freq
            //并且让这个下标下移一位， 这样我们可以最终下一个单词
            words.push_back(word); 
            freq.push_back(1);
            ++ i; 

        }

        //记录这个为上一个单词，好为后面对比
        pre_word = word;

    } 

    //打印出来重复的结果， 没有重复的则输出警告提示
    cout << "Print out outcome ... " << endl; 
    bool is_repeated = false; 
    unsigned max_count = 1;
    string max_count_word; 

    for ( decltype(words.size()) index = 0; index != words.size(); ++index){

        if( freq[index] != 1 ){

            //出现了重复元素我们不用打印警告
            //然后找出这个元素重复的最大次数
            is_repeated = true; 

            decltype(words.size()) pivot = index+1; 
            max_count = freq[index];
            max_count_word = words[index];

            while (pivot != words.size()){

                //找到更大的了
                if( (max_count_word == words[pivot]) && (max_count < freq[pivot]) ) max_count = freq[pivot];
                ++pivot; 

            }

            cout << max_count_word << " has been repeated " <<
            max_count << " times ..." << endl; 

        } 
        
    }

    //没有任何元素重复过
    if( !is_repeated ) cout << "There is no any word repeated ..." << endl; 

}