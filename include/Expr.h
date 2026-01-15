#pragma once
#include <string>
#include <vector>
#include <memory>

class BinaryExpr;
class FieldReadExpr;
class VariableExpr;
class MethodCallExpr;
class ThisExpr;
class ClassRefExpr;
class ConstantExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual void visit_binary_expr(const BinaryExpr& expr) = 0;
    virtual void visit_field_read_expr(const FieldReadExpr& expr) = 0;
    virtual void visit_variable_expr(const VariableExpr& expr) = 0;
    virtual void visit_method_call_expr(const MethodCallExpr& expr) = 0;
    virtual void visit_this_expr(const ThisExpr& expr) = 0;
    virtual void visit_class_ref_expr(const ClassRefExpr& expr) = 0;
    virtual void visit_constant_expr(const ConstantExpr& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(ExprVisitor& visitor) const = 0;
};

class BinaryExpr final : public Expr{
public:
    std::unique_ptr<Expr> lhs, rhs;
    std::string op;

    BinaryExpr(std::unique_ptr<Expr> lhs, std::string op,  std::unique_ptr<Expr> rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)), op(std::move(op)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_binary_expr(*this);
    }
};

class FieldReadExpr final : public Expr {
public:
    std::unique_ptr<Expr> base;
    std::string field_name;

    FieldReadExpr(std::unique_ptr<Expr> base, std::string field_name) : base(std::move(base)), field_name(std::move(field_name)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_field_read_expr(*this);
    }
};

class VariableExpr final : public Expr {
public:
    std::string name;

    explicit VariableExpr(std::string name) : name(std::move(name)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_variable_expr(*this);
    }
};

class MethodCallExpr final : public Expr {
public:
    std::unique_ptr<Expr> base;
    std::string method_name;
    std::vector<std::unique_ptr<Expr>> args;

    MethodCallExpr(std::unique_ptr<Expr> base, std::string method_name, std::vector<std::unique_ptr<Expr>> args)
        : base(std::move(base)), method_name(std::move(method_name)), args(std::move(args)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_method_call_expr(*this);
    }
};

class ThisExpr final : public Expr {
public:
    void accept(ExprVisitor& visitor) const override {
        visitor.visit_this_expr(*this);
    }
};

class ClassRefExpr final : public Expr {
public:
    std::string class_name;
    explicit ClassRefExpr(std::string class_name) : class_name(std::move(class_name)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_class_ref_expr(*this);
    }
};

class ConstantExpr final : public Expr {
public:
    uint32_t value;
    explicit ConstantExpr(const uint32_t value) : value(value) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_constant_expr(*this);
    }
};