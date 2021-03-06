/*

   This file contains the input to the bison compiler generator.
   bison will use this file to generate a C/C++ parser.

   The default output file for bison is: y.tab.c

   $ bison record.y    will produce the file y.tab.c

   This grammar describes a language that is a collection of record
   declarations.  Each has a name and zero or more fields.

   record sally
   {
   height = 63;
   weight = 132;
   age = 42;
   }

   record george
   {
   age = 31;
   phone = 5551212;
   }

   This example DOES NOT demonstrate how a real language would
   create records.  It is a contrived and overly simplified 
   example to demonstrate the bison/flex syntax.

 */

%{  // bison syntax to indicate the start of the header
    // the header is copied directly into y.tab.c (the generated parser)

    extern int yylex();               // this lexer function returns next token
    extern int yyerror(const char *); // used to print errors
    extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include "parser.h"
#include <iostream>
#include <sstream>
#include <string>
    using namespace std;

    // bison syntax to indicate the end of the header
    Game_object *cur_object_under_construction = NULL;
    Animation_block* cur_animation_obj = NULL;
    string cur_game_obj_name;
    %} 

    // The union is used to declare the variable yylval which is used to
    // pass data between the flex generated lexer and the bison generated parser, 
    // and to pass values up/down the parse tree.
    // 
    // A union is kind of like a structure or class, but you can only use one 
    // field at a time.  Each line describes one item in the union.  The left hand
    // side is the type, the right hand side is a name for the type.
    // 
    // Unions do not have any error checking.  For example, if you put an int in
    // the following union  (my_union.union_int = 42)  and then attempt to use it
    // as a string (cout << my_union.union_string) you will get garbage.

    // The "%union" is bison syntax
    // The "union_" is my convention to indicate a member of the union 
    //     (it can be hard to tell what is a union field and what is not)
    //
    // In this example, the union only has one member (union_int).  You will
    // be adding a double declaration to the union.

    %union {
        int            union_int;
        std::string    *union_string;  // MUST be a pointer to a string (this sucks!)
        double         union_double;
        Operator_type  union_op_type;
        Expression     *union_expr;
        Variable       *union_var;
    }

//Global variable

// turn on verbose (longer) error messages
// Tokens with a < > after the %token require a type.
// This is the type of the variable the scanner puts into the union.
// Fill in the < > with the appropriate type
//     for example
//     %token <union_int> T_INT_CONSTANT       "int constant"

%error-verbose

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token <uinion_int> T_FORWARD "forward" // value is line number
%token T_INITIALIZATION      "initialization"

%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_ANIMATION           "animation"

%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <uinion_int> T_PRINT  "print" // value is line number
%token <union_int> T_EXIT    "exit" // value is line number

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="

%token T_ASTERISK            "*"
%token T_DIVIDE              "/"
%token T_MOD                 "%"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_FLOOR               "floor"
%token T_ABS                 "abs"
%token T_RANDOM              "random"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="

%token T_AND                 "&&"
%token T_OR                  "||"
%token T_NOT                 "!"

%token T_ON                  "on"
%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"

%token <union_string> T_ID            	 "identifier"
%token <union_int> T_INT_CONSTANT    "int constant"
%token <union_double> T_DOUBLE_CONSTANT "double constant"
%token <union_string> T_STRING_CONSTANT "string constant"

%type <union_expr> optional_initializer
%type <union_expr> expression
%type <union_expr>  primary_expression 
%type <union_var>  variable
%type <union_op_type> math_operator

/*
   %type <union_type>    simple_type 
   %type <union_exp> expression 
 */

// special token that does not match any production
// used for characters that are not part of the language
%token T_ERROR               "error"
// Just like tokens, grammar symbols can be associated with a type
// This allows values to be passed up (and down) the parse tree

//Add precedence
%nonassoc IF_NO_ELSE
%nonassoc T_ELSE

