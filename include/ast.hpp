#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include "types.hpp"

struct Expr;

/*
    ASTNode
    ├── Decl
    │    ├── VarDecl
    │    ├── ParmVarDecl
    │    ├── FunctionDecl
    │    ├── StructDecl
    │    ├── TypedefDecl
    │    └── UsingDecl
    ├── Stmt
    │    ├── DeclStmt
    │    ├── ExprStmt
    │    ├── ReturnStmt
    │    ├── IfStmt
    │    ├── WhileStmt
    │    ├── ForStmt
    │    └── CompoundStmt
    └── Expr
        ├── LiteralExpr (int, double, string)
        ├── DeclRefExpr
        ├── UnaryExpr
        ├── BinaryExpr
        ├── CallExpr
        └── ParenExpr
*/

/*
    - Statemenet는 하나의 라인 (줄)
        - 따라서 내부적으로 Expr 포함
*/

// ============================================================================
// Base AST Node
// ============================================================================
struct ASTNode
{
    virtual ~ASTNode() {}
};

// ============================================================================
// Declarations (Decl)
// ============================================================================
enum class DeclKind
{
    VarDecl,
    ParmVarDecl,
    FunctionDecl,
    StructDecl,
    TypedefDecl,
    UsingDecl
};

struct Decl : ASTNode
{
    DeclKind    kind;
    std::string name; // 식별자 이름 (변수명)

    Decl(DeclKind k, const std::string &n) : kind(k), name(n) {}
};

struct VarDecl : Decl
{
    Type *type;
    Expr *init;

    VarDecl(const std::string &n, Expr *exp) : Decl(DeclKind::VarDecl, n), init(exp) {}
};

// 추후 다른 선언문들 추가

// ============================================================================
// Statements (Stmt)
// ============================================================================

enum class StmtKind
{
    DeclStmt,
    ExprStmt,
    ReturnStmt,
    IfStmt,
    WhileStmt,
    ForStmt,
    CompoundStmt
};

struct Stmt : ASTNode
{
    StmtKind kind;

    explicit Stmt(StmtKind k) : kind(k) {}
};

/*
DeclStmt: 하나의 선언문을 감싸는 노드

1) 단일 선언: int x = 1;

    DeclStmt
    └── VarDecl(x)

2) 다중 선언: int a = 1, b = 2;

    DeclStmt
    ├── VarDecl("a", IntegerLiteral(1))
    └── VarDecl("b", IntegerLiteral(2))
*/
struct DeclStmt : Stmt
{
    std::vector<Decl> decls;
    DeclStmt() : Stmt(StmtKind::DeclStmt) {}
};

// 추후 다른 문장 구조체들 추가

// ============================================================================
// Expressions (Expr)
// ============================================================================

enum class ExprKind
{
    // literal
    IntegerLiteral,
    DoubleLiteral,
    StringLiteral,
    // non-literal
    DeclRefExpr, // 이미 선언된 변수를 참조 (심볼 테이블에 등록됨)
    UnaryExpr,   // 단항 연산자 (&, *, -)
    BinaryExpr,  // 이항 연산자 (+, -, *, /, ==, <...)
    CallExpr,    // 함수 호출
    ParenExpr,   // 괄호로 묶은 표현식
};

enum class UnaryOp
{
    AddrOf, // &
    Deref,  // *
    Neg,    // -x
    Plus    // +x
};

enum class BinaryOp
{
    Add,      // +
    Sub,      // -
    Mul,      // *
    Div,      // /
    Equal,    // ==
    NotEqual, // !=
    Less,     // <
    Greater,  // >
};

struct Expr : ASTNode
{
    ExprKind kind;

    explicit Expr(ExprKind k) : kind(k) {}
};

// ---------------- literals ----------------

struct IntegerLiteral : Expr
{
    int value;
    IntegerLiteral(int v) : Expr(ExprKind::IntegerLiteral), value(v) {}
};

struct DoubleLiteral : Expr
{
    double value;
    DoubleLiteral(int v) : Expr(ExprKind::DoubleLiteral), value(v) {}
};

struct StringLiteral : Expr
{
    std::string value;
    StringLiteral(const std::string &v) : Expr(ExprKind::StringLiteral), value(v) {}
};

// ---------------- non-literals ----------------

struct DeclRefExpr : Expr
{
    Decl *decl;
    DeclRefExpr(Decl *d) : Expr(ExprKind::DeclRefExpr), decl(d) {}
};

struct UnaryExpr : Expr
{
    UnaryOp op;
    Expr   *operand;

    UnaryExpr(UnaryOp o, Expr *oe) : Expr(ExprKind::UnaryExpr), op(o), operand(oe) {}
};

struct BinaryExpr : Expr
{
    BinaryOp op;
    Expr    *lhs, *rhs;

    BinaryExpr(BinaryOp o, Expr *l, Expr *r) : Expr(ExprKind::BinaryExpr), op(o), lhs(l), rhs(r) {}
};

struct ParenExpr : Expr
{
    Expr *inner;

    ParenExpr(Expr *e) : Expr(ExprKind::ParenExpr), inner(e) {}
};

#endif
