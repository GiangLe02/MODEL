#include <stdio.h>
#include <mpfr.h>
int main (void)
{
  mpfr_t x; mpfr_init2(x,256); mpfr_set_ui(x,5,MPFR_RNDN);
  mpfr_t y; mpfr_init2(y,256); mpfr_set_ui(y,2,MPFR_RNDN);
  if(mpfr_cmp(x,y)<0){
    mpfr_set(x,y,MPFR_RNDN);
  };
  mpfr_printf("%.5Rf %.5RF",x,y);
  return 0;
}
