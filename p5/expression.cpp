#include "expression.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include "error.h"

using namespace std;

Expression::Expression(int valueP)
{
   m_value.int_value = valueP;
   m_lhs = m_rhs = NULL;
   m_var = NULL;
   m_type = INT;
   m_kinds = CONSTANT;
}

Expression::Expression(double valueP)
{
   m_value.double_value = valueP;
   m_lhs = m_rhs = NULL;
   m_var = NULL;
   m_type = DOUBLE;
   m_kinds = CONSTANT;
}

Expression::Expression(std::string valueP)
{
   m_value.string_value = new string(valueP);
   m_lhs = m_rhs = NULL;
   m_var = NULL;
   m_type = STRING;
   m_kinds = CONSTANT;
}

Expression::Expression(Expression *lhs, Operator_type oper, Expression *rhs)
{
   //m_value = NULL;
   m_lhs = lhs;
   m_rhs = rhs;
   m_oper = oper;
   m_var = NULL;
   if(rhs)  //unary operator
   {
      switch(m_oper)
      {
         case AND:
         case OR:
         case EQUAL:
         case NOT_EQUAL:
         case LESS_THAN:
         case LESS_THAN_EQUAL:
         case GREATER_THAN:
         case GREATER_THAN_EQUAL:
            m_type = INT;
            break;
         default:
            if(lhs->get_type() > rhs->get_type())
               m_type = lhs->get_type();
            else
               m_type = rhs->get_type();
            break;
      }
   }
   else
   {
      switch(m_oper)
      {
         case SIN:
         case COS:
         case TAN:
         case ASIN:
         case ACOS:
         case ATAN:
         case SQRT:
            m_type = DOUBLE;
            break;
         case NOT:
         case RANDOM:
         case FLOOR:
            m_type = INT;
            break;
         /*
         case ABS:
            m_type = lhs->get_type();
            if(m_type == INT)
            {
               m_type = DOUBLE;
            }
            break;
            */
         default:
            m_type = lhs->get_type();
            break;
      }
   }
   m_kinds = EXPRESSION;
   //cout << "oper = " << oper << " type = " << m_type << endl;
}

Expression::Expression(Variable *var)
{
   m_var = var;
   m_lhs = m_rhs = NULL;
   m_type = var->get_type();
   m_kinds = VARIABLE;
}

int Expression::eval_int()
{
   if(m_kinds == CONSTANT)
   {
      return m_value.int_value;
   }
   else if(m_kinds == EXPRESSION)
   {
      //We do not do eval_data for int here, we do it after we find type of operands and type of operator
      if(m_rhs) //binary operator
      {
         //Decide which type to used based on operator and operands
         Gpl_type type;
         if(m_lhs->get_type() >= m_rhs->get_type())
         {
            type = m_lhs->get_type();
         }
         else
         {
            type = m_rhs->get_type();
         }
         //Now that we have got type call appropriate eval_int/eval_double/eval_string functions
         int val;
         switch(m_oper)
         {
            case PLUS:
            {
               int lval = m_lhs->eval_int();
               int rval = m_rhs->eval_int();
               val = lval + rval;
               break;
            }
            case MINUS:
            {
               int lval = m_lhs->eval_int();
               int rval = m_rhs->eval_int();
               val = lval - rval;
               break;
            }
            case MULTIPLY:
            {
               int lval = m_lhs->eval_int();
               int rval = m_rhs->eval_int();
               val = lval * rval;
               break;
            }
            case DIVIDE:
            {
               int lval = m_lhs->eval_int();
               int rval = m_rhs->eval_int();
               if(rval == 0)
               {
                  Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
                  val = 0;
               }
               else
                  val = (int)lval/rval;
               break;
            }
            case MOD:
            {
               int lval = m_lhs->eval_int();
               int rval = m_rhs->eval_int();
               if(rval == 0)
               {
                  Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
                  val = 0;
               }
               else
                  val = lval % rval;
               break;
            }
            case AND:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = lval && rval;
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = lval && rval;
               }
               else 
               {
                  assert(false);
               }
               break;
            }
            case OR:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = lval || rval;
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = lval || rval;
               }
               else 
               {
                  assert(false);
               }
               break;
            }
            case EQUAL:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = (lval == rval);
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = (lval == rval);
               }
               else if (type == STRING)
               {
                  string lval = m_lhs->eval_string();
                  string rval = m_rhs->eval_string();
                  val = (lval == rval);
               }
               break;
            }
            case NOT_EQUAL:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = (lval != rval);
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = (lval != rval);
               }
               else if (type == STRING)
               {
                  string lval = m_lhs->eval_string();
                  string rval = m_rhs->eval_string();
                  val = (lval != rval);
               }
               break;
            }
            case LESS_THAN:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = (lval < rval);
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = (lval < rval);
               }
               else  if(type == STRING)
               {
                  string lval = m_lhs->eval_string();
                  string rval = m_rhs->eval_string();
                  val = (lval < rval);
               }
               break;
            }
            case LESS_THAN_EQUAL:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = (lval <= rval);
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = (lval <= rval);
               }
               else 
               {
                  string lval = m_lhs->eval_string();
                  string rval = m_rhs->eval_string();
                  val = (lval <= rval);
               }
               break;
            }
            case GREATER_THAN:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = (lval > rval);
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = (lval > rval);
               }
               else if(type == STRING)
               {
                  string lval = m_lhs->eval_string();
                  string rval = m_rhs->eval_string();
                  val = (lval > rval);
               }
               break;
            }
            case GREATER_THAN_EQUAL:
            {
               if(type == INT)
               {
                  int lval = m_lhs->eval_int();
                  int rval = m_rhs->eval_int();
                  val = (lval >= rval);
               }
               else if (type == DOUBLE)
               {
                  double lval = m_lhs->eval_double();
                  double rval = m_rhs->eval_double();
                  val = (lval >= rval);
               }
               else 
               {
                  string lval = m_lhs->eval_string();
                  string rval = m_rhs->eval_string();
                  val = (lval >= rval);
               }
               break;
            }
            default:
            {
               assert(false);
               break;
            }
         }
         return val;
      }
      else  //unary operator
      {
         int val;
         switch(m_oper)
         {
            case UNARY_MINUS:
               val = -(m_lhs->eval_int());
               break;
            case NOT:
               if(m_lhs->get_type() == DOUBLE)
               {
                  val = !m_lhs->eval_double();
               }
               else
               {
                  val = !(m_lhs->eval_int());
               }
               break;
            case RANDOM:
               val = rand() % (m_lhs->eval_int());
               break;
            case ABS:
               val = abs(m_lhs->eval_int());
               break;
            case SQRT:
               val = sqrt(m_lhs->eval_int());
               break;
            case FLOOR:
               val = floor(m_lhs->eval_double());
               break;
            default:
               assert(false);
               break;
         }
         return val;
      }
   }
   else if(m_kinds == VARIABLE)
   {
      if(m_var)
      {
         int val =  m_var->get_int_value();
         //cout << "Int val for var is " << val << endl;
         return val;
      }
      else
         assert(false);
   }
   else
   {
      assert(false);
   }
   return m_value.int_value;
}

