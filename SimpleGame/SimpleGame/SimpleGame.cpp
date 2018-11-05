/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "ScnMgr.h"
ScnMgr *g_ScnMgr = NULL;
DWORD prev_render_time = 0;
BOOL W_Key_State = false;
BOOL A_Key_State = false;
BOOL S_Key_State = false;
BOOL D_Key_State = false;
int ShootKey = SHOOT_NONE;

void RenderScene(void)	//1초에 최소 60번 이상 출력되어야 하는 함수
{
	if (prev_render_time ==0)
		prev_render_time = timeGetTime();
	//Elapsed Time
	DWORD current_time = timeGetTime();
	DWORD elapsed_time = current_time - prev_render_time;
	prev_render_time = current_time;
	float eTime = elapsed_time / 1000.f;//convert to second
//	std::cout << "elapsedTime:" << eTime << std::endl;
	std::cout << "w:" << W_Key_State << " a:" << A_Key_State << " s:" << S_Key_State << " d:" << D_Key_State << std::endl;
	
	float forceX=0.f, forceY = 0.f;
	float amount = 10.0f;

	if (W_Key_State)
		forceY += amount;
	if (A_Key_State)
		forceX -= amount;
	if (S_Key_State)
		forceY -= amount;
	if (D_Key_State)
		forceX += amount;

	g_ScnMgr->ApplyForce(forceX, forceY, eTime);
	g_ScnMgr->Update(eTime);
	g_ScnMgr->RenderScene();
	g_ScnMgr->Shoot(ShootKey);
	glutSwapBuffers();
}
void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}
void KeyDownInput(unsigned char key, int x, int y)
{
	float amount = 0.1f;
	switch (key) {
	case 'w':
		W_Key_State = TRUE;
		break;
	case 'a':
		A_Key_State = TRUE;
		break;
	case 's':
		S_Key_State = TRUE;
		break;
	case 'd':
		D_Key_State = TRUE;
		break;
	default:
		break;
	}
}
void KeyUpInput(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		W_Key_State = FALSE;
		break;
	case 'a':
		A_Key_State = FALSE;
		break;
	case 's':
		S_Key_State = FALSE;
		break;
	case 'd':
		D_Key_State = FALSE;
		break;
	default:

		break;
	}
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}
void SpecialKeyDownInput(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT) {
		ShootKey = SHOOT_LEFT;
	}
	else if (key == GLUT_KEY_RIGHT) {
		ShootKey = SHOOT_RIGHT;
	}
	else if (key == GLUT_KEY_UP) {
		ShootKey = SHOOT_UP;
	}
	else if (key == GLUT_KEY_DOWN) {
		ShootKey = SHOOT_DOWN;
	}

	RenderScene();

}
void SpecialKeyUpInput(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		ShootKey = SHOOT_NONE;
	}
	else if (key == GLUT_KEY_RIGHT) {
		ShootKey = SHOOT_NONE;
	}
	else if (key == GLUT_KEY_UP) {
		ShootKey = SHOOT_NONE;
	}
	else if (key == GLUT_KEY_DOWN) {
		ShootKey = SHOOT_NONE;
	}
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	g_ScnMgr = new ScnMgr();
	glutMainLoop();
	delete g_ScnMgr;

    return 0;
}

