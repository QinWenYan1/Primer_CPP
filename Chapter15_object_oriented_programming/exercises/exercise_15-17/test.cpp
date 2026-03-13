#include "Bulk_quote.h"
#include <iostream>

using namespace std; 

int main(){

    //Quote error_book; pure virtual function cannot initialize
    //Disc_quote error_book; 
    Bulk_quote book1("C the programming language", 114, 0.5, 1000); 
    Bulk_quote book2("The effective morden cpp", 191, 0.4, 120); 

    book1.debug(cout) << endl; 
    book2.debug(cout) << endl; 

    print_total(cout, book1, 10);
    print_total(cout, book2, 10); 


}