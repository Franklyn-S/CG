#ifndef PRISMA_H_
#define PRISMA_H_

#include "Vector3.h"
#include "Texture.h"
#include "Quadrilatero.h"
#include "Objeto.h"


using namespace std;
class Prisma {
public:
	Quadrilatero *f1;
	Quadrilatero *f2;
	Quadrilatero *f3;
	Quadrilatero *f4;
	Quadrilatero *f5;
	Quadrilatero *f6;
	Prisma(Quadrilatero f1 , Quadrilatero f2 , Quadrilatero f3 , Quadrilatero f4 , Quadrilatero f5 , Quadrilatero f6);
	
	Prisma();
	bool RayIntersects(Vector3 raydir,Vector3 rayor , float *t);

	void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
	void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
};

#endif /* PLANO_H_ */