#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_

#define Kp 10
#define Ki 800
#define Setpoint 1
#define SampleTime 5

double Compute(double Input, unsigned long *lastTime, double *errSum);



#endif