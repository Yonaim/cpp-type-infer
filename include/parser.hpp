#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"
#include <string>
#include <vector>

class Parser
{
  public:
    explicit Parser(Lexer &lex);
    std::vector<Stmt *> parseProgram();

  private:
    // =========== Lexer =============
    Lexer &_lex;
    Token  _cur; // 현재 보고 있는 토큰

    void advance();             // 토큰 하나 소비
    bool match(TokenType type); // 주어진 type이면 소비 후 true

    // ======== Statement Parsing ========

    Stmt *parseStatement();
    Stmt *parseDeclStmt();
    Stmt *parseExprStmt();

    // statement 분기 처리
    bool isTypeSpecifier() const; // 첫 키워드가 타입명(예약어)인지 변수명인지 구분

    // ======== Declaration Parsing ========

    VarDecl *parseVarDecl(const std::string &typeName);

    // ======== Expression Parsing ========
    /*
        대입 연산자(assignment, =) 처리 함수가 별도로 있는 이유:
        다른 연산자들은 left-associative(왼쪽부터 묶어 처리)인데
        '='만은 right-associative(오른쪽부터 묶어 처리)이다.

        ex. 'a = b = c'는,
            'a = (b = c)'와 같이 처리.
    */
    Expr *parseExpression();
    Expr *parsePrimary();
    Expr *parseAssignment();
    Expr *parseUnary();
    Expr *parseBinaryRHS();
    int   getPrecedence() const; // 연산자 우선선위
};

#endif
