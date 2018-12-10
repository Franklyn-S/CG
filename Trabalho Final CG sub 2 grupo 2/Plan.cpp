#include "Plan.h"
#include "Camera.h"

Plan::Plan(){
	texture = Texture();
	pos1 = {0,0,0};
	pos2 = {0,0,0};
	pos3 = {0,0,0};
	polishing = 1;
}
Plan::Plan(Vec3 p1, Vec3 p2, Vec3 p3, Texture t, float p){
	texture = t;
	pos1 = p1;
	pos2 = p2;
	pos3 = p3;
	polishing = p;
}
//fazer as coisas de Vec3
bool Plan::RayIntersects(Vec3 V, Vec3 O, float *t){
	Vec3 w1, w2, w3, Pint, n;
	n = this->getNormal();
	float vDotn = V.dotProduct(n);
	if(vDotn = 0.0f){
		return false;
	}
	Vec3 w = pos1 - O;
	float wDotn = w.dotProduct(n);
	*t = wDotn/vDotn;
	
	Pint = V**t;
	w1 = pos1 - Pint;
	w2 = pos2 - Pint;
	w3 = pos3 - Pint;
	float x,y,z;
	x = (w1->*w2).dotProduct(n);
	y = (w2->*w3).dotProduct(n);
	z = (w3->*w1).dotProduct(n);
	if ( ((x>0)&&(y>0)&&(z>0)) || ((x<0)&&(y<0)&&(z<0))){
		return true;
	}
	return false;

}

Vec3 Plan::getNormal(){
	Vec3 ray1, ray2;
	ray1 = (pos2 - pos1).normalize();
	ray2 = (pos3 - pos2).normalize();
	return ray2->*ray1;
}
Texture Plan::getTexture(){
	return this->texture;
}
float Plan::getPolishing(){
	return polishing;
}

void Plan::cameraWorld(Vec3 camera, Vec3 lookAt,Vec3 viewUp){
	camera_World(camera , lookAt , viewUp , pos1);
	camera_World(camera , lookAt , viewUp , pos2);
	camera_World(camera , lookAt , viewUp , pos3);
}
void Plan::worldCamera(Vec3 camera, Vec3 lookAt,Vec3 viewUp){
	world_Camera(camera , lookAt , viewUp , pos1);
	world_Camera(camera , lookAt , viewUp , pos2);
	world_Camera(camera , lookAt , viewUp , pos3);
}