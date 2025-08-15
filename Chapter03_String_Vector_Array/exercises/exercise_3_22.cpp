#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::string; 

/*
* Exercise 3.22: 
* Revise the loop that printed the first paragraph in text to
* instead change the elements in text that correspond to the first paragraph
* to all uppercase. After you’ve updated text, print its contents.
*/

int main(void){

    //create string container named text
    vector<string> text = {"hello", "this", "", "city" }; 

    // print each line in text up to the first blank line
    for (auto it = text.begin(); it != text.end() && !it->empty(); ++it){

        //convert it to upper case
        for( auto &c: (*it) ){ c = toupper(c); }

        cout << *it << endl;

    }


}
