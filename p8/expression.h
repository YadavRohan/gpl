#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "variable.h"
#include "animation_block.h"
#include "gpl_type.h"
#include <string>

class Expression
{
   private:
      enum Tree_kinds 
      {
         EXPRESSION, 
         CONSTANT, 
         VARIABLE
      };
      union value_type
      {
         int int_value;
         double double_value;
         std::string *string_value;
      };
      Tree_kinds m_kinds;
      Expression *m_lhs;
      Expression *m_rhs;
      Operator_type m_oper;
      Variable *m_var;
      value_type m_value;
      Gpl_type m_type;

   public:
      Expression(int value);
      Expression(double value);
      Expression(std::string value);
      Expression(Expression *m_lhs, Operator_type m_oper, Expression *m_rhs=NULL);
      Expression(Variable *var);
      inline Gpl_type get_type()
      {
         return m_type;
      }

      int eval_int();
      double eval_double();
      std::string eval_string();
      Variable* get_variable()
      {
          return m_var;
      }
      Animation_block* eval_animation_block();
};
#endif
