#ifndef TRIANGULO_H_
#define TRIANGULO_H_

#include "Vector3.h"
#include "Texture.h"
#include "Objeto.h"

using namespace std;
class Triangulo: public Objeto {
public:
	

	Texture textura =Texture({0,0,0},{0,0,0},{0,0,0});
	Vector3 position1;
	Vector3 position2;
	Vector3 position3;
	float polimento;
	
	
	Triangulo(Vector3 position1 ,Vector3 position2,Vector3 position3, Texture textura ,float polimento);
	Triangulo();
	
	bool RayIntersects(Vector3 raydir,Vector3 rayor , float *t);	
	bool Esta_Contido(Vector3 hitpoint);

	Vector3 getNormal(Vector3 hitpoint);
	Texture getTexture();
	float getPolimento();

	void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
	void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
};

#endif /* TRIANGULO_H_ */