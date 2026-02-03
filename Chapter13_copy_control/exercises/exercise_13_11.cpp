/*
* Exercise 13.11: 
* Add a destructor to your HasPtr class from the previous
* exercises.
*/

#include <string>
#include <stdexcept>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) { }
    //add copy constructor declaration
    HasPtr(const HasPtr&);
    //add copy-assignment operator 
    HasPtr& operator= (const HasPtr&); 
    //destructor 
    ~HasPtr(){}; 

private:
    std::string *ps;
    int i;
};

//definition of copy constructor
HasPtr::HasPtr(const HasPtr& arg): 
i(arg.i), ps(new std::string(*arg.ps)){}

//definition of copy-assignment operator
HasPtr& HasPtr::operator= (const HasPtr& arg){
    this->i = arg.i; 
    if (this->ps) delete this->ps; //深度拷贝
    if (arg.ps) {
        this->ps = new std::string(*arg.ps);
    }else{  
        throw std::runtime_error("invalid assignment: invalid right hand pointer ");
    }
    return *this; 
}



