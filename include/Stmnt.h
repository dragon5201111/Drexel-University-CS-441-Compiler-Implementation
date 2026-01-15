#pragma once
#include "Expr.h"
#include "Stmnt.h"

class VariableAssignStmnt;
class IfStmnt;
class WhileStmnt;
class StmntVisitor;

class StmntVisitor {
public:
    virtual ~StmntVisitor() = default;
    virtual void visit_variable_assign_stmnt(const VariableAssignStmnt& stmnt) = 0;
    virtual void visit_if_stmnt(const IfStmnt& stmnt) = 0;
    virtual void visit_while_stmnt(const WhileStmnt& stmnt) = 0;
};

class Stmnt {
public:
    virtual ~Stmnt() = default;
    virtual void accept(StmntVisitor& visitor) const = 0;
};

class VariableAssignStmnt: public Stmnt {
public:
    std::string name;
    std::unique_ptr<Expr> initializer;

    explicit VariableAssignStmnt(std::string name, std::unique_ptr<Expr> initializer) : name(std::move(name)), initializer(std::move(initializer)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_variable_assign_stmnt(*this);
    }
};

class IfStmnt: public Stmnt {
public:
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmnt>> then_branch;
    std::vector<std::unique_ptr<Stmnt>> else_branch;

    explicit IfStmnt(std::unique_ptr<Expr> condition,
        std::vector<std::unique_ptr<Stmnt>> then_branch,
        std::vector<std::unique_ptr<Stmnt>> else_branch = {}) :
    condition(std::move(condition)), then_branch(std::move(then_branch)), else_branch(std::move(else_branch)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_if_stmnt(*this);
    }
};

class WhileStmnt: public Stmnt {
public:
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit WhileStmnt(std::unique_ptr<Expr> condition, std::vector<std::unique_ptr<Stmnt>> body) : condition(std::move(condition)), body(std::move(body)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_while_stmnt(*this);
    }
};

