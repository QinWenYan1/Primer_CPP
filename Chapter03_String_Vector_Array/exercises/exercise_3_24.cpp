#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::string; 

int main(void){

    vector<int> v = {1, 2, 5, 10, 12};
    auto iter = v.cbegin();
    auto senti = v.cend(); 
    auto counter = v.size()/ 2;

    //print sum
    cout << "The sum: " << endl; 
    for( decltype(v.size()) i = 0; i < counter; i++){

        cout << *(iter+i) + *(iter + v.size() - i - 1) << endl; 

    }
    

}