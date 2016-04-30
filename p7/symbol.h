#ifndef SYMBOL_H
#define SYMBOL_H

#include "gpl_type.h"
#include "game_object.h"
#include "rectangle.h"
#include "circle.h"
#include "textbox.h"
#include "triangle.h"
#include "pixmap.h"
#include "animation_block.h"
#include <string>
#include <ostream>
#include <cassert>

//Symbol class will hold entry for simple data types such as int, double, string
//It also holds data for arrays of simple data types.
class Symbol
{
   private:
      Gpl_type type;
      std::string name;
      union Symbol_value
      {
         int int_value;
         double double_value;
         std::string *string_value;
         Game_object *game_value;
         Animation_block *animation_value;
      };

      Symbol_value *m_value;
      int size;

   public:
      Symbol(std::string nameP, int valueP, int sizeP=0);
      Symbol(std::string nameP, double valueP, int sizeP=0);
      Symbol(std::string nameP, std::string valueP, int sizeP=0);
      Symbol(std::string nameP, Game_object *valueP, int sizeP=0, Gpl_type typeP=GAME_OBJECT);
      Symbol(std::string nameP, Gpl_type typeP, int sizeP=0);
      Symbol(std::string nameP, Animation_block *valueP, int sizeP=0);
      ~Symbol();

      void print(std::ostream& os) const;
      
      inline int get_size() const
      {
         return size;
      }
      inline Gpl_type get_type() const
      {
         return type;
      }
      inline Gpl_type get_base_type() 
      {
         Gpl_type temp;
         if( type && ARRAY)
            temp = (Gpl_type) (type ^ ARRAY);
         else
            temp = type;
         return temp;
      }
      inline int get_int_value(int index=0) const
      {
         assert(type == INT || type == INT_ARRAY);
         return m_value[index].int_value;
      }
      inline double get_double_value(int index=0) const
      {
         assert(type == DOUBLE || type == DOUBLE_ARRAY);
         return m_value[index].double_value;
      }
      inline std::string get_string_value(int index=0) const
      {
         assert(type == STRING || type == STRING_ARRAY);
         return *(m_value[index].string_value);
      }
      inline Game_object* get_game_object_value(int index=0)const
      {
          assert(type == GAME_OBJECT || type == GAME_OBJECT_ARRAY);
          return m_value[index].game_value;
      }
      inline bool is_game_object()const
      {
          return (type == GAME_OBJECT || type == GAME_OBJECT_ARRAY) ? true : false;
      }
      inline Animation_block* get_animation_block_value(int index=0)const
      {
          assert(type == ANIMATION_BLOCK);
          return m_value[index].animation_value;
      }
      void set(int valueP, int index=0)
      {
          m_value[index].int_value = valueP;
      }
      void set_double(double valueP, int index=0)
      {
          m_value[index].double_value = valueP;
      }
      void set_string(std::string *valueP, int index=0)
      {
          m_value[index].string_value = valueP;
      }
      void set_animation_block(Animation_block *valueP, int index=0)
      {
          m_value[index].animation_value = valueP;
      }
      std::string getName() 
      { 
          return name; 
      }
      Gpl_type original_type;
};
#endif
