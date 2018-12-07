/*
 * LightSource.cpp
 *
 *  Created on: 26 de set de 2018
 *      Author: joao
 */

#include "LightSource.h"
#include <math.h>
#include "Camera.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Light_Source::Light_Source(Vector3 position,Vector3 color) {
	// TODO Auto-generated constructor stub
	this->position=position;
	this->color=color;
}

Vector3 Light_Source::Iluminacao(Vector3 observer , Vector3 Point_Object , Vector3 Normal_Of_Face , Texture Texture_Object , float polimento){
	Vector3 Ipix;

	Vector3 n=Normal_Of_Face.Normalize();

	Vector3 l=Generate_L_Vector(Point_Object);
	Vector3 v=Generate_V_Vector(Point_Object, observer);
	Vector3 r=Generate_R_Vector(l,n);
	

	//Ipix     =this->color.arroba(Texture_Object.texture_amb) + this->Idif(Texture_Object.texture_dif , l ,n) + this->Iesp(Texture_Object.texture_esp , r ,v,polimento);
	Ipix     =( this->Idif(Texture_Object.texture_dif , l ,n) + this->Iesp(Texture_Object.texture_esp , r ,v,polimento) ) ;//* (0.5*(this->getPosition()-Point_Object).Magnitude()) ;

	return Ipix;
}

Vector3 Light_Source::Iluminacao(Texture textura){
	Vector3 Ipix;
	Ipix =this->color.arroba(textura.texture_amb);
	return Ipix;
}

Vector3 Light_Source::Generate_L_Vector(Vector3 Point_Object){
	return (this->position - Point_Object).Normalize();
}

Vector3 Light_Source::Generate_V_Vector(Vector3 Point_Object, Vector3 observer){
	return (observer - Point_Object).Normalize();
}
Vector3 Light_Source::Generate_R_Vector(Vector3 l,Vector3 n){
	return n*2*(l.Dot(n))- l;
}
Vector3 Light_Source::Idif(Vector3 Texture_Object , Vector3 l , Vector3 n){
	double cos=l.Dot(n);
	if(cos>=0){
		return this->color.arroba(Texture_Object) * cos;
	}else{
		return Vector3(0,0,0);
	}
}

Vector3 Light_Source::Iesp(Vector3 Texture_Object , Vector3 r , Vector3 v, int m){
	double cos=r.Dot(v);
	if(cos>=0){
		return this->color.arroba(Texture_Object) * pow(cos,m);
	}else{
		return Vector3(0,0,0);
	}
}

void Light_Source::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Camera_Mundo(camera , LoockAt , ViewUp , this->position);
}

void Light_Source::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position);
}

Vector3 Light_Source::getPosition(){
	return this->position;
}

Vector3 Light_Source::getColor(){
	return this->color;
}