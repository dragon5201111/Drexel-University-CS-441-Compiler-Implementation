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

}

void AstPrinter::visit_discard_stmnt(const DiscardStmnt &stmnt) {

}

void AstPrinter::visit_if_stmnt(const IfStmnt &stmnt) {

}

void AstPrinter::visit_while_stmnt(const WhileStmnt &stmnt) {

}

void AstPrinter::visit_return_stmnt(const ReturnStmnt &stmnt) {

}

void AstPrinter::visit_print_stmnt(const PrintStmnt &stmnt) {

}

void AstPrinter::visit_field_update_stmnt(const FieldUpdateStmnt &stmnt) {

}
