#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <globals.h>
#include <generatedialog.h>
#include <state.h>
#include "pqitem.h"
#include "pq.h"


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

int heuristic2(State* S) {
    int n=S->n;
    int k=1;
    int m=0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++) {
            if(k!=S->StateMatrix[i][j]) {
                m++;
            }
            k++;
        }
    }
    return m;
}


int heuristic3(State* S) {
    int n=S->n;
    int k=1;
    int m=0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++) {
            int item=S->StateMatrix[i][j];
            if(k!=item) {
                int actRow=item/n;
                int actCol=item%n;
                m=m+abs(actRow-i)+abs(actCol-j);
            }
            k++;
        }
    }
    return m;
}

void MainWindow::on_button_generatePuzzle_clicked()
{
    cleanUp(ui);
    unlockedUp(ui);
    initialState=new State();
    generateDialog dialog1;
    dialog1.setModal(true);
    dialog1.exec();
    QString s;
    s.append(initialState->showMatrix());
    ui->edit_puzzleState->clear();
    ui->edit_puzzleState->appendPlainText(s);
    qDebug()<<"asda";
}

State* getNewState(Matrix M) {
    return new State(M);
}

bool checkIdExists (QList<stateList> *L, QString id){
    QList<stateList>::iterator i;
    for (i = L->begin(); i != L->end(); ++i) {
       if(i->ID==id) return true;
    }
    return false;
}

