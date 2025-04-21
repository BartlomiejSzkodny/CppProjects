#ifndef TOKEN_H
#define TOKEN_H

#include <string>
enum class tokenType {
    Semicolon,
    Assign,

    Plus,
    Minus,
    Multiply,
    Divide,
    Modulus,
    
    RoundBracketOpen,
    RoundBracketClose,
    CurlyBracketOpen,
    CurlyBracketClose,


    Value,

    Comment,

    If,
    Else,
    While,
    For,

    Comparison,

    AND,
    OR,
    Variable,
    VariableId,
    Print,

    Unknown

};



class Token {
public:
    int tokenID;
    tokenType type;
    int lineNumber;
    int columnNumber;
    std::string symbol;
    
    Token() : tokenID(0), type(tokenType::Unknown), lineNumber(0), columnNumber(0), symbol("") {}
    Token(int id, tokenType t, int line, int column, const std::string& sym) : tokenID(id), type(t), lineNumber(line), columnNumber(column), symbol(sym) {}
    std::string tokenTypeToString(){
        switch (type) {
            case tokenType::Semicolon: return "Semicolon";
            case tokenType::Assign: return "Assign";
            case tokenType::Value: return "Value";
            case tokenType::Plus: return "Plus";
            case tokenType::Minus: return "Minus";
            case tokenType::Multiply: return "Multiply";
            case tokenType::Divide: return "Divide";
            case tokenType::RoundBracketOpen: return "RoundBracketOpen";
            case tokenType::RoundBracketClose: return "RoundBracketClose";
            case tokenType::CurlyBracketOpen: return "CurlyBracketOpen";
            case tokenType::CurlyBracketClose: return "CurlyBracketClose";
            case tokenType::Comparison: return "Comparison";
            case tokenType::Modulus: return "Modulus";
            case tokenType::Comment: return "Comment";
            case tokenType::If: return "If";
            case tokenType::Else: return "Else";
            case tokenType::While: return "While";
            case tokenType::For: return "For";
            case tokenType::AND: return "AND";
            case tokenType::OR: return "OR";
            case tokenType::Variable: return "Variable";
            case tokenType::Print: return "Print";
            case tokenType::VariableId: return "VariableId";
            default: return "Unknown";
        }
    }

};
#endif // TOKEN_H