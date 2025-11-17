#ifndef DEBUG_H
#define DEBUG_H

/*
* Exercise 7.53: Define your own version of Debug.
*/

class Debug{

public:
    constexpr Debug() = default;
    constexpr Debug(bool hw, bool io, bool other):
        hw(hw), io(io), other(other){}
    
    constexpr bool get_status(){ return (hw || io || other); }

    void set_hw(bool outcome){ hw = outcome; }
    void set_io(bool outcome){ io = outcome; }
    void set_other(bool outcome){ other = outcome; }


    
private:
    bool hw = false; //硬件是否错误
    bool io = false; //io是否错误
    bool other = false;// 其他错误
};

#endif