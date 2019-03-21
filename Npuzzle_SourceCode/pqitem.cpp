#include "pqitem.h"
#include <QString>
//constructer
PQItem::PQItem(State *p, QString id, int c)
{
    pointer=p;
    ID=id;
    cost=c;
}

