#include "mainwindow.h"
#include "globals.h"
#include <time.h>
#include <state.h>
#include <pq.h>
#include <statelist.h>


//init
State* initialState=new State();
State* finalState=new State();


bool* isARunning=new bool(0);
bool* isIterativeRunning=new bool(0);

QList<stateList> *A_visited=new QList<stateList>();
QList<stateList> *back2initial=new QList<stateList>();

PQ* A_PQ=new PQ();

QString *A_finalID= new QString("");

int * iteration_number = new int(0);
int * max_iteration=new int(0);
bool * iteration_step = new bool(0);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
