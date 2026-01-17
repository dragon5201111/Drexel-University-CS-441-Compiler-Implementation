#pragma once
#include <string>

class Printable {
public:
    virtual ~Printable() = default;
    [[nodiscard]] virtual std::string to_string() const = 0;
};
