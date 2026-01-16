#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Class.h"

class ProgDecl;

class ProgVisitor{
public:
    virtual ~ProgVisitor() = default;
    virtual void visit_prog_decl(const ProgDecl& decl) = 0;
};

class ProgDecl final{
public:
    std::vector<std::string> locals;
    std::vector<std::unique_ptr<ClassDecl>> class_decls;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit ProgDecl(std::vector<std::string> locals, std::vector<std::unique_ptr<ClassDecl>> class_decls, std::vector<std::unique_ptr<Stmnt>> body)
        : locals(std::move(locals)), class_decls(std::move(class_decls)), body(std::move(body)) {}

    void accept(ProgVisitor &visitor) const {
        visitor.visit_prog_decl(*this);
    }
};
