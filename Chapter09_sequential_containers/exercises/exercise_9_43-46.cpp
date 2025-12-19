#include <iostream>
#include <string>

using namespace std; 

/*
* Exercise 9.43: 
* Write a function that takes three strings, s, oldVal, and
* newVal. Using iterators, and the insert and erase functions replace all
* instances of oldVal that appear in s by newVal. Test your function by
* using it to replace common abbreviations, such as “tho” by “though” and
* “thru” by “through”.
* 
* Exercise 9.44: 
* Rewrite the previous function using an index and replace.
*/

/*
* Exercise 9.45: 
* Write a funtion that takes a string representing a name
* and two other strings representing a prefix, such as “Mr.” or “Ms.” and a
* suffix, such as “Jr.” or “III”. Using iterators and the insert and append
* functions, generate and return a new string with the suffix and prefix
* added to the given name.
* 
* Exercise 9.46: 
* Rewrite the previous exercise using a position and length to
* manage the strings. This time use only the insert function.
*/

inline void replace_old_with_new(string s, string oldVal, string newVal){

    s.erase(s.size()-4,4); 
    s.insert(s.size(), newVal); 
    cout << s << endl; 

}

inline string add_prefix_suffix(string name, string prefix, string suffix){

    name.insert(0, prefix); 
    name.append(suffix); 
    return name; 

}

inline string add_prefix_suffix_2(string name, string prefix, string suffix){

    name.insert(0, prefix); 
    name.insert(name.size(), suffix, 0 , 6); 
    return name; 

}


int main(){

    /* ---- 43 - 44 ---- */ 
    string s, oldVal, newVal; 

    oldVal = "ough";
    s = "through"; 
    newVal = "u"; 

    replace_old_with_new(s, oldVal, newVal);
    cout << s << endl;
    s.replace(s.size()-4, 4, newVal); 
    cout << s << endl; 

    /* ------ end ------ */
    /* ------ 45 - 46 ---- */
    string name = "qinwen"; 
    string prefix = "Prof."; 
    string suffix = "Junior"; 

    cout << add_prefix_suffix(name, prefix, suffix) <<endl; 
    cout << add_prefix_suffix_2(name, prefix, suffix) << endl; 


}