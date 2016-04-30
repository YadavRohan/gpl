#include "assignment_stmt.h"
#include "error.h"
#include <sstream>

Assignment_stmt::Assignment_stmt(Expression *exprP, Variable *varP, Operator_type op_typeP) :
    expr(exprP), var(varP), op_type(op_typeP)
{
}


void Assignment_stmt::execute()
{
    Gpl_type type = var->get_type();
    if(type == INT_ARRAY || type == DOUBLE_ARRAY || type == STRING_ARRAY)
    {
        //evaluate if the index is out of bound
        int index = (var->expr) ? var->expr->eval_int() : var->index;

        if(index >= var->sym->get_size() || index < 0)
        {
            std::stringstream ss;
            ss << index;
            Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, var->sym->getName(), ss.str());
        }
    }
    switch(op_type)
    {
        case ASSIGN:
        {
            switch(type)
            {
                break;
                case INT:
                case INT_ARRAY:
                {
                    int value = expr->eval_int();
                    var->set_int_value(value);
                }
                break;
                case DOUBLE:
                case DOUBLE_ARRAY:
                {
                    double value = expr->eval_double();
                    var->set_double_value(value);
                }
                break;
                case STRING:
                case STRING_ARRAY:
                {
                    std::string value = expr->eval_string();
                    std::string *s = new std::string(value);
                    var->set_string_value(s);
                }
                break;
                case ANIMATION_BLOCK:
                {
                    Animation_block* value = expr->eval_animation_block();
                    var->set_animation_block_value(value);
                }
                break;
                default:
                assert(false);
            }
        }
        break;
        case PLUS_ASSIGN:
        {
            switch(type)
            {
                case INT:
                case INT_ARRAY:
                {
                    int value = expr->eval_int();
                    int curr_value = var->get_int_value();
                    var->set_int_value(value+curr_value);
                }
                break;
                case DOUBLE:
                case DOUBLE_ARRAY:
                {
                    double value = expr->eval_double();
                    double curr_value = var->get_double_value();
                    var->set_double_value(value+curr_value);
                }
                break;
                case STRING:
                case STRING_ARRAY:
                {
                    std::string value = expr->eval_string();
                    std::string curr_value = var->get_string_value();
                    var->set_string_value(new std::string(curr_value+value));
                }
                break;
                default:
                assert(false);
            }
        }
        break;
        case MINUS_ASSIGN:
        {
            switch(type)
            {
                case INT:
                case INT_ARRAY:
                {
                    int value = expr->eval_int();
                    int curr_value = var->get_int_value();
                    var->set_int_value(curr_value - value);
                }
                break;
                case DOUBLE:
                case DOUBLE_ARRAY:
                {
                    double value = expr->eval_double();
                    double curr_value = var->get_double_value();
                    var->set_double_value(curr_value - value);
                }
                break;
                default:
                {
                    assert(false);
                }
                break;
            }
        }
        break;
        default:
        assert(false);
    }
}
