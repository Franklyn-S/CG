#ifndef PLANO_H_
#define PLANO_H_

#include "Vector3.h"
#include "Texture.h"
#include "Objeto.h"

using namespace std;
class Plano: public Objeto {
public:
	

	Texture textura =Texture({0,0,0},{0,0,0},{0,0,0});
	Vector3 position1;
	Vector3 position2;
	Vector3 position3;
	float polimento;
	
	
	Plano(Vector3 position1 ,Vector3 position2,Vector3 position3, Texture textura ,float polimento);
	Plano();
	
	bool RayIntersects(Vector3 raydir,Vector3 rayor , float *t);	
	
	Vector3 getNormal(Vector3 hitpoint);
	Texture getTexture();
	float getPolimento();

	void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
	void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
};

#endif /* PLANO_H_ */