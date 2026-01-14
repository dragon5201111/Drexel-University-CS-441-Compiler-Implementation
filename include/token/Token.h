#pragma once
#include <string>
#include <utility>

#include "TokenType.h"

class Token{
public:
    virtual ~Token() = default;
    virtual TokenType getType() = 0;
};

class Number final : public Token {
public:
    long value;
    explicit Number(const long value) : value(value){}

    TokenType getType() override {
        return TokenType::NUMBER;
    }
};

class LeftParen final : public Token {
public:
    TokenType getType() override {
        return TokenType::LEFT_PAREN;
    }
};

class RightParen final : public Token {
public:
    TokenType getType() override {
        return TokenType::RIGHT_PAREN;
    }
};

class LeftBrace final : public Token {
public:
    TokenType getType() override {
        return TokenType::LEFT_BRACE;
    }
};

class RightBrace final : public Token {
public:
    TokenType getType() override {
        return TokenType::RIGHT_BRACE;
    }
};

class Operator final : public Token {
public:
    char op;
    explicit Operator(const char op) : op(op){}

    TokenType getType() override {
        return TokenType::OPERATOR;
    }
};

class Caret final : public Token {
public:
    TokenType getType() override {
        return TokenType::CARET;
    }
};

class Ampersand final : public Token {
public:
    TokenType getType() override {
        return TokenType::AMPERSAND;
    }
};

class AtSign final : public Token {
public:
    TokenType getType() override {
        return TokenType::AT_SIGN;
    }
};

class Not final : public Token {
public:
    TokenType getType() override {
        return TokenType::NOT;
    }
};

class Dot final : public Token {
public:
    TokenType getType() override {
        return TokenType::DOT;
    }
};

class If final : public Token {
public:
    TokenType getType() override {
        return TokenType::IF;
    }
};

class IfOnly final : public Token {
public:
    TokenType getType() override {
        return TokenType::IF_ONLY;
    }
};

class While final : public Token {
public:
    TokenType getType() override {
        return TokenType::WHILE;
    }
};

class Return final : public Token {
public:
    TokenType getType() override {
        return TokenType::RETURN;
    }
};

class Print final : public Token {
public:
    TokenType getType() override {
        return TokenType::PRINT;
    }
};

class Colon final : public Token {
public:
    TokenType getType() override {
        return TokenType::COLON;
    }
};

class Comma final : public Token {
public:
    TokenType getType() override {
        return TokenType::COMMA;
    }
};

class EndOfFile final : public Token {
public:
    TokenType getType() override {
        return TokenType::END_OF_FILE;
    }
};

class Identifier final : public Token {
public:
    std::string name;
    explicit Identifier(const std::string& name) : name(name){}
    explicit Identifier(std::string&& name) : name(std::move(name)){}

    TokenType getType() override {
        return TokenType::IDENTIFIER;
    }
};

class This final : public Token {
public:
    TokenType getType() override {
        return TokenType::THIS;
    }
};



