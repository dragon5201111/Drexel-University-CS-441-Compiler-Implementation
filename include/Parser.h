#pragma once
#include <memory>
#include <utility>

#include "Expr.h"
#include "Stmnt.h"
#include "Tokenizer.h"

class Parser {
    Tokenizer tokenizer;
    std::unique_ptr<Expr> parse_binary_expr();
    std::unique_ptr<Expr> parse_method_call_expr();
    std::unique_ptr<Expr> parse_field_read_expr();
    std::unique_ptr<Expr> parse_class_ref_expr();

    std::unique_ptr<Stmnt> parse_variable_assign_stmnt(const std::string& name);
    std::unique_ptr<Stmnt> parse_discard_stmnt();
    std::unique_ptr<Stmnt> parse_print_stmnt();
    std::unique_ptr<Stmnt> parse_if_stmnt(bool has_else_branch);
    std::unique_ptr<Stmnt> parse_while_stmnt();
    std::vector<std::unique_ptr<Stmnt>> parse_branch();

    static void check_token_type(const Token& token, TokenType expected, const std::string& expected_message) ;
public:
    explicit Parser(Tokenizer tokenizer) : tokenizer(std::move(tokenizer)) {}
    std::unique_ptr<Expr> parse_expr();
    std::unique_ptr<Stmnt> parse_stmt();
};
