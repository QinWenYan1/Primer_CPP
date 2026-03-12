#include "Bulk_quote.h"
#include <iostream>

/*
* Exercise 15.7: 
* Define a class that implements a limited discount strategy,
* which applies a discount to books purchased up to a given limit. If the
* number of copies exceeds that limit, the normal price applies to those
* purchased beyond the limit.
*
* Exercise 15.8: 
* Define static type and dynamic type.
*/

using namespace std; 

int main(){

    Quote book1("C the programming language", 100); 
    Bulk_quote book2("The primer cpp", 120, 0.5); 
    Bulk_quote book3("The morden effective cpp", 500, 0.75); 
    Quote book4 = book3; //static type 
    const Quote &book5 = book3; //dynamic type 

    print_total(cout, book1, 5); 
    print_total(cout, book2, 5);
    print_total(cout, book4, 5); 
    print_total(cout, book5, 5);
    
}