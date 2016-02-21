#ifndef SYMBOL_H
#define SYMBOL_H

#include "gpl_type.h"
#include <string>
#include <ostream>
#include <cassert>

class Symbol
{
   private:
      Gpl_type type;
      std::string name;
      void *value;
      int size;

      void setDefaultValue();
   public:
      Symbol(Gpl_type typeP, std::string nameP, int sizeP=0);
      ~Symbol();

      void print(std::ostream& os) const;
      
      inline Gpl_type get_type() const
      {
         return type;
      }
      //TODO need to get base type than actual type
      inline Gpl_type get_base_type() const
      {
         return type;
      }
      inline int get_int_value(int index=0) const
      {
         assert(type == INT || type == INT_ARRAY);
         return ((int*)this->value)[index];
      }
      inline double get_double_value(int index=0) const
      {
         assert(type == DOUBLE || type == DOUBLE_ARRAY);
         return ((double*)this->value)[index];
      }
      inline std::string get_string_value(int index=0) const
      {
         assert(type == STRING || type == STRING_ARRAY);
         return ((std::string*)this->value)[index];
      }
};
#endif
