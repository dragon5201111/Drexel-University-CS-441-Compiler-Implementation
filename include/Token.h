#pragma once

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
        std::string string_rep;
        switch (type) {
            case TokenType::LEFT_PAREN: string_rep = "LEFT_PAREN"; break;
            case TokenType::RIGHT_PAREN: string_rep = "RIGHT_PAREN"; break;
            case TokenType::LEFT_BRACE: string_rep = "LEFT_BRACE"; break;
            case TokenType::RIGHT_BRACE: string_rep = "RIGHT_BRACE"; break;
            case TokenType::LEFT_BRACKET: string_rep = "LEFT_BRACKET"; break;
            case TokenType::RIGHT_BRACKET: string_rep = "RIGHT_BRACKET"; break;
            case TokenType::CARET: string_rep = "CARET"; break;
            case TokenType::AMPERSAND: string_rep = "AMPERSAND"; break;
            case TokenType::AT_SIGN: string_rep = "AT_SIGN"; break;
            case TokenType::NOT: string_rep = "NOT"; break;
            case TokenType::DOT: string_rep = "DOT"; break;
            case TokenType::COLON: string_rep = "COLON"; break;
            case TokenType::COMMA: string_rep = "COMMA"; break;
            case TokenType::CLASS: string_rep = "CLASS"; break;
            case TokenType::WITH: string_rep = "WITH"; break;
            case TokenType::METHOD: string_rep = "METHOD"; break;
            case TokenType::LOCALS: string_rep = "LOCALS"; break;
            case TokenType::FIELDS: string_rep = "FIELDS"; break;
            case TokenType::THIS: string_rep = "THIS"; break;
            case TokenType::IF: string_rep = "IF"; break;
            case TokenType::IF_ONLY: string_rep = "IF_ONLY"; break;
            case TokenType::WHILE: string_rep = "WHILE"; break;
            case TokenType::RETURN: string_rep = "RETURN"; break;
            case TokenType::PRINT: string_rep = "PRINT"; break;
            case TokenType::END_OF_FILE: string_rep = "END_OF_FILE"; break;
            case TokenType::OPERATOR: string_rep = "OPERATOR"; break;
            case TokenType::ASSIGN: string_rep = "ASSIGN"; break;
            case TokenType::NUMBER: string_rep = "NUMBER"; break;
            case TokenType::IDENTIFIER: string_rep = "IDENTIFIER"; break;
            default: string_rep = "UNKNOWN";
        }
        return "TYPE:" + string_rep + " [value=\"" + value + "\"]";
    }
};


