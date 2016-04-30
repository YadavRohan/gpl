#ifndef EXIT_STMT_H
#define EXIT_STMT_H

#include "statement.h"
#include "expression.h"

class Exit_stmt : public Statement
{
    public:
        Exit_stmt(Expression *exprP, int lineP);
        void execute();
    private:
        Expression *expr;
        int line;
};

#endif
