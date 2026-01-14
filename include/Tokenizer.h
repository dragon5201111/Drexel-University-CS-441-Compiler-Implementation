#pragma once

#include <optional>
#include <unordered_map>

#include "./Token.h"

class Tokenizer {
    const std::unordered_map<std::string, Token> fragment_map = {
        {"if", Token(TokenType::IF)},
        {"ifonly", Token(TokenType::IF_ONLY)},
        {"while", Token(TokenType::WHILE)},
        {"return", Token(TokenType::RETURN)},
        {"print", Token(TokenType::PRINT)},
        {"this", Token(TokenType::THIS)},
    };

    std::string input;
    std::string::size_type input_size;

    int current;
    std::optional<Token> cached;

    Token advance_current();
public:
    explicit Tokenizer(std::string input) : input(std::move(input)), input_size(input.size()), current(0) {}

    Token peek();
    Token next();
};
