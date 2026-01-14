#pragma once
enum class TokenType {
    // Fixed punctuation
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    CARET,
    AMPERSAND,
    AT_SIGN,
    NOT,
    DOT,
    COLON,
    COMMA,
    // Keywords
    THIS,
    IF,
    IF_ONLY,
    WHILE,
    RETURN,
    PRINT,
    END_OF_FILE,
    // Tokens with data
    OPERATOR,
    NUMBER,
    IDENTIFIER
};