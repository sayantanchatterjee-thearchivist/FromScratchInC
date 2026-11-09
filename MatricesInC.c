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
            printf("%.2lf ",X.data[(X.col*i)+(j)]);
        }
        printf("]\n");
    }
}

//OPERATORS: (+) addition, (-) subtraction, (*) scalar multiplcation and hadamard product, (@) matrix multiplication, (**) power, (/) scalar division, (%) scalar modulo, (//) scalar floor division:

matrix add(matrix A, matrix B)
{
    if(A.row!=B.row || A.col!=B.col)
    {
        printf("The two matrices in addition are incompatible.");
    }
    else
    {
        matrix C;
        createMatrix(&C,A.row,A.col);

        for(int i=0; i<A.row*A.col; i++)
        {
            C.data[i]=A.data[i]+B.data[i];
        }
        return C;
    }
}

matrix sub(matrix A, matrix B)
{
    if(A.row!=B.row || A.col!=B.col)
    {
        printf("The two matrices in addition are incompatible.");
    }
    else
    {
        matrix C;
        createMatrix(&C,A.row,A.col);

        for(int i=0; i<A.row*A.col; i++)
        {
            C.data[i]=A.data[i]-B.data[i];
        }
        return C;
    }
}

matrix hadamardMult(matrix A, matrix B)
{
    if(A.row!=B.row || A.col!=B.col)
    {
        printf("The two matrices in addition are incompatible.");
    }
    else
    {
        matrix C;
        createMatrix(&C,A.row,A.col);

        for(int i=0; i<A.row*A.col; i++)
        {
            C.data[i]=A.data[i]*B.data[i];
        }
        return C;
    }
}

matrix scalarMult(double k, matrix A)
{
    matrix C;
    createMatrix(&C,A.row,A.col);

    for(int i=0; i<A.row*A.col; i++)
    {
        C.data[i]=A.data[i]*k;
    }
    return C;
}

matrix matMul(matrix A, matrix B)
{
    if(A.col!=B.row)
    {
        printf("The matrices are incompatible for multiplication,\ntotal columns in first must be equal to columns in second.");
    }
    else
    {
        matrix C;
        createMatrix(&C, A.row, B.col);
        for(int i=0; i<A.row; i++)
        {
            for(int j=0; j<B.col; j++)
            {
                for(int k=0; k<A.col; k++)
                {
                    C.data[(C.col*i)+(j)]+=A.data[(C.col*i)+(k)]*B.data[(C.col*k)+(j)];
                }
            }
        }
        return C;
    }
}

matrix identityMatrix(unsigned int k)
{
    matrix I;
    createMatrix(&I,k,k);
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(i==j)
            {
                I.data[(I.col*i)+(j)]=1;
            }
            else
            {
                I.data[(I.col*i)+(j)]=0;
            }
        }
    }
    return I;
}

matrix power(matrix A, unsigned int k)
{
    if(A.col!=A.row)
    {
        printf("Must be a square matrix.");
    }
    else
    {
        matrix C;
        createMatrix(&C,A.row,A.col);
        matrix I=identityMatrix(A.row); // A.row=A.col, A is a square matrix.
        C=I;
        for(int i=1; i<=k; i++)
        {
            C=matMul(C,A);
        }
        return C;
    }
}

int main()
{
    //quick test:
    matrix X;
    createMatrix(&X,3,3);

    setItem(&X,0,0,4);setItem(&X,0,1,3);setItem(&X,0,2,7);
    setItem(&X,1,0,2);setItem(&X,1,1,5);setItem(&X,1,2,0);
    setItem(&X,2,0,9);setItem(&X,2,1,1);setItem(&X,2,2,3);

    printMatrix(power(X,3));
}
