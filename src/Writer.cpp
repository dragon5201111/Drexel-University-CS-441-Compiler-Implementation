#include "Writer.h"

#include <iostream>

void ConsoleWriter::write(const std::string message) {
    std::cout << message;
}
