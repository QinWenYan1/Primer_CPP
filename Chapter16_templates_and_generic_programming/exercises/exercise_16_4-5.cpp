#include <string>
#include <iostream>
#include <iterator>

// Exercise 16.4: Write a template that acts like the library find algorithm.
// The function will need two template type parameters, one to represent the
// function’s iterator parameters and the other for the type of the value. Use
// your function to find a given value in a vector<int> and in a
// list<string>.
// Exercise 16.5: Write a template version of the print function from § 6.2.4
// (p. 217) that takes a reference to an array and can handle arrays of any size
// and any element type.

using namespace std; 

template <typename T, typename X>
X find_i(X head, const X &tail, const T &target){
    while (head != tail ){
        if (*head++ == target ) return head; 
    }
    return tail; 
}

template <typename T, size_t N>
void print_a(const T(&array)[N]){

    for (int i = 0; i != N; ++i ){ cout << array[i] << " "; } 
    cout << endl; 

}

int main(){

    int a1[10] = {1,2,3,45,6,7,8,9,10,11}; 
    int a2[1] = {112};

    cout << "The element 54 in the array?: " << (find_i(begin(a1), end(a1), 54) != end(a1)) << endl; 
    cout << "The element 45 in the array?: " << (find_i(begin(a1), end(a1), 45) != end(a1)) << endl;
    print_a(a1); 
    print_a(a2); 

}