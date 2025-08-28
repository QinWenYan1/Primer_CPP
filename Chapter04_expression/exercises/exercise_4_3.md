## Exercise 4.3
Order of evaluation for most of the binary operators is left
undefined to give the compiler opportunities for optimization. This strategy
presents a trade-off between efficient code generation and potential pitfalls in
the use of the language by the programmer. Do you consider that an
acceptable trade-off? Why or why not?

### ✅ 支持的理由

* **优化性能**：编译器可以根据目标平台、指令流水线等自由选择最优执行顺序，提高代码效率。
* **简化标准**：标准不强制顺序，给编译器实现更大自由度。
* **只要遵守规则就安全**：程序员避免在同一表达式中修改并使用同一对象，就不会踩坑。

### ❌ 反对的理由

* **增加理解成本**：初学者难以意识到未定义行为的存在，容易写出错误代码。
* **降低可移植性**：不同编译器、不同平台可能给出不同结果。
* **调试困难**：代码行为不可预测，可能导致隐蔽 bug。

---
