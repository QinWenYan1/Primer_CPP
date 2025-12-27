#include <fstream>
#include <vector>
#include <numeric>
#include <iterator>

using namespace std;

int main(){

    ifstream fileInput("input.txt");
    ofstream fileOutputOdd("odds.txt");
    ofstream fileOutputEven("evens.txt"); 
    istream_iterator<int> fi(fileInput), eof; 
    ostream_iterator<int> oddsOutput(fileOutputOdd, " "), evensOutput(fileOutputEven, " "); 
    vector<int> vecInt(fi, eof);

    for (const auto &e: vecInt){

        if (e%2) *oddsOutput++ = e; 
        else *evensOutput++ = e; 

    }

}