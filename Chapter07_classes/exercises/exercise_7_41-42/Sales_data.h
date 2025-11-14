#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>
 

/*
* Exercise 7.41: 
* Rewrite your own version of the Sales_data class to use
* delegating constructors. Add a statement to the body of each of the
* constructors that prints a message whenever it is executed. Write
* declarations to construct a Sales_data object in every way possible. Study
* the output until you are certain you understand the order of execution among
* delegating constructors.
*/


class Sales_data{

    //constructors: public 
    public:
        Sales_data(): bookNo("None"), price(0.0), units_sold(0){}; 

        Sales_data(const std::string str): bookNo(str){

            std::cout << "Executing string constructor" << std::endl;

        }

        //使用委托构造函数
        Sales_data(const std::string str, double price, unsigned num): Sales_data(str) {

            std::cout << "Executed delegating function, now continue executing the delegating function body" << std::endl; 
            this->price = price;
            this->units_sold = num; 

        }

        Sales_data(std::istream &);

        //member function declaration 

        //返回本书的isbn信息
        const std::string& isbn() const { return bookNo; }

        //将右边类加入到左边类
        Sales_data& combine(Sales_data obj1){

            units_sold += obj1.units_sold; 
            double total_price = units_sold * price + 
                                (obj1.units_sold) * (obj1.price);
            price = avg_price(total_price, units_sold);
            return *this; 

        }

 

    //member data: private 
    private:
    
        unsigned units_sold = 0;
        double price = 0.0;   
        std::string bookNo = "None"; 

        //计算平均price在combine之后
        inline double avg_price(double total_price, unsigned total_num){ return total_price/total_num; } 

    //friend functions
    friend inline std::ostream &print(std::ostream &, const Sales_data &);
    friend inline std::istream &read( std::istream &, Sales_data &);

};

//nonmember funciton, but same interface 


//读取数据进入到实例中，返回输入流，支持链式操作
inline std::istream &read( std::istream &in, Sales_data &item ){

    in >> item.bookNo >> item.price >> item.units_sold;  
    return in; 

};

Sales_data::Sales_data(std::istream &in){ read(in, *this); }

//将实例的数据打印出来， 返回输出流，支持链式操作
inline std::ostream &print(std::ostream &out, const Sales_data &item){

    out << "ISBN number: " << item.bookNo << " "
        << "Average price: " << item.price << " "
        << "Sold number: " << item.units_sold << " ";

    return out; 

}

//读取俩个item, 相加，合成一个item 
inline Sales_data add(const Sales_data &lhs, const Sales_data &rhs){

    Sales_data new_item = lhs; 
    new_item.combine(rhs); 
    return new_item; 

}

#endif