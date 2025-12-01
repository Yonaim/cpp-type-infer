#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cstddef>

enum class TokenType
{
    // 식별자 혹은 키워드
    // 키워드라면 추후 키워드로 분류
    Identifier, // 식별자 (변수명, 함수명)

    // 자료형
    NumberInt,
    NumberDouble,
    StringLiteral,

    // 키워드 (예약어)
    KeywordAuto,
    KeywordInt,
    KeywordDouble,
    KeywordString,

    // 연산자
    Ampersand, // &
    Asterisk,  // *
    Plus,      // +
    Minus,     // -
    Slash,     // /
    Equal,     // =

    // 구분자 (Delimiter)
    LParen,    // (
    RParen,    // )
    Semicolon, // ;

    // EOF
    EndOfFile
};

struct Token
{
    TokenType   type;
    const char *begin;
    size_t      length;

    Token() : type(TokenType::EndOfFile), begin(nullptr), length(0) {}
    Token(TokenType t, const char *b, size_t len) : type(t), begin(b), length(len) {}

    std::string str() const { return std::string(begin, length); }
};

class Lexer
{
  private:
    const std::string &_src; // 전체 소스 코드
    size_t             _pos; // 현재 위치

  public:
    // 내부 처리 때문에 std::string이어야하므로 C-style 문자열은 받지 않음
    // explicit 키워드로 implicit conversion 방지
    explicit Lexer(const std::string &src) : _src(src), _pos(0) {}

    // consume and return next token
    Token next()
    {
        // TODO
    }

    // view next token (without consuming)
    Token peek() const
    {
        // TODO
    }

  private:
    void  skip_whitespace() {}
    Token make_token(TokenType type, size_t start, size_t end) const
    {
        return Token(type, &_src[start], end - start);
    }

    // 토큰 생성
    // 연산자, 구분자는 간단해서 별도 함수 없음
    // 키워드는 identifier() 내부에서 판단
    Token identifier()
    {
        // TODO
    }
    Token number()
    {
        // TODO
    }
    Token string_literal()
    {
        // TODO
    }

    bool eof() const { return _pos >= _src.size(); }
    char current() const { return eof() ? '\0' : _src[_pos]; }
};

#endif
