#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    unsigned int row;
    unsigned int col;
    double* data;
};

typedef struct matrix matrix;

void createMatrix(matrix* X, unsigned int row, unsigned int col)
{
    (*X).row=row;
    (*X).col=col;
    (*X).data=malloc(row*col*sizeof(double));
    for(unsigned int i=0; i<row*col; i++)
    {
        (*X).data[i]=0;
    }
}

double getItem(matrix X, unsigned int row, unsigned int col)
{
    unsigned int R=(X).row;
    unsigned int C=(X).col;
    unsigned int coord=(C*row)+(col);
    return (X).data[coord];

}
double setItem(matrix* X, unsigned int row, unsigned int col, double value)
{
    unsigned int R=(*X).row;
    unsigned int C=(*X).col;
    unsigned int coord=(C*row)+(col);

    (*X).data[coord]=value;
}
matrix transpose(matrix X)
{
    matrix Xt;
    createMatrix(&Xt,X.col,X.row);
    for(int i=0; i<X.row; i++)
    {
        for(int j=0; j<X.col; j++)
        {
            Xt.data[(X.col*i)+(j)]=X.data[(X.col*j)+(i)];
        }
    }
    return Xt;
}

void printMatrix(matrix X)
{
    for(int i=0; i<X.row; i++)
    {
        printf("[");
        for(int j=0; j<X.col; j++)
        {
            printf("%.2lf ",X.data[(X.col*j)+(i)]);
        }
        printf("]\n");
    }
}
// To be continued...
int main()
{
    //quick test:
    matrix X;
    createMatrix(&X,3,3);

    setItem(&X,0,0,4);setItem(&X,0,1,3);setItem(&X,0,2,7);
    setItem(&X,1,0,2);setItem(&X,1,1,5);setItem(&X,1,2,0);
    setItem(&X,2,0,9);setItem(&X,2,1,1);setItem(&X,2,2,3);

    printMatrix(X);
}
