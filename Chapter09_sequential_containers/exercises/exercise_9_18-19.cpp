#include <deque>
#include <iostream>
#include <string>
#include <list>

using namespace std;

/*
* Exercise 9.18: 
* Write a program to read a sequence of strings from the
* standard input into a deque. Use iterators to write a loop to print the
* elements in the deque.
*/

/*
* Exercise 9.19: 
* Rewrite the program from the previous exercise to use a
* list. List the changes you needed to make.
*/

int main(){

    deque<string> seq_s; 
    list<string> list_s; 
    string word;

    while(cin >> word) seq_s.push_front(word);

    cout << "Printing stage(deque)..." << endl; 
 
    auto head = seq_s.rend(); 
    for(auto tail =  seq_s.rbegin(); head != tail; ++tail){

        list_s.push_back(*tail); 
        cout << *tail << " ";

    }

    cout << endl;

    cout << "Printing stage(list)..." << endl; 
    auto tail_l = list_s.cend(); 
    for(auto head =  list_s.begin(); head != tail_l; ++head){

        list_s.push_front(*head); 
        cout << *head << " ";

    }




}