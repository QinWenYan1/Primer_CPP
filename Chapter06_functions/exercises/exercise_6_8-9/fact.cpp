#include "Chapter6.h"

//计算输入值的factorial 
//return type: int
//parameter type: int
int fact(int num){

    int fact = 1; 
    while ( num > 1 ) fact *= num--; 
    return fact; 

}