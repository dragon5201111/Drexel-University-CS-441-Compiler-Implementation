#include "Tokenizer.h"

#include <stdexcept>

Token Tokenizer::peek() {
    if (!cached.has_value()) {
        cached = advance_current();
    }
    return cached.value();
}

Token Tokenizer::next() {
    if (!cached.has_value()) {
        return advance_current();
    }
    Token temp = cached.value();
    cached.reset();
    return temp;
}

Token Tokenizer::advance_current() {
    while (current < input_size && isspace(input[current])) {
        current++;
    }

    if (current >= input_size) {
        return Token(TokenType::END_OF_FILE);
    }

    switch (const char current_char = input[current]) {
        case '(': current++; return Token(TokenType::LEFT_PAREN);
        case ')': current++; return Token(TokenType::RIGHT_PAREN);
        case '{': current++; return Token(TokenType::LEFT_BRACE);
        case '}': current++; return Token(TokenType::RIGHT_BRACE);
        case '[': current++; return Token(TokenType::LEFT_BRACKET);
        case ']': current++; return Token(TokenType::RIGHT_BRACKET);
        case ':': current++; return Token(TokenType::COLON);
        case '@': current++; return Token(TokenType::AT_SIGN);
        case '^': current++; return Token(TokenType::CARET);
        case '&': current++; return Token(TokenType::AMPERSAND);
        case '.': current++; return Token(TokenType::DOT);
        case ',': current++; return Token(TokenType::COMMA);

        case '+': current++; return Token(TokenType::OPERATOR, "+");
        case '-': current++; return Token(TokenType::OPERATOR, "-");
        case '*': current++; return Token(TokenType::OPERATOR, "*");
        case '/': current++; return Token(TokenType::OPERATOR, "/");
        case '<': current++; return Token(TokenType::OPERATOR, "<");
        case '>': current++; return Token(TokenType::OPERATOR, ">");

        case '!':
            return match('!', "!=");
        case '=':
            return match('=', "==");

        default:
            if (std::isdigit(current_char)) {
                const int sub_start = current++;
                while (current < input_size && std::isdigit(input[current])) {
                    current++;
                }
                return Token(TokenType::NUMBER, input.substr(sub_start, current - sub_start));
            }

            if (std::isalpha(current_char)) {
                const int sub_start = current++;
                while (current < input_size && std::isalnum(input[current])) {
                    current++;
                }

                const std::string fragment = input.substr(sub_start, current - sub_start);
                if (fragment_map.count(fragment)) {
                    return fragment_map.at(fragment);
                }

                return Token(TokenType::IDENTIFIER, fragment);
            }

            throw std::invalid_argument("Unsupported character: " + current_char);
    }
}

Token Tokenizer::match(const char current_char, std::string value) {
    if (input[++current] == '=') {
        current++;
        return Token(TokenType::OPERATOR, std::move(value));
    }
    return Token(TokenType::OPERATOR, std::string(1, current_char));
}



