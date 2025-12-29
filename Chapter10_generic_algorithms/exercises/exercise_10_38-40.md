Exercise 10.38: List the five iterator categories and the operations that each supports.

Answer:

1. 输入迭代器：只支持++移动，由于无法保存元素状态，所以只支持单次读也不支持--移动
2. 输出迭代器：只支持++移动，由于无法保存元素状态，所以只支持单次写也不支持--移动
3. 前向迭代器：只支持++移动， 可以保存元素状态， 可以多次访问或写入一个元素， 支持基本位置判断， == ，!= 
4. 双向迭代器：支持++ -- 移动， 可以保存元素状态， 可以多次访问或写入一个元素, 支持即本位置判断, ==, != 
5. 自由访问迭代器：支持++ --移动， 可以保存元素状态， 可以多次访问或写入一个元素， 支持迭代器之间的运算， 支持位置判断 == != 以及> < 符号

Exercise 10.39: What kind of iterator does a list have? What about a
vector?
Exercise 10.40: What kinds of iterators do you think copy requires? What
about reverse or unique?