double Expression::eval_double()
{
   if(m_kinds == CONSTANT)
   {
      if(m_type == INT)
      {
         double val = (double)eval_int();
         return val;
      }
      else if(m_type == DOUBLE)
      {
         return m_value.double_value;
      }
      else if(m_type == STRING)
      {
         assert(false);
      }
   }
   else if(m_kinds == EXPRESSION)
   {
      if(m_type == INT)
      {
         return eval_int();
      }
      double lval = m_lhs->eval_double();
      if(m_rhs)  //binary expression
      {
         double rval = m_rhs->eval_double();
         double val;
         switch(m_oper)
         {
            case PLUS:
               val = lval + rval;
               break;
            case MINUS:
               val = lval - rval;
               break;
            case MULTIPLY:
               val = lval * rval;
               break;
            case DIVIDE:
            {
               if(rval == 0)
               {
                  Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
                  val = 0.0;
               }
               else
                  val = lval/rval;
               break;
            }
            default:
               cout << "Operator is " << m_oper << endl;
               assert(false);
               break;
         }
         return val;
      }
      else      //unary expression
      {
         double val;
         switch(m_oper)
         {
            case UNARY_MINUS:
               val = -lval;
               break;
            case NOT:
               val = !lval;
               break;
            case SIN:
               val = sin(lval*M_PI/180);
               break;
            case COS:
               val = cos(lval*M_PI/180);
               break;
            case TAN:
               val = tan(lval*M_PI/180);
               break;
            case ASIN:
               val = asin(lval)*(180/M_PI);
               break;
            case ACOS:
               val = acos(lval)*(180/M_PI);
               break;
            case ATAN:
               val = atan(lval)*(180/M_PI);
               break;
            case SQRT:
               val = sqrt(lval);
               break;
            case FLOOR: 
               val = floor(lval);
               break;
            case ABS:
               val = abs(lval);
               break;
            default:
               assert(false);
               break;
         }
         return val;
      }
   }
   else if(m_kinds == VARIABLE)
   {
      if(m_type == INT || m_var->get_type() == INT_ARRAY)
      {
         double val = (double)eval_int();
         return val;
      }
      else if(m_var && (m_var->get_type() == DOUBLE || m_var->get_type() == DOUBLE_ARRAY) )
      {
         return m_var->get_double_value();
      }
      else if(m_var)
      {
         //cout << "m_var is of type " << m_var->get_type() << endl;
         assert(false);
      }
   }
   else
   {
      assert(false);
   }
   return m_value.double_value;
}

string Expression::eval_string()
{
   stringstream ss;
   if(m_kinds == CONSTANT)
   {
      if(m_type == INT)
      {
         int val = eval_int();
         ss << val;
         return ss.str();
      }
      else if(m_type == DOUBLE)
      {
         double val = eval_double();
         ss << val;
         return ss.str();
      }
      else if(m_type == STRING || m_type == STRING_ARRAY)
      {
         return *(m_value.string_value);
      }
   }
   else if(m_kinds == EXPRESSION)
   {
      stringstream ss;
      if(m_type == INT)
      {
         int val = eval_int();
         ss << val;
         return ss.str();
      }
      else if(m_type == DOUBLE)
      {
         double val = eval_double();
         ss << val;
         return ss.str();
      }
      if(m_oper == PLUS)
      {
         string lval = m_lhs->eval_string();
         string rval = m_rhs->eval_string();
         return lval + rval;
      }
      else
      {
         assert(false);
      }
   }
   else if(m_kinds == VARIABLE)
   {
      stringstream ss;
      if(m_var->get_type() == INT ||
       m_var->get_type() == INT_ARRAY
       )
      {
         int val = eval_int();
         ss << val;
         return ss.str();
      }
      else if(m_var->get_type() == DOUBLE ||
              m_var->get_type() == DOUBLE_ARRAY
             )
      {
         double val = eval_double();
         ss << val;
         return ss.str();
      }
      else if(m_var->get_type() == STRING ||
              m_var->get_type() == STRING_ARRAY
             )
      {
         return m_var->get_string_value();
      }
      else
      {
         assert(false);
      }
   }
   else
   {
      cerr << "Invalid type inside eval_string " << gpl_type_to_string(m_type) << endl;
      assert(false);
   }
   return *(m_value.string_value);
}
