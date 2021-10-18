// for this part, it's used for calculate the distance
// calculate the attractor and  



#include<math.h>

// for this part
static inline void mux_cpx(double* a_re, double* a_im,
                           double  b_re, double  b_im,
                           double  c_re, double  c_im)
{
    *a_re = b_re*c_re - b_im*c_im;
    *a_im = b_re*c_im + b_im*c_re;
}


// from now, we begain to declare differenr degree newton function
static inline void *newton1(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double r1_re = 1, r1_im = 0;
  int max_iter = 100;

  for ( conv = 0, attr = -1; ; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = attr;
           *convergence = conv;
           break;
         }

    // iter the x
    x_re +=  - (x_re - 1);
    x_im += - x_im;


    for (int cpx_num = 0, cpx_num < d, ++cpx_num){
      _r_re = root_re[];
      _r_im = root_im[];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != attr )
        break;
  }
}






































































































    // // if the result is too close to 0
    // if ( ( x_re*x_re + x_im*x_im ) < 0.000001) ){
    //        *attractor = attr;
    //        *convergence = conv;
    //        break;
    //      }
    // // if the result is too big
    // if ( ( fabs(x_re) > 10000000000 || fabs(x_im) > 10000000000) ){
    //        *attractor = attr;
    //        *convergence = conv;
    //        break;
    //      }

