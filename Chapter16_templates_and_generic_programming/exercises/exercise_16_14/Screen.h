/* Exercise 16.14: 
*  Write a Screen class template that uses nontype
*  parameters to define the height and width of the Screen.
*/

#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <iostream>

template <size_t H, size_t W>
class Screen{  
    template <size_t H1, size_t W1> friend std::ostream& operator<<(std::ostream &, const Screen<H1, W1> &obj); 
    size_t height = H, width = W; 
public:
    Screen() = default;
};

template <size_t H1, size_t W1>
inline std::ostream& operator<<(std::ostream &os, const Screen<H1, W1> &obj){ 
    os << "height: " << obj.height << " " << "width: " << obj.width; 
    return os; 
}

#endif 