#include "AstPrinter.h"

#include <iostream>

void AstPrinter::visit_binary_expr(const BinaryExpr &expr) {
    expr.lhs->accept(*this);
    std::cout << expr.op;
    expr.rhs->accept(*this);
}

void AstPrinter::visit_field_read_expr(const FieldReadExpr &expr) {

}

void AstPrinter::visit_variable_expr(const VariableExpr &expr) {
    std::cout << expr.name;
}

void AstPrinter::visit_method_call_expr(const MethodCallExpr &expr) {

}

void AstPrinter::visit_this_expr(const ThisExpr &expr) {

}

void AstPrinter::visit_class_ref_expr(const ClassRefExpr &expr) {

}

void AstPrinter::visit_constant_expr(const ConstantExpr &expr) {
    std::cout << expr.value;
}

void AstPrinter::visit_variable_assign_stmnt(const VariableAssignStmnt &stmnt) {
    std::cout << stmnt.name + "=";
    stmnt.initializer->accept(*this);
}

void AstPrinter::visit_discard_stmnt(const DiscardStmnt &stmnt) {
    std::cout << "Discard stmnt";
    stmnt.expr->accept(*this);
}

void AstPrinter::visit_if_stmnt(const IfStmnt &stmnt) {
    std::cout << "if ";
    stmnt.condition->accept(*this);
    std::cout << ": {";
    for (auto& then_stmnt : stmnt.then_branch) {
        then_stmnt->accept(*this);
    }
    std::cout << "} else {";
    for (auto& else_stmnt : stmnt.else_branch) {
        else_stmnt->accept(*this);
    }
    std::cout << "}";
}

void AstPrinter::visit_while_stmnt(const WhileStmnt &stmnt) {

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

}
