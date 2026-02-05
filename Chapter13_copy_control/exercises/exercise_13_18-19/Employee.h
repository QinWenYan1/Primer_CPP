/*
* Exercise 13.18: 
* Define an Employee class that contains an employee name
* and a unique employee identifier. Give the class a default constructor and a
* constructor that takes a string representing the employee’s name. Each
* constructor should generate a unique ID by incrementing a static data
* member.
*/

/*
* Exercise 13.19: 
* Does your Employee class need to define its own versions
* of the copy-control members? If so, why? If not, why not? Implement
* whatever copy-control members you think Employee needs.
* 
* Answer:
* 按照实际逻辑出发， 是有必要定义拷贝初始化和拷贝赋值操作符的， 因为默认合成的拷贝
* 初始化和拷贝操作符是将员工工牌号都复制过去了， 但是这个和现实逻辑不符合
* 使用我们需要去自己定义， 但是析构函数就不需要， 本身默认合成就完全够用了
* static 成员不会被析构函数销毁， 而是被程序销毁， 这就够了
*/



#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee{

    std::string name; //员工名字
    unsigned personalId = 0; //工牌号
    static unsigned eid; //制造工牌号逻辑

public:
    
    //name getter 
    const std::string &getName() { return name; } 

    //id getter
    const unsigned &getId() { return personalId; }

    //default constructor
    Employee() = default;

    //string constructor
    Employee(std::string arg): name(arg), personalId(++eid){}

    //copy initializer 
    Employee(const Employee &emp): name(emp.name), personalId(++eid){}

    //copy-assignment operator
    Employee &operator=(const Employee &emp){ 
        this->name = emp.name; 
        return *this; 
    }

    //destructor不需要显示申明


}; 

#endif