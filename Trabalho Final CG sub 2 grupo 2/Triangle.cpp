#include "Triangle.h"

Triangle::Triangle(){
	texture = Texture()
	pos1 = {0,0,0}:
	pos2 = {0,0,0}:
	pos3 = {0,0,0}:
	polishing = 1;
}
Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Texture t, float p){
	texture = t;
	pos1 = p1;
	pos2 = p2;
	pos3 = p3;
	polishing = p;
}
//fazer as coisas de Vec3 e vec4
bool Triangle::RayIntersects(Vec3 raydir, Vec3 rayor, float *t);

Vec3 Triangle::getNormal(Vec3 hitPoint);
Texture Triangle::getTexture();
float Triangle::getPolimento();

void Triangle::CameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp);
void Triangle::WorldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp);