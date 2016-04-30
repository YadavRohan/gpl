#ifndef STATEMENT_H
#define STATEMENT_H

class Statement
{
    public:
        virtual ~Statement() { };
        virtual void execute()=0;
};

#endif
