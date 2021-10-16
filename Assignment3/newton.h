// for this part, it's used for calculate the distance
// calculate the attractor and  



#include<math.h>



// for this part, i remain don't know what's main
static inline void mux_cpx(double* a_re, double* a_im,
                           double  b_re, double  b_im,
                           double  c_re, double  c_im)
{
    *a_re = b_re*c_re - b_im*c_im;
    *a_im = b_re*c_im + b_im*c_re;
}


// from now, we begain to declare differenr degree newton function


static inline void *newton1()






















for ( conv = 0, attr = DEFAULT_VALUE; ; ++conv ) {
  if ( CHECK CONDITION ) {
    attr = VALUE;
    break;
  }
  if ( CHECK CONDITION ) {
    attr = VALUE;
    break;
  }
  for ( EXPRESSION )
    if ( CHECK CONDITION ) {
      attr = VALUE_NOT_EQUAL_TO_THE_DEFAULT_ONE;
      break;
    }
  if ( attr != DEFAULT_VALUE )
    break;

  // computation
}