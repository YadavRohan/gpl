#include "for_stmt.h"


For_stmt::For_stmt(Expression *exprP, Statement_block *init_blockP, Statement_block *inc_blockP, Statement_block *body_blockP) :
                   expr(exprP), init_block(init_blockP), inc_block(inc_blockP), body_block(body_blockP)
{
}

void For_stmt::execute()
{
    init_block->execute();
    while(expr->eval_int())
    {
        body_block->execute();
        inc_block->execute();
    }
}

