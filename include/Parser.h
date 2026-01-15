#pragma once
#include <memory>
#include <utility>

#include "Expr.h"
#include "Tokenizer.h"

class Parser {
    Tokenizer tokenizer;
public:
    explicit Parser(Tokenizer tokenizer) : tokenizer(std::move(tokenizer)) {}
    std::unique_ptr<Expr> parse_expr();
};
