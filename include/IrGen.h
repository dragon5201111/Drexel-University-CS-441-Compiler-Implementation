#pragma once
#include "IrValue.h"
#include "Prog.h"
#include "Writer.h"

class IrGenVisitor final :
    public ExprVisitor,
    public StmntVisitor,
    public ClassVisitor,
    public ProgVisitor {

    std::shared_ptr<Writer> writer;
public:
    explicit IrGenVisitor(const std::shared_ptr<Writer>& writer) : writer(writer) {}

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
    void visit_return_stmnt(const ReturnStmnt &stmnt) override;
    void visit_print_stmnt(const PrintStmnt &stmnt) override;
    void visit_field_update_stmnt(const FieldUpdateStmnt &stmnt) override;

    // Class Methods
    void visit_method_decl(const MethodDecl &decl) override;
    void visit_class_decl(const ClassDecl &decl) override;

    //Program Method
    void visit_prog_decl(const ProgDecl &decl) override;

    // Write the IR to writer -- Must be visited by a program declaration beforehand
    void write_ir() const;
};
