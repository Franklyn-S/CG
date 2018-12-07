#include "Prisma.h"
#include "Triangulo.h"
#include "Camera.h"
#include "Prisma.h"
using namespace std;

Prisma::Prisma(Quadrilatero f1 , Quadrilatero f2 , Quadrilatero f3 , Quadrilatero f4 , Quadrilatero f5 , Quadrilatero f6){
	
	
	this->f1= new Quadrilatero(f1.p1 , f1.p2 , f1.p3 , f1.p4 , f1.getTexture() , f1.getPolimento());
	this->f2= new Quadrilatero(f2.p1 , f2.p2 , f2.p3 , f2.p4 , f2.getTexture() , f2.getPolimento());
	this->f3= new Quadrilatero(f3.p1 , f3.p2 , f3.p3 , f3.p4 , f3.getTexture() , f3.getPolimento());
	this->f4= new Quadrilatero(f4.p1 , f4.p2 , f4.p3 , f4.p4 , f4.getTexture() , f4.getPolimento());
	this->f5= new Quadrilatero(f5.p1 , f5.p2 , f5.p3 , f5.p4 , f5.getTexture() , f5.getPolimento());
	this->f6= new Quadrilatero(f6.p1 , f6.p2 , f6.p3 , f6.p4 , f6.getTexture() , f6.getPolimento());
}

Prisma::Prisma(){
	this->f1= new Quadrilatero({0,0,0} , {0,0,0} , {0,0,0} , {0,0,0} , Texture({0,0,0},{0,0,0},{0,0,0}) , 0);
	this->f2= new Quadrilatero({0,0,0} , {0,0,0} , {0,0,0} , {0,0,0} , Texture({0,0,0},{0,0,0},{0,0,0}) , 0);
	this->f3= new Quadrilatero({0,0,0} , {0,0,0} , {0,0,0} , {0,0,0} , Texture({0,0,0},{0,0,0},{0,0,0}) , 0);
	this->f4= new Quadrilatero({0,0,0} , {0,0,0} , {0,0,0} , {0,0,0} , Texture({0,0,0},{0,0,0},{0,0,0}) , 0);
	this->f5= new Quadrilatero({0,0,0} , {0,0,0} , {0,0,0} , {0,0,0} , Texture({0,0,0},{0,0,0},{0,0,0}) , 0);
	this->f6= new Quadrilatero({0,0,0} , {0,0,0} , {0,0,0} , {0,0,0} , Texture({0,0,0},{0,0,0},{0,0,0}) , 0);
}

bool Prisma::RayIntersects(Vector3 raydir,Vector3 rayor , float *t){
	if((this->f1)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	if((this->f2)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	if((this->f3)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	if((this->f4)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	if((this->f5)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	if((this->f6)->RayIntersects(raydir , rayor , t)){
		return true;
	}

	return false;
}


void Prisma::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        
	(this->f1)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
	(this->f2)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
	(this->f3)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
	(this->f4)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
	(this->f5)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
	(this->f6)->Transform_Camera_Mundo(camera ,LoockAt ,ViewUp);
}
void Prisma::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        
	(this->f1)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
	(this->f2)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
	(this->f3)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
	(this->f4)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
	(this->f5)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
	(this->f6)->Transform_Mundo_Camera( camera ,  LoockAt ,  ViewUp);
}