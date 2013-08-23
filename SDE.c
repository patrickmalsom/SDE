/*   SDE.c 
 *   Written Summer 2013 -- Patrick Malsom
 */

// =========================================
// Library Definitions
// =========================================
//STD Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//GNU Scientific Libraries
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

//Define the Force
#define F(x) 4.0*x*(1.0-x*x)

//===============================================================
//               MAIN Program
//===============================================================
int main(int argc, char *argv[])
{ 
  setbuf(stdout,NULL);  //allows a pipe to from stdout to file

  //============= GSL RNG =======================================
  const gsl_rng_type * RanNumType;
  gsl_rng *RanNumPointer; 
  gsl_rng_env_setup();
  RanNumType = gsl_rng_default;
  RanNumPointer= gsl_rng_alloc (RanNumType);
  //===============================================================

  // Define the constants
  double Temp=atof(argv[1]);             // configurational Temperature
  int Numt=atoi(argv[2]);              // total number of time steps.
  double dt=0.001;              // time step
  double xstart=1.0;            // starting position
  double pref=sqrt(2.0*Temp*dt);  // prefactor for the thermal weight
  int trans=0;                  // number of transitions completed
  double basin=xstart;          // value of the last visited basin
  double xold=xstart;           // initialize the starting point
  double xnew;

//===============================================================
  int i;
  for(i=0;i<Numt;i++)
  {
    xnew=xold+dt*F(xold)+pref*gsl_ran_ugaussian(RanNumPointer);
    if(fabs(xnew) > 1.0)
    {
      if(basin * xnew < 0.0 )
      {
        trans=trans+1;
        if(xnew>0.0)
          basin=1.0;
        else
          basin=-1.0;
      }
    }
  xold=xnew;
  }
  //===============================================================
  printf("Temp=%f,Trans=%d\n",Temp,trans);
  //===============================================================

    // GSL random number generator release memory
  gsl_rng_free (RanNumPointer);
  return(0);
}
