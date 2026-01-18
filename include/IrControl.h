#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrValue.h"
#include "Print.h"

class IrControlTransfer : public Printable {
public:
    ~IrControlTransfer() override = default;
    [[nodiscard]] virtual std::vector<std::shared_ptr<IrLabel>> successors() const = 0;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrJumpTransfer final : public IrControlTransfer {
public:
    std::shared_ptr<IrLabel> target;
    explicit IrJumpTransfer(const std::shared_ptr<IrLabel>& target) : target(target) {}

   [[nodiscard]] std::vector<std::shared_ptr<IrLabel>> successors() const override {
        return {target};
    }

    [[nodiscard]] std::string to_string() const override {
        return "jump " + target->to_string();
    }
};

class IrCondTransfer final : public IrControlTransfer {
public:
    std::shared_ptr<IrVariable> var;
    std::shared_ptr<IrLabel> then_block;
    std::shared_ptr<IrLabel> else_block;

    explicit IrCondTransfer(const std::shared_ptr<IrVariable>& var, const std::shared_ptr<IrLabel>& then_block, const std::shared_ptr<IrLabel>& else_block)
        : var(var), then_block(then_block), else_block(else_block) {}

    [[nodiscard]] std::vector<std::shared_ptr<IrLabel>> successors() const override {
        return {then_block, else_block};
    }

    [[nodiscard]] std::string to_string() const override {
        return "if " + var->to_string() + " " + then_block->to_string() + " " + else_block->to_string();
    }
};

class IrReturnTransfer final : public IrControlTransfer {
public:
    std::shared_ptr<IrValue> value;
    explicit IrReturnTransfer(const std::shared_ptr<IrValue>& value) : value(value) {}

    [[nodiscard]] std::vector<std::shared_ptr<IrLabel>> successors() const override {
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

    [[nodiscard]] std::vector<std::shared_ptr<IrLabel>> successors() const override {
        return {};
    }

    [[nodiscard]] std::string to_string() const override {
        return "fail " + reason->to_string();
    }
};