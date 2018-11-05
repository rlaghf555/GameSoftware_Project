#include "stdafx.h"
#include "object.h"
#include <math.h>
#include <float.h>
object::object()
{
	pos_x = 0;	pos_y = 0;
	size_x = 0;	size_y = 0;
	acc_x = 0; acc_y = 0;

}


object::~object()
{
	delete this;
}

void object::Update(float elapsed_time_in_sec)
{
	
	float gz = mass*9.8;
	float friction = coefriction*gz;
	float velmag = sqrtf(velX*velX + velY*velY);

	if (velmag < FLT_EPSILON) {
		velX = 0.f;
		velY = 0.f;
	}
	else {
		//방향 구하기 정규화
		float fx = -friction*velX / velmag;
		float fy = -friction*velY / velmag;

		float accx = fx / mass;
		float accy = fy / mass;
		float newVelX = velX + accx*elapsed_time_in_sec;
		float newVelY = velY + accy*elapsed_time_in_sec;
		if (newVelX*velX < 0.f)
			velX = 0.f;
		else 
			velX = newVelX;
		if (newVelY*velY < 0.f)
			velY = 0.f;
		else 
			velY = newVelY;
	}
	//속도 계산
	velX = velX + acc_x*elapsed_time_in_sec;
	velY = velY + acc_y*elapsed_time_in_sec;

	//갱신될 위치 = 이전 위치 + 속도 * 시간 
	pos_x = pos_x + velX*elapsed_time_in_sec;
	pos_y = pos_y + velY*elapsed_time_in_sec;

	

}
void object::setLocation(float x, float y, float z)
{
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

void object::getLocation(float *x, float *y, float *z)
{
	*x = pos_x;
	*y = pos_y;
	*z = pos_z;
}

void object::setSize(float size_x, float size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;

}

void object::getSize(float *size_x, float *size_y)
{
	*size_x = this->size_x;
	*size_y = this->size_y;

}

void object::setVelocity(float velX, float velY)
{
	this->velX = velX;
	this->velY = velY;
}

void object::getVelocity(float * velX, float * velY)
{
	*velX = this->velX;
	*velY = this->velY;
}

void object::setAcc(float acc_x, float acc_y)
{
	this->acc_x = acc_x;
	this->acc_y = acc_y;
}

void object::getAcc(float * acc_x, float * acc_y)
{
	*acc_x = this->acc_x;
	*acc_y = this->acc_y;
}

void object::setforce(float forceX, float forceY)
{
	this->forceX = forceX;
	this->forceY = forceY;
}

void object::getforce(float * forceX, float * forceY)
{
	*forceX = this->forceX;
	*forceY = this->forceY;
}

void object::setmass(float mass)
{
	this->mass = mass;
}

void object::getmass(float * mass)
{
	*mass = this->mass;
}

void object::setfrictionCoef(float friction)
{
	this->coefriction = friction;

}

void object::getfrictionCoef(float * friction)
{

	*friction = this->coefriction;

}

void object::setkind(int kind)
{
	this->kind = kind;
}

void object::getkind(int * kind)
{
	*kind = this->kind;

}

void object::ApplyForce(float forceX, float forceY, float elapsed_time_in_sec)
{
	//가속도 계산 힘/질량
	acc_x = forceX / mass;
	acc_y = forceY / mass;

	//속도 계산
	velX = velX + acc_x*elapsed_time_in_sec;
	velY = velY + acc_y*elapsed_time_in_sec;

	acc_x = 0;
	acc_y = 0;

	
}


