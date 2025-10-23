#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>


/*
* Exercise 7.9: 
* Add operations to read and print Person objects to the code
* you wrote for the exercises in § 7.1.2 (p. 260).
*/

/*
* Exercise 7.10: 
* What does the condition in the following if statement do?
* if (read(read(cin, data1), data2))
* 
* Answer: 
* 将输入流输入数据先输入到第一个实例data1然后又将下一个输入流数据输入到data2
* 相当于 cin >> data1 >> data2
*/

struct Person {
 

    //member data 
    std::string name; //储存名字
    std::string address; //储存地址

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



#endif 
