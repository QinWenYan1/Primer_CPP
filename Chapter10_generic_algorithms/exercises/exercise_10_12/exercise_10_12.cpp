#include <iostream>
#include <numeric>
#include "Sales_data.h"

using namespace std; 

bool compareIsbn(Sales_data item1, Sales_data item2){ return item1.isbn() < item2.isbn();}

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

    stable_sort(sale_list.begin(), sale_list.end(), compareIsbn); 

    for (const auto e: sale_list) cout << e.isbn() << " has been sold: " << e.soldNum() << endl; 

}