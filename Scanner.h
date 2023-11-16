#ifndef SCANNER_H
#define SCANNER_H
#include <fstream>


class Scanner {
private:
    std::ifstream stream;
    int line;
    int column;
public:
    explicit Scanner(const std::string& file) : stream(file), line(0), column(0) {}
    char Next();
    char Peek();
    void Ignore();
    int GetLine() const;
    int GetColumn() const;
    bool IsFailed() const;
    bool IsEndOfFile() const;
};



#endif //SCANNER_H
