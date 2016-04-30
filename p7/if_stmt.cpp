#include "if_stmt.h"

If_stmt::If_stmt(Expression *exprP, Statement_block *if_blockP,Statement_block *else_blockP) :
    expr(exprP), if_block(if_blockP), else_block(else_blockP)
{
}

void If_stmt::execute()
{
    assert(expr != NULL);
    int value = expr->eval_int();
    if(value)
    {
        if_block->execute();
    }
    else if(else_block != NULL)
    {
        else_block->execute();
    }
}
