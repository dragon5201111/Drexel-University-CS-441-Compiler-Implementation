#pragma once
#include <utility>

#include "Tokenizer.h"

class Parser {
    Tokenizer tokenizer;
public:
    explicit Parser(Tokenizer tokenizer) : tokenizer(std::move(tokenizer)) {}
};
