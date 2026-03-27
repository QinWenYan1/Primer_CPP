#include "Sales_data.h"

int main(){

    Sales_data item1("1145", 100, 20), item2; 
    std::cout << "item1 is less than item2 is: " << compare(item1,item2) << std::endl;
    std::cout << compare(1,2) << std::endl;  

}