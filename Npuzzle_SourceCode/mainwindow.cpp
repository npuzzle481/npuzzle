#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <globals.h>
#include <generatedialog.h>
#include <state.h>
#include "pqitem.h"
#include "pq.h"


// TODO

int heuristic2() {return 0;}
int heuristic3() {return 0;}
int A_star() {return 0;}
int DFS() {return 0;}
int iterativeDeeping() {return 0;}
int BFS() {return 0;}

void MainWindow::on_button_generatePuzzle_clicked(){}
void MainWindow::on_button_start_toggled(bool checked){}
void MainWindow::on_button_showTheSol_clicked(){}
void MainWindow::on_button_step_clicked(){}


//create main window
void lockedUp(Ui::MainWindow *ui){
    ui->button_start->setDisabled(1);
    ui->button_step->setDisabled(1);
    ui->combo_chooseMethod->setDisabled(1);
}
void unlockedUp(Ui::MainWindow *ui){
    ui->button_start->setDisabled(0);
    ui->button_step->setDisabled(0);
    ui->combo_chooseMethod->setDisabled(0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lockedUp(ui);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int heuristic1(State* S) 
{
    int n=S->n;
    return (n - 2 - S->indexCol[0] + n - S->indexRow[0]+n - 2 - S->indexCol[1] + n - S->indexRow[1]);
}

void BFS_cleanUp(){
    while(!BFS_visited->isEmpty()) {
        State* ptr=BFS_visited->takeFirst().pointer;
        if(ptr!=NULL) {
            delete ptr;
        }
    }
    while(!BFS_nextStates->isEmpty()) {
        State* ptr=BFS_nextStates->takeFirst().pointer;
        if(ptr!=NULL) {
            delete ptr;
        }
    }
    while(!BFS_currentStates->isEmpty()) {
        State* ptr=BFS_currentStates->takeFirst().pointer;
        if(ptr!=NULL) {
            delete ptr;
        }
    }
    delete isBFSRunning;
    isBFSRunning= new bool(0);
    BFS_finalID->clear();
}

int BFS(Ui::MainWindow *ui){
    if(!*isBFSRunning) {
        qDebug()<<"BFS is Started;";
        BFS_currentStates->append(stateList(initialState->uniqueID,initialState));
        BFS_visited->clear();
        BFS_nextStates->clear();
        *isBFSRunning=true;
        *iteration_number=0;
        int size=initialState->n;
        for (int i=1;i<=size*size;i++) {
            if(i==size*size) BFS_finalID->append("0");
            else if(i==(size*size)-1) BFS_finalID->append("0");
            else {
                BFS_finalID->append(QString::number(i));
            }
        }
        qDebug()<<"BFS Final "<<*BFS_finalID;
    }

    bool stop_search=0;
        if(BFS_finalID==initialState->uniqueID){
            stop_search=1;
            QMessageBox msgBox;
            msgBox.setText("The Path is trivial.");
            msgBox.exec();
        }
        while(!BFS_currentStates->isEmpty() && !stop_search && (ui->button_start->isChecked() || *iteration_step) ) {
            while(!BFS_currentStates->isEmpty() && !stop_search && (ui->button_start->isChecked() || *iteration_step)) {
                State* interestState=BFS_currentStates->takeFirst().pointer;
                *iteration_number=*iteration_number+1;
                ui->edit_iterationNumber->setText(QString::number(*iteration_number));
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                QString s;
                s.append(interestState->showMatrix());
                ui->edit_puzzleState->clear();
                ui->edit_puzzleState->appendPlainText(s);
                _SuccList list1=interestState->succsList;
                while(!list1.empty()) {
                    succObject aObject=list1.takeFirst();
                    Matrix M = interestState->moveTile(aObject.row , aObject.col, aObject.rowold , aObject.colold);
                    State* newState=getNewState(M);

                    newState->backPointer=interestState;
                    if(!checkIdExists(BFS_visited,newState->uniqueID)) {
                        BFS_nextStates->append(stateList(newState->uniqueID,newState));
                        if(newState->uniqueID==*BFS_finalID) {
                            stop_search=1;
                            finalState=newState;
                            QString s;
                            s.append(newState->showMatrix());
                            ui->edit_puzzleState->clear();
                            ui->edit_puzzleState->appendPlainText(s);
                            *isBFSRunning=0;
                            ui->button_start->setChecked(0);
                        }
                    }
                    else{
                        delete newState;
                    }

                }

                *iteration_step=0;
                BFS_visited->append(stateList(interestState->uniqueID,interestState));

            }

           if(BFS_currentStates->isEmpty()) {
                QList<stateList>* dummy;
                dummy=BFS_currentStates;
                BFS_currentStates=BFS_nextStates;
                BFS_nextStates=dummy;
                BFS_nextStates->clear();
            }
        }

        if(!ui->button_start->isChecked() && stop_search) {
            QMessageBox msgBox;
            if(stop_search==0) {
                msgBox.setText("The path is not found");

            }
            else {
                msgBox.setText("The path is found");
            }
            lockedUp(ui);
            msgBox.exec();
        }
}


