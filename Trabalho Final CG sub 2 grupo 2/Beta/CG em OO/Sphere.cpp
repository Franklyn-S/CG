#include "Sphere.h"
#include <math.h>
#include "LightSource.h" 
#include "Iluminacao.h"
#include "Camera.h"
Sphere::Sphere(Vector3 centro , double raio,float polimento , Texture textura){
	this->centro=centro;
	this->raio=raio;
	this->textura=textura;
        this->polimento=polimento;
}
Sphere::Sphere(){
        this->centro={0,0,0};
        this->raio=0.0f;
        this->textura=Texture({0,0,0},{0,0,0},{0,0,0});
        this->polimento=1;
}
bool Sphere::RayIntersects(Vector3 raydir ,Vector3 rayor, float *distancia){
        
        float a = raydir.Dot(raydir);
        
        float b = raydir .Dot( ( (rayor - this->centro)))*2.0f;
        
        float c=(rayor - this->centro).Dot((rayor - this->centro)) - this->raio*this->raio;
        
        float D = b*b + (-4.0f)*a*c;

        if (D < 0){
                return false;
        }
        
        D=sqrtf(D);

        float t = (-0.5f)*(b+D)/a;
        
        if (t >= 0.0f){  
                *distancia=t;
        }
        else{
                return false;
        }

        return true;
}



Vector3 Sphere::getNormal(Vector3 hitpoint){
        return (hitpoint - this->centro) / this->raio;
}

Texture Sphere::getTexture(){
        return this->textura;
}

float Sphere::getPolimento(){
        return this->polimento;
}

void Sphere::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Camera_Mundo(camera , LoockAt , ViewUp , this->centro);
}
void Sphere::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->centro);
}