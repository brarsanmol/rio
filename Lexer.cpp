#include "Lexer.h"

#include <iostream>

Token Lexer::Pass() {
    if (this->scanner.IsFailed()) {
        throw std::runtime_error("File stream failed to open.");
    }

    if (this->scanner.IsEndOfFile())
        return Token{ EndOfFile, this->scanner.GetLine(), this->scanner.GetColumn() };

    this->scanner.Ignore();
    return this->Next();
}

void Lexer::Error(const Token& token) {
    std::cout << "ERROR! " << token.Type << " (" << token.Line << ", " << token.Column << ")";
}

Token Lexer::Next() {
    const char character = this->scanner.Next();
    const int line = this->scanner.GetLine();
    const int column = this->scanner.GetColumn();

    if (this->scanner.IsEndOfFile()) {
        return Token { EndOfFile, line, column };
    }

    if (isspace(character) || iswspace(character)) {
        return this->Next();
    }

    switch (character) {
        case LeftBrace:
            return Token { LeftBrace, line, column };
        case RightBrace:
            return Token { RightBrace, line, column };
        case LeftParenthesis:
            return Token { LeftParenthesis, line, column };
        case RightParenthesis:
            return Token { RightParenthesis, line, column };
        case LeftSquareBracket:
            return Token { LeftSquareBracket, line, column };
        case RightSquareBracket:
            return Token { RightSquareBracket, line, column };
        case SemiColon:
            return Token { SemiColon, line, column };
        case Comma:
            return Token { Comma, line, column };
        case Plus:
            return Token { Plus, line, column };
        case Minus:
            return Token { Minus, line, column };
        case Multiplication:
            return Token { Multiplication, line, column };
        case Division:
            return Token { Division, line, column };
        case Remainder:
            return Token { Remainder, line, column };
        case '&': {
            if (this->scanner.Peek() == '&') {
                this->scanner.Next();
                return Token { LogicalAnd, line, column };
            }
            Error(Token { Invalid, line, column });
        }
        case '|': {
            if (this->scanner.Peek() == '|') {
                this->scanner.Next();
                return Token { LogicalOr, line, column };
            }
            Error(Token { Invalid, line, column });
        }
        case '=': {
            if (this->scanner.Peek() == '=') {
                this->scanner.Next();
                return Token { EqualTo, line, column };
            }
            return Token { Assignment, line, column };
        }
        case '!': {
            if (this->scanner.Peek() == '=') {
                this->scanner.Next();
                return Token { NotEqualTo, line, column };
            }
            Error(Token { Invalid, line, column });
        }
        case '<': {
            if (this->scanner.Peek() == '=') {
                this->scanner.Next();
                return Token { LessThanOrEqualTo, line, column };
            }
            return Token { LessThan, line, column };
        }
        case '>': {
            if (this->scanner.Peek() == '=') {
                this->scanner.Next();
                return Token { GreaterThanOrEqualTo, line, column };
            }
            return Token { GreaterThan, line, column };
        }
        case '\"': {
            char current;
            std::string data;
            while ((current = this->scanner.Next()) != '\"') {
                if (this->scanner.IsEndOfFile())
                    return Token { Invalid, this->scanner.GetLine(), this->scanner.GetColumn() };
                data += current;
            }

            return Token { StringLiteral, data, this->scanner.GetLine(), this->scanner.GetColumn() };
        }
        case '\'': {
            const char data = this->scanner.Next();
            this->scanner.Ignore();
            return Token { CharacterLiteral, std::string { data }, this->scanner.GetLine(), this->scanner.GetColumn() };
        }
        default: {
            if (isalpha(character) || character == '_') {
                std::string data { character };

                while (isalnum(this->scanner.Peek()) || this->scanner.Peek() == '_') {
                    data += this->scanner.Next();
                }

                if (data == "void")
                    return Token { Void, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "int")
                    return Token { Integer, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "str")
                    return Token { String, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "char")
                    return Token { Character, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "if")
                    return Token { If, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "else")
                    return Token { Else, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "while")
                    return Token { While, this->scanner.GetLine(), this->scanner.GetColumn() };
                if (data == "return")
                    return Token { Return, this->scanner.GetLine(), this->scanner.GetColumn() };

                return Token { Identifier, data, this->scanner.GetLine(), this->scanner.GetColumn() };
            }

            if (isdigit(character)) {
                std::string data { character };
                while (isdigit(this->scanner.Peek())) {
                    data += this->scanner.Next();
                }

                return Token { IntegerLiteral, data, this->scanner.GetLine(), this->scanner.GetColumn() };
            }
        }
    }

    Error(Token { Invalid, line, column });
    return Token { Invalid, line, column };
}
