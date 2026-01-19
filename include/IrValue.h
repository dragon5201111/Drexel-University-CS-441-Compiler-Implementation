#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Print.h"

class IrValue : public Printable {
public:
    ~IrValue() override = default;
    [[nodiscard]] std::string to_string() const override = 0;
    [[nodiscard]] virtual std::string as_value() const { return to_string(); } // For IrValues that can be represented in two ways
};

class IrVariable final: public IrValue {
    std::string name;
public:
    explicit IrVariable(std::string name) : name(std::move(name)) {}

    [[nodiscard]] std::string to_string() const override {
        return "%" + name;
    }
};

class IrName final: public IrValue {
    std::string name;
public:
    explicit IrName(std::string name) : name(std::move(name)) {}

    [[nodiscard]] std::string to_string() const override {
        return name;
    }
};

class IrConstant final: public IrValue {
    uint32_t value;
public:
    explicit IrConstant(const uint32_t value) : value(value) {}

    [[nodiscard]] std::string to_string() const override {
        return std::to_string(value);
    }
};

class IrGlobalData final: public IrValue {
    std::string name;
    std::vector<std::shared_ptr<IrValue>> values;
public:
    explicit IrGlobalData(std::string name, const std::vector<std::shared_ptr<IrValue>>& values)
        : name(std::move(name)), values(values) {}

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

    [[nodiscard]] std::string as_value() const override {
        return "@" + name;
    }
};