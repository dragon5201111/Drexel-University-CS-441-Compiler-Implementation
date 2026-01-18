#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

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

class IrLabel : public IrValue {
public:
    std::string name;
    explicit IrLabel(std::string name) : name(std::move(name)) {}

    [[nodiscard]] std::string to_string() const override {
        return name;
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

class IrGlobalData : public Printable {
public:
    std::string name;
    std::vector<std::unique_ptr<IrValue>> values;

    explicit IrGlobalData(std::string name) : name(std::move(name)) {}

    [[nodiscard]] std::string to_string() const override {
        std::string body = "global array " + name + ": { ";
        const auto num_values = values.size();
        for (auto i = 0; i < num_values; i++) {
            if (i > 0) {
                body += ", ";
            }

            body += values[i]->to_string();
        }
        return body + " }";
    }
};