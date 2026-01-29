#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <memory> //use shared_ptr
#include <vector> // use vector
#include <string> //use string 
#include <map>    //use map 
#include <set>    //use set 
#include <fstream> //use ifstream
#include "QueryResult.h" //use QueryResult

/* 
* Exercise 12.27: The TextQuery and QueryResult classes use only
* capabilities that we have already covered. Without looking ahead, write your
* own versions of these classes.
*/

class TextQuery{
    //原文，查找目标
    std::shared_ptr<std::vector<std::string>> searchTarget; 
    //查找后得到的出现位置
    std::shared_ptr<std::map<std::string, std::set<size_t>>> lookupTable;

public:
    
    //构造函数
    TextQuery(std::ifstream &input): 
        searchTarget(std::make_shared<std::vector<std::string>>()), 
        lookupTable(std::make_shared<std::map<std::string, std::set<size_t>>>())
    {

        std::string line; 
        auto tablePtr = searchTarget.get(); 
        while (std::getline(input, line)) tablePtr->push_back(line); 
        
    }

    const QueryResult query(const std::string &str){

        auto tablePtr = searchTarget.get();
        auto outcomePtr = lookupTable.get(); 

        for (size_t i = 0; i != tablePtr->size(); ++i){

            if((*tablePtr)[i].find(str) != std::string::npos){//查找成功
                (*outcomePtr)[str].insert(i); 
            }

        }

        QueryResult outcome(lookupTable, str); 
        return outcome; 

    }

}; 

#endif 