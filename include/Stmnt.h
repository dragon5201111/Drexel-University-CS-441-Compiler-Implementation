#pragma once
#include "Expr.h"
#include "Stmnt.h"

class VariableAssignStmnt;
class DiscardStmnt;
class IfStmnt;
class WhileStmnt;
class ReturnStmnt;
class PrintStmnt;
class FieldUpdateStmnt;

class StmntVisitor {
public:
    virtual ~StmntVisitor() = default;
    virtual void visit_variable_assign_stmnt(const VariableAssignStmnt& stmnt) = 0;
    virtual void visit_discard_stmnt(const DiscardStmnt& stmnt) = 0;
    virtual void visit_if_stmnt(const IfStmnt& stmnt) = 0;
    virtual void visit_while_stmnt(const WhileStmnt& stmnt) = 0;
    virtual void visit_return_stmnt(const ReturnStmnt& stmnt) = 0;
    virtual void visit_print_stmnt(const PrintStmnt& stmnt) = 0;
    virtual void visit_field_update_stmnt(const FieldUpdateStmnt& stmnt) = 0;
};

class Stmnt {
public:
    virtual ~Stmnt() = default;
    virtual void accept(StmntVisitor& visitor) const = 0;
};

class VariableAssignStmnt final: public Stmnt {
public:
    std::string name;
    std::unique_ptr<Expr> initializer;

    explicit VariableAssignStmnt(std::string name, std::unique_ptr<Expr> initializer) : name(std::move(name)), initializer(std::move(initializer)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_variable_assign_stmnt(*this);
    }
};

class DiscardStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> expr;

    explicit DiscardStmnt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_discard_stmnt(*this);
    }
};

// Can reuse IfStmnt class for if only, with empty else branch
class IfStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmnt>> then_branch;
    std::vector<std::unique_ptr<Stmnt>> else_branch;

    explicit IfStmnt(std::unique_ptr<Expr> condition,
        std::vector<std::unique_ptr<Stmnt>> then_branch,
        std::vector<std::unique_ptr<Stmnt>> else_branch) :
    condition(std::move(condition)), then_branch(std::move(then_branch)), else_branch(std::move(else_branch)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_if_stmnt(*this);
    }
};

class WhileStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit WhileStmnt(std::unique_ptr<Expr> condition, std::vector<std::unique_ptr<Stmnt>> body) : condition(std::move(condition)), body(std::move(body)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_while_stmnt(*this);
    }
};

class ReturnStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> expr;
    explicit ReturnStmnt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_return_stmnt(*this);
    }
};

class PrintStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> expr;
    explicit PrintStmnt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_print_stmnt(*this);
    }
};

class FieldUpdateStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> base;
    std::string field_name;
    std::unique_ptr<Expr> value;

    explicit FieldUpdateStmnt(std::unique_ptr<Expr> base, std::string field_name, std::unique_ptr<Expr> value) :
        base(std::move(base)), field_name(std::move(field_name)), value(std::move(value)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_field_update_stmnt(*this);
    }
};

