#ifndef ASSIGNMENT_STMT_H
#define ASSIGNMENT_STMT_H

#include "statement.h"
#include "expression.h"
#include "variable.h"
#include "gpl_type.h"

class Assignment_stmt : public Statement
{
    public:
        Assignment_stmt(Expression *exprP, Variable *varP, Operator_type op_typeP);
        void execute();
    private:
        Expression *expr;
        Variable *var;
        Operator_type op_type;
};
#endif
