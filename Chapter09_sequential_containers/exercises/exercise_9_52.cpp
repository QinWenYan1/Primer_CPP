#include <stack>
#include <vector>
#include <string>
#include <iostream>

using namespace std; 

/*
* Exercise 9.52: 
* Use a stack to process parenthesized expressions. When
* you see an open parenthesis, note that it was seen. 
* When you see a close
* parenthesis after an open parenthesis, pop elements down to and including
* the open parenthesis off the stack. push a value onto the stack to
* indicate that a parenthesized expression was replaced.
*/

int main(){

    string expr = "{[(This is my world)]}"; 
    string expr2 = "{[(This is my world)}"; 
    stack<string, vector<string>> compiler;
    compiler.push("empty"); 
    
    for (const auto e : expr){

        if (e == '[') compiler.emplace("o"); 
        else if (e == '{') compiler.emplace("c"); 
        else if (e == '(') compiler.emplace("cc"); 
        else if (e == ']' && compiler.top() == "o") compiler.pop(); 
        else if (e == ')' && compiler.top() == "cc") compiler.pop(); 
        else if (e == '}' && compiler.top() == "c") compiler.pop(); 

    }

    if (compiler.top() == "empty") cout << "The expression has been handled" << endl; 
    else cout << "The expression has not been handled" << endl; 

    for (const auto e : expr2){

        if (e == '[') compiler.emplace("o"); 
        else if (e == '{') compiler.emplace("c"); 
        else if (e == '(') compiler.emplace("cc"); 
        else if (e == ']' && compiler.top() == "o") compiler.pop(); 
        else if (e == ')' && compiler.top() == "cc") compiler.pop(); 
        else if (e == '}' && compiler.top() == "c") compiler.pop(); 

    }

    if (compiler.top() == "empty") cout << "The expression has been handled" << endl; 
    else cout << "The expression has not been handled" << endl; 



}

