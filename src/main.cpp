#include <fstream>
#include <iostream>
#include <sstream>

#include "Cfg.h"
#include "../include/AstPrinter.h"
#include "Parser.h"
#include "Tokenizer.h"

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
    std::shared_ptr<Writer> writer = std::make_shared<ConsoleWriter>();
    AstPrinter ast_printer(writer);

    std::cout << "===PRINTING AST OF PROGRAM===" << std::endl;
    auto prog_decl = parser.parse_prog_decl();
    prog_decl->accept(ast_printer);
    std::cout <<  "===END AST OF PROGRAM===" << std::endl;
}
