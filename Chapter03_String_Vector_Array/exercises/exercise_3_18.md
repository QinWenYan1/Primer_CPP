

## Exercise 3.18

**题意**：

```cpp
vector<int> ivec;
ivec[0] = 42;
```

**结论**：编译能过，但**运行时未定义行为**。`ivec` 为空，`operator[]` 只能访问**已存在**的元素，不能新增。

**修正**（任选其一）：

```cpp
#include <vector>
using namespace std;

int main() {
    vector<int> v(1);   // 先确立 1 个元素
    v[0] = 42;

    // 或者：
    vector<int> v2;
    v2.push_back(42);   // 追加一个元素
}
```

---

