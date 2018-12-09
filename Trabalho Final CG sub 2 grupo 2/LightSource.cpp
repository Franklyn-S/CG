#include "LightSource.h"
#include "Camera.h"

#include<math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

LightSource::LightSource(Vec3 position, Vec3 color){
	this->position=position;
	this->color=color;
}
Vec3 LightSource::getPosition(){
	return position;
}
Vec3 LightSource::getColor(){
	return color;
}

Vec3 LightSource::Ilumination(Vec3 observer, Vec3 Pint, Vec3 normalOfFaces, Texture texture, float polishing){
	Vec3 Ipix, n, l, v, r;
	n = normalOfFaces.normalize();
	l = generateL(Pint);
	v = generateV(Pint, observer);
	r = generateR(l, n);

	Ipix = Idif(texture.dif, l, n) + Iesp(texture.esp, r, v, polishing);
	return Ipix;
}

Vec3 LightSource::Ilumination(Texture t){
	Vec3 Ipix = color.arroba(t.amb);
	return Ipix;
}

void LightSource::cameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp){
	camera_World(camera, lookAt, viewUp, position);
}
void LightSource::worldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp){
	world_Camera(camera, lookAt, viewUp, position);
}

Vec3 LightSource::generateL(Vec3 Pint){
	return (position-Pint).normalize();
}
Vec3 LightSource::generateV(Vec3 Pint, Vec3 observer){
	return (observer - Pint).normalize();
}
Vec3 LightSource::generateR(Vec3 l, Vec3 n){
	return n*(2*(l.dotProduct(n))) - l;
}

Vec3 LightSource::Idif(Vec3 textureObj, Vec3 l, Vec3 n){
	double cos = l.dotProduct(n);
	if (cos >= 0){
		return color.arroba(textureObj) * cos;
	}
	return Vec3();
}
Vec3 LightSource::Iesp(Vec3 textureObj, Vec3 r, Vec3 v, int m){
	double cos = v.dotProduct(r);
	if (cos >= 0){
		return color.arroba(textureObj) * pow(cos,m);
	}
	return Vec3();
}