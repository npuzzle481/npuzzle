#ifndef PQ_H
#define PQ_H
#include <QList>
#include"pqitem.h"
#include "QString"
class PQ
{
public:
    PQ();
    void put(PQItem item);
    int isExists(QString id);
    PQItem get();
    QList<PQItem> list;
private:

};

#endif // PQ_h