int A_Search(Ui::MainWindow *ui,int h) {
    // The A is started at first
    if(!*isARunning) {
        qDebug()<<"A is Started;";
        A_PQ->put(PQItem(initialState,initialState->uniqueID,0));
        A_visited->clear();
        *isARunning=true;
        *iteration_number=0;
        A_finalID->clear();
        int size=initialState->n;
        for (int i=1;i<=size*size;i++) {
            if(i==size*size) A_finalID->append("0");
            else if(i==(size*size)-1) A_finalID->append("0");
            else {
                A_finalID->append(QString::number(i));
            }

        }
        qDebug()<<"A Final "<<*A_finalID;
    }
        bool stop_search=0;
        if(A_finalID==initialState->uniqueID) {
            QMessageBox msgBox;
            msgBox.setText("The Path is trivial.");
            msgBox.exec();
            stop_search=1;
        }
        while(!A_PQ->list.isEmpty() && !stop_search && (ui->button_start->isChecked() || *iteration_step) ) {
            PQItem pqitem=A_PQ->get();
            //qDebug()<<"ıntereset item: "<<pqitem.ID<<" , "<<pqitem.cost;
            A_visited->append(stateList(pqitem.ID,pqitem.pointer));
            *iteration_number=*iteration_number+1;
            ui->edit_iterationNumber->setText(QString::number(*iteration_number));
            QString s;
            s.append(pqitem.pointer->showMatrix());
            ui->edit_puzzleState->clear();
            ui->edit_puzzleState->appendPlainText(s);
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            if(pqitem.ID==*A_finalID) {
                stop_search=1;
                finalState=pqitem.pointer;
                QString s;
                s.append(finalState->showMatrix());
                ui->edit_puzzleState->clear();
                ui->edit_puzzleState->appendPlainText(s);
                *isARunning=0;
                ui->button_start->setChecked(0);
            }
            _SuccList list1=pqitem.pointer->succsList;
            while(!list1.isEmpty() && !stop_search) {
                succObject aObject=list1.takeFirst();
                Matrix M = pqitem.pointer->moveTile(aObject.row , aObject.col, aObject.rowold , aObject.colold);
                State* newState=getNewState(M);
               // qDebug()<<"New real item: "<<newState->uniqueID<<" , "<<newState->cost;
                // Set the Back Pointer
                newState->backPointer=pqitem.pointer;
                if(!checkIdExists(A_visited,newState->uniqueID)) {
                    int i_PQ=A_PQ->isExists(newState->uniqueID);
                    int cost;
                    if(h==1) cost=pqitem.pointer->cost+1+heuristic1(newState);
                    else if (h==2) cost=pqitem.pointer->cost+1+heuristic2(newState);
                    else if (h==3) cost=pqitem.pointer->cost+1+heuristic3(newState);
                    //qDebug()<<"heuristic cost: "<<cost;
                    if(i_PQ>0) {
                        if(A_PQ->list[i_PQ].cost>cost){
                           A_PQ->list[i_PQ].pointer->backPointer=pqitem.pointer;
                           A_PQ->list[i_PQ].cost=cost;
                           //qDebug()<<"old heuristic cost: "<<A_PQ->list[i_PQ].cost;
                           //qDebug()<<"heuristic cost updated: "<<cost;
                        }

                    }
                    else {
                        newState->addCost(pqitem.pointer->cost+1);
                        //qDebug()<<"New item actual cost updated: "<<newState->cost;
                        A_PQ->put(PQItem(newState,newState->uniqueID,cost));
                        //qDebug()<<"New item heuristic cost updated: "<<cost;
                    }
                }
                else {
                    //qDebug()<<"Already visited: "<<newState->uniqueID;
                    delete newState;

                }
            }
            *iteration_step=0;

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

int DFS_iterative(Ui::MainWindow *ui) {
    // The DFS is started at first
        bool stop_search=0;
        if(DFS_finalID==initialState->uniqueID) {
            finalState=initialState;
            return 1;
        }
        while(!DFS_Stack->isEmpty() && !stop_search && (ui->button_start->isChecked() || *iteration_step) ) {
            *dfs_iteration_number=*dfs_iteration_number+1;
            stateList aStateList=DFS_Stack->takeFirst();
            int sss=DFS_Stack->size();
             DFS_visited->append(aStateList);
            *iteration_number=*iteration_number+1;
            //qDebug()<<"DFS Iteration number:"<<*dfs_iteration_number;
            ui->edit_iterationNumber->setText(QString::number(*iteration_number));
            QString s;
            s.append(aStateList.pointer->showMatrix());
            ui->edit_puzzleState->clear();
            ui->edit_puzzleState->appendPlainText(s);
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //qDebug()<<aStateList.ID;
            if(aStateList.ID==*DFS_finalID) {
                qDebug()<<"ID is Found";
                finalState=aStateList.pointer;
                return 1;
                ui->button_start->setChecked(0);
            }
                _SuccList list1=aStateList.pointer->succsList;
                while(!list1.isEmpty() && !stop_search && (aStateList.pointer->cost < *max_iteration)) {


                    succObject aObject=list1.takeFirst();
                    Matrix M = aStateList.pointer->moveTile(aObject.row , aObject.col,aObject.rowold , aObject.colold);
                    State* newState=getNewState(M);

                    // Set the Back Pointer
                    newState->backPointer=aStateList.pointer;
                    newState->addCost(aStateList.pointer->cost + 1);
                    if(!checkIdExists(DFS_visited,newState->uniqueID)) {
                        stateList alist(newState->uniqueID,newState);
                        DFS_Stack->push_front(alist);
                        qDebug()<<"New added State:"<<newState->uniqueID<<" : "<<newState->cost;
                    }
                    else delete newState;
                }
            qDebug()<<"-----------";
            *iteration_step=0;


       }
        if (ui->button_start->isChecked() || *iteration_step) {
            //qDebug()<<"Not Found in this iteration:"<<*dfs_iteration_number;
            return 0;
        }
        else return -1;
}


void iterativeDeeping(Ui::MainWindow *ui) {
    if(!*isIterativeRunning) {
        //qDebug()<<"Iterative is Started;";
        stateList alist(initialState->uniqueID,initialState);
        DFS_Stack->push_front(alist);
        DFS_visited->clear();
        *isDFSRunning=true;
        *max_iteration=*max_iteration+1;
        *dfs_iteration_number=0;
        DFS_finalID->clear();
        int size=initialState->n;
        for (int i=1;i<=size*size;i++) {
            if(i==size*size) DFS_finalID->append("0");
            else if(i==(size*size)-1) DFS_finalID->append("0");
            else {
                DFS_finalID->append(QString::number(i));
            }

        }
        //qDebug()<<"DFS Final "<<*DFS_finalID;
    }
    while (ui->button_start->isChecked() || *iteration_step) {
        qDebug()<<"DFS is startedwith max:"<<*max_iteration;
        int result=DFS_iterative(ui);
        //qDebug()<<result;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if(result==0) {
           qDebug()<<"Not Found by max: "<<*max_iteration;
            *max_iteration=*max_iteration+1;
            *dfs_iteration_number=0;
            *isIterativeRunning=0;
            State* dummy=new State(initialState->StateMatrix);
            DFS_cleanUp();
            initialState=dummy;
            //qDebug()<<"DFS Cleaned";
            stateList alist(initialState->uniqueID,initialState);
            DFS_Stack->push_front(alist);
            int size=initialState->n;
            for (int i=1;i<=size*size;i++) {
                if(i==size*size) DFS_finalID->append("0");
                else if(i==(size*size)-1) DFS_finalID->append("0");
                else {
                    DFS_finalID->append(QString::number(i));
                }

            }
        }
        else if(result==1) {
            QMessageBox msgBox;
            msgBox.setText("The path is found");
            lockedUp(ui);
            msgBox.exec();
            *isIterativeRunning=0;
            return;
        }
        else {

        }

    }
}

int DFS(Ui::MainWindow *ui) {
    // The DFS is started at first
    if(!*isDFSRunning) {
        qDebug()<<"DFS is Started;";
        stateList alist(initialState->uniqueID,initialState);
        DFS_Stack->push_front(alist);
        DFS_visited->clear();
        *isDFSRunning=true;
        *iteration_number=0;
        DFS_finalID->clear();
        int size=initialState->n;
        for (int i=1;i<=size*size;i++) {
            if(i==size*size) DFS_finalID->append("0");
            else if(i==(size*size)-1) DFS_finalID->append("0");
            else {
                DFS_finalID->append(QString::number(i));
            }

        }
        qDebug()<<"DFS Final "<<*DFS_finalID;
    }
        bool stop_search=0;
        if(DFS_finalID==initialState->uniqueID) {
            QMessageBox msgBox;
            msgBox.setText("The Path is trivial.");
            msgBox.exec();
            stop_search=1;
        }
        while(!DFS_Stack->isEmpty() && !stop_search && (ui->button_start->isChecked() || *iteration_step) ) {

            stateList aStateList=DFS_Stack->takeFirst();
            DFS_visited->append(aStateList);
            *iteration_number=*iteration_number+1;
            ui->edit_iterationNumber->setText(QString::number(*iteration_number));
            QString s;
            s.append(aStateList.pointer->showMatrix());
            ui->edit_puzzleState->clear();
            ui->edit_puzzleState->appendPlainText(s);
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            if(aStateList.ID==*DFS_finalID) {
                stop_search=1;
                finalState=aStateList.pointer;
                QString s;
                s.append(finalState->showMatrix());
                ui->edit_puzzleState->clear();
                ui->edit_puzzleState->appendPlainText(s);
                *isDFSRunning=0;
                ui->button_start->setChecked(0);
            }
            _SuccList list1=aStateList.pointer->succsList;
            while(!list1.isEmpty() && !stop_search) {
                succObject aObject=list1.takeFirst();
                Matrix M = aStateList.pointer->moveTile(aObject.row , aObject.col,aObject.rowold , aObject.colold);
                State* newState=getNewState(M);

                // Set the Back Pointer
                newState->backPointer=aStateList.pointer;
                if(!checkIdExists(DFS_visited,newState->uniqueID)) {
                    stateList alist(newState->uniqueID,newState);
                    DFS_Stack->push_front(alist);
                }
                else delete newState;
            }
            *iteration_step=0;

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

void DFS_cleanUp() {
    while(!DFS_visited->isEmpty()) {
        State* ptr=DFS_visited->takeFirst().pointer;
        //qDebug()<<"Wİll be deleted:"<<ptr->uniqueID;
        if(ptr!=NULL) {
            //qDebug()<<"deleted:"<<ptr->uniqueID;
            delete ptr;
        }
    }
    delete isDFSRunning;
    isDFSRunning= new bool(0);
    DFS_finalID->clear();
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

void A_cleanUp() {
    while(!A_visited->isEmpty()) {
        State* ptr=A_visited->takeFirst().pointer;
        //qDebug()<<"Wİll be deleted:"<<ptr->uniqueID;
        if(ptr!=NULL) {
            //qDebug()<<"deleted:"<<ptr->uniqueID;
            delete ptr;
        }
    }
    delete A_PQ;
    A_PQ=new PQ();
    delete isARunning;
    isARunning= new bool(0);
    A_finalID->clear();
}

void cleanUp(Ui::MainWindow *ui) {
    int choise=ui->combo_chooseMethod->currentIndex();
    ui->combo_chooseMethod->setDisabled(1);
    if(choise==0) {
        qDebug()<<"bfs is chosen";
        BFS_cleanUp();
    }
    else if(choise==1) {
        qDebug()<<"dfs is chosen";
     DFS_cleanUp();
    }
    else if(choise==2 || choise==3) {
        qDebug()<<"A is chosen";
     A_cleanUp();
    }
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

void MainWindow::on_button_start_toggled(bool checked)
{
        if(checked==1) {
            ui->button_start->setText("Pause");
            int choise=ui->combo_chooseMethod->currentIndex();
            ui->combo_chooseMethod->setDisabled(1);
            if(choise==0) {
                qDebug()<<"bfs is chosen";
                BFS(ui);
            }
            else if(choise==1) {
                qDebug()<<"dfs is chosen";
             DFS(ui);
            }
            else if(choise==2) {
                qDebug()<<"A-1 is chosen";
                A_Search(ui,1);
            }
            else if(choise==3) {
                qDebug()<<"A-2 is chosen";
                A_Search(ui,2);
            }
            else if(choise==4) {
                qDebug()<<"A-3 is chosen";
                A_Search(ui,3);
            }
            else if(choise==5) {
                qDebug()<<"A-3 is chosen";
                iterativeDeeping(ui);
            }

        }
        else {
            ui->button_start->setText("Start");

        }
}

void MainWindow::on_button_step_clicked()
{
    *iteration_step=1; 
    int choise=ui->combo_chooseMethod->currentIndex();
    ui->combo_chooseMethod->setDisabled(1);
    if(choise==0) {
        qDebug()<<"bfs is chosen";
        BFS(ui);
    }
    else if(choise==1) {
        qDebug()<<"dfs is chosen";
     DFS(ui);
    }
    else if(choise==2) {
        qDebug()<<"A-1 is chosen";
        A_Search(ui,1);
    }
    else if(choise==3) {
        qDebug()<<"A-1 is chosen";
        A_Search(ui,2);
    }
    else if(choise==4) {
        qDebug()<<"A-1 is chosen";
        A_Search(ui,3);
    }
}

void MainWindow::on_button_showTheSol_clicked()
{
    State* current;
    current=finalState;
    back2initial->push_front(stateList(finalState->uniqueID,finalState));
    while(current->backPointer!=NULL) {
        back2initial->push_front(stateList(current->backPointer->uniqueID,current->backPointer));
        //qDebug()<<current->backPointer->uniqueID;
        current=current->backPointer;
    }
    ui->edit_step2sol->clear();
    ui->edit_step2sol->setText(QString::number(back2initial->size()-1));
    //qDebug()<<"steps to sol: "<<back2initial->size();
    QString s;

    ui->edit_puzzleState->clear();
    while(!back2initial->isEmpty()) {
        State* ptr=back2initial->takeFirst().pointer;
        s.append(ptr->showMatrix());
        s.append("-----------------\n");
    }
    ui->edit_puzzleState->appendPlainText(s);
}





