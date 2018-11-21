
double** Create_A(int n, int m, double h_sqr, double k_sqr, double d)
{
  int dim = n*m;
  double** A = new double*[dim];
  for(int i=0; i<dim; i++)
    A[i] = new double[dim];
  for(int i=0; i<dim; i++){
    A[i][i] = d;
    if(1<=i)
      A[i][i-1] = -1/h_sqr;
    if(i < dim-1)
      A[i][i+1] = -1/h_sqr;
    if(n<=i)
      A[i][i-n] = -1/k_sqr;
    if(i<dim-n)
      A[i][i+n] = -1/k_sqr;
  }
  int count_1 = 0;
  for(int i=m; i<dim-m+1; i++){
    if((count_1 % m) == 0)
      A[i][i-1] = 0;
    count_1++;
  }
  count_1 = 0;
  for(int i=dim-m-1; i>m-2; i--){
    if((count_1 % m) == 0)
      A[i][i+1] = 0;
    count_1++;
  }
  return A;
} 



float* Create_b(int n, int m, float a, float b, float sqr_k, float sqr_h, int dim)
{
  float* b = new float[dim];
  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
      b[i + (j-1)*m] = f(i*h, j*k);
  for(int i>0; i<(m-1); i++){
    b[i+(n-1)*m] += g(i*h, b)/sqr_k;
    b[i] += g(i*h, 0)/sqr_k;
  }
  for(int j>0; j<(n-1); j++){
    b[1+(j-1)*n] += g(0, j*k)/sqr_h;
    b[m+(j-1)*n] += g(a, j*k)/sqr_h;
  }
}
