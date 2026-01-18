#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrStmnt.h"
#include "IrControl.h"

class BasicBlock : public Printable{
public:
    std::unique_ptr<IrName> name;
    std::vector<std::unique_ptr<IrStmnt>> primitives;
    std::unique_ptr<IrControlTransfer> control;

    [[nodiscard]] std::string to_string() const override {

    }
};
