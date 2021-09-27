#include <stdio.h>
#include <time.h>

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

      as[ix] = bs[ix] * cs[ix] - bs[ix + 1] * cs[ix + 1];
      as[ix + 1] = bs[ix] * cs[ix + 1] + bs[ix + 1] * cs[ix];
    }
  }
  end = clock();

  // Calculate the elapsed time:
  printf("time = %f secs\n",(double)(end-start) / CLOCKS_PER_SEC); 
  
  return(0);
}

// time = 0.000002 secs