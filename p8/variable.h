#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "symbol.h"
#include "gpl_type.h"

class Expression;
class Variable
{
   private:
      static const int DEFAULT_INT;
      static const double DEFAULT_DOUBLE;
      static const std::string DEFAULT_STRING;
   public:
      Variable(Symbol *symP, Expression *exprP=NULL, int index =0 );
      Variable(Symbol *symP, std::string value, int index =0, Expression *expr=NULL);
      Gpl_type get_type();
      int get_int_value(int index=0);
      double get_double_value(int index=0);
      std::string get_string_value(int index=0);
      Animation_block* get_animation_block_value(int index=0);
      Game_object* get_game_object_value(int index=0);
      Symbol* get_symbol() { return sym; };
      void set_int_value(int value, int index=0);
      void set_double_value(double value, int index=0);
      void set_string_value(std::string *value, int index=0);
      void set_animation_block_value(Animation_block *value);
      std::string get_member_var() 
      { 
        if(member_var.length() == 0)
        {
            return sym->getName();
        }
        else
            return member_var;
      }
      Symbol *sym;
      Expression *expr;
      std::string member_var;
      int index;
};
#endif
