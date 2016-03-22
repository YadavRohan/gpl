#include "symbol.h"

using namespace std;

Symbol :: Symbol(string nameP, int valueP, int sizeP) : name(nameP), size(sizeP)
{
   if(sizeP == 0)
   {
      type = INT;
      m_value = new Symbol_value[1];
      m_value[0].int_value = valueP;
   }
   else
   {
      type = INT_ARRAY;
      m_value = new Symbol_value[sizeP];
      for(int i = 0; i < sizeP; i++)
      {
         m_value[i].int_value = valueP;
      }
   }
}

Symbol :: Symbol(string nameP, double valueP, int sizeP) : name(nameP), size(sizeP)
{
   if(sizeP == 0)
   {
      type = DOUBLE;
      m_value = new Symbol_value[1];
      m_value[0].double_value = valueP;
   }
   else
   {
      type = DOUBLE_ARRAY;
      m_value = new Symbol_value[sizeP];
      for(int i = 0; i < sizeP; i++)
      {
         m_value[i].double_value = valueP;
      }
   }
}

Symbol :: Symbol(string nameP, string valueP, int sizeP) : name(nameP), size(sizeP)
{
   if(sizeP == 0)
   {
      type = STRING;
      m_value = new Symbol_value[1];
      m_value[0].string_value = new string(valueP);
   }
   else
   {
      type = STRING_ARRAY;
      m_value = new Symbol_value[sizeP];

      for(int i = 0; i < sizeP; i++)
      {
         m_value[i].string_value = new string(valueP);
      }
   }
}

void Symbol :: print(std::ostream& os) const
{
   //print the each symbol entry in the format
   //<type>  <name>  =  <value>
   Gpl_type m_type = get_type();
   switch(m_type)
   {
      case INT:
         os << gpl_type_to_base_string(type) << " " <<  name;
         os << " = " << this->get_int_value() << endl;
         break;
      case DOUBLE:
         os << gpl_type_to_base_string(type) << " " <<  name;
         os << " = " << this->get_double_value() << endl;
         break;
      case STRING:
         os << gpl_type_to_base_string(type) << " " <<  name;
         os << " = \"" << this->get_string_value() << "\"" << endl;
         break;
      case INT_ARRAY:
         for(int i = 0; i < this->size; i++)
         {
            os << gpl_type_to_base_string(type) << " " <<  name << "[" << i << "]";
            os << " = " << this->get_int_value(i) << endl;
         }
         break;
      case DOUBLE_ARRAY:
         for(int i = 0; i < this->size; i++)
         {
            os << gpl_type_to_base_string(type) << " " <<  name << "[" << i << "]";
            os << " = " << this->get_double_value(i) << endl;
         }
         break;
      case STRING_ARRAY:
         for(int i = 0; i < this->size; i++)
         {
            os << gpl_type_to_base_string(type) << " " <<  name << "[" << i << "]";
            os << " = \"" << this->get_string_value(i) << "\"" << endl;
         }
         break;
      case ANIMATION_BLOCK:
      case GAME_OBJECT:
      case CIRCLE:
      case RECTANGLE:
      case TRIANGLE:
      case TEXTBOX:
      case PIXMAP:
      case ARRAY:
      case GAME_OBJECT_ARRAY:
      case CIRCLE_ARRAY:
      case RECTANGLE_ARRAY:
      case TRIANGLE_ARRAY:
      case TEXTBOX_ARRAY:
      case PIXMAP_ARRAY:
      case NO_TYPE:
         break;

   }
}

Symbol :: ~Symbol()
{
   //TODO write dtor
   /*
   switch(type)
   {
      case INT:
      case INT_ARRAY:
      {
         int * ptr = (int *)this->value;
         delete []ptr;
      }
      break;
      case DOUBLE:
      case DOUBLE_ARRAY:
      {
         double * ptr = (double *)this->value;
         delete []ptr;
      }
      break;
      case STRING:
      case STRING_ARRAY:
      {
         string * ptr = (string *)this->value;
         delete []ptr;
      }
      break;
      case ANIMATION_BLOCK:
      case GAME_OBJECT:
      case CIRCLE:
      case RECTANGLE:
      case TRIANGLE:
      case TEXTBOX:
      case PIXMAP:
      case ARRAY:
      case GAME_OBJECT_ARRAY:
      case CIRCLE_ARRAY:
      case RECTANGLE_ARRAY:
      case TRIANGLE_ARRAY:
      case TEXTBOX_ARRAY:
      case PIXMAP_ARRAY:
      case NO_TYPE:
         break;
   }
   */
}
