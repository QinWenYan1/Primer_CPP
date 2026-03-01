#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>
 

/*
* Exercise 14.20: 
* Define the addition and compound-assignment operators
for your Sales_data class.
*/

/*
* Exercise 14.21-25: 
* 略
*/

class Sales_data{

//constructors: public 
public:
    friend inline std::ostream &operator<<(std::ostream&, const Sales_data&);
    friend inline std::istream &operator>>(std::istream&, Sales_data&);
    
    Sales_data(): bookNo("None"), price(0.0), units_sold(0){}; 

    Sales_data(const std::string str): bookNo(str){}

    Sales_data(const std::string str, double price, unsigned num):bookNo(str), price(price), units_sold(num){}

    Sales_data(std::istream &in){ in >> *this; }

    //移动构造函数
    Sales_data(Sales_data && rhs) noexcept : bookNo(rhs.bookNo), price(rhs.price), units_sold(rhs.units_sold) {
        std::cout << "move constructor complete" << std::endl; 
    }

    //member function declaration 
    //返回本书的isbn信息
    const std::string& isbn() const { return bookNo; }

    //左操作数和右操作数相加，产生一个新的Sale_data
    //是两者合并后的数据
    //左右操作数内部数据不变
    //如果两者的bookNo不同， 则返回一个初始化的Sale_datas
    Sales_data operator+(const Sales_data& obj1) const {

        Sales_data outcome; 
        outcome += obj1; 
        return outcome;  

    }

    //左操作数和右操作数相加，产生一个Sale_data
    //是两者合并后的数据
    //左操作数的内部数据改变
    //如果两者的bookNo不同， 则返回原本左操数
    Sales_data& operator+=(const Sales_data& obj1) {
 
        if ( obj1.bookNo != bookNo) return *this; 
        units_sold += obj1.units_sold; 
        double total_price = units_sold * price + 
                            obj1.units_sold * obj1.price;
        price = avg_price(total_price, units_sold);
        return *this; 

    }


private: //member data: private 
    
    unsigned units_sold = 0;
    double price = 0.0;   
    std::string bookNo = "None"; 

    //计算平均price在combine之后
    double avg_price(double total_price, unsigned total_num) const { return total_price/total_num; } 

};

//nonmember funciton, but same interface 


//读取数据进入到实例中，返回输入流，支持链式操作
inline std::istream &operator>>(std::istream &in, Sales_data &item){

    in >> item.bookNo >> item.units_sold >> item.price;  
    if (!in) { //如果有问题的话那么我们进行初始化处理
        std::cout << "Input error detected ..." << std::endl; 
        item.bookNo = "None"; 
        item.price = 0.0; 
        item.units_sold = 0; 

    }

    return in; 

};

//将实例的数据打印出来， 返回输出流，支持链式操作
inline std::ostream &operator<<(std::ostream &out, const Sales_data &item){

    out << "ISBN number: " << item.bookNo << " "
        << "Average price: " << item.price << " "
        << "Sold number: " << item.units_sold << " ";

    return out; 

}



#endif