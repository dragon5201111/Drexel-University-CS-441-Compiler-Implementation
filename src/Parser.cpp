#include "Parser.h"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <bits/ostream.tcc>

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
    check_token_type(op, TokenType::OPERATOR, "operator");

    std::unique_ptr<Expr> rhs = parse_expr();
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");

    return std::make_unique<BinaryExpr>(std::move(lhs), op.get_value(), std::move(rhs));
}

std::unique_ptr<Expr> Parser::parse_method_call_expr() {
    std::unique_ptr<Expr> base = parse_expr();
    check_token_type(tokenizer.next(), TokenType::DOT, "dot");

    const Token method_name = tokenizer.next();
    check_token_type(method_name, TokenType::IDENTIFIER, "method name");

    check_token_type(tokenizer.next(), TokenType::LEFT_PAREN, "left parenthesis");

    std::vector<std::unique_ptr<Expr>> args;
    if (tokenizer.peek().get_type() != TokenType::RIGHT_PAREN) {
        args.push_back(parse_expr());

        while (tokenizer.peek().get_type() == TokenType::COMMA) {
            tokenizer.next();
            args.push_back(parse_expr());
        }
    }

    // Consume right parenthesis
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");

    return std::make_unique<MethodCallExpr>(std::move(base), method_name.get_value(), std::move(args));
}

std::unique_ptr<Expr> Parser::parse_field_read_expr() {
    std::unique_ptr<Expr> base = parse_expr();

    check_token_type(tokenizer.next(), TokenType::DOT, "dot");

    const Token field_name = tokenizer.next();
    check_token_type(field_name, TokenType::IDENTIFIER, "field name");

    return std::make_unique<FieldReadExpr>(std::move(base), field_name.get_value());
}

std::unique_ptr<Expr> Parser::parse_class_ref_expr() {
    const Token class_name = tokenizer.next();
    check_token_type(class_name, TokenType::IDENTIFIER, "class name");
    return std::make_unique<ClassRefExpr>(class_name.get_value());
}

std::unique_ptr<Stmnt> Parser::parse_stmt() {
    switch (const Token token = tokenizer.next(); token.get_type()) {
        case TokenType::END_OF_FILE: throw std::runtime_error("No expression to parse, end of file.");
        case TokenType::IDENTIFIER: return parse_variable_assign_stmnt(token.get_value());
        case TokenType::NOT: return parse_field_update_stmnt();
        case TokenType::UNDERSCORE: return parse_discard_stmnt();
        case TokenType::PRINT: return parse_print_stmnt();
        case TokenType::IF: return parse_if_stmnt(true);
        case TokenType::IF_ONLY: return parse_if_stmnt(false);
        case TokenType::WHILE: return parse_while_stmnt();
        case TokenType::RETURN: return std::make_unique<ReturnStmnt>(parse_expr());
        default: throw std::runtime_error("Token " + token.to_string() + " is not a valid start of a statement.");
    }
}

std::unique_ptr<Stmnt> Parser::parse_variable_assign_stmnt(const std::string& name) {
    check_token_type(tokenizer.next(), TokenType::ASSIGN, "assign");
    return std::make_unique<VariableAssignStmnt>(name, parse_expr());
}

std::unique_ptr<Stmnt> Parser::parse_field_update_stmnt() {
    std::unique_ptr<Expr> base = parse_expr();
    check_token_type(tokenizer.next(), TokenType::DOT, "dot");

    const Token field_name = tokenizer.next();
    check_token_type(field_name, TokenType::IDENTIFIER, "field name");

    check_token_type(tokenizer.next(), TokenType::ASSIGN, "assign");
    return std::make_unique<FieldUpdateStmnt>(std::move(base), std::move(field_name.get_value()), std::move(parse_expr()));
}

std::unique_ptr<Stmnt> Parser::parse_discard_stmnt() {
    check_token_type(tokenizer.next(), TokenType::ASSIGN, "assign");
    return std::make_unique<DiscardStmnt>(parse_expr());
}

std::unique_ptr<Stmnt> Parser::parse_print_stmnt() {
    check_token_type(tokenizer.next(), TokenType::LEFT_PAREN, "left parenthesis");
    std::unique_ptr<Expr> expr = parse_expr();
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");
    return std::make_unique<PrintStmnt>(std::move(expr));
}

std::unique_ptr<Stmnt> Parser::parse_if_stmnt(const bool has_else_branch) {
    std::unique_ptr<Expr> condition = parse_expr();
    check_token_type(tokenizer.next(), TokenType::COLON, "colon");

    std::vector<std::unique_ptr<Stmnt>> then_branch = parse_branch();


    std::vector<std::unique_ptr<Stmnt>> else_branch;
    if (has_else_branch) {
        check_token_type(tokenizer.next(), TokenType::ELSE, "else");
        else_branch = std::move(parse_branch());
    }

    return std::make_unique<IfStmnt>(std::move(condition), std::move(then_branch), std::move(else_branch));
}

