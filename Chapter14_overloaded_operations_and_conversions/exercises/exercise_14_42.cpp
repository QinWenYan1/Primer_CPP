/*
* Exercise 14.44: 
* Write your own version of a simple desk calculator that can
* handle binary operations.
*/

#include <functional>
#include <iostream>
#include <string>
#include <map>

using namespace std; 
int main(){

    //制备计算器，我们使用map
    unordered_map<string, function<int(int, int)>> calculator; //使用unordered_map，在频繁访问的使用下更快
    calculator.insert({"+", [](int i, int j){ return i+j; }}); //加法
    calculator.insert({"*", [](int i, int j){ return i*j; }}); //乘法
    calculator.insert({"%", [](int i, int j){ return i%j; }}); //余法
    calculator.insert({"-", [](int i, int j){ return i-j; }}); //减法
    calculator.insert({"/", [](int i, int j){ return i/j; }}); //除法

    cout << "calculator beginning ..." << endl; 
    while(1){
        cout << "please input(operand1 + binary operator + operand2) ..." << endl;
        cout << "enter q for exiting ..." << endl; 
        int lhs, rhs; 
        string oper, order;
        if (!(cin >> lhs)) break; 
        cin >> oper >> rhs;

        cout << "The outcome is: " << calculator[oper](lhs, rhs) << endl;
    }
    cout << "exiting ..." << endl; 

}