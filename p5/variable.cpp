#include "variable.h"

const int Variable::DEFAULT_INT = 0;
const double Variable::DEFAULT_DOUBLE = 0.0;
const std::string Variable::DEFAULT_STRING = "";

Variable::Variable(Symbol *symP, Expression *exprP) : sym(symP), expr(exprP)
{
}

Gpl_type Variable::get_type()
{
   if(sym)
   {
      return sym->get_type();
   }
   return INT;
}

int Variable::get_int_value()
{
   if(sym)
   {
      return sym->get_int_value();
   }
   return DEFAULT_INT;
}

double Variable::get_double_value()
{
   if(sym)
   {
      return sym->get_double_value();
   }
   return DEFAULT_DOUBLE;
}

std::string Variable::get_string_value()
{
   if(sym)
   {
      return sym->get_string_value();
   }
   return DEFAULT_STRING;
}

