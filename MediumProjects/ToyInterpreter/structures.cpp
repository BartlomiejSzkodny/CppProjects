#include <string>
enum class tokenType {
    Semicolon,
    Assign,
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    RoundBracketOpen,
    RoundBracketClose,
    CurlyBracketOpen,
    CurlyBracketClose,
    Equal,
    Modulus,
    String,
    Char,
    Comment,
    If,
    Else,
    While,
    For,
    Boolean,
    LessThan,
    GreaterThan,
    NotEqual,
    LessThanOrEqual,
    GreaterThanOrEqual,
    AND,
    OR,
    Variable,
    Print,
    VariableId,
    Unknown

};



class Token {
public:
    int tokenID;
    tokenType type;
    int lineNumber;
    int columnNumber;
    std::string symbol;
    
    Token() : tokenID(0), type(tokenType::String), lineNumber(0), columnNumber(0), symbol("") {}
    Token(int id, tokenType t, int line, int column, const std::string& sym) : tokenID(id), type(t), lineNumber(line), columnNumber(column), symbol(sym) {}
    std::string tokenTypeToString(){
        switch (type) {
            case tokenType::Semicolon: return "Semicolon";
            case tokenType::Assign: return "Assign";
            case tokenType::Number: return "Number";
            case tokenType::Plus: return "Plus";
            case tokenType::Minus: return "Minus";
            case tokenType::Multiply: return "Multiply";
            case tokenType::Divide: return "Divide";
            case tokenType::RoundBracketOpen: return "RoundBracketOpen";
            case tokenType::RoundBracketClose: return "RoundBracketClose";
            case tokenType::CurlyBracketOpen: return "CurlyBracketOpen";
            case tokenType::CurlyBracketClose: return "CurlyBracketClose";
            case tokenType::Equal: return "Equal";
            case tokenType::Modulus: return "Modulus";
            case tokenType::String: return "String";
            case tokenType::Char: return "Char";
            case tokenType::Comment: return "Comment";
            case tokenType::If: return "If";
            case tokenType::Else: return "Else";
            case tokenType::While: return "While";
            case tokenType::For: return "For";
            case tokenType::Boolean: return "Boolean";
            case tokenType::LessThan: return "LessThan";
            case tokenType::GreaterThan: return "GreaterThan";
            case tokenType::NotEqual: return "NotEqual";
            case tokenType::LessThanOrEqual: return "LessThanOrEqual";
            case tokenType::GreaterThanOrEqual: return "GreaterThanOrEqual";
            case tokenType::AND: return "AND";
            case tokenType::OR: return "OR";
            case tokenType::Variable: return "Variable";
            case tokenType::Print: return "Print";
            case tokenType::VariableId: return "VariableId";
            default: return "Unknown";
        }
    }

};

struct Line {
    public:
        int lineNumber;
        std::string lineContent;
    };