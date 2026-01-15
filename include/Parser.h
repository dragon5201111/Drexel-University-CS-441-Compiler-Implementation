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
public:
    explicit Parser(Tokenizer tokenizer) : tokenizer(std::move(tokenizer)) {}
    std::unique_ptr<Expr> parse_expr();
    std::unique_ptr<Stmnt> parse_stmt();
};
