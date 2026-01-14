#include <fstream>
#include <iostream>
#include <sstream>

#include "Expr.h"
#include "Tokenizer.h"

int main(const int argc, char* argv[]) {
    std::ifstream input("../test/source.441");

    std::stringstream s;
    s << input.rdbuf();

    Tokenizer tokenizer(s.str());
    for (auto& token : tokenizer.collect()) {
        std::cout << token.to_string() << std::endl;
    }
}
