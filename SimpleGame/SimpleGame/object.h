#pragma once
class object
{
	int hp;
	float pos_x, pos_y, pos_z;
	float size_x, size_y, maxX, maxY;

	float velX, velY;
	float acc_x, acc_y;
	float forceX, forceY;
	
	float mass;
	float coefriction;
	float elapsed_time_in_sec;
	
	int kind;

public:
	object();
	~object();
	void Update(float elapsed_time_in_sec);

	void setLocation(float x, float y, float z);
	void getLocation(float *x,float *y, float *z);
	void setSize(float size_x, float size_y);
	void getSize(float *size_x, float *size_y);

	void setVelocity(float velX, float velY);
	void getVelocity(float *velX, float *velY);

	void setAcc(float acc_x, float acc_y);
	void getAcc(float *acc_x, float *acc_y);
	
	void setforce(float forceX, float forceY);
	void getforce(float *forceX, float *forceY);

	void setmass(float mass);
	void getmass(float *mass);

	void setfrictionCoef(float friction);
	void getfrictionCoef(float *friction);

	void setkind(int kind);
	void getkind(int *kind);

	void ApplyForce(float forceX, float forceY,float elapsed_time_in_sec);


};
