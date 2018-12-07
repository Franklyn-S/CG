/*
 * Sphere.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef SPHERE_H_
#define SPHERE_H_
#include "Vector3.h"
#include "GameObject.h"
#include "Texture.h"
#include "LightSource.h"
#include "Objeto.h"
class Sphere: public Objeto {
public:
	Vector3 centro={0,0,0};
	Texture textura=Texture({0,0,0},{0,0,0},{0,0,0});
	double raio;
	float polimento;
	
	Sphere(Vector3 centro , double raio,float polimento , Texture textura);
	Sphere();
	
	bool RayIntersects(Vector3 raydir,Vector3 rayor , float *t);

	Vector3 getNormal(Vector3 hitpoint);
	Texture getTexture();
	float getPolimento();

	void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
	void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
};

#endif /* SPHERE_H_ */
