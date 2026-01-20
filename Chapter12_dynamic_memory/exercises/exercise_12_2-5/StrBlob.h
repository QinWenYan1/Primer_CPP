#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

/*
* Exercise 12.2: 
* Write your own version of the StrBlob class including the
* const versions of front and back.
*/

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    std::string& front();
    std::string& back();
    const std::string& front() const; 
    const std::string& back() const; 
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg) const;
};

// 构造函数
StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) { }
StrBlob::StrBlob(std::initializer_list<std::string> il):
              data(std::make_shared<std::vector<std::string>>(il)) { }

// check 函数
void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

// 元素访问成员
std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::front() const{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string& StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

#endif 