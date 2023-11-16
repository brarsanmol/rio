#ifndef LEXER_H
#define LEXER_H
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Scanner.h"

enum TokenType {
    Identifier,
    Assignment = '=',
    LeftBrace = '{',
    RightBrace = '}',
    LeftParenthesis = '(',
    RightParenthesis = ')',
    LeftSquareBracket = '[',
    RightSquareBracket = ']',
    SemiColon = ';',
    Comma = ',',

    Void,
    Integer,
    String,
    Character,

    If,
    Else,
    While,
    Return,

    IntegerLiteral,
    StringLiteral,
    CharacterLiteral,

    LogicalAnd,
    LogicalOr,

    EqualTo,
    NotEqualTo,
    LessThan,
    GreaterThan,
    LessThanOrEqualTo,
    GreaterThanOrEqualTo,

    Plus = '+',
    Minus = '-',
    Multiplication = '*',
    Division = '/',
    Remainder = '%',

    EndOfFile,
    Invalid
};

static const std::unordered_map<TokenType, std::string> TOKEN_TYPE_TO_STRING_MAP = {
    {Identifier, "Identifier"},
    {Assignment, "Assignment"},
    {LeftBrace, "LeftBrace"},
    {RightBrace, "RightBrace"},
    {LeftParenthesis, "LeftParenthesis"},
    {RightParenthesis, "RightParenthesis"},
    {LeftSquareBracket, "LeftSquareBracket"},
    {RightSquareBracket, "RightSquareBracket"},
    {SemiColon, "SemiColon"},
    {Comma, "Comma"},

    {Void, "Void"},
    {Integer, "Integer"},
    {String, "String"},
    {Character, "Character"},

    {If, "If"},
    {Else, "Else"},
    {While, "While"},
    {Return, "Return"},

    {IntegerLiteral, "IntegerLiteral"},
    {StringLiteral, "StringLiteral"},
    {CharacterLiteral, "CharacterLiteral"},

    {LogicalAnd, "LogicalAnd"},
    {LogicalOr, "LogicalOr"},

    {EqualTo, "EqualTo"},
    {NotEqualTo, "NotEqualTo"},
    {LessThan, "LessThan"},
    {GreaterThan, "GreaterThan"},
    {LessThanOrEqualTo, "LessThanOrEqualTo"},
    {GreaterThanOrEqualTo, "GreaterThanOrEqualTo"},

    {Plus, "Plus"},
    {Minus, "Minus"},
    {Multiplication, "Multiplication"},
    {Division, "Division"},
    {Remainder, "Remainder"},

    {EndOfFile, "EndOfFile"},
    {Invalid, "Invalid"},
};

struct Token {
    TokenType Type;
    std::string Data;
    int Line;
    int Column;
    Token(const TokenType type, std::string data, const int line, const int column) : Type(type), Data(std::move(data)), Line(line), Column(column) {}
    Token(const TokenType type, const int line, const int column) : Type(type), Line(line), Column(column) {}
    Token& operator=(Token&& other) noexcept {
        if (this != &other) {
            this->Type = other.Type;
            this->Data = other.Data;
            this->Line = other.Line;
            this->Column = other.Column;
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& stream, Token const& token) {
        const std::string& type = TOKEN_TYPE_TO_STRING_MAP.at(token.Type);

        stream
        << type
        << (!token.Data.empty() ? '(' + token.Data  + ')' : "")
        << ' ';

        return stream;
    }
};

class Lexer {
private:
    Scanner scanner;
    Token Pass();
    static void Error(const Token& token);
public:
    Token Next();
    explicit Lexer(const std::string& file) : scanner(file) {}
};

#endif //LEXER_H
