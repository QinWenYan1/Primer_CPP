#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account{

private:
    static double interestRate; 
    double total; 
    std::string name; 
    std::string type; 

public:
    Account(const std::string& name = "None", const std::string& type = "None"):
        name(name), type(type), total(0.0){}
    std::string& get_name(){ return name; }
    std::string& get_type(){ return type; }
    double get_total(){ return total; }

    friend double get_interestRate(Account);

};

double get_interestRate(Account a){ return a.interestRate; }

#endif