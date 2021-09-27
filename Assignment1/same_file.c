#include <stdio.h>
#include <time.h>

// Function declaration:
void
mul_cpx(
    double *a_re,
    double *a_im,
    double *b_re,
    double *b_im,
    double *c_re,
    double *c_im
    );

int main(){
  #define SIZE 30000
  double as[2*SIZE]; // Requires 0.45 MiB of memory -> all 3 arrays can fit on stack.
  double bs[2*SIZE];
  double cs[2*SIZE];

  size_t n_iter = 100000;
  clock_t start, end;

  start = clock();
  for ( int iter = 0; iter < n_iter; ++iter ){
    for ( size_t ix = 0; ix < 2*SIZE - 1; ix += 2 ) {
      // Initialize both Re and Im parts with 1 to get 2 only in Im part of the product:
      bs[ix] = 1; bs[ix+1] = 1;
      cs[ix] = 1; cs[ix+1] = 1;
      
      mul_cpx( &as[ix], &as[ix + 1], &bs[ix], &bs[ix + 1], &cs[ix], &cs[ix + 1] );    
    }
  }
  end = clock();

  // Calculate the elapsed time:
  printf("time = %f secs\n",(double)(end-start) / CLOCKS_PER_SEC); 
  
  return(0);
}
//
// Function definition:
void
mul_cpx(
    double *a_re,
    double *a_im,
    double *b_re,
    double *b_im,
    double *c_re,
    double *c_im
    )
{
  *a_re = *b_re * *c_re - *b_im * *c_im;
  *a_im = *b_re * *c_im + *b_im * *c_re;
}

// time = 0.000003 secs