std::unique_ptr<Stmnt> Parser::parse_while_stmnt() {
    std::unique_ptr<Expr> condition = parse_expr();
    check_token_type(tokenizer.next(), TokenType::COLON, "colon");
    return std::make_unique<WhileStmnt>(std::move(condition), std::move(parse_branch()));
}

std::vector<std::unique_ptr<Stmnt>> Parser::parse_branch() {
    check_token_type(tokenizer.next(), TokenType::LEFT_BRACE, "left brace");

    std::vector<std::unique_ptr<Stmnt>> branch = parse_stmts([this] {
        const Token token = tokenizer.peek();
        return token.get_type() != TokenType::RIGHT_BRACE;
    });

    check_token_type(tokenizer.next(), TokenType::RIGHT_BRACE, "right brace");
    return branch;
}

std::unique_ptr<ClassDecl> Parser::parse_class_decl() {
    check_token_type(tokenizer.next(), TokenType::CLASS, "class");

    const Token class_name = tokenizer.next();
    check_token_type(class_name, TokenType::IDENTIFIER, "identifier");

    check_token_type(tokenizer.next(), TokenType::LEFT_BRACKET, "left bracket");
    check_token_type(tokenizer.next(), TokenType::FIELDS, "fields");

    std::vector<std::string> fields = parse_field_decls();
    std::vector<std::unique_ptr<MethodDecl>> methods = parse_method_decls();

    check_token_type(tokenizer.next(), TokenType::RIGHT_BRACKET, "right bracket");
    return std::make_unique<ClassDecl>(std::move(class_name.get_value()), std::move(fields), std::move(methods));
}

std::vector<std::unique_ptr<MethodDecl>> Parser::parse_method_decls() {
    std::cerr << "PARSING METHOD DECLARATIONS NOT IMPLEMENTED." << std::endl;
    return {};
}

std::unique_ptr<MethodDecl> Parser::parse_method_decl() {
    check_token_type(tokenizer.next(), TokenType::METHOD, "method");

    const Token method_name = tokenizer.next();
    check_token_type(method_name, TokenType::IDENTIFIER, "identifier");

    check_token_type(tokenizer.next(), TokenType::LEFT_PAREN, "left parenthesis");
    std::vector<std::string> params = parse_identifiers([this] {
        const Token token = tokenizer.peek();
        return token.get_type() != TokenType::RIGHT_PAREN;
    }, "identifier");

    if (params.size() > MethodDecl::PARAM_MAX) {
        throw std::invalid_argument("Too many arguments, must be in the range 0-6");
    }

    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");
    check_token_type(tokenizer.next(), TokenType::WITH, "with");
    check_token_type(tokenizer.next(), TokenType::LOCALS, "locals");

    std::vector<std::string> locals = parse_identifiers([this] {
        const Token token = tokenizer.peek();
        return token.get_type() != TokenType::COLON;
    }, "identifier");

    check_token_type(tokenizer.next(), TokenType::COLON, "colon");

    std::vector<std::unique_ptr<Stmnt>> stmnts = parse_stmts([this] {
        const Token token = tokenizer.peek();
        return token.get_type() != TokenType::RIGHT_BRACKET && token.get_type() != TokenType::METHOD;
    });

    return std::make_unique<MethodDecl>(std::move(method_name.get_value()), std::move(params), std::move(locals), std::move(stmnts));
}

std::vector<std::string> Parser::parse_field_decls() {
    return parse_identifiers(
        [this] {
            const Token token = tokenizer.peek();
            return token.get_type() != TokenType::METHOD
                && token.get_type() != TokenType::RIGHT_BRACKET;
        },
        "field name"
    );
}

// Helper method to aid with parsing method declarations
std::vector<std::string> Parser::parse_identifiers(
    const std::function<bool()>& should_continue,
    const std::string& what)
{
    std::vector<std::string> identifiers;

    while (should_continue()) {
        Token token = tokenizer.next();
        check_token_type(token, TokenType::IDENTIFIER, what);
        identifiers.push_back(token.get_value());

        if (tokenizer.peek().get_type() == TokenType::COMMA) {
            tokenizer.next();
            check_token_type(tokenizer.peek(), TokenType::IDENTIFIER, "identifier");
        }
    }

    return identifiers;
}

std::vector<std::unique_ptr<Stmnt>> Parser::parse_stmts(
     const std::function<bool()>& should_continue) {
    std::vector<std::unique_ptr<Stmnt>> stmnts;
    while (should_continue()) {
        stmnts.push_back(parse_stmt());
    }

    if (stmnts.empty()) {
        throw std::runtime_error("Expected at least one statement, got none.");
    }
    return stmnts;
}

// Helper method to avoid duplication across parser
void Parser::check_token_type(const Token &token, const TokenType expected, const std::string& expected_message) {
    if (token.get_type() != expected) {
        throw std::runtime_error("Expected " + expected_message + ", got " + token.to_string());
    }
}

