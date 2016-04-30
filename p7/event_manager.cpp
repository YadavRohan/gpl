// updated 2/14/2016

#include "event_manager.h"
#include "gpl_assert.h"
using namespace std;

Event_manager *Event_manager::m_instance = 0;

Event_manager *Event_manager::instance()
{
  if (!m_instance)
    m_instance = new Event_manager();
  return m_instance;
}

Event_manager::Event_manager()
{
}

Event_manager::~Event_manager()
{
}


void 
Event_manager::execute_handlers(Window::Keystroke keystroke)
{
    for(const auto &it : event_statement[keystroke])
    {
        it->execute();
    }
}

void Event_manager::set_statement(Window::Keystroke keystroke, Statement_block *block)
{
    auto it = event_statement.find(keystroke);
    if(it == event_statement.end())
    {
        //keystroke is not found insert a new vector
        vector<Statement_block*> temp;
        temp.push_back(block);
        event_statement[keystroke] = temp;
    }
    else
    {
        //keystroke is found push back to the vector
        event_statement[keystroke].push_back(block);
    }
}
