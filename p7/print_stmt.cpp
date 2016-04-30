#include "print_stmt.h"
#include <iostream>

using namespace std;

Print_stmt::Print_stmt(Expression *exprP, int lineP) : expr(exprP), line(lineP)
{
}

void Print_stmt::execute()
{
    assert(expr != NULL);
    string result = expr->eval_string();
    cout << "print[" << line << "]: " << result << endl;
}
