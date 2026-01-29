#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <memory> //use shared_ptr
#include <vector> // use vector
#include <string> //use string 
#include <map>    //use map 
#include <set>    //use set 
#include <fstream> //use ifstream

/* 
* Exercise 12.27: The TextQuery and QueryResult classes use only
* capabilities that we have already covered. Without looking ahead, write your
* own versions of these classes.
*/

class QueryResult{
    
    //查找后得到的出现位置
    std::shared_ptr<std::map<std::string, std::set<size_t>>> lookupTable;
    const std::string keyword; 

public:
    
    //构造函数
    QueryResult(std::shared_ptr<std::map<std::string, std::set<size_t>>> &copy, const std::string &key): lookupTable(copy), keyword(key){}


    std::set<size_t> getResult() const { 
        if((*lookupTable).find(keyword) != (*lookupTable).end()) return (*lookupTable).find(keyword)->second;
        return std::set<size_t>(); // 返回一个空的 set
    }

}; 

#endif 