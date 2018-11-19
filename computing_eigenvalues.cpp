
float Puis_Iteree(float** A, float* x_n, int n)
{
  float* x_n_1 = Prod_Mat_Vec(A, x_n, n);
  float count_1 = Prod_Vec(x_n_1, x_n, n)/Prod_Vec(x_n, x_n, n);
  x_n = Prod_Mat_Vec(A, x_n, n);
  x_n_1 = Prod_Mat_Vec(A, x_n, n);
  float count_2 = Prod_Vec(x_n_1, x_n, n)/Prod_Vec(x_n, x_n, n);
  if(count_1 == count_2)
    return count_2;
  while(count_1 != count_2){
    x_n = Prod_Mat_Vec(A, x_n, n);
    x_n_1 = Prod_Mat_Vec(A, x_n, n);
    count_1 = count_2;
    count_2 = Prod_Vec(x_n_1, x_n, n)/Prod_Vec(x_n, x_n, n);
  }
  return count_2;
}

