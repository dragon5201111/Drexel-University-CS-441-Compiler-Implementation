#pragma once
#include "Expr.h"

class VariableDeclStmnt;

class StmntVisitor {
    virtual ~StmntVisitor() = default;

};

class Stmnt {
public:
    virtual ~Stmnt() = default;
    virtual void accept(StmntVisitor& visitor) const = 0;
};

class VariableDeclStmnt: public Stmnt {

};

