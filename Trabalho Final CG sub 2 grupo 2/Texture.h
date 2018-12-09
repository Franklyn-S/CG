#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vec3.h"

class Texture{
public:
	Vec3 amb, dif, esp;
	Texture();
	Texture(Vec3 amb, Vec3 dif, Vec3 esp);
};




#endif

