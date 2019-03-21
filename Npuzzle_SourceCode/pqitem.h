#ifndef PQITEM_H
#define PQITEM_H
#include <state.h>
#include <QString>
class PQItem
{
public:
    PQItem(State* p, QString id, int c);
    State* pointer;
    QString ID;
    int cost;
};

#endif // PQITEM_h
