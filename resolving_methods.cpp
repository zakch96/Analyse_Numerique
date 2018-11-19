
float* Grad_Conjug(float** A, float* b, float* x_k, int n)
{
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
    if("r_k_1 est suffisamment petit")
      return x_k_1;
    beta_k = Prod_Vec(r_k_1, r_k_1, n)/Prod_Vec(r_k, r_k, n);
    for(int i=0; i<n; i++)
      p_k_1[i] = r_k_1[i] + beta_k*p_k[i];
    for(int i=0; i<n; i++){
      r_k[i] = r_k_1[i];
      p_k[i] = p_k_1[i];
    }
  }
}

