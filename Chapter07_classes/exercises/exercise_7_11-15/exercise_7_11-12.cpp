#include <iostream>
#include <cstdlib>
#include "Sales_data.h"

using std::string; 
using std::cout; 
using std::cin;
using std::endl; 

/*
* Exercise 7.11: 
* Add constructors to your Sales_data class and write a
* program to use each of the constructors
*/

/*
* Exercise 7.12: 
* Move the definition of the Sales_data constructor that
* takes an istream into the body of the Sales_data class.
*/

int main(){

    Sales_data item1; // using default initialization
    Sales_data item2 = Sales_data("1145"); // using string initialization 
    Sales_data item3 = Sales_data("1145", 100, 2); // using the standard initialization
    Sales_data item4 = Sales_data(cin); // using istream initialization

    //now print the outcome to check the status 
    cout << "ISBN\t" << "Price\t" << "Sold number\t" << endl; 
    cout << item1.isbn() << "\t" << item1.price << "\t" << item1.units_sold << endl; 
    cout << item2.isbn() << "\t" << item2.price << "\t" << item2.units_sold << endl; 
    cout << item3.isbn() << "\t" << item3.price << "\t" << item3.units_sold << endl; 
    cout << item4.isbn() << "\t" << item4.price << "\t" << item4.units_sold << endl; 


}