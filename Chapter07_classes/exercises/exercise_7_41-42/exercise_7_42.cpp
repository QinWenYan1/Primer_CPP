#include <iostream>
#include "Employee.h"

/*
* Exercise 7.42: For the class you wrote for exercise 7.40 in § 7.5.1 (p. 291),
* decide whether any of the constructors might use delegation. If so, write the
* delegating constructor(s) for your class. If not, look at the list of abstractions
* and choose one that you think would use a delegating constructor. Write the
* class definition for that abstraction.
*/

int main(){

    Employee e1; 
    Employee e2("qinwen", 1145);
    Employee e3("ryan", 1919, 20.0, 14, "software dev"); 

}