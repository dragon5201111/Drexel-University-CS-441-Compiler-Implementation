#pragma once

#include <map>
#include <string>
#include "TokenType.h"

class Token{
    TokenType type;
    std::string value;
public:
    explicit Token (const TokenType type) : type(type) {}
    explicit Token (const TokenType type, std::string value) : type(type), value(std::move(value)) {}

    [[nodiscard]] std::string get_value() const { return value; }
    [[nodiscard]] TokenType get_type() const { return type; }

    [[nodiscard]] std::string to_string() const {
        switch (type) {
            case TokenType::LEFT_PAREN: return "LEFT_PAREN";
            case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
            case TokenType::LEFT_BRACE: return "LEFT_BRACE";
            case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
            case TokenType::CARET: return "CARET";
            case TokenType::AMPERSAND: return "AMPERSAND";
            case TokenType::AT_SIGN: return "AT_SIGN";
            case TokenType::NOT: return "NOT";
            case TokenType::DOT: return "DOT";
            case TokenType::COLON: return "COLON";
            case TokenType::COMMA: return "COMMA";
            case TokenType::THIS: return "THIS";
            case TokenType::IF: return "IF";
            case TokenType::IF_ONLY: return "IF_ONLY";
            case TokenType::WHILE: return "WHILE";
            case TokenType::RETURN: return "RETURN";
            case TokenType::PRINT: return "PRINT";
            case TokenType::END_OF_FILE: return "END_OF_FILE";
            case TokenType::OPERATOR: return "OPERATOR";
            case TokenType::NUMBER: return "NUMBER";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            default: return "UNKNOWN";
        }
    }
};


