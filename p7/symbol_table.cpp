#include "symbol_table.h"

Symbol_table* Symbol_table::object = NULL;

Symbol_table *Symbol_table :: instance()
{
   if(object == NULL)
   {
      object = new Symbol_table();
   }
   return object;
}

Symbol* Symbol_table :: lookup(std::string name)
{
   auto iter = symbolMap.find(name); 
   if (iter != symbolMap.end() )
   {
      return iter->second;
   }
   return NULL;
}

void Symbol_table :: print(std::ostream &os)const
{
   std::map<std::string, Symbol*> orderdMap(symbolMap.begin(), symbolMap.end());
   for(auto itr : orderdMap)
   {
      itr.second->print(os);
   }
}

void Symbol_table :: insert(std::string key, Symbol *value)
{
   symbolMap[key] = value;
}

Symbol_table :: ~Symbol_table()
{
   for(auto itr : symbolMap)
   {
      delete itr.second;
   }
}
