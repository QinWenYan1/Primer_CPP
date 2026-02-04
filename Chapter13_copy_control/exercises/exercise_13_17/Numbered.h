#ifndef NUMBERED_H
#define NUMBERED_H

struct Numbered{
    //拷贝初始化
    Numbered(const Numbered &temp){
        this->mysn = temp.mysn + 1; 
    }
    
    //需要手动提供默认初始化函数了
    Numbered() = default; 

    unsigned mysn = 114514; 
};

#endif 