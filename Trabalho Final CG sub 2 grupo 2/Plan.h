#ifndef PLAN_H
#define PLAN_H

#include "Vec3.h"
#include "Texture.h"
#include "Object.h"


class Plan: public Object{
public:
	Texture texture = Texture();
	Vec3 pos1, pos2, pos3;
	float polishing;

	Plan();
	Plan(Vec3 p1, Vec3 p2, Vec3 p3, Texture t, float p);

	bool RayIntersects(Vec3 V, Vec3 O, float *t);

	Vec3 getNormal();
	Texture getTexture();
	float getPolimento();

	void cameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp);
	void worldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp);
};

#endif