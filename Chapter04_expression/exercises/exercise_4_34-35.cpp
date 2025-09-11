#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

/*
* Exercise 4.34:
* Given the variable definitions in this section, explain what
* conversions take place in the following expressions:
* float fval; double dval; char cval; int ival; 
* (a) if (fval) 
* Answer: 在条件语句中，非布尔类型（如 float）会转换为 bool。
* 如果 fval 为0.0，结果为 false；否则为 true。
* (b) dval = fval + ival; 
* Answer: 首先计算 fval + ival：由于 fval 是 float，ival 是 int，ival 被转换为 float（算术转换），加法结果为 float 类型的右值。
* 然后赋值给 dval（double）：float 结果被转换为 double。
* 所以转换是：ival → float →（加法）→ float → double（赋值）。
* (c) dval + ival * cval; 
* Answer: 先计算 ival * cval：由于 * 优先级高于 +，先处理乘法。
* cval 是 char，首先进行整型提升为 int。ival 是 int，所以乘法结果为 int。
* 然后计算 dval + (结果)：dval 是 double，所以乘法结果（int）被转换为 double，加法结果为 double 类型的右值。
* 所以转换是：cval → int →（乘法结果为 int）→ int → double（用于加法）。

/*
* Exercise 4.35: Given the following definitions,
* char cval;        int ival; 
* unsigned int ui;  float fval;     
* double dval;
* identify the implicit type conversions, if any, taking place:
* (a) cval = 'a' + 3; 
* Answer: 'a' 是 char，但参与加法时被提升为 int，加3后结果为 int。
* 赋值给 cval（char）时，int 被转换为 char（可能发生截断）。
*
* (b) fval = ui - ival * 1.0; 
* Answer:  先计算 ival * 1.0：ival 是 int，1.0 是 double，所以 ival 转换为 double，乘法结果为 double。
* 然后计算 ui - (结果)：ui 是 unsigned int，与 double 运算，所以 ui 转换为 double，减法结果为 double。
* 最后赋值给 fval（float）：double 被转换为 float。
*
* (c) dval = ui * fval; 
* Answer: 正确。乘法中 ui（unsigned int）和 fval（float）运算时，ui 转换为 float，乘法结果为 float。
* 赋值给 dval（double）时，float 转换为 double。
*
* (d) cval = ival + fval + dval; 
* Answer: 正确。乘法中 ui（unsigned int）和 fval（float）运算时，
* ui 转换为 float，乘法结果为 float。赋值给 dval（double）时，float 转换为 double。
*/

int main(void){/**/}