#include "generatedialog.h"
#include "ui_generatedialog.h"
#include "time.h"
#include "globals.h"
//generate matrix
Matrix generateMatrix(int size,int n){
    srand(time(NULL));
    int arry[size*size];
    // initilizeMatrix
    int k=1;
    for (int i=0;i<size*size;i++){
        *(arry+i)=k;
        if(k==size*size) *(arry+i)=0;
        if(k==(size*size)-1) *(arry+i)=0;
        k++;

    }

    Matrix aMatrix(size,size,arry);
    int numSwap=0;
    int indexCol,indexRow,indexCol2,indexRow2;
    indexCol=size-1;
    indexRow=size-1;
    int randNumber=0,lastRand=-1;
    while(numSwap<n){
        bool isSwapped=false;
        while(!isSwapped) {
            randNumber=rand()%4+1;
            indexCol2=indexCol;
            indexRow2=indexRow;
            if(randNumber==1) {
                // UP
                indexRow2--;
            }
            else if(randNumber==2) {
                // RIGHT
                indexCol2++;
            }
            else if(randNumber==3) {
                // DOWN
                indexRow2++;
            }
            else {
                //LEFT
                indexCol2--;
            }
        	if((indexCol2>=0 && indexCol2<size)&&(indexRow2>=0 && indexRow2<size)){
            	int diff=abs(randNumber-lastRand);
            	if(diff!=2) {
              	//  qDebug()<<"swapped";
               		mswap(aMatrix[indexRow][indexCol],aMatrix[indexRow2][indexCol2]);
                	indexRow=indexRow2;
                	indexCol=indexCol2;
                	isSwapped=true;
                	numSwap++;
                	lastRand=randNumber;
            	}
        	}
        }
    }



    return aMatrix;
}


generateDialog::generateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generateDialog){
    ui->setupUi(this);
}

generateDialog::~generateDialog(){
    delete ui;
}

void generateDialog::on_buttonBox_accepted()
{
    Matrix M;
    int size;
    int n;
    n=ui->edit_step2sol->text().toInt();
    size=ui->edit_puzzleSize->text().toInt();
    M=generateMatrix(size,n);
    initialState->update(M);
    qDebug()<<initialState->showMatrix();
}
