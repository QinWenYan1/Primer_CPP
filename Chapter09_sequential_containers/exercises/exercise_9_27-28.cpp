#include <iostream>
#include <forward_list>

using namespace std;

/*
* Exercise 9.27: 
* Write a program to find and remove the odd-valued
* elements in a forward_list<int>.
* 
* Exercise 9.28: 
* Write a function that takes a forward_list<string> and
* two additional string arguments. The function should find the first string
* and insert the second immediately following the first. If the first string is
* not found, then insert the second string at the end of the list.
*/

forward_list<string>& insert_string_after(forward_list<string>& fl_s,const string& tar,const string& i){

    auto prev = fl_s.before_begin(); 
    auto curr = fl_s.begin(); 
    auto tail = fl_s.end(); 
    
    while(curr != tail){

        if(*curr == tar){
            prev = curr++; 
            fl_s.emplace_after(prev, i);
            return fl_s; 
        }else{
            prev = curr++; 
        }
    }

    if( curr == tail) fl_s.emplace_after(prev, i);  
    return fl_s;
    
}

int main(){

    forward_list<int> fl_i = {114, 314, 1341, 4514, 0, 1919, 251}; 

    auto prev = fl_i.before_begin(); 
    auto curr = fl_i.begin(); 
    auto tail = fl_i.end(); 

    while (curr != tail){

        if(*curr%2 == 1) curr = fl_i.erase_after(prev);
        else{
            prev = curr; 
            ++ curr; 
        }

    }

    for(const auto e: fl_i){ cout << e << " "; }

    cout << endl; 

    forward_list<string> fl_s = {"Hello", "This", "qinwen"}; 
    insert_string_after(fl_s, "Hell", "Good Morning");

    for(const auto e: fl_s) cout << e << " "; 

}