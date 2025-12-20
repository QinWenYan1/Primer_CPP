#ifndef TIMER_H
#define TIMER_H
#include <string>

 

class Timer{

    unsigned  year = 0; 
    unsigned  month = 0; 
    unsigned  date = 0; 
    std::string monthPattern = "JanFebMarAprMayJunJulAugSepOctNovDec";


public:
    Timer(std::string words): year(stoi(words.substr(words.size()-4, 4))){

        //处理month逻辑
        auto loc = monthPattern.find(words.substr(0,3)); 
        if (loc != std::string::npos) month = loc/3 + 1; 
        else month = stoi(words.substr(0,words.find_first_of("/")));

        //处理date逻辑
        std::string::size_type pos; 
        if((pos = words.find_first_of(",")) != std::string::npos){

            date = stoi(words.substr(words.find_first_of("1234567890"), pos));

        }else{

            pos = words.find_first_of("/");
            auto end = words.find_last_of("/");
            date = stoi(words.substr(pos+1, end));

        }
        

    }

    Timer() = default; 

    unsigned get_date(){ return date; }
    unsigned get_month(){ return month; }
    unsigned get_year(){ return year; }
    

};

#endif 