//Operator precedence
%left T_OR
%left T_AND
%left T_EQUAL T_NOT_EQUAL
%left T_LESS T_GREATER T_LESS_EQUAL T_GREATER_EQUAL
%left T_PLUS T_MINUS
%left T_ASTERISK T_DIVIDE T_MOD
%left T_NOT
%nonassoc UNARY_OPS

%type <union_int> simple_type
%type <union_int> object_type


%% // indicates the start of the rules
//---------------------------------------------------------------------
program:
declaration_list block_list
;

//---------------------------------------------------------------------
declaration_list:
declaration_list declaration
| empty
;

//---------------------------------------------------------------------
declaration:
variable_declaration T_SEMIC
| object_declaration T_SEMIC
| forward_declaration T_SEMIC
;

//---------------------------------------------------------------------
variable_declaration:
simple_type  T_ID  optional_initializer
{
    Symbol_table *stb = Symbol_table::instance();
    if(stb->lookup(*$2) != NULL)
    {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
    }
    if($1 == INT)
    {
        int value = 0;
        if($3)
        {
            if($3->get_type() != INT && $3->get_type() != INT_ARRAY)
            {
                //throw an error
                Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,gpl_type_to_string($3->get_type()),*$2, "int");
            }
            else
            {
                value = $3->eval_int();
            }
        }
        stb->insert(*$2, new Symbol(*$2,value));
    }
    else if($1 == DOUBLE)
    {
        double value = 0.0;
        if($3)
        {
            if($3->get_type() != DOUBLE && $3->get_type() != INT &&
                    $3->get_type() != DOUBLE_ARRAY && $3->get_type() != INT_ARRAY
              )
            {
                //throw an error
                Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,gpl_type_to_string($3->get_type()),*$2, "double");
            }
            else
            {
                value = $3->eval_double();
            }
        }
        stb->insert(*$2, new Symbol(*$2, value));
    }
    else if($1 == STRING)
    {
        string value = "";
        if($3)
        {
            if($3->get_type() != STRING && $3->get_type() != DOUBLE && $3->get_type() != INT &&
                    $3->get_type() != STRING_ARRAY && $3->get_type() != DOUBLE_ARRAY && $3->get_type() != INT_ARRAY
              )
            {
                //throw an error
                Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,gpl_type_to_string($3->get_type()),*$2, "string");
            }
            else
            {
                value = $3->eval_string();
            }
        }
        stb->insert(*$2, new Symbol(*$2, value));
    }
}
| simple_type  T_ID  T_LBRACKET expression T_RBRACKET
{
    Symbol_table *stb = Symbol_table::instance();
    if(stb->lookup(*$2) != NULL)
    {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
    }
    Expression *expr = $4;
    int size = 0;
    if(expr->get_type() == INT)
    {
        size = expr->eval_int();
    }
    if(expr->get_type() == DOUBLE || expr->get_type() == STRING || size < 1)
    {
        //throw an error
        stringstream ss;
        if(expr->get_type() == DOUBLE)
        {
            ss << expr->eval_double();
        }
        else if(expr->get_type() == STRING)
        {
            ss << expr->eval_string();
        }
        else
        {
            ss << size;
        }
        Error::error(Error::INVALID_ARRAY_SIZE, *$2, ss.str());
    }
    else
    {
        if($1 == INT)
        {
            stb->insert(*$2, new Symbol(*$2, 0, size));
        }
        else if($1 == DOUBLE)
        {
            stb->insert(*$2, new Symbol(*$2, 0.0, size));
        }
        else if($1 == STRING)
        {
            stb->insert(*$2, new Symbol(*$2, "", size));
        }
    }
}
;

//---------------------------------------------------------------------
simple_type:
T_INT { $$ = INT; }
| T_DOUBLE { $$ = DOUBLE; }
| T_STRING { $$ = STRING; }
;

//---------------------------------------------------------------------
optional_initializer:
T_ASSIGN expression
{
    $$ = $2;
}
| empty
{
    $$ = NULL;
}
;

