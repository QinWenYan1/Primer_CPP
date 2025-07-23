## ✅ Exercise 2.1

### 🔸 Differences between `int`, `long`, `long long`, and `short`

* `short`: At least 16 bits. Smaller range than `int`.
* `int`: At least 16 bits (commonly 32 bits). Default integer type.
* `long`: At least 32 bits. May offer a larger range than `int`.
* `long long`: At least 64 bits. Used when very large integer values are needed.

> 🔑 Rule of thumb: Use `int` unless you have a good reason to use a wider or narrower type.

### 🔸 Differences between `unsigned` and `signed` types

* `signed` types: Can store both positive and negative values.
* `unsigned` types: Can only store non-negative values, but with a larger positive range.

> ⚠️ Note: Mixing signed and unsigned types can cause unexpected results due to implicit conversions.

### 🔸 Differences between `float` and `double`

* `float`: 32-bit floating-point number with \~6 significant digits precision.
* `double`: 64-bit floating-point number with \~10 significant digits precision.

> ✅ Prefer `double` when precision matters (e.g. in scientific or financial calculations).

---

## ✅ Exercise 2.2

### 💡 What types to use for a mortgage payment calculation?

* **Rate**: `double`

  > Because it usually involves decimal fractions (e.g., 3.75%) and requires precision.

* **Principal**: `double`

  > Large monetary values often with decimals (e.g., 350000.00).

* **Payment**: `double`

  > The result of a calculation involving rate and principal, precision is needed.

> 🔍 Why not `float`? Because its limited precision can lead to rounding errors over time in financial computations.

---

✅ **Summary**: Use `double` for financial calculations due to better precision; understand the size and signedness of integer types to use them appropriately.
