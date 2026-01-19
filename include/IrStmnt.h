#pragma once
#include "IrValue.h"
#include "Print.h"


class IrStmnt : public Printable{
public:
    ~IrStmnt() override = default;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrAssignStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrValue> src;
public:
    explicit IrAssignStmnt(const std::shared_ptr<IrVariable>& dest, const std::shared_ptr<IrValue>& src)
        : dest(dest), src(src) {}

    [[nodiscard]] std::string to_string() const override {
        return dest->to_string() + " = " + src->as_value();
    }
};

class IrBinaryOpStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrVariable> lhs;
    std::shared_ptr<IrVariable> rhs;
    std::string op;
public:
    IrBinaryOpStmnt(const std::shared_ptr<IrVariable>& dest,
                    const std::shared_ptr<IrVariable>& lhs,
                    const std::shared_ptr<IrVariable>& rhs,
                    std::string op)
        : dest(dest), lhs(lhs), rhs(rhs), op(std::move(op)) {}

    [[nodiscard]] std::string to_string() const override {
        return dest->to_string() + " = " + lhs->to_string() + " " + op + " " + rhs->to_string();
    }
};

class IrCallStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrVariable> addr;
    std::shared_ptr<IrVariable> receiver;
    std::vector<std::shared_ptr<IrValue>> args;
public:
    IrCallStmnt(const std::shared_ptr<IrVariable>& dest,
                const std::shared_ptr<IrVariable>& addr,
                const std::shared_ptr<IrVariable>& receiver,
                std::vector<std::shared_ptr<IrValue>> args)
        : dest(dest), addr(addr), receiver(receiver), args(std::move(args)) {}

    [[nodiscard]] std::string to_string() const override {
        std::string call = dest->to_string() + " = call(" + addr->to_string() + ", " + receiver->to_string();
        for (auto &arg : args) {
            call += ", " + arg->as_value();
        }
        call += ")";
        return call;
    }
};

class IrPhiStmnt final: public IrStmnt {
public:
};

class IrAllocStmnt final: public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrConstant> size;
public:
    explicit IrAllocStmnt(const std::shared_ptr<IrVariable>& dest, const std::shared_ptr<IrConstant>& size)
        : dest(dest), size(size) {}

    [[nodiscard]] std::string to_string() const override {
        return dest->to_string() + " = alloc(" + size->to_string() + ")";
    }
};

class IrPrintStmnt final : public IrStmnt {
    std::shared_ptr<IrValue> src;
public:
    explicit IrPrintStmnt(const std::shared_ptr<IrValue>& src) : src(src) {}

    [[nodiscard]] std::string to_string() const override {
        return "print(" + src->as_value() + ")";
    }
};

class IrGetElStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrVariable> src;
    std::shared_ptr<IrValue> index;
public:
    IrGetElStmnt(const std::shared_ptr<IrVariable>& dest,
                 const std::shared_ptr<IrVariable>& src,
                 const std::shared_ptr<IrValue>& index)
        : dest(dest), src(src), index(index) {}

    [[nodiscard]] std::string to_string() const override {
        return dest->to_string() + " = getelt(" + src->to_string() + ", " + index->as_value() + ")";
    }
};


class IrSetElStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrValue> index_one;
    std::shared_ptr<IrValue> index_two;
public:
    IrSetElStmnt(const std::shared_ptr<IrVariable>& dest,
                 const std::shared_ptr<IrValue>& index_one,
                 const std::shared_ptr<IrValue>& index_two)
        : dest(dest), index_one(index_one), index_two(index_two) {}

    [[nodiscard]] std::string to_string() const override {
        return "setelt(" + dest->to_string() + ", " + index_one->as_value() + ", " + index_two->as_value() + ")";
    }
};

class IrLoadStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrVariable> src;
public:
    IrLoadStmnt(const std::shared_ptr<IrVariable>& dest, const std::shared_ptr<IrVariable>& src)
        : dest(dest), src(src) {}

    [[nodiscard]] std::string to_string() const override {
        return dest->to_string() + " = load(" + src->to_string() + ")";
    }
};

class IrStoreStmnt final : public IrStmnt {
    std::shared_ptr<IrVariable> base;
    std::shared_ptr<IrValue> value;
public:
    IrStoreStmnt(const std::shared_ptr<IrVariable>& base, const std::shared_ptr<IrValue>& value)
        : base(base), value(value) {}

    [[nodiscard]] std::string to_string() const override {
        return "store(" + base->to_string() + ", " + value->as_value() + ")";
    }
};
