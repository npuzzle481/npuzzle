#include "mainwindow.h"
#include "globals.h"
#include <time.h>
#include <state.h>
#include <pq.h>
#include <statelist.h>


//init
State* initialState=new State();
State* finalState=new State();
State* BFS_currentState;

bool* isARunning=new bool(0);
bool* isIterativeRunning=new bool(0);
bool* isBFSRunning=new bool(0);
bool* isDFSRunning=new bool(0);

QList<stateList> *A_visited=new QList<stateList>();
QList<stateList> *back2initial=new QList<stateList>();
QList<stateList> *BFS_visited=new QList<stateList>();
QList<stateList>  *BFS_nextStates=new QList<stateList>();
QList<stateList>  *BFS_currentStates=new QList<stateList>();
QList<stateList> *DFS_Stack=new QList<stateList>();
QList<stateList> *DFS_visited=new QList<stateList>();
PQ* A_PQ=new PQ();

QString *A_finalID= new QString("");
QString *BFS_finalID= new QString("");
QString *DFS_finalID= new QString("");

int * iteration_number = new int(0);
int * max_iteration=new int(0);
int * dfs_iteration_number = new int(0);
bool * iteration_step = new bool(0);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
