// Exercise 16.6: How do you think the library begin and end functions that
// take an array argument work? Define your own versions of these functions.


// Exercise 16.7: Write a constexpr template that returns the size of a given
// array.

#include <string>
#include <iostream>
using namespace std; 

template <typename T,  size_t N>
T *begin_i(T (&a)[N]){
    return a; 
}

template <typename T,  size_t N>
T *end_i(T (&a)[N]){
    return a+N; 
}

template<typename T, size_t N>
constexpr size_t size_i(const T (&a)[N]){ return N; }

int main(){
    int arr[] = {1,2,3,4,5};
    int arr1[] = {110,120,134};
    std::cout << (begin(arr) == begin_i(arr)) << std::endl;   
    std::cout << (end(arr) == end_i(arr)) << endl; 
    std::cout << size_i(arr) << std::endl; 
}
