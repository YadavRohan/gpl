#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "statement.h"
#include "expression.h"
#include "statement_block.h"

class For_stmt : public Statement
{
    public:
        For_stmt(Expression *exprP, Statement_block *init_blockP, Statement_block *inc_blockP, Statement_block *body_blockP);
        void execute();
    private:
        Expression *expr;
        Statement_block *init_block;
        Statement_block *inc_block;
        Statement_block *body_block;
};
#endif
