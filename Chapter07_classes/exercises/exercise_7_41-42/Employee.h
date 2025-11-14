#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee {
private:
    std::string name;
    int employeeId;
    double salary;
    int level;                   // 职级
    std::string departmentName;  // 部门名称

public:

    // 1. 基本构造函数 - 只有基本信息的员工， 名字和id, 刚入职
    Employee(const std::string& n = "Unknown", int id = 0) : name(n), employeeId(id){ }

    // 2. 主要构造函数 - 员工信息完整，信息齐全， 已经分配到部门
    Employee(const std::string& n, int id, double sal,  int lvl, const std::string& dept)
        : Employee(n, id) {

            this->salary = sal;
            this->level = lvl; 
            this->departmentName = dept; 

         }


};

#endif