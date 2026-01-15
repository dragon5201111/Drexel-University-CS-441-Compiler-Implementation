#include <fstream>
#include <iostream>
#include <sstream>

#include "AstPrinter.h"
#include "Parser.h"
#include "Tokenizer.h"
#include "Stmnt.h"

int main(const int argc, char* argv[]) {
    std::ifstream input("../test/source.441");

    std::stringstream stream;
    stream << input.rdbuf();

    std::string source(stream.str());

    std::cout << "===PRINTING SOURCE===" << std::endl;
    std::cout << source << std::endl;
    std::cout << "===END SOURCE===" << std::endl;

    std::cout << "===PRINTING TOKENS===" << std::endl;
    Tokenizer tokenizer(source);
    for (auto& token : tokenizer.collect()) {
        std::cout << token.to_string() << std::endl;
    }
    std::cout << "===END TOKENS===" << std::endl;

    tokenizer.reset();

    Parser parser(tokenizer);
    AstPrinter astPrinter;
    auto c = parser.parse_class_decl();

}
