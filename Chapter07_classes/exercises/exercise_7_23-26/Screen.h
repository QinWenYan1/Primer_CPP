#ifndef SCREEN_H
#define SCREEN_H

#include <string>

/*
* Exercise 7.23: Write your own version of the Screen class.
* 
* Exercise 7.24: Give your Screen class three constructors: a default
* constructor; a constructor that takes values for height and width and
* initializes the contents to hold the given number of blanks; and a constructor
* that takes values for height, width, and a character to use as the contents of
* the screen.
* 
* Exercise 7.25: Can Screen safely rely on the default versions of copy and
* assignment? If so, why? If not, why not?
*
* Answer: 可以依赖，因为Screen类里面不存在类外的动态内存
* 使用默认合成的拷贝赋值是没有危险的 
*/

class Screen {

    public:
        //成员类型
        using pos = std::string::size_type; 

        //构造函数
        Screen() = default; 
        Screen(pos height, pos width): height(height), width(width), content(height*width, ' '){} 
        Screen(pos height, pos width, char c): height(height), width(width), content(height*width, c) {}

        //接口集合

        // 返回Screen实例中的cursor信息，不可改动
        const pos &get_cursor() const { return this->cursor; }

        // 返回Screen实例中的height信息，不可改动
        const pos &get_height() const { return this->height; } 

        // 返回Screen实例中的width信息，不可改动
        const pos &get_width() const { return this->width; }

        // 返回Screen实例中的content内容信息，不可改动
        const std::string &get_content() const { return this->content; }

    private:
        pos cursor = 0; //提供 in-class initializer 
        pos height = 0; //提供 in-class initializer 
        pos width = 0; //提供 in-class initializer
        std::string content = "None"; // 提供 in-class blank initializer

}; 

#endif