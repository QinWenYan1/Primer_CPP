#include <iostream>

using std::cout;
using std::cin; 
using std::endl; 
using std::string; 


/*
* Exercise 6.3: 
* Write and test your own version of fact.
*
* Exercise 6.4: 
* Write a function that interacts with the user, asking for a
* number and generating the factorial of that number. Call this function from
* main.
*
* Exercise 6.5: 
* Write a function to return the absolute value of its argument.
*/ 


//This function is used to calculate the factorial of certain number 
//return type: int 
//parameter type: int
int fact(int num){

    if (num < 0) {
        // 处理负数输入，例如返回错误码或抛出异常
        return -1; // 简单返回 -1 表示错误
    }
    
    int fact = 1;
    while(num > 1 ){

        fact *= num; 
        -- num; 

    }
    return fact; 
}

//This function is mainy used to interact with user and call fact function 
// to calculate factorial of number for user
// return type: int
// parameter type void
int interact(void){

    int input_num;

    cout << "Please input an integer to get factorial of this number ..." << endl;
    cin >> input_num;
    return fact(input_num);

}

// this function is used to get absolute value of input number 
// return type: int
// parameter type: int
int abs(int value){

    if (value < 0 ) return -value; 
    return value; 

}

int main(void){

    cout << "We call the interact function to interact with user ..." << endl; 
    cout << "After calling the function, we can get outcome: \n"
         << interact() << endl; 
    
    int value;
    cout << "Now we call the abs funciton to calculate absolute value ... \n" << endl; 
    cin >> value; 
    cout << abs(value) << endl; 
    

}