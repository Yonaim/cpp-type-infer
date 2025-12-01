#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

enum class TypeKind
{
    Int,
    Double,
    String,
    Pointer,
    Reference,
    Unknown
};

struct Type
{
    TypeKind kind;
    Type    *base;
    // 다른 타입을 베이스로 할 수 있다
    // 예: int 타입의 레퍼런스, float 포인터 타입의 포인터

    Type(TypeKind k, Type *b = nullptr) : kind(k), base(b) {}

    std::string Type::str() const
    {
        switch (kind)
        {
        case TypeKind::Int:
            return "int";
        case TypeKind::Double:
            return "double";
        case TypeKind::String:
            return "string";
        case TypeKind::Pointer:
            return base->str() + "*";
        case TypeKind::Reference:
            return base->str() + "&";
        case TypeKind::Unknown:
        default:
            return "unknown";
        }
    }
};

// built-in global type objects
extern Type TYPE_INT;
extern Type TYPE_INT;
extern Type TYPE_STRING;
extern Type TYPE_UNKNOWN;

#endif
