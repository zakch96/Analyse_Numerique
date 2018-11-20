float** Create_A(int n, int m, float h_sqr, float k_sqr, float d, int dim)
{
  float** A = new float*[dim];
  for(int i=0; i<m; i++)
    A[i] = new float[dim];
  for(int i=0; i<dim; i++){
    A[i][i] = d;
    if(1=<i)
      A[i][i-1] = -1/h_sqr;
    if(i < dim-1)
      A[i][i+1] = -1/h_sqr;
    if(n=<i)
      A[i][i-n] = -1/k_sqr;
    if(i<dim-n)
      A[i][i+n] = -1/k_sqr;
  }
  int count = 0;
  for(int i=m; i<dim-m+1; i++){
    if((cout % m) == 0)
      A[i][i-1] = 0;
    count++;
  }
  count = 0;
  for(int i=dim-m-1; i>m-2; i--){
    if((cout % m) == 0)
      A[i][i+1] = 0;
    count++;
  }
}
