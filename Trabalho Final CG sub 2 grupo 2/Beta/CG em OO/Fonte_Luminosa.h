#ifndef FONTE_LUMINOSA_H_
#define FONTE_LUMINOSA_H_

#include "Vector3.h"
#include "Texture.h"


using namespace std;
class Fonte_Luminosa {
public:
	
	virtual Vector3 Iluminacao(Vector3 observer , Vector3 Point_Object , Vector3 Normal_Of_Face , Texture Texture_Object , float polimento)=0;

	virtual Vector3 Iluminacao(Texture textura)=0;

	virtual void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp)=0;
	virtual void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp)=0;
	
	virtual Vector3 getPosition()=0;
	virtual Vector3 getColor()=0;
};

#endif /* PLANO_H_ */