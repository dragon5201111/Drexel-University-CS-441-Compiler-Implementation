#pragma once
#include "Stmnt.h"
#include <memory>
#include <string>
#include <vector>

class MethodDecl;
class ClassDecl;

class ClassVisitor {
public:
    virtual ~ClassVisitor() = default;
    virtual void visit_method_decl(const MethodDecl& decl) = 0;
    virtual void visit_class_decl(const ClassDecl& decl) = 0;
};

class Decl {
public:
    virtual ~Decl() = default;
    virtual void accept(ClassVisitor& visitor) const = 0;
};

class MethodDecl final : public Decl {
public:
    static constexpr int PARAM_MAX = 6;
    std::string name;
    std::vector<std::string> params;
    std::vector<std::string> locals;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit MethodDecl(std::string name, std::vector<std::string> params, std::vector<std::string> locals, std::vector<std::unique_ptr<Stmnt>> body)
        : name(std::move(name)), params(std::move(params)), locals(std::move(locals)), body(std::move(body)) {}

    void accept(ClassVisitor& visitor) const override {
        visitor.visit_method_decl(*this);
    }
};

class ClassDecl final : public Decl {
public:
    std::string name;
    std::vector<std::string> fields;
    std::vector<std::unique_ptr<MethodDecl>> methods;

    explicit ClassDecl(std::string name, std::vector<std::string> fields, std::vector<std::unique_ptr<MethodDecl>> methods)
        : name(std::move(name)), fields(std::move(fields)), methods(std::move(methods)) {}

    void accept(ClassVisitor& visitor) const override {
        visitor.visit_class_decl(*this);
    }
};