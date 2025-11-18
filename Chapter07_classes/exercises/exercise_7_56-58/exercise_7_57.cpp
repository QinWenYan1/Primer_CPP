#include <string>
#include <iostream>
#include "Account.h"

double Account::interestRate = 1.5; 

int main(){

    //我们运行一下自己写的对吗
    Account a1; 
    std::cout << a1.get_total() << " "
        << a1.get_type() << " "
        << a1.get_name() << " "
        << get_interestRate(a1) << std::endl; 
    


}