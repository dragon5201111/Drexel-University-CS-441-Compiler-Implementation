#include "../include/AstPrinter.h"

#include <iostream>

void AstPrinter::visit_binary_expr(const BinaryExpr &expr) {
    expr.lhs->accept(*this);
    writer->write(expr.op);
    expr.rhs->accept(*this);
}

void AstPrinter::visit_field_read_expr(const FieldReadExpr &expr) {
    writer->write("&");
    expr.base->accept(*this);
    writer->write("." + expr.field_name);
}

void AstPrinter::visit_variable_expr(const VariableExpr &expr) {
    writer->write(expr.name);
}

void AstPrinter::visit_method_call_expr(const MethodCallExpr &expr) {
    writer->write("^");
    expr.base->accept(*this);
    writer->write("." + expr.method_name + "(");
    for (auto& arg : expr.args) {
        arg->accept(*this);
        writer->write(",");
    }
    writer->write(")");
}

void AstPrinter::visit_this_expr(const ThisExpr &expr) {
    writer->write("this");
}

void AstPrinter::visit_class_ref_expr(const ClassRefExpr &expr) {
    writer->write("@" + expr.class_name);
}

void AstPrinter::visit_constant_expr(const ConstantExpr &expr) {
    writer->write(std::to_string(expr.value));
}

void AstPrinter::visit_variable_assign_stmnt(const VariableAssignStmnt &stmnt) {
    writer->write(stmnt.name + "=");
    stmnt.initializer->accept(*this);
}

void AstPrinter::visit_discard_stmnt(const DiscardStmnt &stmnt) {
    writer->write("_ = ");
    stmnt.expr->accept(*this);
}

void AstPrinter::visit_if_stmnt(const IfStmnt &stmnt) {
    writer->write("\n");
    writer->write("if ");
    stmnt.condition->accept(*this);
    writer->write(": {");
    print_stmnts(stmnt.then_branch);
    writer->write("} else {");
    print_stmnts(stmnt.else_branch);
    writer->write("}");
}

void AstPrinter::visit_while_stmnt(const WhileStmnt &stmnt) {
    writer->write("\n");
    writer->write("while ");
    stmnt.condition->accept(*this);
    writer->write(": {");
    print_stmnts(stmnt.body);
    writer->write("}");
}

void AstPrinter::print_stmnts(const std::vector<std::unique_ptr<Stmnt>>& stmnts) {
    for (const auto& stmnt : stmnts) {
        stmnt->accept(*this);
        writer->write(",");
    }
}

void AstPrinter::visit_return_stmnt(const ReturnStmnt &stmnt) {
    writer->write("return ");
    stmnt.expr->accept(*this);
}

void AstPrinter::visit_print_stmnt(const PrintStmnt &stmnt) {
    writer->write("print(");
    stmnt.expr->accept(*this);
    writer->write(")");
}

void AstPrinter::visit_field_update_stmnt(const FieldUpdateStmnt &stmnt) {
    writer->write("!");
    stmnt.base->accept(*this);
    writer->write("." + stmnt.field_name + "=");
    stmnt.value->accept(*this);
}

void AstPrinter::visit_method_decl(const MethodDecl &decl) {
    writer->write("method " + decl.name + "(");
    for (auto& param : decl.params) {
        writer->write(param + ",");
    }
    writer->write(") with locals ");
    for (auto& local : decl.locals) {
        writer->write(local + ",");
    }
    writer->write(": \n");
    for (auto& stmnt : decl.body) {
        stmnt->accept(*this);
        writer->write("\n");
    }
}

void AstPrinter::visit_class_decl(const ClassDecl &decl) {
    writer->write("class " + decl.name + "[\n");
    writer->write("fields ");
    for (auto& field : decl.fields) {
        writer->write(field + ",");
    }
    writer->write("\n");
    for (auto& method : decl.methods) {
        writer->write(" ");
        method->accept(*this);
    }
    writer->write("]\n");
}

void AstPrinter::visit_prog_decl(const ProgDecl &decl) {
    for (auto& class_decl : decl.class_decls) {
        class_decl->accept(*this);
        writer->write("\n");
    }
    writer->write("main with ");
    for (auto& local : decl.locals) {
        writer->write(local + ",");
    }
    writer->write(":\n");
    for (auto& stmnt : decl.body) {
        stmnt->accept(*this);
        writer->write("\n");
    }
}


