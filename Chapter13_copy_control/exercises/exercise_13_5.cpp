/*
* Exercise 13.5: 
* Given the following sketch of a class, write a copy
* constructor that copies all the members. Your constructor should dynamically
* allocate a new string (§ 12.1.2, p. 458) and copy the object to which ps
* points, rather than copying ps itself.
*/

#include <string>


class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) { }
    //add copy constructor declaration
    HasPtr(const HasPtr&);

private:
    std::string *ps;
    int i;
};

//definition of copy constructor
HasPtr::HasPtr(const HasPtr& arg): 
i(arg.i), ps(new std::string(*arg.ps)){}