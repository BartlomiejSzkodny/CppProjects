#include <string>
enum class tokenType {
    Number,
    Identifier,
    Intiger,
    String,
    Char,
    Float,
    Double,
    Boolean,
    Equal,
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulus,
    ParenthesisOpen,
    ParenthesisClose,
    Semicolon
};



class Token {
public:
    int tokenID;
    tokenType type;
    int lineNumber;
    int columnNumber;
    std::string symbol;
    

};

struct Line {
    public:
        int lineNumber;
        std::string lineContent;
    };