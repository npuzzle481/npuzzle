#include "state.h"
#include <iostream>
#include <string>
#include "QString"
//states
using namespace std;
State::State() {

}
void State::addCost(int a) {
    cost=cost+a;
}

void State::update(Matrix elementMatrix) {
    StateMatrix=elementMatrix;
    n=StateMatrix.colsize();
    determineType();
}

State::State(Matrix elementMatrix)
{
    StateMatrix=elementMatrix;
    n=StateMatrix.colsize();
    determineType();
}

QString State::showMatrix()
{
    QString s="";
    int k=0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            k=StateMatrix[i][j];
            if(k<10) {
                s.append(" ");
            }
                s.append(QString::number(k).append(" "));
        }
        s.append("\n");
    }
    return s;
}

Matrix State::moveTile(int row, int col, int rowold, int colold) {
    Matrix B=StateMatrix;
    mswap(B[row][col],B[rowold][colold]);
    return B;
}
/*
 *Look for position of 0, and determine type accordingly
 * */
void State::determineType(){
    uniqueID="";
    int zeronumber=0;

    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            uniqueID.append(QString::number(StateMatrix[i][j]));

            if(StateMatrix[i][j]==0) {
                indexCol[zeronumber]=j;
                indexRow[zeronumber]=i;
                // Zero is found, determine where it is
                if(i==0){
                    if(j==0){
                        if (StateMatrix[i+1][j]==0) {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else if (StateMatrix[i][j+1]==0) {
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else  {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        //type=1;
                    }
                    else if (j==(n-1)) {
                        if (StateMatrix[i][j-1]==0) {
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else if (StateMatrix[i+1][j]==0) {
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else  {
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        //type=2;
                    }
                    else {
                        if (StateMatrix[i][j-1]==0) {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else if (StateMatrix[i][j+1]==0) {
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else if (StateMatrix[i+1][j]==0) {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                             // LEFT
                             succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                        else  {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                         }
                        //type=5;
                    }

                }
                else if (i==(n-1))
                    if(j==0){
                        if (StateMatrix[i-1][j]==0) {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                       else if (StateMatrix[i][j+1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            }
                        else  {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        //type=4;
                            }
                    else if (j==(n-1)) {
                        if (StateMatrix[i-1][j]==0) {
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                       else if (StateMatrix[i][j-1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            }
                        else  {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        //type=3;
                            }
                    else {
                        if (StateMatrix[i][j-1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                       else if (StateMatrix[i][j+1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                            }
                        else if (StateMatrix[i-1][j]==0) {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                             // LEFT
                             succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        else  {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        //type=7;
                    }

                else {
                    if(j==0){
                        if (StateMatrix[i-1][j]==0) {
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                        }
                       else if (StateMatrix[i][j+1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            }
                        else if (StateMatrix[i+1][j]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));;
                             }
                        else  {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        //type=8;
                            }
                    else if (j==(n-1)) {
                        if (StateMatrix[i-1][j]==0) {
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                        }
                       else if (StateMatrix[i][j-1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            }
                        else if (StateMatrix[i+1][j]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        else  {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        //type=6;
                            }
                    else {
                        if (StateMatrix[i-1][j]==0) {
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                        }
                       else if (StateMatrix[i][j+1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                            }
                        else if (StateMatrix[i+1][j]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        else if (StateMatrix[i][j-1]==0) {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        else  {
                            // UP
                            succsList.append(succObject(indexRow[zeronumber]-1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // RIGHT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]+1,indexRow[zeronumber],indexCol[zeronumber]));
                            // DOWN
                            succsList.append(succObject(indexRow[zeronumber]+1,indexCol[zeronumber],indexRow[zeronumber],indexCol[zeronumber]));
                            // LEFT
                            succsList.append(succObject(indexRow[zeronumber],indexCol[zeronumber]-1,indexRow[zeronumber],indexCol[zeronumber]));
                             }
                        //type=0;
                    }
                }
                
                zeronumber++;
            }

        }
    }     
}




