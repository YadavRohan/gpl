#ifndef PRINT_STMT_H
#define PRINT_STMT_H

#include "statement.h"
#include "expression.h"

class Print_stmt: public Statement
{
    public:
        Print_stmt(Expression *exprP, int lineP);
        void execute();
    private:
        Expression *expr;
        int line;
};
#endif
