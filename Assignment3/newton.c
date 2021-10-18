// for this part, it's used for calculate the distance
// calculate the attractor and  
#include <math.h>
#include <stdio.h>
// for this part
void iter_result(double *re_re, double *re_im, double a_re, double a_im, int degree)
{
    double temp_re = a_re, temp_im = a_im, temp;
    for(int ix = 0; ix < degree / 2; ix++)
    {
        temp = temp_re * temp_re - temp_im * temp_im;
        temp_im = 2 * temp_re * temp_im;
        temp_re = temp;
    }
    if(degree % 2)
    {
        temp = temp_re * a_re - temp_im * a_im;
        temp_im = temp_re * a_im + temp_im * a_re;
        temp_re = temp;
    }
    *re_re = temp_re;
    *re_im = temp_im;
}


// from now, we begain to declare differenr degree newton function
static inline void *newton1(double x_re, double x_im,
                            int *attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1};
  double root_im[] = {0};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;



  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x
    x_re +=  - (x_re - 1);
    x_im += - x_im;


    for (int cpx_num = 0; cpx_num<1; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;
  }
}








static inline void *newton2(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1, -1};
  double root_im[] = {0, 0};
  double temp_re, temp_im, prime_re, prime_im;
  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x
    x_re +=  - (x_re - 1);
    x_im += - x_im;


    for (int cpx_num = 0; cpx_num < 2; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double norm = x_re * x_re + _r_im * _r_im;
    prime_re = x_re / norm;
    prime_im = 0 - _r_im / norm;
    temp_re = x_re - prime_re;
    temp_im = _r_im - prime_im;
    x_re -= temp_re / 2;
    _r_im -= temp_im / 2;

  }
}




static inline void *newton3(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  * attractor = - 1;

  for ( int conv = 0; conv < max_iter; ++conv ){
    printf("%.2f ",x_re);
    printf("%.2f\n",x_im);

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        *attractor = cpx_num;
        *convergence = conv;
        break;
        }
    }

    if ( *attractor != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 2);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 3;
    x_im -= temp_im / 3;
    
  }
}




static inline void *newton4(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        *convergence = conv;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 3);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 4;
    x_im -= temp_im / 4;
    
  }
}






static inline void *newton5(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){


    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 4);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 5;
    x_im -= temp_im / 5;
    
  }
}






static inline void *newton6(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 5);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 6;
    x_im -= temp_im / 6;
    
  }
}



static inline void *newton7(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 6);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 7;
    x_im -= temp_im / 7;
    
  }
}


static inline void *newton8(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 7);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 8;
    x_im -= temp_im / 8;
    
  }
}

static inline void *newton9(double x_re, double x_im,
                            int* attractor, int* convergence)
{
  //We should know all root of the function
  double root_re[] = {1,-0.5,-0.5};
  double root_im[] = {0,0.86603,-0.86606};

  int max_iter = 100;
  double _r_re;
  double _r_im;
  int attr = -1;

  for ( int conv = 0; conv < max_iter; ++conv ){

    // if the result is too close to 0 or too big
    if ( ( x_re*x_re + x_im*x_im ) < 0.000001 || 
         ( fabs(x_re) > 10000000000 || 
         fabs(x_im) > 10000000000) ){
           *attractor = -1;
           *convergence = conv;
           break;
         }

    // iter the x

    for (int cpx_num = 0; cpx_num < 3; ++cpx_num){
      _r_re = root_re[cpx_num];
      _r_im = root_im[cpx_num];

      if ( ((x_re - _r_re)*(x_re - _r_re) + (x_im - _r_im)*(x_im - _r_im)) < 0.000001) {
        attr = cpx_num;
        *attractor = cpx_num;
        break;
        }
    }

    if ( attr != -1 )
        break;

    double temp_re, temp_im, prime_re, prime_im;
    iter_result(&prime_re, &prime_im, x_re, x_im, 8);
    double norm = prime_re * prime_re + prime_im * prime_im;
    prime_re = prime_re / norm;
    prime_im = 0 - prime_im / norm;
    temp_re = x_re - prime_re;
    temp_im = x_im - prime_im;
    x_re -= temp_re / 9;
    x_im -= temp_im / 9;
    
  }
}



int main(){
  double x_re = 3;
  double x_im = 1;
  int attractor;
  int convergence;

  newton3(x_re, x_im, &attractor, &convergence);
  printf("attractor %.2f",attractor);
  printf("convergence %.2f",convergence);

}
















































































