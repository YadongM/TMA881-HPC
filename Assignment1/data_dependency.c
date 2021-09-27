#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void
row_sums(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
)
{
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum = 0.;
    for ( size_t jx = 0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

void
row_sums_unrolled2(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
)
{
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum0 = 0.;
    double sum1 = 0.;
    for ( size_t jx = 0; jx < ncs; jx += 2 ) {
      sum0 += matrix[ix][jx];
      sum1 += matrix[ix][jx+1];
    }
    sums[ix] = sum0 + sum1;
  }
}

void
row_sums_unrolled4(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
)
{
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum0 = 0.;
    double sum1 = 0.;
    double sum2 = 0.;
    double sum3 = 0.;
    for ( size_t jx = 0; jx < ncs; jx += 4 ) {
      sum0 += matrix[ix][jx];
      sum1 += matrix[ix][jx+1];
      sum2 += matrix[ix][jx+2];
      sum3 += matrix[ix][jx+3];
    }
    sums[ix] = sum0 + sum1 + sum2 + sum3;
  }
}

void
row_sums_unrolled4_2(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
)
{
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum[4] = {0.,0.,0.,0.};
    for ( size_t jx = 0; jx < ncs; jx += 4 ) {
      sum[0] += matrix[ix][jx];
      sum[1] += matrix[ix][jx+1];
      sum[2] += matrix[ix][jx+2];
      sum[3] += matrix[ix][jx+3];
    }
    sums[ix] = sum[0] + sum[1] + sum[2] + sum[3];
  }
}

void
row_sums_unrolled8(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
)
{
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum0 = 0.;
    double sum1 = 0.;
    double sum2 = 0.;
    double sum3 = 0.;
    double sum4 = 0.;
    double sum5 = 0.;
    double sum6 = 0.;
    double sum7 = 0.;
    for ( size_t jx = 0; jx < ncs; jx += 8 ) {
      sum0 += matrix[ix][jx];
      sum1 += matrix[ix][jx+1];
      sum2 += matrix[ix][jx+2];
      sum3 += matrix[ix][jx+3];
      sum4 += matrix[ix][jx];
      sum5 += matrix[ix][jx+1];
      sum6 += matrix[ix][jx+2];
      sum7 += matrix[ix][jx+3];
    }
    sums[ix] = sum0 + sum1 + sum2 + sum3;
  }
}

int main(){
  const size_t SIZE = 1000;
  double sums[SIZE]; // Sums of elements in rows. *\/ */
  clock_t start, end;
  int n_iter = 10000; // How many times summation needs to be repeated.
  double t_elapsed_avg;

  double * mentries = (double*) malloc(sizeof(double) * SIZE*SIZE);
  double ** m = (double**) malloc(sizeof(double*) * SIZE);
  for ( size_t ix = 0, jx = 0; ix < SIZE; ++ix, jx+=SIZE )
    m[ix] = mentries + jx;

  // Initialize matrix:
  for ( size_t ix = 0; ix < SIZE; ++ix  ) {
    for ( size_t jx = 0; jx < SIZE; ++jx  ) {
      m[ix][jx] = (double)jx; // Sum of each row is SIZE*(SIZE+1)/2, sum of col i={0,SIZE-1} is i*SIZE;
    }
  }
  
  /////////////////////////////////// time row summation ///////////////////////
  start = clock(); 
  for ( int iter = 0; iter < n_iter; ++iter ){
    row_sums( sums, (const double**)m, SIZE, SIZE );
  }
  end = clock();

  // Calculate the elapsed time:
  t_elapsed_avg = (double)(end-start) / CLOCKS_PER_SEC;
  printf("Elapsed time of row summation: %f secs.\n",
         n_iter, t_elapsed_avg);

  /////////////////////////////////// time row_unrolled2 summation ///////////////////////
  start = clock();
  for ( int iter = 0; iter < n_iter; ++iter ){
    row_sums_unrolled2( sums, (const double**)m, SIZE, SIZE );
  }
  end = clock();

  // Calculate the elapsed time:
  t_elapsed_avg = (double)(end-start) / CLOCKS_PER_SEC;
  printf("Elapsed time of unrolled 2: %f secs.\n",
         n_iter, t_elapsed_avg);
  
  /////////////////////////////////// time row_unrolled4 summation ///////////////////////
  start = clock();
  for ( int iter = 0; iter < n_iter; ++iter ){
    row_sums_unrolled4( sums, (const double**)m, SIZE, SIZE );
  }
  end = clock();

  // Calculate the elapsed time:
  t_elapsed_avg = (double)(end-start) / CLOCKS_PER_SEC;
  printf("Elapsed time of unrolled 4: %f secs.\n",
         n_iter, t_elapsed_avg);

  /////////////////////////////////// time row_unrolled4_2 summation ///////////////////////
  start = clock();
  for ( int iter = 0; iter < n_iter; ++iter ){
    row_sums_unrolled4_2( sums, (const double**)m, SIZE, SIZE );
  }
  end = clock();

  // Calculate the elapsed time:
  t_elapsed_avg = (double)(end-start) / CLOCKS_PER_SEC;
  printf("Elapsed time of unrolled 4_2: %f secs.\n",
         n_iter, t_elapsed_avg);

  /////////////////////////////////// time row_unrolled8 summation ///////////////////////
  start = clock();
  for ( int iter = 0; iter < n_iter; ++iter ){
    row_sums_unrolled8( sums, (const double**)m, SIZE, SIZE );
  }
  end = clock();

  // Calculate the elapsed time:
  t_elapsed_avg = (double)(end-start) / CLOCKS_PER_SEC;
  printf("Elapsed time of unrolled 8: %f secs.\n",
         n_iter, t_elapsed_avg);

  free(m);
  m = NULL;
  free(mentries);
  mentries = NULL;

  return(0);
}