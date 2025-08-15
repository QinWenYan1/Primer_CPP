#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main(void){

    //{0-9, 10-19, 20-29, 30-39, 40-49, 50-59, 60-69, 70-79, 80-89, 90-99, 100}
    vector<int> grade(11);
    int temp;
    auto iter = grade.begin();
    auto sent = grade.cend(); 
    
    //input
    while( cin >> temp ){

        auto iter_new = iter + ( temp / 10 ); 

        //valid iterator
        if (iter_new < sent){

            (*iter_new) ++;

        }else{

            cout << "invalid input number! " << endl; 

        }

    }

    //print 
    cout << "The outcome: " << endl;
    for(auto e : grade){

        cout << e << endl;
        
    }
    
}
