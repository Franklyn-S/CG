#ifndef QUADRILATERO_H_
#define QUADRILATERO_H_

#include "Vector3.h"
#include "Texture.h"
#include "Triangulo.h"
#include "Objeto.h"

using namespace std;
class Quadrilatero: public Objeto{
public:
	Texture textura =Texture({0,0,0},{0,0,0},{0,0,0});
	Triangulo *f1;
	Triangulo *f2;
	float polimento;
	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;
	
	
	Quadrilatero(Vector3 position1 ,Vector3 position2,Vector3 position3,Vector3 position4, Texture textura ,float polimento);
	Quadrilatero();
	
	bool RayIntersects(Vector3 raydir,Vector3 rayor , float *t);	
	bool Esta_Contido(Vector3 hitpoint);

	Vector3 getNormal(Vector3 hitpoint);
	Texture getTexture();
	float getPolimento();

	void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
	void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
};

#endif