//---------------------------------------------------------------------
object_declaration:
object_type T_ID
{
    cur_game_obj_name = *$2;
    switch($1)
    {
        case RECTANGLE:
            {
                cur_object_under_construction = new Rectangle();
            }
            break;
        case CIRCLE:
            {
                cur_object_under_construction = new Circle();
            }
            break;
        case TEXTBOX:
            cur_object_under_construction = new Textbox();
            break;
        case TRIANGLE:
            cur_object_under_construction = new Triangle();
            break;
        case PIXMAP:
            cur_object_under_construction = new Pixmap();
            break;
        default:
            break;
    }
}
T_LPAREN parameter_list_or_empty T_RPAREN
{
    int t = $1;
    string s = *$2;
    Symbol_table *stb = Symbol_table::instance();
    if(stb->lookup(*$2) != NULL)
    {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
    }
    Symbol *sym = new Symbol(*$2, cur_object_under_construction, 0);
    stb->insert(*$2, sym);
}
| object_type T_ID T_LBRACKET expression T_RBRACKET
{
    Symbol_table *stb = Symbol_table::instance();
    cur_game_obj_name = *$2;
    if(stb->lookup(*$2) != NULL)
    {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
    }
    Expression *expr = $4;
    int size = 0;
    if(expr->get_type() == INT)
    {
        size = expr->eval_int();
    }
    if(expr->get_type() == DOUBLE || expr->get_type() == STRING || size < 1)
    {
        //throw an error
        stringstream ss;
        if(expr->get_type() == DOUBLE)
        {
            ss << expr->eval_double();
        }
        else if(expr->get_type() == STRING)
        {
            ss << expr->eval_string();
        }
        else
        {
            ss << size;
        }
        Error::error(Error::INVALID_ARRAY_SIZE, *$2, ss.str());
    }
    else
    {
        stb->insert(*$2, new Symbol(*$2, (Gpl_type)$1, size));
    }
}
;

//---------------------------------------------------------------------
object_type:
 T_RECTANGLE { $$ = RECTANGLE; }
| T_CIRCLE { $$ = CIRCLE; }
| T_TEXTBOX { $$ = TEXTBOX; }
| T_TRIANGLE { $$ = TRIANGLE; }
| T_PIXMAP { $$ = PIXMAP; }
;

//---------------------------------------------------------------------
parameter_list_or_empty :
parameter_list
| empty
;

//---------------------------------------------------------------------
parameter_list :
parameter_list T_COMMA parameter
| parameter
;

//---------------------------------------------------------------------
parameter:
T_ID T_ASSIGN expression
{
    string member_name = *$1;
    Expression *expr = $3;
    Gpl_type type = expr->get_type();
    Status status = OK;
    if ((status = cur_object_under_construction->get_member_variable_type(*$1, type)) != Status::OK) 
    {
        Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, cur_object_under_construction->type(), *$1);
    } 
    else 
    {
        switch(type)
        {
            case INT:
                type = expr->get_type();
                if(type == INT)
                {
                    status = cur_object_under_construction->set_member_variable(member_name, expr->eval_int());
                }
                else
                {
                    Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE,cur_game_obj_name, member_name); 
                }
                break;
            case DOUBLE:
                if(expr->get_type() == STRING)
                {
                    Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE,cur_game_obj_name, member_name); 
                }
                else
                {
                    status = cur_object_under_construction->set_member_variable(member_name, expr->eval_double());
                }
                break;
            case STRING:
                status = cur_object_under_construction->set_member_variable(member_name, expr->eval_string());
                break;
            case ANIMATION_BLOCK:
            {
                cur_animation_obj = expr->eval_animation_block();

                if(cur_object_under_construction->type() != cur_animation_obj->get_parameter_symbol()->get_game_object_value()->type())
                {
                    Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, 
                                 cur_game_obj_name, cur_animation_obj->name()
                                );
                }
                else
                {
                    status = cur_object_under_construction->set_member_variable(member_name, cur_animation_obj);
                }
            }
            break;
            default:
                Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, member_name, expr->eval_string()); 
                break;
        }
    }
    /*
    if(status != OK)
    {
        Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, member_name, expr->eval_string());
    }
    */
}
;

