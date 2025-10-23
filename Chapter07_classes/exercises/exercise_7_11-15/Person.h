#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>


/*
* Exercise 7.14: Write a version of the default constructor that explicitly
* initializes the members to the values we have provided as in-class initializers.
* Exercise 7.15: Add appropriate constructors to your Person class.
*/

struct Person {
 
    //constructors

    Person() = default; 

    Person(std::string name): name(name) { }

    Person(std::string name, std::string address): name(name), address(address) { }

    Person(std::istream &); 

    //member data 
    std::string name = "None"; //储存名字
    std::string address = "None"; //储存地址

    //member function definition

    //获得名字接口
    const std::string& get_name() const { return name; }

    //获得地址的接口
    const std::string& get_address() const { return address; } 

    
};

//nonmember function interface

//将输入流数据写入到实例中
//先写名字在写地址
std::istream &read( std::istream &in, Person &people ) { 

    in >> people.name >> people.address;
    return in; 

}

//将实例信息打印到标准输出流
//先打印名字再地址
std::ostream &print( std::ostream &out, const Person &people ){ 
    
    out << people.name << people.address; 
    return out; 

}

Person::Person(std::istream &input){ read(input, *this); }



#endif 
