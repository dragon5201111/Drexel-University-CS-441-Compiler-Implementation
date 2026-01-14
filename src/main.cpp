#include <iostream>

#include "../include/token/Token.h"

int main(){
    const std::string s = "foo";
    const Identifier ident(s);
    std::cout << ident.name;
}
