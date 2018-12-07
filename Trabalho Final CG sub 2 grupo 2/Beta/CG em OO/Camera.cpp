#include "Camera.h"
#include "Vector3.h"

using namespace std;

void Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp , Vector3 &ponto){
	Vector3 Kc;
	Vector3 Ic;
	Vector3 Jc;
	Vector3 aux;

	Kc=(LoockAt-camera).Normalize();
	
	aux=ViewUp-LoockAt;

	Ic=(Kc.Cross(aux)).Normalize();

	Jc= (Ic.Cross(Kc)).Normalize();
	
	float MundoParaCamera[4][4];

	MundoParaCamera[0][0] = Ic[0];
	MundoParaCamera[0][1] = Ic[1];
	MundoParaCamera[0][2] = Ic[2];
	MundoParaCamera[0][3] = -Ic.Dot(camera);

	MundoParaCamera[1][0] = Jc[0];
	MundoParaCamera[1][1] = Jc[1];
	MundoParaCamera[1][2] = Jc[2];
	MundoParaCamera[1][3] = -Jc.Dot(camera);

	MundoParaCamera[2][0] = Kc[0];
	MundoParaCamera[2][1] = Kc[1];
	MundoParaCamera[2][2] = Kc[2];
	MundoParaCamera[2][3] = -Kc.Dot(camera);

	MundoParaCamera[3][0] = 0;
	MundoParaCamera[3][1] = 0;
	MundoParaCamera[3][2] = 0;
	MundoParaCamera[3][3] = 1;

	aux[0] = MundoParaCamera[0][0] * ponto[0] + MundoParaCamera[0][1] * ponto[1] + MundoParaCamera[0][2] * ponto[2] + MundoParaCamera[0][3];

	aux[1] = MundoParaCamera[1][0] * ponto[0] + MundoParaCamera[1][1] * ponto[1] + MundoParaCamera[1][2] * ponto[2] + MundoParaCamera[1][3];

	aux[2] = MundoParaCamera[2][0] * ponto[0] + MundoParaCamera[2][1] * ponto[1] + MundoParaCamera[2][2] * ponto[2] + MundoParaCamera[2][3];
	
	for (int i = 0; i < 3; i++){
 		ponto[i] = aux[i];
	}	

}

void Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp , Vector3 &ponto){
	Vector3 Kc;
	Vector3 Ic;
	Vector3 Jc;
	Vector3 aux;

	Kc=(LoockAt-camera).Normalize();
	
	aux=ViewUp-LoockAt;

	Ic=(Kc.Cross(aux)).Normalize();

	Jc= (Ic.Cross(Kc)).Normalize();
	
	float CameraParaMundo[4][4];

	CameraParaMundo[0][0] = Ic[0];
	CameraParaMundo[0][1] = Jc[0];
	CameraParaMundo[0][2] = Kc[0];
	CameraParaMundo[0][3] = camera[0];

	CameraParaMundo[1][0] = Ic[1];
	CameraParaMundo[1][1] = Jc[1];
	CameraParaMundo[1][2] = Kc[1];
	CameraParaMundo[1][3] = camera[1];

	CameraParaMundo[2][0] = Ic[2];
	CameraParaMundo[2][1] = Jc[2];
	CameraParaMundo[2][2] = Kc[2];
	CameraParaMundo[2][3] = camera[2];

	CameraParaMundo[3][0] = 0;
	CameraParaMundo[3][1] = 0;
	CameraParaMundo[3][2] = 0;
	CameraParaMundo[3][3] = 1;

	aux[0] = CameraParaMundo[0][0] * ponto[0] + CameraParaMundo[0][1] * ponto[1] + CameraParaMundo[0][2] * ponto[2] + CameraParaMundo[0][3];

	aux[1] = CameraParaMundo[1][0] * ponto[0] + CameraParaMundo[1][1] * ponto[1] + CameraParaMundo[1][2] * ponto[2] + CameraParaMundo[1][3];

	aux[2] = CameraParaMundo[2][0] * ponto[0] + CameraParaMundo[2][1] * ponto[1] + CameraParaMundo[2][2] * ponto[2] + CameraParaMundo[2][3];
	
	for (int i = 0; i < 3; i++){
 		ponto[i] = aux[i];
	} 

}