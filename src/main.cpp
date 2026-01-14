
#include <iostream>
#include <bits/ostream.tcc>

#include "Tokenizer.h"

int main() {
    const std::string source = "class A [fields x \n method m() with locals: \n \t return &this.x]";
    Tokenizer tokenizer(source);
    while (tokenizer.peek().get_type() != TokenType::END_OF_FILE) {
        std::cout << tokenizer.peek().to_string() << std::endl;
        tokenizer.next();
    }
}
