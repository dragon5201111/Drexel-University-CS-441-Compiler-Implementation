#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "./Token.h"

class Tokenizer {
    const std::unordered_map<std::string, Token> fragment_map = {
        {"if", Token(TokenType::IF)},
        {"ifonly", Token(TokenType::IF_ONLY)},
        {"else", Token(TokenType::ELSE)},
        {"while", Token(TokenType::WHILE)},
        {"return", Token(TokenType::RETURN)},
        {"print", Token(TokenType::PRINT)},
        {"this", Token(TokenType::THIS)},
        {"class", Token(TokenType::CLASS)},
        {"with", Token(TokenType::WITH)},
        {"method", Token(TokenType::METHOD)},
        {"locals", Token(TokenType::LOCALS)},
        {"fields", Token(TokenType::FIELDS)}
    };

    std::string input;
    std::string::size_type input_size;

    int current;
    std::optional<Token> cached;

    Token advance_current();
    Token get_number();
    Token get_identifier();
    Token match_operator(char current_char, std::string value, TokenType default_type);
public:
    explicit Tokenizer(std::string input) {
        this->input = std::move(input);
        input_size = this->input.size();
        current = 0;
    }

    Token peek();
    Token next();
    std::vector<Token> collect();
    void reset();
};
