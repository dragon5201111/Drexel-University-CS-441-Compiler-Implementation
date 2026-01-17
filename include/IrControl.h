#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrValue.h"
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
    std::unique_ptr<IrVariable> var;
    std::string then_block;
    std::string else_block;

    explicit IrCondTransfer(std::unique_ptr<IrVariable> var, std::string then_block, std::string else_block)
        : var(std::move(var)), then_block(std::move(then_block)), else_block(std::move(else_block)) {}

    [[nodiscard]] std::vector<std::string> successors() const override {
        return {then_block, else_block};
    }

    [[nodiscard]] std::string to_string() const override {
        return "if " + var->to_string() + " " + then_block + " " + else_block;
    }
};

class IrReturnTransfer final : public IrControlTransfer {
public:
    std::unique_ptr<IrValue> value;
    explicit IrReturnTransfer(std::unique_ptr<IrValue> value) : value(std::move(value)) {}

    [[nodiscard]] std::vector<std::string> successors() const override {
        return {};
    }

    [[nodiscard]] std::string to_string() const override {
        return "ret " + value->to_string();
    }
};

class IrFailReason : public Printable {
public:
    ~IrFailReason() override = default;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrFailReasonNotAPointer : public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NotAPointer";
    }
};

class IrFailReasonNotANumber : public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NotANumber";
    }
};

class IrFailReasonNoSuchField : public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NoSuchField";
    }
};

class IrFailReasonNoSuchMethod : public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NoSuchMethod";
    }
};

class IrFailTransfer final : public IrControlTransfer {
public:
    std::unique_ptr<IrFailReason> reason;
    explicit IrFailTransfer(std::unique_ptr<IrFailReason> reason) : reason(std::move(reason)) {}

    [[nodiscard]] std::vector<std::string> successors() const override {
        return {};
    }

    [[nodiscard]] std::string to_string() const override {
        return "fail " + reason->to_string();
    }
};