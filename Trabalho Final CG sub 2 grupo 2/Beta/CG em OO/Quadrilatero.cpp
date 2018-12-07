#include "Quadrilatero.h"
#include "Triangulo.h"
#include "Camera.h"
using namespace std;

Quadrilatero::Quadrilatero(Vector3 position1 ,Vector3 position2,Vector3 position3,Vector3 position4, Texture textura ,float polimento){
	this->textura=textura;
	this->p1=position1; 
	this->p2=position2;
	this->p3 =position3;
	this->p4 = position4;
	this->f1=new Triangulo(position1 , position2 , position3 , this->textura , polimento);
	this->f2=new Triangulo(position3 , position4 , position1 , this->textura , polimento);
	
	this->polimento=polimento;
}

Quadrilatero::Quadrilatero(){
	this->textura=Texture({0,0,0} , {0,0,0} , {0,0,0});
	this->f1=new Triangulo({0,0,0} , {0,0,0} , {0,0,0} , this->textura , 1);
	this->f2=new Triangulo({0,0,0} , {0,0,0} , {0,0,0} , this->textura , 1);
	this->polimento=1;
}

bool Quadrilatero::RayIntersects(Vector3 raydir,Vector3 rayor , float *t){
	if((this->f1)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	if((this->f2)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	return false;
}

Vector3 Quadrilatero::getNormal(Vector3 hitpoint){
	
	if((this->f1)->Esta_Contido(hitpoint)){
		return this->f1->getNormal(hitpoint);
	}

	return (this->f2)->getNormal(hitpoint);


}

Texture Quadrilatero::getTexture(){
	return this->textura;
}

float Quadrilatero::getPolimento(){
	return this->polimento;
}
void Quadrilatero::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        
	(this->f1)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
	(this->f2)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
}
void Quadrilatero::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        
	(this->f1)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
	(this->f2)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
}