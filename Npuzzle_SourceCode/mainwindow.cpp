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
