#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

/*
* Exercise 5.22: 
* The last example in this section that jumped back to begin
* could be better written using a loop. Rewrite the code to eliminate the goto.
*/

int get_size(){

    return 1; 

}

int main(void){

    int sz = get_size(); 
    while(sz <= 0 ){ sz = get_size(); }
    cout << "execution terminated ..." << endl; 

}
