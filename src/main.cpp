#include <iostream>
#include <bits/ostream.tcc>

#include "Expr.h"
#include "Tokenizer.h"

int main(const int argc, char* argv[]) {
    Tokenizer tokenizer("x==2 , x=2, x != 2");
    for (auto& token : tokenizer.collect()) {
        std::cout << token.to_string() << std::endl;
    }
}
