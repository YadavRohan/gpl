#include "variable.h"

const int Variable::DEFAULT_INT = 0;
const double Variable::DEFAULT_DOUBLE = 0.0;
const std::string Variable::DEFAULT_STRING = "";

Variable::Variable(Symbol *symP, Expression *exprP) : sym(symP), expr(exprP)
{
}

Variable::Variable(Symbol *symP, std::string valueP) : sym(symP), expr(NULL), member_var(valueP)
{
}



Gpl_type Variable::get_type()
{
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_type();
   }
   else if(sym)
   {
       Gpl_type type;
       Status status = sym->get_game_object_value()->get_member_variable_type(member_var, type);
       if(status == OK)
       {
           return type;
       }
   }
   return INT;
}

int Variable::get_int_value(int index)
{
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_int_value();
   }
   else if(sym)
   {
       int value;
       sym->get_game_object_value(index)->get_member_variable(member_var, value);
       return value;
   }
   return DEFAULT_INT;
}

double Variable::get_double_value(int index)
{
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_double_value();
   }
   else if(sym)
   {
       double value;
       sym->get_game_object_value(index)->get_member_variable(member_var, value);
       return value;
   }
   return DEFAULT_DOUBLE;
}

std::string Variable::get_string_value(int index)
{
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_string_value();
   }
   else if(sym)
   {
       std::string value;
       sym->get_game_object_value(index)->get_member_variable(member_var, value);
       return value;
   }
   return DEFAULT_STRING;
}

Animation_block* Variable::get_animation_block_value(int index)
{
    return sym->get_animation_block_value(index);
}
