#include "symbol.h"

using namespace std;

Symbol :: Symbol(Gpl_type typeP, string nameP, int sizeP) :
     type(typeP), name(nameP), size(sizeP)
{
   setDefaultValue();
}

void Symbol :: setDefaultValue()
{
   switch(this->type)
   {
      case INT:
         this->value = new int[1];
         ((int *)this->value)[0] = 42;
         break;
      case DOUBLE:
         this->value = new double[1];
         ((double *)this->value)[0] = 3.14159;
         break;
      case STRING:
         this->value = new string[1];
         ((string *)this->value)[0] = "Hello world";
         break;
      case INT_ARRAY:
         this->value = new int[this->size];
         for(int i = 0; i < size; i++)
         {
            ((int *)this->value)[i] = 42;
         }
         break;
      case DOUBLE_ARRAY:
         this->value = new double[this->size];
         for(int i = 0; i < size; i++)
         {
            ((double *)this->value)[i] = 3.14159;
         }
         break;
      case STRING_ARRAY:
         this->value = new string[this->size];
         for(int i = 0; i < size; i++)
         {
            ((string  *)this->value)[i] = "Hello world";
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

void Symbol :: print(std::ostream& os) const
{
   //print the each symbol entry in the format
   //<type>  <name>  =  <value>
   switch(this->get_type())
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
}
