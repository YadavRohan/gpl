// updated 2/14/2016

/*
  ALWAYS include parser.h instead of y.tab.h

  Here is why:

    Since the union created by bison contains several gpl objects,
    a forward class declaration, or including the .h file must be 
    done before the union is created.

    Bison generates y.tab.h where the union is created. 
    I can't find a way to get bison to generate a y.tab.h that includes 
    forward class declarations and #include's, so I created this file.


*/

#ifndef PARSER_H
#define PARSER_H

// for each type used in the union, you will need to 
// put the appropriate include here
// For example, the union must hold a C++ string, so <string> is included
//   since it is bad programming practice to include "using namespace std"
//   in a .h file, you will have to put "std::string" in the union instead
//   of "string"

#include <string>
#include <stack>

#include "gpl_type.h"
#include "symbol.h"
#include "symbol_table.h"
#include "expression.h"
#include "game_object.h"
#include "rectangle.h"
#include "circle.h"
#include "textbox.h"
#include "pixmap.h"
#include "statement_block.h"
#include "statement.h"
#include "print_stmt.h"
#include "if_stmt.h"
#include "exit_stmt.h"
#include "for_stmt.h"
#include "event_manager.h"
#include "assignment_stmt.h"
#include "y.tab.h"

#endif // #ifndef PARSER_H
