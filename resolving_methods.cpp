float* Descent(float** A, int dim, float* vec)
{
  float* vec1 = new float[dim];
  for(int i=0; i<dim; i++)
    if(A[i][i] == 0)
      exit(1);
  vec1[0] = vec[0]/A[0][0];
  for(int i=1; i<dim; i++){
    vec1[i] = vec[i]; 
      for(int j=0; j<i; j++)
	vec1[i] -= A[i][j]*vec1[j];
      vec1[i] = vec1[i]/A[i][i];
  }
  return vec1;
}




float* Climb(float** A, int dim, float* vec)
{
  float* vec1 = new float[dim];
  for(int i=0; i<dim; i++)
    if(A[i][i] == 0)
      exit(1);
  vec1[dim-1] = vec[dim-1]/A[dim-1][dim-1];
  for(int i=1; i<dim; i++){
    vec1[dim-1-i] = vec[dim-1-i]; 
      for(int j=dim-i; j<dim; j++)
	vec1[dim-1-i] -= A[dim-1-i][j]*vec1[j];
      vec1[dim-1-i] = vec1[dim-1-i]/A[dim-1-i][dim-1-i];
  }
  return vec1;
}







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
  float* prod_mat_vec_x = Prod_Mat_Vec(A, x_k, n);
  float* prod_mat_vec_p = Prod_Mat_Vec(A, p_k, n);
  for(int i=0; i<n; i++)
    r_k[i] = b[i] - prod_mat_vec_x[i];
  for(int i=0; i<n; i++)
    p_k[i] = r_k[i];
  float alpha_k;
  float beta_k;
  while(1){
    alpha_k = Prod_Vec(r_k, r_k, n)/Pro_Vec(p_k, prod_mat_vec_p, n);
    for(int i=0; i<n; i++){
      x_k_1[i] = x_k[i] + alpha_k*p_k[i];
      r_k_1[i] = r_k[i] - alpha_k*prod_mat_vec_p[i];
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






float** Cholesky_Decomp(float** A, int dim)
{
  float count;
  float** T = new float*[n];
  for(int i=0; i<n; i++)
    T[i] = new float[n];
  T[0][0] = sqrt(A[0][0]);
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      if(i>j)
	T[i][j] = 0;
      if(j>=1)
	T[0][j] = T[0][0]/A[0][j];
      count =0;
      if(i>=1){
	for(int k=0; k<i; k++)
	  count += T[k][i]*T[k][i];
	T[i][i] = sqrt(A[i][i] - count);
      }
      count =0;
      if(j>i){
	for(int k=0; k<i; k++)
	  count += T[k][i]*T[k][j];
	T[i][j] = (A[i][j] - count)/T[i][i];
      }	
    }
  }
	return T;		
}


