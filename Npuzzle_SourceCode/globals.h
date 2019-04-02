#ifndef GLOBALS
#define GLOBALS
#include <QApplication>
#include <QtCore/QCoreApplication>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <state.h>
#include <QTime>
#include "statelist.h"
#include "succobject.h"
#include <QMessageBox>
#include <QStack>
#include "pq.h"
#include "pqitem.h"

extern State* initialState;
extern State* finalState;
extern State* BFS_currentState;
extern QList<stateList> *BFS_visited;
extern QList<stateList> *DFS_visited;
extern QList<stateList> *A_visited;
extern QList<stateList>  *BFS_nextStates;
extern QList<stateList>  *BFS_currentStates;
extern QList<stateList> *back2initial;
extern QList<stateList> *DFS_Stack;
extern PQ *A_PQ;
extern QString *BFS_finalID;
extern QString *A_finalID;
extern QString *DFS_finalID;
extern bool* isBFSRunning;
extern bool* isDFSRunning;
extern bool* isARunning;
extern bool* isIterativeRunning;
extern int* iteration_number;
extern int* dfs_iteration_number;
extern int* max_iteration;
extern bool * iteration_step;

#endif // GLOBAL
