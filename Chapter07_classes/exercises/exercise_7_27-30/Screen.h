#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <iostream>


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

        //移动cursor, 并返回这个对象为左值， 可改动， 支持链式操作
        Screen &move(pos r, pos c) {

            pos step = r * width; 
            cursor = step + c; 
            return *this;  

        }

        //将现在cursor所在位置的字符修改, 并返回这个对象为左值， 可改动， 支持链式操作
        Screen &set(char c) {

            content[cursor] = c; 
            return *this;    

        }
        
        //打印图, 并返回这个对象为左值， 可改动， 支持链式操作
        Screen &display(std::ostream &seeout){

            do_display(seeout);
            return *this; 

        }

        //打印图, 并返回这个对象为左值， 不可改动， 不支持链式操作
        const Screen &display(std::ostream &seeout) const {

            do_display(seeout);
            return *this; 

        }

    private:
        pos cursor = 0; //提供 in-class initializer 
        pos height = 0; //提供 in-class initializer 
        pos width = 0; //提供 in-class initializer
        std::string content = "None"; // 提供 in-class blank initializer

        //private utility function 
        void do_display(std::ostream &seeout) const {
            
            for(pos i = 0; i != content.size(); ++i ){
                
                if ( (i != 0) && (i % width == 0) ) seeout << "\n";
                seeout << content[i];

            }
        
        }

}; 

#endif