#ifndef IF_STMT
#define IF_STMT

#include "statement.h"
#include "expression.h"
#include "statement_block.h"

class If_stmt : public Statement
{
    public:
        If_stmt(Expression *exprP, Statement_block *if_blockP, Statement_block *else_blockP=NULL);
        void execute();
        ~If_stmt() { };
    private:
        Expression *expr;
        Statement_block *if_block;
        Statement_block *else_block;
};
#endif
