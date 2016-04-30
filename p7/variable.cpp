#include "variable.h"
#include "expression.h"

const int Variable::DEFAULT_INT = 0;
const double Variable::DEFAULT_DOUBLE = 0.0;
const std::string Variable::DEFAULT_STRING = "";

Variable::Variable(Symbol *symP, Expression *exprP, int indexP) : sym(symP), expr(exprP), index(indexP)
{
}

Variable::Variable(Symbol *symP, std::string valueP, int indexP, Expression *exprP) : sym(symP), expr(exprP), member_var(valueP), index(indexP)
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
       else
       {
           return sym->get_type();
       }
   }
   return INT;
}

int Variable::get_int_value(int index)
{
   index = (expr) ? (expr->eval_int()) : this->index;
    if(sym && (index >= sym->get_size() || index < 0) )
    {
        index = 0;
    }
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_int_value(index);
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
   index = (expr) ? expr->eval_int() : this->index;
   if(sym && (index >= sym->get_size() || index < 0))
   {
        index = 0;
   }
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_double_value(index);
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
    index = (expr) ? expr->eval_int() : this->index;
   if(sym && (index >= sym->get_size() || index < 0) )
   {
        index = 0;
   }
   if(sym && (sym->get_type() != GAME_OBJECT && sym->get_type() != GAME_OBJECT_ARRAY))
   {
      return sym->get_string_value(index);
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
   index = (expr) ? expr->eval_int() : this->index;
   if(sym && (index >= sym->get_size() || index < 0))
   {
       index = 0;
   }
   return sym->get_animation_block_value(index);
}

void Variable::set_int_value(int value, int index)
{
    index = (expr) ? expr->eval_int() : this->index;
    if(sym && (index >= sym->get_size() || index < 0) )
    {
        index = 0;
    }
    if(sym->get_type() == GAME_OBJECT || sym->get_type() == GAME_OBJECT_ARRAY)
    {
        sym->get_game_object_value(index)->set_member_variable(member_var, value);
    }
    else
    {
        sym->set(value,index);
    }
}

void Variable::set_double_value(double value, int index)
{
    index = (expr) ? expr->eval_int() : this->index;
    if(sym && (index >= sym->get_size() || index < 0) )
    {
        index = 0;
    }
    if(sym->get_type() == GAME_OBJECT || sym->get_type() == GAME_OBJECT_ARRAY)
    {
        sym->get_game_object_value(index)->set_member_variable(member_var, value);
    }
    else
    {
        sym->set_double(value,index);
    }
}

void Variable::set_string_value(std::string *value, int index)
{
    index = (expr) ? expr->eval_int() : this->index;
    if( sym && (index >= sym->get_size() || index < 0))
    {
        index = 0;
    }
    if(sym->get_type() == GAME_OBJECT || sym->get_type() == GAME_OBJECT_ARRAY)
    {
        //sym->get_game_object_value(index)->set_member_variable(member_var, value);
    }
    else
    {
        sym->set_string(value, index);
    }
}

void Variable::set_animation_block_value(Animation_block *value, int index)
{
    index = (expr) ? expr->eval_int() : this->index;
    if( sym && (index >= sym->get_size() || index < 0))
    {
        index = 0;
    }
    sym->set_animation_block(value, index);
}
