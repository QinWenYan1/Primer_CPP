#ifndef PERSON_H
#define PERSON_H

#include <string>
using std::string; 

/*
* Exercise 7.4: 
* Write a class named Person that represents the name and
* address of a person. Use a string to hold each of these elements.
* Subsequent exercises will incrementally add features to this class.
*/

/*
* Exercise 7.5:  
* Provide operations in your Person class to return the name
* and address. Should these functions be const? Explain your choice.
* 
* Answer: 
* 当然， 这俩个成员函数需要应该是const, 因为考虑到类在使用时这俩个函数仅仅是读取数据并且
* 防止这些接口无意间修改到实例的数据造成严重后果， 
* 同时在使用时，如果这个类被声明为常量了
* 依然可以调用， 而不是无法调用
*/

struct Person {

    //member data 
    string name; //储存名字
    string address; //储存地址

    //member function declaration 
    const string& get_name() const;
    const string& get_address() const; 

};

//member function definition 
const string& Person::get_name() const { return name; }

const string& Person::get_address() const { return address; }


#endif 
