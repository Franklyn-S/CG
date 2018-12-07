#ifndef OBJETO_H_
#define OBJETO_H_

#include "Vector3.h"
#include "Texture.h"

using namespace std;
class Objeto {
public:
	//Objeto(){}
	virtual bool RayIntersects(Vector3 raydir,Vector3 rayor , float *t)=0;


	virtual Vector3 getNormal(Vector3 hitpoint)=0;
	virtual Texture getTexture()=0;
	virtual float getPolimento()=0;

	virtual void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp)=0;
	virtual void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp)=0;
};

#endif /* PLANO_H_ */