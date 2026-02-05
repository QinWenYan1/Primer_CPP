#include <iostream>
#include "Employee.h"

using namespace std; 

unsigned Employee::eid = 100; 
int main (){

    Employee e1("Qinwen"); 
    Employee e2("yan");
    Employee e3 = e1; 
    cout << "e1: " << e1.getId() << "-" << e1.getName()
        << "e2: " << e2.getId() << "-" << e2.getName()
        << "e3: " << e3.getId() << "-" << e3.getName() << endl; 

    e3 = e2; 

    cout << "e1: " << e1.getId() << "-" << e1.getName()
        << "e2: " << e2.getId() << "-" << e2.getName()
        << "e3: " << e3.getId() << "-" << e3.getName() << endl;


    
}