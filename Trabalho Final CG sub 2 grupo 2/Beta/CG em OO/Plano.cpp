#include "Plano.h"
#include "Camera.h"

Plano::Plano(Vector3 position1 ,Vector3 position2,Vector3 position3, Texture textura , float polimento){
	this->textura=textura;
	this->position1=position1;
	this->position2=position2;
	this->position3=position3;
	this->polimento=polimento;
	
}

Plano::Plano(){
	this->textura=Texture({0,0,0} , {0,0,0} , {0,0,0});
	this->position1={0,0,0};
	this->position2={0,0,0};
	this->position3={0,0,0};
	this->polimento=1;	
}


bool Plano::RayIntersects(Vector3 raydir,Vector3 rayor , float *distancia){
	

	float dDotN = raydir.Dot(this->getNormal({0,0,0}));
	
	Vector3 aux={0,0,0};
	
	//paralelo ao plano = infinitas interseções
	if (dDotN == 0.0f){
		return false;
	}

	float t =(( this->position1-rayor ).Dot( this->getNormal({0,0,0}) )) / dDotN;

	//perto demais
	if (t <= 0.05) {
		return false;
	}
	
	*distancia = t;
	
	return true;
}

Vector3 Plano::getNormal(Vector3 hitpoint){
	Vector3 ray1= (this->position2 - this->position1).Normalize();
	Vector3 ray2=(this->position3 - this->position2).Normalize();
	Vector3 aux={0,1,0};
	return ray2.Cross(ray1);
	//return aux;

}

Texture Plano::getTexture(){
	return this->textura;
}

float Plano::getPolimento(){
	return this->polimento;
}
void Plano::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Camera_Mundo(camera , LoockAt , ViewUp , this->position1);
        Camera_Mundo(camera , LoockAt , ViewUp , this->position2);
        Camera_Mundo(camera , LoockAt , ViewUp , this->position3);
}
void Plano::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position1);
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position2);
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position3);
}