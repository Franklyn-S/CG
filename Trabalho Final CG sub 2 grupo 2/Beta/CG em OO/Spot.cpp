
#include "Spot.h"
#include <math.h>
#include "Camera.h"

using namespace std;

Spot::Spot(Vector3 position,Vector3 color){
	this->position=position;
	this->color=color;
}

Vector3 Spot::Iluminacao(Vector3 observer , Vector3 Point_Object , Vector3 Normal_Of_Face , Texture Texture_Object , float polimento){
	
	Vector3 Ipix;

	Vector3 n=Normal_Of_Face.Normalize();

	Vector3 l=Generate_L_Vector(Point_Object);
	Vector3 v=Generate_V_Vector(Point_Object, observer);
	Vector3 r=Generate_R_Vector(l,n);
	
	Ipix     =(this->Idif(Texture_Object.texture_dif , l ,n) .arroba( this->Iesp(Texture_Object.texture_esp , r ,v,polimento)) )*this->spotlight(Point_Object,l*-1,{0,-1,0},polimento);

	return Ipix;
}
Vector3 Spot::Iluminacao(Texture textura){
	Vector3 Ipix;
	Ipix =this->color.arroba(textura.texture_amb);
	//return Ipix;
	return this->color;
}
double Spot::spotlight(Vector3 point ,Vector3 l,Vector3 s, double e){
	
	double cos = l.Dot(s);
	
	if(cos >=0.8){
	
		//return pow(cos,e);
		return 0;
	
	}else{
	
		return pow(cos,e);
	
	}

}

Vector3 Spot::Generate_L_Vector(Vector3 Point_Object){
	return (this->position - Point_Object).Normalize();
}

Vector3 Spot::Generate_V_Vector(Vector3 Point_Object, Vector3 observer){
	return (observer - Point_Object).Normalize();
}
Vector3 Spot::Generate_R_Vector(Vector3 l,Vector3 n){
	return n*2*(l.Dot(n))- l;
}

Vector3 Spot::Idif(Vector3 Texture_Object , Vector3 l , Vector3 n){
	double cos=l.Dot(n);
	if(cos>=0){
		return this->color.arroba(Texture_Object) * cos;
	}else{
		return Vector3(0,0,0);
	}
}

Vector3 Spot::Iesp(Vector3 Texture_Object , Vector3 r , Vector3 v, int m){
	double cos=r.Dot(v);
	if(cos>=0){
		return this->color.arroba(Texture_Object) * pow(cos,m);
	}else{
		return Vector3(0,0,0);
	}
}

void Spot::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Camera_Mundo(camera , LoockAt , ViewUp , this->position);
}

void Spot::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position);
}

Vector3 Spot::getPosition(){
	return this->position;
}

Vector3 Spot::getColor(){
	return this->color;
}