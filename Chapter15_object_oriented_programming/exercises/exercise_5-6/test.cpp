#include "Bulk_quote.h"
#include <iostream>

using namespace std; 

int main(){

    Quote book1("C the programming language", 100); 
    Bulk_quote book2("The primer cpp", 120, 0.5); 

    print_total(cout, book1, 5); 
    print_total(cout, book2, 5);
    
}