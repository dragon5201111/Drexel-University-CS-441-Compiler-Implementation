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
    std::unique_ptr<IrVariable> dest;
    std::unique_ptr<IrValue> src;

    explicit IrAssignStmnt(std::unique_ptr<IrVariable> dest, std::unique_ptr<IrValue> src)
        : dest(std::move(dest)), src(std::move(src)) {}

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