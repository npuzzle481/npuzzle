#ifndef STATELIST_H
#define STATELIST_H
#include <QString>
#include <state.h>

class stateList
{
public:
    stateList(QString ID2,State* pointer2);
    QString ID;
    State* pointer;
};

#endif // STATELIST_h
