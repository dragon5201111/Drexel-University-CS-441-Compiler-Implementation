#pragma once
#include "Expr.h"
#include "Stmnt.h"

class AstPrinter : public ExprVisitor, public StmntVisitor {
public:
    // Expression methods
    void visit_binary_expr(const BinaryExpr &expr) override;
    void visit_field_read_expr(const FieldReadExpr &expr) override;
    void visit_variable_expr(const VariableExpr &expr) override;
    void visit_method_call_expr(const MethodCallExpr &expr) override;
    void visit_this_expr(const ThisExpr &expr) override;
    void visit_class_ref_expr(const ClassRefExpr &expr) override;
    void visit_constant_expr(const ConstantExpr &expr) override;

    // Statement methods
    void visit_variable_assign_stmnt(const VariableAssignStmnt &stmnt) override;
    void visit_discard_stmnt(const DiscardStmnt &stmnt) override;
    void visit_if_stmnt(const IfStmnt &stmnt) override;
    void visit_while_stmnt(const WhileStmnt &stmnt) override;
    void print_stmnts(const std::vector<std::unique_ptr<Stmnt>>& stmnts);
    void visit_return_stmnt(const ReturnStmnt &stmnt) override;
    void visit_print_stmnt(const PrintStmnt &stmnt) override;
    void visit_field_update_stmnt(const FieldUpdateStmnt &stmnt) override;
};
