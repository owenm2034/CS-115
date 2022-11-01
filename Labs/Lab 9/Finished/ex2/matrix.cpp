// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 29th

#include "matrix.h"
#include <iostream>
using namespace std;

template <typename M_type>
Matrix<M_type>::Matrix()
{
  rows = MAXROWS;
  cols = MAXCOLS;
  for (int x = 0; x < rows; x++)
  {
    for(int y = 0; y < cols; y++)
    {
	    doubleArray[x][y] = '\0';
    }
  }
}   

template <typename M_type>
void Matrix<M_type>::printMatrix()
{
  for (int r = 0; r < rows; r++)
  {
    for(int c = 0; c < cols; c++)
    {
	    cout << doubleArray[r][c] << "   ";
    }
    cout << endl;
  }
}

template <typename M_type>
void Matrix<M_type>::setMatrix(M_type otherArray[][MAXCOLS])
{
  for (int rowNum = 0; rowNum < rows; rowNum++)
  {
    for(int colNum = 0; colNum < cols; colNum++)
    {
	    doubleArray[rowNum][colNum] = otherArray[rowNum][colNum];
    }
  }
}

template <typename M_type>
void Matrix<M_type>::addMatrix(M_type otherArray[][MAXCOLS])
{
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
	    doubleArray[i][j] += otherArray[i][j];
    }
  }
}

template <typename M_type>
void Matrix<M_type>::addMatrix(Matrix<M_type> otherMatrix)
{
  addMatrix(otherMatrix.doubleArray);
}


// add template types below.


template class Matrix <int>;
template class Matrix <string>;
template class Matrix <double>;
