#include "Cfg.h"

void CfgBuilder::visit_binary_expr(const BinaryExpr &expr) {
    expr.lhs->accept(*this);
    std::shared_ptr<IrValue> lhs = current_expr;

    expr.rhs->accept(*this);
    std::shared_ptr<IrValue> rhs = current_expr;

    std::shared_ptr<IrVariable> dest = fresh_variable();

    auto ir_binary_op_stmnt = std::make_unique<IrBinaryOpStmnt>(dest, lhs, rhs, expr.op);

    current_block->primitives.push_back(std::move(ir_binary_op_stmnt));
    current_expr = dest;
}

void CfgBuilder::visit_field_read_expr(const FieldReadExpr &expr) {

}

void CfgBuilder::visit_variable_expr(const VariableExpr &expr) {

}

void CfgBuilder::visit_method_call_expr(const MethodCallExpr &expr) {

}

void CfgBuilder::visit_this_expr(const ThisExpr &expr) {

}

void CfgBuilder::visit_class_ref_expr(const ClassRefExpr &expr) {

}

void CfgBuilder::visit_constant_expr(const ConstantExpr &expr) {
    current_expr = std::make_shared<IrConstant>(expr.value);
}

void CfgBuilder::visit_variable_assign_stmnt(const VariableAssignStmnt &stmnt) {

}

void CfgBuilder::visit_discard_stmnt(const DiscardStmnt &stmnt) {

}

void CfgBuilder::visit_if_stmnt(const IfStmnt &stmnt) {

}

void CfgBuilder::visit_while_stmnt(const WhileStmnt &stmnt) {

}

void CfgBuilder::visit_return_stmnt(const ReturnStmnt &stmnt) {
    stmnt.expr->accept(*this);
    current_block->control = std::make_unique<IrReturnTransfer>(current_expr);
}

void CfgBuilder::visit_print_stmnt(const PrintStmnt &stmnt) {
    stmnt.expr->accept(*this);
    current_block->primitives.push_back(std::move(std::make_unique<IrPrintStmnt>(current_expr)));
}

void CfgBuilder::visit_field_update_stmnt(const FieldUpdateStmnt &stmnt) {


}

void CfgBuilder::visit_method_decl(const MethodDecl &decl) {

}

void CfgBuilder::visit_class_decl(const ClassDecl &decl) {

}

void CfgBuilder::visit_prog_decl(const ProgDecl &decl) {

}



