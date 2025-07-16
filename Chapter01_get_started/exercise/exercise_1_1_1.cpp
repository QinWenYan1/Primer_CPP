/*
* Exercise 1.1:
* Review the documentation for your compiler and determine
* what file naming convention it uses. Compile and run the main program from
* page 2.
*/

/*
* answer:
* Clang 在MacOs里面使用的是 .cpp 最为后缀
*/

/*
* Exercise 1.2:
* Change the program to return -1. A return value of -1 is
* often treated as an indicator that the program failed. Recompile and rerun
* your program to see how your system treats a failure indicator from main.
*/

/*
* answer: 
* 当程序返回 -1 时，我们在终端中运行 echo $?，会看到输出为 255。
* 这是因为 shell 将 main 函数的返回值解释为一个无符号的 8 位整数。
* 在这种情况下，-1 被转换为 255，系统据此认为程序执行失败，因为在类 Unix 系统中，非零的退出码通常表示错误或异常终止。
*/

int 
main(){
    return -1;
}