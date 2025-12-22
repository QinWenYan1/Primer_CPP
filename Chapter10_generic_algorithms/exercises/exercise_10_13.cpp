#include <numeric>
#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std; 

bool overfiveChar(const string & str){ return (str.size() > 5); }


int main(){

    list<string> str_list = {
        "this", "world", "hilton",
        "Cpp primer", "programming", "fuck",
        "Gethin", "Qinwen", "Glasgow"
    };

    str_list.erase(partition(str_list.begin(), str_list.end(), overfiveChar), str_list.end());

    for (const auto e : str_list) cout << e << endl; 


}