//---------------------------------------------------------------------
forward_declaration:
T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
{
    Symbol_table *stb = Symbol_table::instance();
    if(stb->lookup(*$3) != NULL)
    {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3);
    }
    Animation_block *obj = new Animation_block();
    stb->insert(*$3, new Symbol(*$3, obj,0));
    Symbol *sym = stb->lookup(cur_game_obj_name);
    obj->initialize(sym, *$3);
}
;

//---------------------------------------------------------------------
block_list:
block_list block
| empty
;

//---------------------------------------------------------------------
block:
initialization_block
| animation_block
| on_block
;

//---------------------------------------------------------------------
initialization_block:
T_INITIALIZATION statement_block
;

//---------------------------------------------------------------------
animation_block:
T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE { } statement_list T_RBRACE end_of_statement_block
;

//---------------------------------------------------------------------
animation_parameter:
object_type T_ID
{
    Symbol_table *stb = Symbol_table::instance();
    if(stb->lookup(*$2) != NULL)
    {
        Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
    }
    cur_game_obj_name = *$2;
    
    switch($1)
    {
        case RECTANGLE:
            {
                cur_object_under_construction = new Rectangle();
            }
            break;
        case CIRCLE:
            {
                cur_object_under_construction = new Circle();
            }
            break;
        case TEXTBOX:
            cur_object_under_construction = new Textbox();
            break;
        case TRIANGLE:
            cur_object_under_construction = new Circle();
            break;
        case PIXMAP:
            cur_object_under_construction = new Pixmap();
            break;
        default:
            break;
    }
    cur_object_under_construction->never_animate();
    cur_object_under_construction->never_draw();
    stb->insert(*$2, new Symbol(*$2, cur_object_under_construction, 0));
}
;

//---------------------------------------------------------------------
check_animation_parameter:
T_TRIANGLE T_ID
| T_PIXMAP T_ID
| T_CIRCLE T_ID
| T_RECTANGLE T_ID
| T_TEXTBOX T_ID
;

//---------------------------------------------------------------------
on_block:
T_ON keystroke statement_block
;

//---------------------------------------------------------------------
keystroke:
T_SPACE
| T_UPARROW
| T_DOWNARROW
| T_LEFTARROW
| T_RIGHTARROW
| T_LEFTMOUSE_DOWN
| T_MIDDLEMOUSE_DOWN
| T_RIGHTMOUSE_DOWN
| T_LEFTMOUSE_UP
| T_MIDDLEMOUSE_UP
| T_RIGHTMOUSE_UP
| T_MOUSE_MOVE
| T_MOUSE_DRAG
| T_AKEY 
| T_SKEY 
| T_DKEY 
| T_FKEY 
| T_HKEY 
| T_JKEY 
| T_KKEY 
| T_LKEY 
| T_WKEY 
| T_F1
;

//---------------------------------------------------------------------
if_block:
statement_block_creator statement end_of_statement_block
| statement_block
;

//---------------------------------------------------------------------
statement_block:
T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
;

//---------------------------------------------------------------------
statement_block_creator:
// this goes to nothing so that you can put an action here in p7
;

//---------------------------------------------------------------------
end_of_statement_block:
// this goes to nothing so that you can put an action here in p7
;

//---------------------------------------------------------------------
statement_list:
statement_list statement
| empty
;

//---------------------------------------------------------------------
statement:
if_statement
| for_statement
| assign_statement T_SEMIC
| print_statement T_SEMIC
| exit_statement T_SEMIC
;

//---------------------------------------------------------------------
if_statement:
T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
| T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
;

//---------------------------------------------------------------------
for_statement:
T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
;

//---------------------------------------------------------------------
print_statement:
T_PRINT T_LPAREN expression T_RPAREN
;

