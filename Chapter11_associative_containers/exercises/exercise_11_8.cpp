#include <iostream>
#include <set>
#include <vector>
#include <numeric>
#include <map>

using namespace std; 

/*
* Exercise 11.8: 
* Write a program that stores the excluded words in a vector
* instead of in a set. What are the advantages to using a set?
*/

/*
* Answer: 
* 使用set的优势狠简单，就是set拒绝了重复元素的出现
* 每次查找在set里面都是有意义的， 节约了空间并且
*/



int main(){

    // count the number of times each word occurs in the input
    map<string, size_t> word_count; // empty map from string to size_t
    vector<string> exclude = {"The", "But", "And", "Or", "An", "A",
    "the", "but", "and", "or", "an",
    "a"};
    string word;

    auto search = [](const vector<string> &v, const string &word) -> bool { for(auto e:v) if(e == word )return true; return false; }; 

    while (cin >> word)
        // count only words that are not in exclude
        if (!search(exclude, word))
            ++word_count[word]; // fetch and increment the counter for word
    
    for (const auto &e : word_count) cout << e.first << " occurs " << e.second << " times " << endl; 
}