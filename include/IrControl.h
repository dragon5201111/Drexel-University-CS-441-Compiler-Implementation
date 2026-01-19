#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrValue.h"
#include "Print.h"

class IrControlTransfer : public Printable {
public:
    ~IrControlTransfer() override = default;
    [[nodiscard]] virtual std::vector<std::shared_ptr<IrName>> successors() const = 0;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrJumpTransfer final: public IrControlTransfer {
    std::shared_ptr<IrName> target;
public:
    explicit IrJumpTransfer(const std::shared_ptr<IrName>& target) : target(target) {}

   [[nodiscard]] std::vector<std::shared_ptr<IrName>> successors() const override {
        return {target};
    }

    [[nodiscard]] std::string to_string() const override {
        return "jump " + target->to_string();
    }
};

class IrCondTransfer final: public IrControlTransfer {
    std::shared_ptr<IrVariable> var;
    std::shared_ptr<IrName> then_block;
    std::shared_ptr<IrName> else_block;
public:
    explicit IrCondTransfer(const std::shared_ptr<IrVariable>& var, const std::shared_ptr<IrName>& then_block, const std::shared_ptr<IrName>& else_block)
        : var(var), then_block(then_block), else_block(else_block) {}

    [[nodiscard]] std::vector<std::shared_ptr<IrName>> successors() const override {
        return {then_block, else_block};
    }

    [[nodiscard]] std::string to_string() const override {
        return "if " + var->to_string() + " " + then_block->to_string() + " " + else_block->to_string();
    }
};

class IrReturnTransfer final: public IrControlTransfer {
    std::shared_ptr<IrValue> value;
public:
    explicit IrReturnTransfer(const std::shared_ptr<IrValue>& value) : value(value) {}

    [[nodiscard]] std::vector<std::shared_ptr<IrName>> successors() const override {
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

class IrFailReasonNotAPointer final: public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NotAPointer";
    }
};

class IrFailReasonNotANumber final: public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NotANumber";
    }
};

class IrFailReasonNoSuchField final: public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NoSuchField";
    }
};

class IrFailReasonNoSuchMethod final: public IrFailReason {
    [[nodiscard]] std::string to_string() const override {
        return "NoSuchMethod";
    }
};

class IrFailTransfer final: public IrControlTransfer {
    std::unique_ptr<IrFailReason> reason;
public:
    explicit IrFailTransfer(std::unique_ptr<IrFailReason> reason) : reason(std::move(reason)) {}

    [[nodiscard]] std::vector<std::shared_ptr<IrName>> successors() const override {
        return {};
    }

    [[nodiscard]] std::string to_string() const override {
        return "fail " + reason->to_string();
    }
};