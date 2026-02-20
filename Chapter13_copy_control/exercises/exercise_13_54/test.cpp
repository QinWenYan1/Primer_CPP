/*
* Exercise 13.54: 
* What would happen if we defined a HasPtr move-
* assignment operator but did not change the copy-and-swap operator? Write
* code to test your answer.
*/

/*
* Answer: more than one operator "=" matches these operands
*/

#include "HasPtr.h"
#include <vector>

using namespace std; 

int main(){

    HasPtr p1("NTU"); 
    HasPtr p2("UoG"); 
    HasPtr p3; 
    vector<HasPtr> s{HasPtr("1"), HasPtr("2"), HasPtr("3")}; 
    cout << p1.getString() << " " << p2.getString() << " " << p3.getString() << endl;
    p2 = p1; 
    p3 = std::move(p1); 
    vector<HasPtr> temp; 
    temp = s; 
    for (const auto e : temp) cout << e.getString() << endl; 

}