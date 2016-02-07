/* Simple main() that demonstrates how to interact with parser generated
   by flex & bison.

   The goal of this assignment is to understand flex and bison syntax, 
   not to pass the tests.

   This program reads a collection of record declarations of the form:

      record tom
      {
        height = 60;
        age = 42;
      }

      record sally
      {
        age = 38;
        weight = 138;
      }

   And prints them to standard output.

   If a filename is specified on the command line, the input is 
   read from the file.

   If no filename is specified, the input is read from standard 
   input (from the keyboard).

   Assignment p2 adds features to this program:
    (1) counting the fields in each record
    (2) adding doubles to the records
    (3) adding quoted strings
    (4) adding dates of the form JAN 20, 2015
    (5) extending identifiers to include _ and 0-9

  The only files you need to change to add these features is record.l and record.y.
  Do not change any other files.

*/

#include "parser.h" // substitute for y.tab.h
#include "error.h"  // gpl's error reporting

#include <iostream>
using namespace std;
#include <stdio.h> // for fopen()

extern int yylex();
extern int yyparse();

extern "C" int yywrap ( );

int yywrap(void)
{
  return true;
}

// this function is called by bison when it encounters an error
int yyerror(const char *str)
{
  // use the error reporting method from error.h/error.cpp
  Error::error(Error::PARSE_ERROR, str);
  return 0;
}


int main(int argc, char **argv)
{
  // lexer generated by flex reads from yyin
   extern FILE *yyin;

  // if a command line argument is given, assume it is a filename
  // to read from
  if (argc == 2 && argv[1])
  {
    yyin = fopen(argv[1],"r");

    cout << "parser.cpp::main() reading file " << argv[1] << endl;
  }
  // else read from standard input (default for lex/flex)
  else
  {
    cout << "parser.cpp::main() reading standard input." << endl;
  }

  cout << "parser.cpp::main() about to call yyparse()" << endl
       << "type zero or more record declarations followed by ^D:" << endl
       << endl;

  cout << "------------------------------------------------------\n";
  int parse_result = yyparse();
  cout << "------------------------------------------------------\n";
  cout << endl
       << "parser.cpp::main() after call to yyparse()" << endl
       << endl;

  if (parse_result != 0)
    cout << "yyparse() found errors" << endl;
  else cout << "no errors found by yyparse()" << endl;

  cout << endl << "parser.cpp::main() end of program." << endl;
}
