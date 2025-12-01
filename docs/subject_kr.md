알겠어.
아래는 **방금 너에게 제공한 영어 버전**을 **목차·구조·문장 스타일을 1:1 그대로 유지한 한국어 번역본**이다.
(Introduction / Common Instructions / Mandatory part / Bonus part / Submission and peer-evaluation 순서 그대로)

---

# **cpp_type_infer**

### *최소한의 C++ 타입 추론 엔진*

---

# **I — Introduction (소개)**

C++은 표현식, 변수, 템플릿 인스턴스화의 타입을 결정하기 위해 복잡한 컴파일타임 타입 분석을 수행한다.
이 프로젝트에서는 **제한된 C++ 부분집합**을 대상으로 하는 **C++ 스타일 타입 추론 엔진**을 직접 구현하게 된다.

당신은 다음을 구축해야 한다:

* 토크나이저(tokenizer)
* 파서(parser)
* 표현식 타입 평가기(expression type evaluator)
* `auto` 타입 추론 엔진
* 추론된 타입을 저장하는 심볼 테이블

이 프로젝트는 프로그램을 실행하거나 기계어를 생성할 필요가 없다.
당신은 **파싱**, **타입 제약 해결**, **최종 추론된 타입 출력**에만 집중하면 된다.

Mandatory 파트는 **`auto` 타입 추론 엔진 구현**에 초점을 맞춘다.
Bonus 파트는 여기에 **decltype 규칙**, **템플릿 타입 인자 추론**, 그리고 추가 기능을 확장하는 형태다.

---

# **II — Common Instructions (공통 지침)**

* 반드시 **C++17 이상**을 사용해야 한다.
* 프로젝트는 다음 컴파일 플래그로 빌드되어야 한다:

```
-Wall -Wextra -Werror
```

* 프로젝트는 반드시 **C++로만** 작성해야 한다.
* 다음 외부 파서 라이브러리는 사용할 수 없다:
  `boost::spirit`, `ANTLR`, `PEGTL`, 등
* 다음 외부 컴파일러 프런트엔드를 사용해서는 안 된다:
  Clang, libclang, GCC, 그 밖의 컴파일러 API
* 반드시 직접:

  * tokenizer
  * parser
  * AST
  * type system
  * inference logic
    을 구현해야 한다.
* 메모리 누수 및 undefined behavior는 허용되지 않는다.

### 허용 라이브러리

* C++ 표준 라이브러리
* `<string>`, `<vector>`, `<map>`, `<memory>`, `<sstream>`, `<iostream>`
* 스마트 포인터 (`unique_ptr`, `shared_ptr`)

### 금지

* C++ 파싱 또는 타입 추론을 수행하는 모든 외부 라이브러리
* `system()`
* 런타임 코드 실행
* 외부 컴파일러 API

---

# **III — Mandatory Part (필수 파트)**

Mandatory 파트에서는 최소한의 타입 추론 엔진을 구현해야 하며, 다음 기능을 포함해야 한다:

---

## **1. 지원되는 Mini-C++ 문법**

### 기본 타입

* `int`
* `double`
* `string`

### 타입 변형자

* 포인터: `T*`
* 레퍼런스: `T&`

### 변수 선언

다음과 같은 형태의 선언을 지원해야 한다:

```
auto x = 10;
auto y = x + 1;
auto p = &x;
auto z = y * 3;
```

### 표현식

* 이항 연산자: `+`, `-`, `*`, `/`
* 비교 연산자: `==`, `!=`, `<`, `>`
* 단항 연산자: `&`, `*`
* 괄호 표현식

### 함수 호출 (템플릿 없음)

사전에 정의된 함수라면 호출할 수 있다.

---

## **2. Mandatory — auto 타입 추론**

간소화된 C++ `auto` 타입 추론 규칙을 구현해야 한다.

```
auto x = 1;       // int
auto y = 1.0;     // double
auto z = x + y;   // double
auto p = &x;      // int*
auto r = p;       // int*
```

### 산술 변환 규칙

다음과 같이 간소화된 C++ 일반 산술 변환 규칙을 적용해야 한다.

* `int + int` → `int`
* `int + double` → `double`
* `double + int` → `double`

---

## **3. 출력 요구사항**

프로그램은 **심볼 테이블(symbol table)**에 저장된 모든 추론된 타입을 출력해야 한다.

예시 입력:

```
auto x = 10;
auto y = x + 1;
int a = 3;
auto p = &a;
auto r = *p;
```

출력:

```
x : int
y : int
a : int
p : int*
r : int
```

---

## **4. 파서 요구사항**

파서는 최소한 다음을 지원해야 한다:

* 변수 선언
* 이항 연산
* 단항 연산 (`&`, `*`)
* 괄호 표현식
* 리터럴
* 식별자 참조

AST 사용이 적극 권장된다.

---

## **5. 오류 처리**

다음 오류를 반드시 감지하고 메시지를 출력해야 한다:

* 타입 불일치
* 선언되지 않은 식별자 사용
* 잘못된 포인터/레퍼런스 연산
* 지원되지 않는 문법

오류 발생 시 프로그램이 크래시하거나 undefined behavior를 일으켜서는 안 된다.

---

## **6. 필수 디렉토리 구조**

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

## **7. Makefile 규칙**

메이크파일은 42 규칙을 따라야 한다:

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

# **IV — Bonus Part (보너스 파트)**

보너스는 **Mandatory 구현이 완벽해야만** 평가된다.

---

### **1. decltype 지원**

아래 규칙을 포함한 간소화된 decltype 동작을 구현하라:

* `decltype(identifier)` → 해당 변수 타입
* `decltype(literal)` → 리터럴 타입
* `decltype(expr1 + expr2)` → 산술 규칙 기반
* `decltype(*p)` → `T&`
* `decltype((x))` → `T&` (괄호로 감싸진 lvalue)

---

### **2. 템플릿 타입 인자 추론**

다음 형태의 템플릿 함수를 지원해야 한다:

```
template <typename T>
T add(T a, T b);
```

호출 시 타입을 유추해야 한다:

```
auto x = add(1, 2);     // T = int
auto y = add(1.5, 2.5); // T = double
```

타입 불일치 시 오류:

```
add(1, 2.0); // ERROR
```

---

### **3. 추가 보너스 기능**

* const correctness
* 배열 타입 추론
* 단순화된 lambda 타입 추론
* canonical type printer (정규화된 타입 출력기)

---

# **V — Submission and Peer-Evaluation (제출 및 평가)**

최종 제출물은 다음을 포함해야 한다:

* 모든 소스 코드
* Makefile
* 예제 `.mcpp` 파일

평가자는 다음을 확인한다:

* 프로젝트가 요구 플래그로 컴파일되는가
* Mandatory 기능이 정확히 동작하는가
* Bonus 기능이 Mandatory 기능을 손상시키지 않는가
* 오류 처리가 안정적이고 명확한가
* 메모리 안전성
* 코드 구조 및 가독성 (42 기준 준수)

잘 설계되고 모듈화된 구조는 높은 평가를 받는다.
