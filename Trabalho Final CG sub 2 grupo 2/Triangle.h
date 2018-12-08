#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vec3.h"
#include "Texture.h"
#include "Object.h"


class Triangle: public Object{
public:
	Texture texture = Texture();
	Vec3 pos1, pos2, pos3;
	float polishing;

	Triangle();
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Texture t, float p);

	bool RayIntersects(Vec3 V, Vec3 O, float *t);

	Vec3 getNormal();
	Texture getTexture();
	float getPolimento();

	void CameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp);
	void WorldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp);
};

#endif