#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Vec3.h"
#include "Texture.h"
#include "Light.h"

class LightSource: public Light{
private:
	Vec3 position = {0,0,0};
	Vec3 color = {0,0,0};
public:
	LightSource(Vec3 position, Vec3 color);
	Vec3 getPosition();
	Vec3 getColor();

	Vec3 Ilumination(Vec3 observer, Vec3 Pint, Vec3 normalOfFaces, Texture texture, float polimento);

	Vec3 Ilumination(Texture t);
	
	void cameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp);
	void worldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp);

	Vec3 generateL(Vec3 Pint);
	Vec3 generateV(Vec3 Pint, Vec3 observer);
	Vec3 generateR(Vec3 l, Vec3 n);

	Vec3 Idif(Vec3 textureObj, Vec3 l, Vec3 n);
	Vec3 Iesp(Vec3 textureObj, Vec3 r, Vec3 v, int m);

};


#endif
