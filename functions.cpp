#include<iostream>
#include<cmath>

using namespace std;



float** Create_Matrix(int n)
{
  float** matrix;
  matrix = new float*[n];
  for(int i=0; i<n; i++){
    matrix[i] = new float[n];
  }
  return matrix;
}


float*** Create_Array_Matrix(int size, int n)
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


void getCofactor(float** A, float** temp, int p, int q, int n) 
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




float determinant(float** A, int n) 
{ 
  float D = 0; 
  if (n == 1) 
    return A[0][0]; 
  
  float** temp= Create_Matrix(n); 
  
  int sign = 1;  
  for (int f = 0; f < n; f++) 
    {  
      getCofactor(A, temp, 0, f, n); 
      D += sign * A[0][f] * determinant(temp, n - 1);  
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




void adjoint(float** A, float** adj, int n) 
{ 
  if (n == 1){ 
    adj[0][0] = 1; 
  } 
  int sign = 1;
  float** temp = Create_Matrix(n); 
  for (int i=0; i<n; i++) { 
    for (int j=0; j<n; j++) 
      { 
	getCofactor(A, temp, i, j, n); 
	if((i+j) % 2 == 0)
	  sign = 1;
	else
	  sign = -1;
	adj[j][i] = (sign)*(determinant(temp, n-1)); 
      } 
  } 
} 

bool inverse(float** A, float** inverse, int n) 
{ 
  float det = determinant(A, n); 
  if (det == 0) 
    {  
      return false; 
    }   
  float** adj = Create_Matrix(n); 
  adjoint(A, adj, n); 
  for (int i=0; i<n; i++) 
    for (int j=0; j<n; j++) 
      inverse[i][j] = adj[i][j]/det; 
  return true; 
} 

