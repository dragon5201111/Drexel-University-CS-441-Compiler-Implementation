#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrStmnt.h"
#include "IrControl.h"

class BasicBlock{
public:
    std::string name;
    std::vector<std::unique_ptr<IrStmnt>> primitives;
    std::unique_ptr<IrControlTransfer> control;
};
