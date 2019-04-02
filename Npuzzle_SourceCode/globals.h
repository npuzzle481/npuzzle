#ifndef GLOBALS
#define GLOBALS
#include <QString>
#include <state.h>
#include "statelist.h"
#include "succobject.h"
#include "pq.h"
#include "pqitem.h"

extern State* BFS_currentState;
extern QList<stateList> *BFS_visited;
extern QList<stateList>  *BFS_nextStates;
extern QList<stateList>  *BFS_currentStates;
extern bool* isBFSRunning;
extern QString *BFS_finalID;
extern int* iteration_number;
extern bool * iteration_step;

#endif // GLOBAL