//---------------------------------------------------------------------
exit_statement:
T_EXIT T_LPAREN expression T_RPAREN
;

//---------------------------------------------------------------------
assign_statement:
variable T_ASSIGN expression
| variable T_PLUS_ASSIGN expression
| variable T_MINUS_ASSIGN expression
;

//---------------------------------------------------------------------
variable:
T_ID
{
    Symbol *sym = Symbol_table::instance()->lookup(*$1);
    if(sym == NULL)
    {
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
    }
    $$ = new Variable(sym);
}
| T_ID T_LBRACKET expression T_RBRACKET
{
    Expression *expr = $3;
    Symbol *sym = Symbol_table::instance()->lookup(*$1);
    if(expr->get_type() != INT)
    {
        if(expr->get_type() == DOUBLE)
        {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A double expression");
        }
        else if(expr->get_type() == STRING)
        {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A string expression");
        }
    }
    else
    {
        if(!sym)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
        }
        if(sym->get_type() != INT_ARRAY &&
                sym->get_type() != DOUBLE_ARRAY &&
                sym->get_type() != STRING_ARRAY
          )
        {
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
        }
        else
        {
            int index = expr->eval_int();
            if(sym && (index < 0 || index >= sym->get_size()) )
            {
                stringstream ss;
                ss << index;
                Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, *$1, ss.str());
            }
        }

    }
    $$ = new Variable(sym,$3);
}
| T_ID T_PERIOD T_ID
{
    Symbol_table *stb = Symbol_table::instance();
    Symbol *sym = stb->lookup(*$1);
    if (sym == NULL) 
    {
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
    } 
    else if (sym->get_type() != GAME_OBJECT) 
    {
        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
    } 
    else if (sym->get_type() == GAME_OBJECT) 
    {
        Gpl_type type;
        Status status = sym->get_game_object_value()->get_member_variable_type(*$3, type);
        if (status == Status::MEMBER_NOT_DECLARED) 
        {
            Error::error(Error::UNDECLARED_MEMBER, *$1, *$3);
        }
    }
    $$ = new Variable(sym, *$3);
}
| T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
{
    Expression *expr = $3;
    Symbol *sym = Symbol_table::instance()->lookup(*$1);
    if (sym == NULL) 
    {
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
    } 
    else if (sym->get_type() != GAME_OBJECT_ARRAY) 
    {
        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
    } 
    else if (sym->get_type() == GAME_OBJECT_ARRAY) 
    {
        Gpl_type type;
        Status status = sym->get_game_object_value()->get_member_variable_type(*$6, type);
        if (status == Status::MEMBER_NOT_DECLARED) 
        {
            Error::error(Error::UNDECLARED_MEMBER, *$1, *$6);
        }
        if(expr->get_type() != INT)
        {
            if(expr->get_type() == DOUBLE)
            {
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A double expression");
            }
            else if(expr->get_type() == STRING)
            {
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A string expression");
            }
        }
        else
        {
            int index = expr->eval_int();
            if(sym && (index < 0 || index >= sym->get_size()) )
            {
                stringstream ss;
                ss << index;
                Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, *$1, ss.str());
            }
        }
    }
    
    $$ = new Variable(sym,*$6);
}
;

