#pragma once
#include <string>
#include "Print.h"

class IrControlTransfer : public Printable {
public:
    ~IrControlTransfer() override = default;
    [[nodiscard]] virtual std::vector<std::string> successors() const = 0;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrJumpTransfer final : public IrControlTransfer {
public:
    std::string target;
    explicit IrJumpTransfer(std::string target) : target(std::move(target)) {}

   [[nodiscard]] std::vector<std::string> successors() const override {
        return {target};
    }

    [[nodiscard]] std::string to_string() const override {
        return "jump " + target;
    }
};

class IrCondTransfer final : public IrControlTransfer {
public:
    std::string var;
    std::string then_block;
    std::string else_block;

    explicit IrCondTransfer(std::string var, std::string then_block, std::string else_block)
        : var(std::move(var)), then_block(std::move(then_block)), else_block(std::move(else_block)) {}

    [[nodiscard]] std::vector<std::string> successors() const override {
        return {then_block, else_block};
    }

    [[nodiscard]] std::string to_string() const override {
        return "if " + var + " " + then_block + " " + else_block;
    }
};

class IrReturnTransfer final : public IrControlTransfer {
public:
    std::string value;
    explicit IrReturnTransfer(std::string value) : value(std::move(value)) {}

    [[nodiscard]] std::vector<std::string> successors() const override {
        return {};
    }

    [[nodiscard]] std::string to_string() const override {
        return "ret " + value;
    }
};

class IrFailTransfer final : public IrControlTransfer {
public:
    std::string reason;
    explicit IrFailTransfer(std::string reason) : reason(std::move(reason)) {}

    [[nodiscard]] std::vector<std::string> successors() const override {
        return {};
    }

    [[nodiscard]] std::string to_string() const override {
        return "fail " + reason;
    }
};