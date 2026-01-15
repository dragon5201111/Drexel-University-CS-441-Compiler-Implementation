#pragma once
#include "Stmnt.h"
#include <memory>
#include <string>
#include <vector>

class MethodDecl {
public:
    std::string name;
    std::vector<std::string> params;
    std::vector<std::string> locals;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit MethodDecl(std::string name, std::vector<std::string> params, std::vector<std::string> locals, std::vector<std::unique_ptr<Stmnt>> body)
        : name(std::move(name)), params(std::move(params)), locals(std::move(locals)), body(std::move(body)) {}

};

class ClassDecl {
public:
    std::string name;
    std::vector<std::string> fields;
    std::vector<std::unique_ptr<MethodDecl>> methods;

    explicit ClassDecl(std::string name, std::vector<std::string> fields, std::vector<std::unique_ptr<MethodDecl>> methods)
        : name(std::move(name)), fields(std::move(fields)), methods(std::move(methods)) {}
};