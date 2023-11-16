#include <iostream>

#include "Lexer.h"

int main()
{
    Lexer lexer { "./hello.rio" };

    for (Token token = lexer.Next(); token.Type != EndOfFile; token = lexer.Next()) {
         std::cout << token;
    }

    return 0;
}
