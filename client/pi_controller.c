#include "pi_controller.h"
#include <time.h>

double Compute(double Input, unsigned long *lastTime, double *errSum)
{
   unsigned long now = msecond();
   int timeChange = (now - (*lastTime));
   if(timeChange>=SampleTime)
   {
      /*Compute all the working error variables*/
      double error = Setpoint - Input;
      (*errSum) += error*timeChange;
 
      /*Remember time for next time*/
      (*lastTime) = now;
      /*Compute PID Output*/
      return (Kp * error + Ki * (*errSum));
 
   }
}

