#ifndef ILUMINATION_H
#define ILUMINATION_H

#include "LightSource.h"
#include "Vec3.h"
#include "Texture.h"

class Ilumination {
public:
	Vec3 Ipix = {0,0,0};
	Ilumination(Vec3 observer, Vec3 Pint, Vec3 normalOfFaces, Texture texture, LightSource &post);

	Ilumination(Texture t, LightSource &post);

	Vec3 generateL(Vec3 Pint, LightSource &post);
	Vec3 generateV(Vec3 Pint, Vec3 observer);
	Vec3 generateR(Vec3 l, Vec3 n);

	Vec3 Idif(LightSource &post, Vec3 textureObj, Vec3 l, Vec3 n);
	Vec3 Iesp(LightSource &post, Vec3 textureObj, Vec3 r, Vec3 v, int m);
};


#endif
