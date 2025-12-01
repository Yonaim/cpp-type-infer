# **cpp_type_infer**

### *A minimal C++ type inference engine*

---

# **I — Introduction**

C++ performs sophisticated compile-time type analysis to determine the types of expressions, variables, and template instantiations.
In this project, you will implement the foundation of a C++-like type inference engine for a **restricted subset of C++**.

You will build:

* a tokenizer
* a parser
* an expression type evaluator
* an `auto` type deduction engine
* a symbol table containing all inferred types

This project will not ask you to generate code or execute programs.
You will focus exclusively on **parsing**, **type constraint solving**, and **reporting the final inferred types**.

The mandatory part focuses on **implementing `auto` deduction**, which forms the core of a minimal C++ type inference engine.
The bonus part expands the engine with **decltype rules**, **template argument deduction**, and additional advanced features.

---

# **II — Common Instructions**

* You must use **C++17 or higher**.
* Your project must compile with:

```
-Wall -Wextra -Werror
```

* The project must be written entirely in **C++**.
* You **must not** use external parsing libraries such as:

  * `boost::spirit`, `ANTLR`, `PEGTL`, etc.
* You **must not** embed any external compiler front-ends:

  * Clang, libclang, GCC plugins, or similar tools.
* You must implement **your own**:

  * tokenizer
  * parser
  * AST
  * type system
  * inference logic
* Memory leaks or undefined behavior are not tolerated.

### Allowed Libraries

You may use:

* Standard C++ library
* `<string>`, `<vector>`, `<map>`, `<memory>`, `<sstream>`, `<iostream>`
* Smart pointers (`unique_ptr`, `shared_ptr`)

Forbidden:

* Any library that performs parsing or type inference for you
* `system()`
* Runtime code execution
* External compiler-related APIs

---

# **III — Mandatory Part**

In the mandatory section, you must implement a minimal type inference engine that supports:

## **1. Supported Mini-C++ Syntax**

### Built-in types

* `int`
* `double`
* `string`

### Type modifiers

* Pointers: `T*`
* References: `T&`

### Variable declarations

You must support:

```
auto x = 10;
auto y = x + 1;
auto p = &x;
auto z = y * 3;
```

### Expressions

* Binary: `+`, `-`, `*`, `/`
* Comparison: `==`, `!=`, `<`, `>`
* Unary: `&`, `*`
* Parenthesized expressions

### Function calls (without templates)

A function may appear in the global symbol table if predeclared.

---

## **2. Mandatory — auto type deduction**

You must implement a simplified version of C++ `auto` deduction.
Examples:

```
auto x = 1;       // int
auto y = 1.0;     // double
auto z = x + y;   // double
auto p = &x;      // int*
auto r = p;       // int*
```

### Arithmetic conversion rules

Your engine must implement simplified C++ usual arithmetic conversions:

* `int + int` → `int`
* `int + double` → `double`
* `double + int` → `double`

---

## **3. Output Requirements**

Your program must output a **symbol table** listing all inferred types.

Example:

Input:

```
auto x = 10;
auto y = x + 1;
int a = 3;
auto p = &a;
auto r = *p;
```

Output:

```
x : int
y : int
a : int
p : int*
r : int
```

---

## **4. Parser Requirements**

Your parser must support:

* variable declarations
* binary expressions
* unary expressions (`&`, `*`)
* parentheses
* literal values
* identifier references

AST nodes are strongly recommended.

---

## **5. Error Handling**

Your program must detect errors such as:

* Type mismatches
* Using undeclared identifiers
* Invalid pointer or reference operations
* Unsupported syntax

Errors must result in a readable message and must not crash the program.

---

## **6. Mandatory Folder Structure**

```
cpp_type_infer/
├── Makefile
├── include/
│   ├── lexer.hpp
│   ├── parser.hpp
│   ├── ast.hpp
│   ├── types.hpp
│   ├── infer.hpp
│   ├── symbol_table.hpp
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   ├── types/
│   ├── infer/
│   └── main.cpp
└── examples/
```

---

## **7. Makefile Rules**

Your Makefile must contain the usual 42 rules:

```
NAME = cpp_type_infer
CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Iinclude
SRCS = $(shell find src -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
```

---

# **IV — Bonus Part**

The bonus part extends your engine beyond `auto` and is checked **only if the mandatory part is perfect**.

### **1. decltype support**

Implement simplified decltype behavior:

* `decltype(identifier)` → identifier’s type
* `decltype(literal)` → literal type
* `decltype(expr1 + expr2)` → arithmetic conversion
* `decltype(*p)` → `T&`
* `decltype((x))` → `T&` (parenthesized lvalue)

### **2. Template argument deduction**

Support:

```
template <typename T>
T add(T a, T b);

auto x = add(1, 2);     // T = int
auto y = add(1.5, 2.5); // T = double
```

Mismatched template arguments must produce an error:

```
add(1, 2.0); // ERROR
```

### **3. Additional Bonus Features**

* Const-correctness
* Array type deduction
* Simplified lambda type deduction
* Full canonical type printer

---

# **V — Submission and Peer-Evaluation**

Your final submission must include:

* All source files
* A complete Makefile
* Example `.mcpp` files for evaluation

During peer-evaluation, the evaluator will ensure:

* The program compiles with the required flags
* Mandatory features work exactly as specified
* Bonus features do not break mandatory behavior
* Error handling is clean and robust
* Memory safety is respected
* Code organization and readability follow 42 standards

A well-designed, modular, and readable architecture will be highly valued.
