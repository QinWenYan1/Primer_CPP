#include <iostream>
#include "Sales_data.h"


/*
* Exercise 2.40: 
* Write your own version of the Sales_data class.
*/

/*
* Exercise 2.41: 
* Use your Sales_data class to rewrite the exercises in §
* 1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25). For now, you should define
* your Sales_data class in the same file as your main function.
*
*/




int main(void){


    Sales_data book1, book2;

    //now we take in two ISBN and then count their sum 
    std::cin >> book1.bookNo >> book1.units_sold >> book1.price; 
    std::cin >> book2.bookNo >> book2.units_sold >> book2.price;
    
    //now we should tell if the ISBN of books are same 
    if( book1.bookNo == book2.bookNo ){

        double total_num = book1.units_sold + book2.units_sold; 
        double total_revenue = book1.price * book1.units_sold + book2.price * book2.units_sold;
        double average_revenue = total_revenue / total_num;

        //now we print out 
        std::cout << "the total number of books is: " << total_num 
        << " the average price of book is: " << average_revenue << std::endl; 

    }else{

        std::cout << " should input identical ISBN " << std::endl; 
    }


}