#pragma once
#include "IrValue.h"
#include "Print.h"


class IrStmnt : public Printable{
public:
    ~IrStmnt() override = default;
    [[nodiscard]] std::string to_string() const override = 0;
};

class IrAssignStmnt final: public IrStmnt {
public:
    std::shared_ptr<IrVariable> dest;
    std::shared_ptr<IrValue> src;

    explicit IrAssignStmnt(const std::shared_ptr<IrVariable>& dest, const std::shared_ptr<IrValue>& src)
        : dest(dest), src(src) {}

    [[nodiscard]] std::string to_string() const override {
        return dest->to_string() + " = " + src->to_string();
    }
};

class IrBinaryOpStmnt final: public IrStmnt {
public:
};

class IrCallStmnt final: public IrStmnt {
public:
};

class IrPhiStmnt final: public IrStmnt {
public:
};

class IrAllocStmnt final: public IrStmnt {
public:
};

class IrPrintStmnt final: public IrStmnt {
public:
};

class IrGetElStmnt final: public IrStmnt {
public:
};

class IrSetElStmnt final: public IrStmnt {
public:
};

class IrLoadStmnt final: public IrStmnt {
public:
};

class IrStoreStmnt final: public IrStmnt {
public:
};