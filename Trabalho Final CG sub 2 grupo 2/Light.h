#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3.h"
#include "Texture.h"

class Light {
public:
	virtual Vec3 Ilumination(Vec3 observer, Vec3 Pint, Vec3 normalOfFaces, Vec3 texture, float polimento)=0;

	virtual Vec3 Ilumination(Texture t)= 0;
	
	virtual void cameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp)=0;
	virtual void worldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp)=0;

	virtual Vec3 getPosition()=0;
	virtual Vec3 getColor()=0;
};

#endif