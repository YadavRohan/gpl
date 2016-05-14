#include <iostream>
#include "exit_stmt.h"
using namespace std;

Exit_stmt::Exit_stmt(Expression *exprP, int lineP) : expr(exprP), line(lineP)
{
}

void Exit_stmt::execute()
{
    int value = expr->eval_int();
    cout << "gpl[" << line << "]: exit(" << value << ")" << endl;
    exit(value);
}
