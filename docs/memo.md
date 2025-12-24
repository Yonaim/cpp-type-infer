
# 처리 순서
Lexer → Parser → AST → TypeInfer → SymbolTable

- Lexer: 문자열 → Token
- Parser: Token → AST
- AST: 트리 구조
- TypeInfer: AST → Type 결론
- SymbolTable: 최종 타입 기록

# AST

- 일반 트리 (n-ary tree)

## 연산 종류 

| 종류                   | 설명        | 예시               |
| -------------------- | --------- | ---------------- |
| **Binary Operation** | 2개의 피연산자  | `a + b`, `x * y` |
| **Unary Operation**  | 1개의 피연산자  | `-x`, `&x`, `*p` |
| **Call Expression**  | n개의 인자    | `f(a, b)`        |
| **Block**            | 여러 문장의 묶음 | `{ ... }`        |
| **Program**          | 전체 문장 리스트 | 파일 전체            |


## 1. 이항 연산 (Binary Operation)

### 예시 코드

```cpp
a + b
```

### AST 구조

```
BinaryExpr("+")
 ├── VarExpr("a")
 └── VarExpr("b")
```

---

### 예시 코드

```cpp
x * (y + 1)
```

### AST 구조

```
BinaryExpr("*")
 ├── VarExpr("x")
 └── BinaryExpr("+")
      ├── VarExpr("y")
      └── IntLiteral(1)
```

---

## 2. 단항 연산 (Unary Operation)

### 예시 코드

```cpp
-x
```

### AST 구조

```
UnaryExpr("-")
 └── VarExpr("x")
```

---

### 예시 코드

```cpp
&value
```

### AST 구조

```
UnaryExpr("&")
 └── VarExpr("value")
```

---

### 예시 코드

```cpp
*p
```

### AST 구조

```
UnaryExpr("*")
 └── VarExpr("p")
```

---

## 3. 함수 호출 (Call Expression)

### 예시 코드

```cpp
f(a, b, c)
```

### AST 구조

```
CallExpr
 ├── VarExpr("f")
 ├── VarExpr("a")
 ├── VarExpr("b")
 └── VarExpr("c")
```

(참고: 현재 mandatory AST에는 CallExpr이 없지만 "구조 예시"로 포함)

---

## 4. 블록 / 스코프 (Block Statement)

### 예시 코드

```cpp
{
    int x;
    x = x + 1;
}
```

### AST 구조

```
BlockStmt
 ├── VarDecl("x")
 └── AssignStmt
      ├── VarExpr("x")
      └── BinaryExpr("+")
           ├── VarExpr("x")
           └── IntLiteral(1)
```

---

## 5. 프로그램 전체 (Program)

### 예시 입력

```
auto a = 1;
auto b = 2;
auto c = a + b;
```

### AST 구조

```
Program
 ├── VarDecl("a")
 ├── VarDecl("b")
 └── VarDecl("c")
```


| 종류               | child 개수 | AST 예시                       |
| ---------------- | -------- | ---------------------------- |
| Binary Operation | 2        | `BinaryExpr("+") → lhs, rhs` |
| Unary Operation  | 1        | `UnaryExpr("-") → operand`   |
| Call Expression  | 0..N     | `CallExpr → function + args` |
| Block            | N        | 문장 리스트                       |
| Program          | N        | 전체 문장 리스트                    |


## Node Name

- Declaration(Decl): 선언
- Expression(Expr): 값 생성 (표헌식)
- Statement(Stmt): 제어문 (if문, for문, return문)

| 개념          | Clang AST 노드 이름                |
| ----------- | ------------------------------ |
| 변수 선언       | VarDecl                    |
| 함수 선언       | FunctionDecl               |
| 멤버 변수       | FieldDecl                      |
| 바디 없는 함수 선언 | FunctionProtoType              |
| 이항 연산       | BinaryOperator             |
| 단항 연산       | UnaryOperator              |
| 리터럴         | IntegerLiteral, StringLiteral… |
| 변수 참조       | DeclRefExpr                    |
| 함수 호출       | CallExpr                       |
| if문         | IfStmt                         |
| for 문       | ForStmt                        |
| return 문    | ReturnStmt                     |

### statement vs expression

- statement
    - '코드 라인 하나' (문장)
    - 예시: x = 1;
- expression
    - '값을 생성'하는 표현식 
    - 예시: x = 1

```
statement:
      labeled-statement
    | compound-statement
    | expression-statement
    | selection-statement   (if/switch)
    | iteration-statement   (for/while/do)
    | jump-statement        (return/break)
    | declaration-statement
```

```
ExprStmt (x = 1;)
 └── AssignExpr("=")
        ├── VarExpr("x")
        └── LiteralExpr(1)
```

### 실제 컴파일러 구현 (Clang)

1) ExpressionStatement(ExprStmt) 같은 노드를 만들지 않는다
    - Expression이 Stmt의 서브클래스
2) 세미콜론은 AST 노드가 아니다

이유??
- 어차피 표현식(Expression)이 곧 문장(Statement)
- C/C++ 언어 자체가 expression을 statement로 허용하는 문법 구조
- C++ 컴파일러들은 보통 이럼

```
Stmt
 ├── Expr
 │     ├── BinaryOperator
 │     ├── CallExpr
 │     ├── UnaryOperator
 │     ├── IntegerLiteral
 │     └── ...
 ├── IfStmt
 ├── WhileStmt
 └── ReturnStmt
```
