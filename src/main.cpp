#include <fstream>
#include <sstream>

#include "Parser.h"
#include "Tokenizer.h"

int main(const int argc, char* argv[]) {
    std::ifstream input("../test/source.441");

    std::stringstream s;
    s << input.rdbuf();

    Tokenizer tokenizer(s.str());
    Parser parser(tokenizer);
    while (true) {
        auto e = parser.parse_expr();
    }
}
