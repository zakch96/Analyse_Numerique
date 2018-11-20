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


