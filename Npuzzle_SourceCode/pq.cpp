#include "pq.h"

PQ::PQ()
{
//empty
}

void PQ::put(PQItem item){
    if(list.isEmpty()) {
        list.append(item);
    }
    else{
        int size=list.size();
        for(int i=0;i<size;i++){
            if(item.cost<=list[i].cost){
                list.insert(i,item);
                return;
            }
        }
        list.push_back(item);
    }
}

PQItem PQ::get(){
    return list.takeFirst();
}
int PQ::isExists(QString id){
    int size=list.size();
    for(int i=0;i<size;i++){
        if(id==list[i].ID){
            return i;
        }
    }
    return 0;
}
