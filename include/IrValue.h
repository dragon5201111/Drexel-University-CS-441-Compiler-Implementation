#pragma once
#include <cstdint>
#include <string>
#include "Print.h"

class IrValue : public Printable {
public:
    ~IrValue() override = default;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrVariable : public IrValue {
public:
    std::string name;
    explicit IrVariable(std::string name) : name(std::move(name)) {}

    [[nodiscard]] std::string to_string() const override {
        return "%" + name;
    }
};

class IrConstant : public IrValue {
public:
    uint32_t value;
    explicit IrConstant(const uint32_t value) : value(value) {}

    [[nodiscard]] std::string to_string() const override {
        return std::to_string(value);
    }
};