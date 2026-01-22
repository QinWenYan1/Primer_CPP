## 📊 练习批改与分析

### Exercise 12.14 & 12.15 使用shared_ptr管理连接

**原题：**
- **Exercise 12.14:** Write your own version of a function that uses a shared_ptr to manage a connection.
- **Exercise 12.15:** Rewrite the first exercise to use a lambda in place of the end_connection function.

**你的代码：**
```cpp
#include <memory>

using namespace std;

struct destination; // represents what we are connecting to
struct connection; // information needed to use the connection
connection *connect(destination*); // open the connection
void disconnect(connection*); // close the given connection

void f(destination &d /* other parameters */){
    // get a connection; must remember to close it when done
    connection *c = connect(&d);
    // use the connection
    // if we forget to call disconnect before exiting f, there will be no way to close c
    shared_ptr<connection> p(c, [](connection *p)-> void { disconnect(p); });

}
```

**批改：** ⭐⭐⭐⭐ 4/5 优秀答案！但可以更完整

**详细分析：**
- ✅ **核心概念正确**：正确使用了shared_ptr自定义删除器
- ✅ **lambda使用正确**：语法正确，返回类型推导
- ⚠️ **代码不完整**：缺少main函数和实际使用示例
- ⚠️ **可读性可改进**：lambda可以更简洁，缺少错误处理
- ✅ **资源管理正确**：确保连接会被正确关闭

**完整实现：**

### Exercise 12.14 使用函数作为删除器
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

// 前置声明
struct destination;
struct connection;

// 模拟的连接管理函数
connection* connect(destination* dest);
void disconnect(connection* conn);
void end_connection(connection* conn);  // 用于shared_ptr删除器的包装函数

// 目的地结构（模拟）
struct destination {
    std::string address;
    int port;
    destination(const std::string& addr, int p) : address(addr), port(p) {}
};

// 连接结构（模拟）
struct connection {
    std::string address;
    int port;
    bool connected;
    connection(const std::string& addr, int p) 
        : address(addr), port(p), connected(true) {
        std::cout << "Connection established to " << addr << ":" << p << std::endl;
    }
};

// 模拟连接函数
connection* connect(destination* dest) {
    if (!dest) {
        throw std::invalid_argument("Destination cannot be null");
    }
    return new connection(dest->address, dest->port);
}

// 模拟断开连接
void disconnect(connection* conn) {
    if (conn && conn->connected) {
        std::cout << "Disconnecting from " << conn->address 
                  << ":" << conn->port << std::endl;
        conn->connected = false;
        // 实际中这里会有清理资源的代码
    }
}

// 用于shared_ptr删除器的包装函数
void end_connection(connection* conn) {
    disconnect(conn);
    delete conn;  // 释放动态分配的内存
}

// 使用shared_ptr管理连接的函数
void process_data(destination& dest, const std::string& data) {
    // 创建连接
    connection* raw_conn = connect(&dest);
    
    // 使用shared_ptr管理，自定义删除器为end_connection
    std::shared_ptr<connection> conn(raw_conn, end_connection);
    
    // 使用连接处理数据
    std::cout << "Processing data: " << data 
              << " through connection to " 
              << conn->address << ":" << conn->port << std::endl;
    
    // 模拟数据处理
    // ...
    
    // 注意：不需要手动调用disconnect或delete
    // shared_ptr离开作用域时会自动调用end_connection
    std::cout << "Leaving process_data function..." << std::endl;
}

int main() {
    try {
        destination dest("example.com", 8080);
        std::cout << "=== Exercise 12.14: Using function as deleter ===" << std::endl;
        process_data(dest, "Sample data");
        std::cout << "Connection automatically closed after function exit." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

---