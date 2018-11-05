#include "stdafx.h"
#include "ScnMgr.h"


ScnMgr::ScnMgr()
{

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		objs[i] = NULL;
	}
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	Character_Texture = m_Renderer->CreatePngTexture("./Textures/IsaacCry.png");
	Explosion_Texture = m_Renderer->CreatePngTexture("./Textures/8X6explosion.png");

	objs[HERO_ID]=new object();
	objs[HERO_ID]->setLocation(0, 0, 0.5f);
	objs[HERO_ID]->setAcc(0, 0);
	objs[HERO_ID]->setforce(0, 0);
	objs[HERO_ID]->setfrictionCoef(0.5f);
	objs[HERO_ID]->setmass(1.f);
	objs[HERO_ID]->setVelocity(0, 0);
	objs[HERO_ID]->setSize(0.5f, 0.5f);
	objs[HERO_ID]->setkind(KIND_HERO);

}
int seq = 0;
void ScnMgr::RenderScene()	//1초에 최소 60번 이상 출력되어야 하는 함수
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i] != NULL) {
			float x, y, z;
			objs[i]->getLocation(&x, &y, &z);
			float width, height;
			objs[i]->getSize(&width, &height);
			float newx, newy, newz, neww, newh;
			newx = x*100.f;
			newy = y*100.f;
			newz = z*100.f;
			neww = width*100.f;
			newh = height*100.f;
			int seqX = 0;
			int seqY=0;
			seqX=seq % 9;
			seqY = (int)seq / 9;
			seq++;
			if (seq > 48)
				seq = 0;
			glRotated(90.f, 0, 0, 1);
			
			m_Renderer->DrawTextureRectHeight(x*100.f, y*100.f, 0, width * 100, height * 100, 1, 1, 1, 1, Character_Texture, z*100.f);
	/*		m_Renderer->DrawTextureRectSeqXY(
				x*100.f, y*100.f, 0, width * 100, height * 100,
				1, 1, 1, 1,
				Explosion_Texture,
				seqX, seqY,
				8, 6);
				*/
		}
	}
}

ScnMgr::~ScnMgr()
{
	
}
float temp = 10.f;
void ScnMgr::Update(float elapsed_time_in_sec)
{

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i]) {
			objs[i]->Update(elapsed_time_in_sec);
		}
	}
}

void ScnMgr::ApplyForce(float forceX, float forceY, float elapsed_time_in_sec)
{

	objs[HERO_ID]->ApplyForce(forceX, forceY, elapsed_time_in_sec);
	
}

void ScnMgr::AddObject(float px, float py, float pz, float sx, float sy, float vx, float vy,int kind)
{
	int index = FindEmptyObjectSlot();
	if (index < 0) {
		std::cout << "Can't create object with minus index" << std::endl;
		return;
	}
	objs[index] = new object();
	objs[index]->setLocation(px, py, pz);
	objs[index]->setAcc(0, 0);
	objs[index]->setforce(0, 0);
	objs[index]->setfrictionCoef(0.5f);
	objs[index]->setmass(1.f);
	objs[index]->setVelocity(vx, vy);
	objs[index]->setSize(sx, sy);
	objs[index]->setkind(kind);
}

void ScnMgr::Shoot(int ShootKey)
{
	if (ShootKey == SHOOT_NONE) {
		return;
	}
		float px, py, pz;
		float sx, sy;
		float vx, vy;
		objs[HERO_ID]->getLocation(&px, &py, &pz);
		sx = 0.1f;
		sy = 0.1f;
		objs[HERO_ID]->getVelocity(&vx, &vy);
		switch (ShootKey) {
			case SHOOT_LEFT:
				vx += -10.f;
				vy += 0.f;
				break;
			case SHOOT_RIGHT:
				vx += 10.0f;
				vy += 0.f;
				break;
			case SHOOT_UP:
				vx += 0.f;
				vy += 10.f;
				break;
			case SHOOT_DOWN:
				vx += 0.f;
				vy += -10.f;
				break;
		}

		AddObject(
			px, py, pz,
			sx, sy,
			vx, vy,
			KIND_BULLET);
	
}

void ScnMgr::DeleteObject(unsigned int id)
{
	if (objs[id]){
		delete objs[id];
		objs[id] = NULL;
	}
}

int ScnMgr::FindEmptyObjectSlot()
{
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i] == NULL)
			return i;
	}
	std::cout << "object list is full.\n";
	return -1;
}


