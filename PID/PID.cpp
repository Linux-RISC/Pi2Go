#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "PID.hpp"

using namespace std;

//--------------------------------------------------------------------------------
PID::PID (float Kp,float Ki,float Kd,float setPoint,float minOutput, float maxOutput) {

	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	this->setPoint = setPoint;
	this->minOutput = minOutput;
	this->maxOutput = maxOutput;
	reset();
}
//--------------------------------------------------------------------------------
void PID::reset () {

	b_get_previous_time = true;
	sampleTime_ms = 100;
	previous_error = 0;
	integral = 0;

	// not necessary for calculations, just to assign initial values
	dt = 100;
	proportional = 0;
	derivative = 0;
	error = 0;
	output = 0;
	input = 0;
}
//--------------------------------------------------------------------------------
float PID::get_Kp () {

	return Kp;
}
//--------------------------------------------------------------------------------
void PID::set_Kp (float Kp) {

	this->Kp = Kp;
}
//--------------------------------------------------------------------------------
float PID::get_Ki () {

	return Ki;
}
//--------------------------------------------------------------------------------
void PID::set_Ki (float Ki) {

	this->Ki = Ki;
}
//--------------------------------------------------------------------------------
float PID::get_Kd () {

	return Kd;
}
//--------------------------------------------------------------------------------
void PID::set_Kd (float Kd) {

	this->Kd = Kd;
}
//--------------------------------------------------------------------------------
float PID::get_minOutput () {

	return minOutput;
}
//--------------------------------------------------------------------------------
void PID::set_minOutput (float minOutput) {

	this->minOutput = minOutput;
}
//--------------------------------------------------------------------------------
float PID::get_maxOutput () {

	return maxOutput;
}
//--------------------------------------------------------------------------------
void PID::set_maxOutput (float maxOutput) {

	this->maxOutput = maxOutput;
}
//--------------------------------------------------------------------------------
float PID::get_setPoint () {

	return setPoint;
}
//--------------------------------------------------------------------------------
void PID::set_setPoint (float setPoint) {

	this->setPoint = setPoint;
}
//--------------------------------------------------------------------------------
unsigned PID::get_sampleTime_ms () {

	return sampleTime_ms;
}
//--------------------------------------------------------------------------------
void PID::set_sampleTime_ms (unsigned sampleTime_ms) {
	
	if (sampleTime_ms==0)
		return;
	this->sampleTime_ms = sampleTime_ms;
}
//--------------------------------------------------------------------------------
float PID::get_input () {

	return input;
}
//--------------------------------------------------------------------------------
float PID::get_output () {

	return output;
}
//--------------------------------------------------------------------------------
float PID::get_dt () {

	return dt;
}
//--------------------------------------------------------------------------------
float PID::get_previous_error () {

	return previous_error;
}
//--------------------------------------------------------------------------------
float PID::get_error () {

	return error;
}
//--------------------------------------------------------------------------------
float PID::get_proportional () {

	return proportional;
}
//--------------------------------------------------------------------------------
float PID::get_integral () {

	return integral;
}
//--------------------------------------------------------------------------------
float PID::get_derivative () {

	return derivative;
}
//--------------------------------------------------------------------------------
float PID::difftime_ms (const struct timeval& startTime,const struct timeval& endTime)
{
	// some times the calculation is incorrect this way, perhaps due to consecutive fabs() calls
    //return fabs((endTime.tv_sec - startTime.tv_sec)*1000.0) + fabs((endTime.tv_usec - startTime.tv_usec)/1000.0);
	return fabs(endTime.tv_sec*1000.0+endTime.tv_usec/1000.0 - (startTime.tv_sec*1000.0+startTime.tv_usec/1000.0));
}
//--------------------------------------------------------------------------------
float PID::difftime_ms_msg (const struct timeval &startTime,const struct timeval &endTime,char *msg) {

	float totalTime = difftime_ms (startTime,endTime);
	printf("%s %.2f ms\n",msg,totalTime);
	return totalTime;
}
/*----------------------------------------------------------------------------*/
clock_t PID::difftime_ms (clock_t startTime,clock_t endTime) {

	return (endTime>startTime ? endTime-startTime : startTime-endTime)/(CLOCKS_PER_SEC/1000.0);
}
/*----------------------------------------------------------------------------*/
clock_t PID::difftime_ms_msg (clock_t startTime,clock_t endTime,char *msg) {

	clock_t totalTime = difftime_ms (startTime,endTime);
	printf("%s %lu ms\n",msg,totalTime);
	return totalTime;
}
/*----------------------------------------------------------------------------*/
bool PID::compute (float input,bool externalTimeCheck) {
/*
https://en.wikipedia.org/wiki/PID_controller#Pseudocode
previous_error = 0
integral = 0 
start:
  error = setpoint - input
  integral = integral + error*dt
  derivative = (error - previous_error)/dt
  output = Kp*error + Ki*integral + Kd*derivative
  previous_error = error
  wait(dt)
  goto start
*/
	struct timeval current_time;
	//clock_t current_time;

	if (!externalTimeCheck)
		if (b_get_previous_time) {
			gettimeofday(&previous_time,NULL);
			//previous_time = clock();
			b_get_previous_time = false;
			return false;
		}

	gettimeofday(&current_time,NULL);
	//current_time = clock();
	if (!externalTimeCheck)
		if ((dt=difftime_ms(previous_time,current_time))<sampleTime_ms) {
			//printf ("-%.2f\n",dt);
			return false;
		}
	//printf ("+%.2f\n",dt);
	b_get_previous_time = true;
	previous_time = current_time;
	this->input = input;
	previous_error = error;
	error = setPoint - input;
	proportional = error;
	integral = integral+error*dt;
	derivative = (error - previous_error)/dt;
	output = Kp*error + Ki*integral + Kd*derivative;

	if (output>maxOutput)
		output = maxOutput;
	else
		if (output<minOutput)
			output = minOutput;

	return true;
}
//--------------------------------------------------------------------------------

