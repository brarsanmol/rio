#include "Scanner.h"

char Scanner::Peek() {
    return static_cast<char>(this->stream.peek());
}

char Scanner::Next() {
    char character;
    this->stream.get(character);

    if (character == '\n') {
        this->column = 0;
        this->line++;
    } else {
        this->column++;
    }

    return character;
}

void Scanner::Ignore() {
    this->stream.ignore();
}

int Scanner::GetLine() const {
    return this->line;
}

int Scanner::GetColumn() const {
    return this->column;
}

bool Scanner::IsFailed() const {
    return this->stream.fail();
}

bool Scanner::IsEndOfFile() const {
    return this->stream.eof();
}
