#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include "Sales_item.h"

using namespace std;

/*
* Exercise 10.32: 
* Rewrite the bookstore problem from § 1.6 (p. 24) using a
* vector to hold the transactions and various algorithms to do the processing.
* Use sort with your compareIsbn function from § 10.3.1 (p. 387) to
* arrange the transactions in order, and then use find and accumulate to
* do the sum.
*/

int main() {
    // 1. 读入数据
    istream_iterator<Sales_item> in(cin), eof;
    vector<Sales_item> items(in, eof);

    if (items.empty()) return 0;

    // 2. 按 ISBN 排序
    sort(items.begin(), items.end(), compareIsbn);

    // 3. 按 ISBN 分组并累加
    for (auto it = items.begin(); it != items.end(); ) {
        auto range_end = it;

        // 找到 ISBN 不同的位置
        while (range_end != items.end() &&
               range_end->isbn() == it->isbn()) {
            ++range_end;
        }

        // 累加当前 ISBN
        Sales_item sum = accumulate(
            it, range_end, Sales_item(it->isbn())
        );

        cout << sum << endl;

        // 移动到下一个分组
        it = range_end;
    }
}
