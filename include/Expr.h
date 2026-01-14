#pragma once
#include <string>
#include <bits/unique_ptr.h>

class BinaryExpr;

class ExprVisitor {
public:
  virtual ~ExprVisitor() = default;
  virtual void visit(const BinaryExpr& expr) = 0;
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
        visitor.visit(*this);
    }
};