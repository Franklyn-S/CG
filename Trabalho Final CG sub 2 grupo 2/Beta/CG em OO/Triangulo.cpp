#include "Triangulo.h"
#include "Camera.h"

Triangulo::Triangulo(Vector3 position1 ,Vector3 position2,Vector3 position3, Texture textura , float polimento){
	this->textura=textura;
	this->position1=position1;
	this->position2=position2;
	this->position3=position3;
	this->polimento=polimento;
	
}

Triangulo::Triangulo(){
	this->textura=Texture({0,0,0} , {0,0,0} , {0,0,0});
	this->position1={0,0,0};
	this->position2={0,0,0};
	this->position3={0,0,0};
	this->polimento=1;	
}


bool Triangulo::RayIntersects(Vector3 raydir,Vector3 rayor , float *distancia){
	float dDotN =raydir.Dot(this->getNormal({0,0,0})); //dot(intersection.ray.direction, normal);
    
    //paralelo ao plano = infinitas interseções
    if (dDotN == 0.0f){
        return false;
    }
    
    Vector3 w=(this->position1 - rayor);
    float t =  w.Dot(this->getNormal({0,0,0}))/dDotN;  //dot(position - intersection.ray.origin, normal) / dDotN;
    
    //perto demais
    if (t <= 0.05) {
        return false;
    }
    
    
    if(!this->Esta_Contido(rayor + raydir*t)){
        
        return false;
    }
    
    *distancia = t;
    
    
return true;
}

bool Triangulo::Esta_Contido(Vector3 hitpoint){
    // Compute vectors
    Vector3 v1 = this->position3 - this->position1; //point3 - point1;
    Vector3 v2 = this->position2 - this->position1; //point2 - point1;
    Vector3 v3 = hitpoint - this->position1; //point1;
    
    // Compute dot products
    float dot11 = v1.Dot(v1); //dot(v1, v1);
    float dot12 = v1.Dot(v2); //dot(v1, v2);
    float dot13 = v1.Dot(v3); //dot(v1, v3);
    float dot22 = v2.Dot(v2); //dot(v2, v2);
    float dot23 = v2.Dot(v3); //dot(v2, v3);
    
    // Compute barycentric coordinates
    float invDenom = 1 / (dot11 * dot22 - dot12 * dot12);
    float u = (dot22 * dot13 - dot12 * dot23) * invDenom;
    float v = (dot11 * dot23 - dot12 * dot13) * invDenom;
    
    // Check if point is in triangle
return (u >= 0) && (v >= 0) && (u + v < 1);
}

Vector3 Triangulo::getNormal(Vector3 hitpoint){
	Vector3 ray1= (this->position2 - this->position1).Normalize();
	Vector3 ray2=(this->position3 - this->position2).Normalize();
	Vector3 aux={0,1,0};
	return ray2.Cross(ray1);
	//return aux;

}

Texture Triangulo::getTexture(){
	return this->textura;
}

float Triangulo::getPolimento(){
	return this->polimento;
}
void Triangulo::Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Camera_Mundo(camera , LoockAt , ViewUp , this->position1);
        Camera_Mundo(camera , LoockAt , ViewUp , this->position2);
        Camera_Mundo(camera , LoockAt , ViewUp , this->position3);
}
void Triangulo::Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp){
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position1);
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position2);
        Mundo_Camera(camera ,LoockAt ,ViewUp , this->position3);
}