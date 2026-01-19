#pragma once
#include <memory>
#include <string>
#include <vector>

#include "IrStmnt.h"
#include "IrControl.h"

class BasicBlock final : public Printable {
public:
    std::shared_ptr<IrName> label;
    std::vector<std::shared_ptr<IrVariable>> params;
    std::vector<std::unique_ptr<IrStmnt>> primitives;
    std::unique_ptr<IrControlTransfer> control;

    explicit BasicBlock(std::shared_ptr<IrName> label) : label(std::move(label)) {}

    [[nodiscard]] std::string to_string() const override {
        std::string block = label->to_string();
        if (!params.empty()) {
            block += "(";
            for (size_t i = 0; i < params.size(); ++i) {
                if (i > 0) block += ", ";
                block += params[i]->to_string();
            }
            block += ")";
        }

        block += ":\n";

        for (const auto &stmnt : primitives) {
            block += "  " + stmnt->to_string() + "\n";
        }

        block += "  " + control->to_string() + "\n";
        return block;
    }
};
