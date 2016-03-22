#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "symbol.h"
#include "gpl_type.h"

class Expression;
class Variable
{
   private:
      Symbol *sym;
      Expression *expr;
      static const int DEFAULT_INT;
      static const double DEFAULT_DOUBLE;
      static const std::string DEFAULT_STRING;
   public:
      Variable(Symbol *symP, Expression *exprP=NULL);
      Gpl_type get_type();
      int get_int_value();
      double get_double_value();
      std::string get_string_value();
};
#endif
