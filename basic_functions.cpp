#include<iostream>
#include<cmath>

using namespace std;


float g(float x, float y) {return (x*x +y*y)sin(x*y)}

float f(float x, float y) {return sin(x*y)}


float** Create_Matrix(int n)
{
  float** matrix;
  matrix = new float*[n];
  for(int i=0; i<n; i++){
    matrix[i] = new float[n];
  }
  return matrix;
}


float*** Create_Array_Of_Matrix(int size, int n)
{
  float*** Array;
  Array = new float**[size];
  for(int i=0; i<size; i++){
    Array[i] = new float*[n];
    for(int j=0; j<n; j++){
      Array[i][j] = new float[n];
    }
  }
  return Array;
}


void Get_Cofactor(float** A, float** temp, int p, int q, int n) 
{ 
  int i = 0, j = 0; 
  
  
  for (int row = 0; row < n; row++) { 
    for (int col = 0; col < n; col++) { 
      if (row != p && col != q) { 
	temp[i][j++] = A[row][col]; 
	if (j == n - 1) { 
	  j = 0; 
	  i++; 
	} 
      } 
    } 
  } 
} 




float Determinant(float** A, int n) 
{ 
  float D = 0; 
  if (n == 1) 
    return A[0][0]; 
  
  float** temp= Create_Matrix(n); 
  
  int sign = 1;  
  for (int f = 0; f < n; f++) 
    {  
      Get_Cofactor(A, temp, 0, f, n); 
      D += sign * A[0][f] * Determinant(temp, n - 1);  
      sign = -sign; 
    } 
  return D; 
} 

float** Prod_Mat(float** L, float** A, int n)
{
  float** M = Create_Matrix(n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      for(int k=0; k<n; k++){
	M[i][j] += L[i][k]*A[k][j];
      }
    }
  }
  return M;
}




void Adjoint(float** A, float** adj, int n) 
{ 
  if (n == 1){ 
    adj[0][0] = 1; 
  } 
  int sign = 1;
  float** temp = Create_Matrix(n); 
  for (int i=0; i<n; i++) { 
    for (int j=0; j<n; j++) 
      { 
	Get_Cofactor(A, temp, i, j, n); 
	if((i+j) % 2 == 0)
	  sign = 1;
	else
	  sign = -1;
	adj[j][i] = (sign)*(Determinant(temp, n-1)); 
      } 
  } 
} 

bool Inverse(float** A, float** inverse, int n) 
{ 
  float det = Determinant(A, n); 
  if (det == 0) 
    {  
      return false; 
    }   
  float** adj = Create_Matrix(n); 
  Adjoint(A, adj, n); 
  for (int i=0; i<n; i++) 
    for (int j=0; j<n; j++) 
      inverse[i][j] = adj[i][j]/det; 
  return true; 
} 


float* Prod_Mat_Vec(float** A, float* b, int n)
{
  float* a = new float[n];
  float count;
  for(int i=0; i<n; i++){
    count = 0;
    for(int j=0; j<n; j++)
      count += A[i][j]*b[j];
    a[i] = count;
  }
  return a;
}


float Prod_Vec(float* x, float* y, int n)
{
  float count = 0;
  for(int i=0; i<n; i++)
    count += x[i]*y[i];
  return count;
}