//---------------------------------------------------------------------
expression:
primary_expression
{
    $$ = $1;
}
| expression T_OR expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(OR));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(OR));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, OR, $3);
}
| expression T_AND expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(AND));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(AND));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, AND, $3);
}
| expression T_LESS_EQUAL expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(LESS_THAN_EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(LESS_THAN_EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, LESS_THAN_EQUAL, $3);
}
| expression T_GREATER_EQUAL  expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(GREATER_THAN_EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(GREATER_THAN_EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, GREATER_THAN_EQUAL, $3);
}
| expression T_LESS expression 
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(LESS_THAN));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(LESS_THAN));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, LESS_THAN, $3);
}
| expression T_GREATER  expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(GREATER_THAN));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(GREATER_THAN));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, GREATER_THAN, $3);
}
| expression T_EQUAL expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING &&
            rhs->get_type() != INT_ARRAY && rhs->get_type() != DOUBLE_ARRAY && rhs->get_type() != STRING_ARRAY
      )
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, EQUAL, $3);
}
| expression T_NOT_EQUAL expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(NOT_EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(NOT_EQUAL));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, NOT_EQUAL, $3);
}
| expression T_PLUS expression 
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE && lhs->get_type() != STRING &&
            lhs->get_type() != INT_ARRAY && lhs->get_type() != DOUBLE_ARRAY && lhs->get_type() != STRING_ARRAY
      )
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(PLUS));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE && rhs->get_type() != STRING &&
            rhs->get_type() != INT_ARRAY && rhs->get_type() != DOUBLE_ARRAY && rhs->get_type() != STRING_ARRAY
      )
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(PLUS));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, PLUS, $3);
}
| expression T_MINUS expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MINUS));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MINUS));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, MINUS, $3);
}
| expression T_ASTERISK expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MULTIPLY));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MULTIPLY));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, MULTIPLY, $3);
}
| expression T_DIVIDE expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT && lhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(DIVIDE));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(DIVIDE));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, DIVIDE, $3);
}
| expression T_MOD expression
{
    Expression *lhs = $1;
    Expression *rhs = $3;
    bool flag = true;
    if(lhs->get_type() != INT)
    {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MOD));
        $$ = new Expression(0);
        flag = false;
    }
    if(rhs->get_type() != INT)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MOD));
        $$ = new Expression(0);
        flag = false;
    }
    if(flag)
        $$ = new Expression($1, MOD, $3);
}
| T_MINUS  expression %prec UNARY_OPS
{
    Expression *rhs = $2;
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(UNARY_MINUS));
        $$ = new Expression(0);
    }
    else
        $$ = new Expression($2, UNARY_MINUS, NULL);
}
| T_NOT  expression 
{
    Expression *rhs = $2;
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(NOT));
        $$ = new Expression(0);
    }
    else
        $$ = new Expression($2, NOT, NULL);
}
| math_operator T_LPAREN expression T_RPAREN
{
    Expression *rhs = $3;
    if(rhs->get_type() != INT && rhs->get_type() != DOUBLE)
    {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string($1));
        $$ = new Expression(0);
    }
    else 
        $$ = new Expression($3, $1, NULL);
}
| variable geometric_operator variable
{
    //We do not need to do this for p5
    $$ = NULL;
}
;

//---------------------------------------------------------------------
primary_expression:
T_LPAREN  expression T_RPAREN
{
    $$  = $2;
}
| variable
{
    $$ = new Expression($1);
}
| T_INT_CONSTANT
{
    $$ = new Expression($1);
}
| T_TRUE
{
    $$ = new Expression(1);
}
| T_FALSE
{
    $$ = new Expression(0);
}
| T_DOUBLE_CONSTANT
{
    $$ = new Expression($1);
}
| T_STRING_CONSTANT
{
    $$ = new Expression(*$1);
}
;

//---------------------------------------------------------------------
geometric_operator:
T_TOUCHES
| T_NEAR
;

//---------------------------------------------------------------------
math_operator:
T_SIN
{
    $$ = SIN;
}
| T_COS
{
    $$ = COS;
}
| T_TAN
{
    $$ = TAN;
}
| T_ASIN
{
    $$ = ASIN;
}
| T_ACOS
{
    $$ = ACOS;
}
| T_ATAN
{
    $$ = ATAN;
}
| T_SQRT
{
    $$ = SQRT;
}
| T_ABS
{
    $$ = ABS;
}
| T_FLOOR
{
    $$ = FLOOR;
}
| T_RANDOM
{
    $$ = RANDOM;
}
;

//---------------------------------------------------------------------
empty:
// empty goes to nothing so that you can use empty in productions
// when you want a production to go to nothing
;
