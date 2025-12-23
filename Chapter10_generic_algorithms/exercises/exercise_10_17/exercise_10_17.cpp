#include <iostream>
#include <numeric>
#include "Sales_data.h"

using namespace std; 

/*
* Exercise 10.17: 
* Rewrite exercise 10.12 from § 10.3.1 (p. 387) to use a
* lambda in the call to sort instead of the compareIsbn function.
*/

int main(){

    vector<Sales_data> sale_list = {
        Sales_data("Harry potter", 110.0, 2), 
        Sales_data("The world", 10, 50), 
        Sales_data("C the programming language", 500, 0),
        Sales_data("primer cpp", 1000, 50),
        Sales_data("python", 1, 0),
        Sales_data("python", 1, 4),
        Sales_data("python", 1, 3)
    }; 

    stable_sort(
        sale_list.begin(), 
        sale_list.end(),
        [](const Sales_data &s1, const Sales_data &s2){ return s1.isbn().size() < s2.isbn().size(); }
    ); 

    for (const auto e: sale_list) cout << e.isbn() << " has been sold: " << e.soldNum() << endl; 

}