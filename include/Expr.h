#pragma once
#include <string>
#include <vector>
#include <memory>

class BinaryExpr;
class FieldReadExpr;
class VariableExpr;
class MethodCallExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual void visitBinaryExpr(const BinaryExpr& expr) = 0;
    virtual void visitFieldReadExpr(const FieldReadExpr& expr) = 0;
    virtual void visitVariableExpr(const VariableExpr& expr) = 0;
    virtual void visitMethodCallExpr(const MethodCallExpr& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(ExprVisitor& visitor) const = 0;
};

class BinaryExpr final : public Expr{
public:
    std::unique_ptr<Expr> lhs;
    std::string op;
    std::unique_ptr<Expr> rhs;
    BinaryExpr(std::unique_ptr<Expr> lhs, std::string op,  std::unique_ptr<Expr> rhs)
        : lhs(std::move(lhs)), op(std::move(op)), rhs(std::move(rhs)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visitBinaryExpr(*this);
    }
};

class FieldReadExpr final : public Expr {
public:
    std::unique_ptr<Expr> base;
    std::string field_name;
    FieldReadExpr(std::unique_ptr<Expr> base, std::string field_name) : base(std::move(base)), field_name(std::move(field_name)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visitFieldReadExpr(*this);
    }
};

class VariableExpr final : public Expr {
public:
    std::string name;
    explicit VariableExpr(std::string name) : name(std::move(name)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visitVariableExpr(*this);
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
        visitor.visitMethodCallExpr(*this);
    }
};