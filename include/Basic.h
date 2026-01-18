#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrStmnt.h"
#include "IrControl.h"

class BasicBlock final: public Printable{
public:
    std::shared_ptr<IrLabel> label;
    std::vector<std::unique_ptr<IrStmnt>> primitives;
    std::unique_ptr<IrControlTransfer> control;

    explicit BasicBlock(
        std::shared_ptr<IrLabel> label,
        std::vector<std::unique_ptr<IrStmnt>>&& primitives,
        std::unique_ptr<IrControlTransfer> control
    )
    : label(std::move(label)),
      primitives(std::move(primitives)),
      control(std::move(control)) {}

    [[nodiscard]] std::string to_string() const override {
        std::string block = label->to_string() + ":\n";
        for (const auto& stmnt : primitives) {
            block +=  " " + stmnt->to_string() + "\n";
        }
        block += " " + control->to_string() + "\n";
        return block;
    }
};
