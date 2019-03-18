#ifndef STATE_H
#define STATE_H
#include <cmatrix>
#include <iostream>
#include <string>
#include <QString>
#include <succobject.h>
#include <QList>
typedef techsoft::matrix<int>  Matrix;
typedef QList<succObject> _SuccList;
using namespace std;
/*
 * This is state class that holds all the informatin about the state
 * State(int n) -> n stands for the puzzle size
 * StateMatrix -> is Matrix of n*n consisting of integer
 * type defines the State type dependin on Empty Tiles place
1	5	5	5	2
8	0	0	0	6
8	0	0	0	6
8	0	0	0	6
4	7	7	7	3
 */
class State
{
public:
    int n=0;
    int indexCol[2]={0,0},indexRow[2]={0,0};
    State();
    State(Matrix elementMatrix);
    State* backPointer=NULL;
    void update(Matrix elementMatrix);
    QString showMatrix();
    QString uniqueID="";
    void determineType();
    int getType();
    int cost=0;
    void addCost(int a);
    Matrix moveTile(int row,int col, int rowold, int colold);
    _SuccList succsList;
    void listSuccessors();
    Matrix StateMatrix;

private:

    int type=0;
};

#endif // STATE_H
