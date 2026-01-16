#pragma once
enum class TokenType {
    // Fixed punctuation
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    CARET,
    AMPERSAND,
    AT_SIGN,
    NOT,
    DOT,
    COLON,
    COMMA,

    // Keywords
    CLASS,
    THIS,
    IF,
    IF_ONLY,
    ELSE,
    WHILE,
    RETURN,
    PRINT,
    END_OF_FILE,
    WITH,
    METHOD,
    LOCALS,
    FIELDS,
    MAIN,

    ASSIGN,
    OPERATOR,
    NUMBER,
    IDENTIFIER,
    UNDERSCORE,
};