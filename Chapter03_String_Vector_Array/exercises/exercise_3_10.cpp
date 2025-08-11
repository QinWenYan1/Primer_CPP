#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::cin;
using std::string; 


int main(void){

    string input;
    getline(cin, input);

    //handle it character by character! 
    for( char &c : input ){

        //this chracter is punctuation, delete itself 
        if( ispunct(c) ){
            
            c -= c; 
        }

    }

    //now let's print it 
    cout << input <<endl; 

    return 0; 

}