#ifndef SCREEN_H
#define SCREEN_H


#include <string>
#include <iostream>
#include <vector>
#include "Window_mgr.h"



class Screen {
    // 友元声明 - 现在 Window_mgr 已经完整定义了
    friend void Window_mgr::clear(screen_index);

public:
    // 成员类型
    using pos = std::string::size_type; 

    // 构造函数
    Screen() = default; 
    Screen(pos height, pos width): height(height), width(width), content(height*width, ' '){} 
    Screen(pos height, pos width, char c): height(height), width(width), content(height*width, c) {}

    // 接口集合
    const pos &get_cursor() const { return this->cursor; }
    const pos &get_height() const { return this->height; } 
    const pos &get_width() const { return this->width; }
    std::string &get_content() { return this->content; }

    Screen &move(pos r, pos c) {
        pos step = r * width; 
        cursor = step + c; 
        return *this;  
    }

    Screen &set(char c) {
        content[cursor] = c; 
        return *this;    
    }
    
    Screen &display(std::ostream &seeout) {
        do_display(seeout);
        return *this; 
    }

    const Screen &display(std::ostream &seeout) const {
        do_display(seeout);
        return *this; 
    }

private:
    pos cursor = 0;
    pos height = 0;
    pos width = 0;
    std::string content = "None";

    void do_display(std::ostream &seeout) const {
        for(pos i = 0; i != content.size(); ++i ) {
            if ((i != 0) && (i % width == 0)) seeout << "\n";
            seeout << content[i];
        }
    }
};

// Window_mgr::clear 的实现必须在 Screen 类定义之后
inline void Window_mgr::clear(screen_index index) {
    Screen &screen = windows[index];
    screen.content = std::string(screen.height * screen.width, ' ');  // 直接访问私有成员
}

#endif