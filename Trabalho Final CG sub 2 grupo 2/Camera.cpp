#include "Camera.h"


void camera_World(Vec3 camera , Vec3 lookAt , Vec3 viewUp , Vec3 &ponto){
	Vec3 kc, ic, jc, Vup, I, aux;
	kc = (lookAt-camera).normalize();
	Vup = viewUp-lookAt;
	I = Vup->*kc;
	ic = I.normalize();
	jc = kc->*ic;

	float cameraWorld[4][4] = { 
		{ic[0],ic[1], ic[2], -(ic.dotProduct(camera))},
		{jc[0],jc[1], jc[2], -(jc.dotProduct(camera))},
		{kc[0],kc[1], kc[2], -(kc.dotProduct(camera))},
		{0, 0, 0, 1}};

	aux[0] = cameraWorld[0][0]*ponto[0] + cameraWorld[0][1]*ponto[1] + cameraWorld[0][2]*ponto[2] + cameraWorld[0][3];
	aux[1] = cameraWorld[1][0]*ponto[0] + cameraWorld[1][1]*ponto[1] + cameraWorld[1][2]*ponto[2] + cameraWorld[1][3];
	aux[2] = cameraWorld[2][0]*ponto[0] + cameraWorld[2][1]*ponto[1] + cameraWorld[2][2]*ponto[2] + cameraWorld[2][3];

	ponto[0]= aux[0];
	ponto[1]= aux[1];
	ponto[2]= aux[2];
}
void world_Camera(Vec3 camera , Vec3 lookAt , Vec3 viewUp , Vec3 &ponto){
	Vec3 kc, ic, jc, Vup, I, aux;
	kc = (lookAt-camera).normalize();
	Vup = viewUp-lookAt;
	I = Vup->*kc;
	ic = I.normalize();
	jc = kc->*ic;

	float worldCamera[4][4] = { 
		{ic[0],ic[1], ic[2], camera[0]},
		{jc[0],jc[1], jc[2], camera[1]},
		{kc[0],kc[1], kc[2], camera[2]},
		{0, 0, 0, 1}};

	aux[0] = worldCamera[0][0]*ponto[0] + worldCamera[0][1]*ponto[1] + worldCamera[0][2]*ponto[2] + worldCamera[0][3];
	aux[1] = worldCamera[1][0]*ponto[0] + worldCamera[1][1]*ponto[1] + worldCamera[1][2]*ponto[2] + worldCamera[1][3];
	aux[2] = worldCamera[2][0]*ponto[0] + worldCamera[2][1]*ponto[1] + worldCamera[2][2]*ponto[2] + worldCamera[2][3];

	ponto[0]= aux[0];
	ponto[1]= aux[1];
	ponto[2]= aux[2];
}