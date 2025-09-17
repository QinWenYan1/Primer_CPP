#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;  
using std::vector; 


/*
* Exercise 5.16: 
* The while loop is particularly good at executing while some
* condition holds; for example, when we need to read values until end-of-file.
* The for loop is generally thought of as a step loop: An index steps through
* a range of values in a collection. Write an idiomatic use of each loop and
* then rewrite each using the other loop construct. If you could use only one
* loop, which would you choose? Why?
*/

/*
* Exercise 5.17: Given two vectors of ints, write a program to determine
* whether one vector is a prefix of the other. For vectors of unequal
* length, compare the number of elements of the smaller vector. For
* example, given the vectors containing 0, 1, 1, and 2 and 0, 1, 1, 2, 3, 5,
* 8, respectively your program should return true.
*/

bool is_prefix(vector<int> list1, vector<int> list2){

    using prefix_size = decltype(list1.size()); 

    //size更小的我们标为prefix, 和更长的为list， 方便比较
    prefix_size p_size = (list1.size() > list2.size())? list2.size(): list1.size();  

    //那么现在开始比较使用for循环
    //使用is_same来标定是否匹配
    bool is_same = true; 
    for( prefix_size ix = 0; ix != p_size; ++ ix){

        if( list1[ix] != list2[ix] ) is_same = false; 

    }

    return is_same; 

}

int main(void){

    // exercise 16
    //while loop, 适用于read value until end-of-file
    //我们用for去重写
    
    string word;
    while ( cin >> word ); 
    cout << "The last word is: " << word << endl; 

    for (; cin >> word ; ); 
    cout << "The last word is: " << word << endl; 

    //for循环适用于对序列的遍历
    //我们用while来重写

    vector<int> list(10,1); 

    for (auto init = list.begin(); init != list.end(); ++init) cout << *init << endl; 

    auto beginner = list.begin();
    while ( beginner != list.end() ){ 
 
        cout << *beginner << endl;
        ++ beginner; 

    }

    //如果只能用使用一种loop， 我愿意使用while
    // while的表达更为自由

    //exercise 17 
    vector<int> example = {114, 514, 110};
    vector<int> longer_example = {114, 514, 1919, 819};
    cout << "Print out the outcome ..." << endl; 
    cout << is_prefix(longer_example, example) << endl; 

}