// updated 2/14/16

#include "statement_block.h"
#include "gpl_assert.h"
using namespace std;


Statement_block::Statement_block()
{

}

// this function is called for all non-animation_block statement_blocks
// Implement it for p7
void Statement_block::execute()
{
  // This function should be defined before it is ever called
  // This assert will cause the program to abort if this function 
  // is called before it is implemented.

  // *** ==> Remove this assert when you implement this function
  //assert(false);
  for(auto &it : statement_vect)
  {
      it->execute();
  }
}

bool Statement_block::empty()
{
    return statement_vect.size() == 0 ? true: false;
}

void Statement_block::push_statement(Statement *stmt)
{
    statement_vect.push_back(stmt);
}
