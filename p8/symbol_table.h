#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include <map>
#include <unordered_map>
#include <ostream>
#include <algorithm>

class Symbol_table
{
   private:
      std::unordered_map<std::string, Symbol*> symbolMap;
      static Symbol_table* object;
      Symbol_table() { };
      Symbol_table(const Symbol_table &);
      Symbol_table &operator=(const Symbol_table &);
   public:
      static Symbol_table* instance();
      Symbol* lookup(std::string name);
      void print(std::ostream &os) const;
      void insert(std::string key, Symbol* value);
      ~Symbol_table();
};
#endif
