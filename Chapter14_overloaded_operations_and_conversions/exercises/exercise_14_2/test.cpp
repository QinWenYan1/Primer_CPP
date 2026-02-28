#include "Sales_data.h"
#include <string>

using namespace std; 

int main(){

    Sales_data item1("1145", 114, 2); 
    Sales_data item2("1145", 514, 2); 
    Sales_data item3 = std::move(item1 + item2); 
    cout << item3 << endl; 

    cin >> item3; 

    cout << "New item3 outcome is:" << endl; 
    cout << item3 << endl; 

}