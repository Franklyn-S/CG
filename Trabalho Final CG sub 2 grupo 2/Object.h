#ifndef OBJECT_H
#define OBJECT_H

#include "Vec3.h"
#include "Texture.h"

class Object {
public:
	virtual bool RayIntersects(Vec3 raydir, Vec3 rayor, float *t)=0;

	virtual Vec3 getNormal(Vec3 hitPoint)=0;
	virtual Texture getTexture()=0;
	virtual float getPolishing()=0;

	virtual void CameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp)=0;
	virtual void WorldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp)=0;
};

#endif