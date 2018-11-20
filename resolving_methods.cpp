float*** Cholesky_Factorization(float** A,int n)
{
  float*** C; 
  float** D;
  float ** L;
  float s = 0;
  C= new float**[2];
  D = new float*[1];
  L = new float*[n];
  for(int i=0; i<n; i++)
    L[i]= new float[n];
  D[0]= new float[n];
  for(int j=0; j<n; j++){
    D[0][j] = A[j][j];
    for(int k=0; k<j-1; k++1){
      s+=L[j][k]*L[j][k]*D[0][k];
    }
    D[0][j] -= s;
    s = 0;
    for(int i=0; i<n; i++){
      if(i>j){
	for(int k=0; k<j-1; k++)
	  s += L[i][k]*L[j][k]*D[0][k];
	L[i][j] = (A[i][j] - s)/D[0][j];
	s=0;
      }
      else if(i=j) {
	L[i][j]=1;
      }
      else if(i<j) {
	L[i][j]=0;
      } 
    }
  }
  C[1]=L;
  C[2]=D;
  return C;
}






float* Relax(float** A, float* b, float* u_k, int n, float w)
{
  float* u_k_1 = new float[n];
  float* diff = new float[n];
  float count = 0;
  for(int i=0;i<n;i++){
    u_k_1[i] = (1-w)*u_k[i];
    for(int j=0; j<i; j++)
      count -= A[i][j]*u_k_1[j];
    for(int j=i+1; j<n; j++)
      count -= A[i][j]*u_k[j];
    for(int i=0; i<n; i++)
      count += b[i];
    count = count*w;
    count = count/A[i][i];
    u_k_1[i] += count;
  }
  for(int i=0; i<n; i++)
    diff[i] = u_k_1[i] - u_k[i];
  while(sqrt(Prod_Vec(diff, diff)) > w){
    for(int i=; i<n; i++)
      u_k[i] = u_k_1[i];
    for(int i=0;i<n;i++){
      u_k_1[i] = (1-w)*u_k[i];
      for(int j=0; j<i; j++)
	count -= A[i][j]*u_k_1[j];
      for(int j=i+1; j<n; j++)
	count -= A[i][j]*u_k[j];
      for(int i=0; i<n; i++)
	count += b[i];
      count = count*w;
      count = count/A[i][i];
      u_k_1[i] += count;
    }
  }
  return u_k_1;
}






float* Grad_Conjug(float** A, float* b, float* x_k, int n)
{
  int count_itere = 0;
  float* r_k = new float[n];
  float* p_k = new float[n];
  float* r_k_1 = new float[n];
  float* x_k_1 = new float[n];
  float* p_k_1 = new float[n];
  float* prod_mat_vec = Prod_Mat_Vec(A, x_k, n);
  for(int i=0; i<n; i++)
    r_0[i] = b[i] - prod_mat_vec[i];
  for(int i=0; i<n; i++)
    p_k[i] = r_k[i];
  int k = 0;
  float alpha_k;
  float beta_k;
  while(1){
    alpha_k = Prod_Vec(r_k, r_k, n)/Pro_Vec(p_k, Prod_Mat_Vec(A, p_k, n), n);
    for(int i=0; i<n; i++){
      x_k_1[i] = x_k[i] + alpha_k*p_k[i];
      r_k_1[i] = r_k[i] + alpha_k*p_k[i];
    }
    count_itere++;
    if("r_k_1 est suffisamment petit"){
      cout << "le nombre d'itérations est" << count_itere << endl;
      return x_k_1;
    }
    beta_k = Prod_Vec(r_k_1, r_k_1, n)/Prod_Vec(r_k, r_k, n);
    for(int i=0; i<n; i++)
      p_k_1[i] = r_k_1[i] + beta_k*p_k[i];
    for(int i=0; i<n; i++){
      r_k[i] = r_k_1[i];
      p_k[i] = p_k_1[i];
    }
  }
}


