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
      std::string member_var;
      static const int DEFAULT_INT;
      static const double DEFAULT_DOUBLE;
      static const std::string DEFAULT_STRING;
   public:
      Variable(Symbol *symP, Expression *exprP=NULL);
      Variable(Symbol *symP, std::string value);
      Gpl_type get_type();
      int get_int_value(int index=0);
      double get_double_value(int index=0);
      std::string get_string_value(int index=0);
      Animation_block* get_animation_block_value(int index=0);
};
#endif
