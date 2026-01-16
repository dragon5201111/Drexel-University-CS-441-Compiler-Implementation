#include "AstPrinter.h"

#include <iostream>

void AstPrinter::visit_binary_expr(const BinaryExpr &expr) {
    expr.lhs->accept(*this);
    std::cout << expr.op;
    expr.rhs->accept(*this);
}

void AstPrinter::visit_field_read_expr(const FieldReadExpr &expr) {
    std::cout << "&";
    expr.base->accept(*this);
    std::cout << "." + expr.field_name;
}

void AstPrinter::visit_variable_expr(const VariableExpr &expr) {
    std::cout << expr.name;
}

void AstPrinter::visit_method_call_expr(const MethodCallExpr &expr) {
    std::cout << "^";
    expr.base->accept(*this);
    std::cout << "." + expr.method_name + "(";
    for (auto& arg : expr.args) {
        arg->accept(*this);
        std::cout << ",";
    }
    std::cout << ")";
}

void AstPrinter::visit_this_expr(const ThisExpr &expr) {
    std::cout << "this";
}

void AstPrinter::visit_class_ref_expr(const ClassRefExpr &expr) {
    std::cout << "@" + expr.class_name;
}

void AstPrinter::visit_constant_expr(const ConstantExpr &expr) {
    std::cout << expr.value;
}

void AstPrinter::visit_variable_assign_stmnt(const VariableAssignStmnt &stmnt) {
    std::cout << stmnt.name + "=";
    stmnt.initializer->accept(*this);
}

void AstPrinter::visit_discard_stmnt(const DiscardStmnt &stmnt) {
    std::cout << "_ = ";
    stmnt.expr->accept(*this);
}

void AstPrinter::visit_if_stmnt(const IfStmnt &stmnt) {
    std::cout << std::endl;
    std::cout << "if ";
    stmnt.condition->accept(*this);
    std::cout << ": {";
    print_stmnts(stmnt.then_branch);
    std::cout << "} else {";
    print_stmnts(stmnt.else_branch);
    std::cout << "}";
}

void AstPrinter::visit_while_stmnt(const WhileStmnt &stmnt) {
    std::cout << std::endl;
    std::cout << "while ";
    stmnt.condition->accept(*this);
    std::cout << ": {";
    print_stmnts(stmnt.body);
    std::cout << "}";
}

void AstPrinter::print_stmnts(const std::vector<std::unique_ptr<Stmnt>>& stmnts) {
    for (const auto& stmnt : stmnts) {
        stmnt->accept(*this);
        std::cout << ",";
    }
}

void AstPrinter::visit_return_stmnt(const ReturnStmnt &stmnt) {
    std::cout << "return ";
    stmnt.expr->accept(*this);
}

void AstPrinter::visit_print_stmnt(const PrintStmnt &stmnt) {
    std::cout << "print(";
    stmnt.expr->accept(*this);
    std::cout << ")";
}

void AstPrinter::visit_field_update_stmnt(const FieldUpdateStmnt &stmnt) {
    std::cout << "!";
    stmnt.base->accept(*this);
    std::cout << "." + stmnt.field_name + "=";
    stmnt.value->accept(*this);
}

void AstPrinter::visit_method_decl(const MethodDecl &decl) {
    std::cout << "method " + decl.name + "(";
    for (auto& param : decl.params) {
        std::cout << param + ",";
    }
    std::cout << ") with locals ";
    for (auto& local : decl.locals) {
        std::cout << local + ",";
    }
    std::cout << ": ";
    for (auto& stmnt : decl.body) {
        stmnt->accept(*this);
    }
}

void AstPrinter::visit_class_decl(const ClassDecl &decl) {
    std::cout << "class " + decl.name + "[";
    std::cout << "fields ";
    for (auto& field : decl.fields) {
        std::cout << field + ",";
    }
    for (auto& method : decl.methods) {
        std::cout << " ";
        method->accept(*this);
    }
    std::cout << "]";
}


