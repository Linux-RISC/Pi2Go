#ifndef __PID_HPP__
#define __PID_HPP__

// some ideas taken from https://github.com/br3ttb/Arduino-PID-Library
class PID {

	float Kp, Ki, Kd;
	float setPoint;
	float input;
	float output;
	float minOutput, maxOutput;
	unsigned sampleTime_ms;
	float dt;
	//clock_t dt;
	float proportional, integral, derivative;
	float previous_error, error;
	struct timeval previous_time;
	//clock_t previous_time;
	bool b_get_previous_time; // to get previous_time

public:

	PID (float Kp,float Ki,float Kd,float setPoint,float minOutput,float maxOutput);
	bool compute (float input,bool externalTimeCheck=false);
	// resets firstCall, sampleTime_ms, integral and previous_error
	void reset();

	static float difftime_ms (const struct timeval& startTime,const struct timeval& endTime);
	static float difftime_ms_msg (const struct timeval& startTime,const struct timeval& endTime,char *msg);
	static clock_t difftime_ms (clock_t startTime,clock_t endTime);
	static clock_t difftime_ms_msg (clock_t startTime,clock_t endTime,char *msg);
	
	// get/set methods
	float get_Kp();
	void set_Kp(float Kp);
	float get_Ki();
	void set_Ki(float Ki);
	float get_Kd();
	void set_Kd(float Kd);
	float get_minOutput();
	void set_minOutput(float minOutput);
	float get_maxOutput();
	void set_maxOutput(float maxOutput);
	float get_setPoint();
	void set_setPoint(float setPoint);
	unsigned get_sampleTime_ms();
	void set_sampleTime_ms(unsigned sampleTime_ms);
	float get_input();
	float get_output();
	//clock_t get_dt();
	float get_dt();
	float get_previous_error();
	float get_error();
	float get_proportional();
	float get_integral();
	float get_derivative();
};

#endif
