#include "Parser.h"

#include <stdexcept>

std::unique_ptr<Expr> Parser::parse_expr() {
    switch (const Token token = tokenizer.next(); token.get_type()) {
        case TokenType::END_OF_FILE: throw std::runtime_error("No expression to parse, end of file.");
        case TokenType::NUMBER: return std::make_unique<ConstantExpr>(static_cast<uint32_t>(std::stoul(token.get_value())));
        case TokenType::IDENTIFIER: return std::make_unique<VariableExpr>(token.get_value());
        case TokenType::LEFT_PAREN: return parse_binary_expr();
        case TokenType::CARET: return parse_method_call_expr();
        case TokenType::AMPERSAND: return parse_field_read_expr();
        case TokenType::AT_SIGN: return parse_class_ref_expr();
        case TokenType::THIS: return std::make_unique<ThisExpr>();
        default: throw std::runtime_error("Token " + token.to_string() + " is not a valid start of an expression.");
    }
}

std::unique_ptr<Expr> Parser::parse_binary_expr() {
    std::unique_ptr<Expr> lhs = parse_expr();

    const Token op = tokenizer.next();
    if (op.get_type() != TokenType::OPERATOR) {
        throw std::runtime_error("Expected operator, got " + op.to_string());
    }

    std::unique_ptr<Expr> rhs = parse_expr();
    if (const Token close = tokenizer.next(); close.get_type() != TokenType::RIGHT_PAREN) {
        throw std::runtime_error("Expected right parenthesis, got " + close.to_string());
    }

    return std::make_unique<BinaryExpr>(std::move(lhs), op.get_value(), std::move(rhs));
}

std::unique_ptr<Expr> Parser::parse_method_call_expr() {
    std::unique_ptr<Expr> base = parse_expr();
    if (const Token dot = tokenizer.next(); dot.get_type() != TokenType::DOT) {
        throw std::runtime_error("Expected dot, got " + dot.to_string());
    }

    const Token method_name = tokenizer.next();
    if (method_name.get_type() != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected method name, got " + method_name.to_string());
    }

    if (const Token open = tokenizer.next(); open.get_type() != TokenType::LEFT_PAREN) {
        throw std::runtime_error("Expected left parenthesis, got " + open.to_string());
    }

    std::vector<std::unique_ptr<Expr>> args;
    if (tokenizer.peek().get_type() != TokenType::RIGHT_PAREN) {
        args.push_back(parse_expr());

        while (tokenizer.peek().get_type() == TokenType::COMMA) {
            tokenizer.next();
            args.push_back(parse_expr());
        }
    }

    // Consume right parenthesis
    if (const Token close = tokenizer.next(); close.get_type() != TokenType::RIGHT_PAREN) {
        throw std::runtime_error("Expected right parenthesis, got " + close.to_string());
    }

    return std::make_unique<MethodCallExpr>(std::move(base), method_name.get_value(), std::move(args));
}

std::unique_ptr<Expr> Parser::parse_field_read_expr() {
    std::unique_ptr<Expr> base = parse_expr();
    if (const Token dot = tokenizer.next(); dot.get_type() != TokenType::DOT) {
        throw std::runtime_error("Expected dot, got " + dot.to_string());
    }

    const Token field_name = tokenizer.next();
    if (field_name.get_type() != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected field name, got " + field_name.to_string());
    }

    return std::make_unique<FieldReadExpr>(std::move(base), field_name.get_value());
}

std::unique_ptr<Expr> Parser::parse_class_ref_expr() {
    const Token class_name = tokenizer.next();
    if (class_name.get_type() != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected class name, got " + class_name.to_string());
    }

    return std::make_unique<ClassRefExpr>(class_name.get_value());
}

std::unique_ptr<Stmnt> Parser::parse_stmt() {
    switch (const Token token = tokenizer.next(); token.get_type()) {
        case TokenType::END_OF_FILE: throw std::runtime_error("No expression to parse, end of file.");
        case TokenType::IDENTIFIER: {
        }
        default: throw std::runtime_error("Token " + token.to_string() + " is not a valid start of a statement.");
    }
}

