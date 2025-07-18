#include <iostream>

/*
* Exercise 1.17:
* What happens in the program 
* presented in this section if the
* input values are all equal? 
* What if there are no duplicated values?
*
*/

/*
* 如果都一样的话，只会输出一次报告。但是如果都不一样，没换一次数
* 就会输出一次报告，也就是每一次输入一个数就一个报告
*/


/*
* Exercise 1.18: 
* Compile and run the program from this section giving it only
* equal values as input. 
* Run it again giving it values in which no number is repeated.
*/

/*
* 如果啥都不输入的话，也没有任何信息打印。
*/


int main() {
    int currVal = 0, val = 0;
    if (std::cin >> currVal) {
        int cnt = 1;
        while (std::cin >> val) {
            if (val == currVal) {
                ++cnt;
            } else {
                std::cout << currVal << " occurs " << cnt << " times" << std::endl;
                currVal = val;
                cnt = 1;
            }
        }
        std::cout << currVal << " occurs " << cnt << " times" << std::endl;
    }
    return 0;
}