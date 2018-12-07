
#define RADIANOS_PARA_GRAUS 180 / 3.14159265358979323846f

#include "Vec3.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>

Vec3::Vec3(){
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3 (float  x, float y, float z){
	this->x=x;
	this->y=y;
	this->z=z;
}

float& Vec3::operator [] (int id){
	switch(id){
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
	}
}

Vec3 Vec3::operator + (Vec3 v){
	return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
}

void Vec3::operator = (Vec3 v){
	if(this != &v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
}
Vec3 Vec3::operator - (Vec3 v){
	return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);	
}

//Faz a operação dentro do próprio vértice
void Vec3::operator *= (float escalar){
	x = x * escalar;
	y = y * escalar;
	z = z * escalar;		
}

//Retorna outro vértice com a soma
Vec3 Vec3::operator * (float escalar){
	return Vec3(this->x *escalar, this->y *escalar, this->z *escalar);
}

void Vec3::operator /= (float escalar){
	x = x / escalar;
	y = y / escalar;
	z = z / escalar;		
}

Vec3 Vec3::operator / (float escalar){
	return Vec3(this->x/escalar, this->y/escalar, this->z/escalar);	
}

// Operação de produto vetorial é vetor ->* vetor2
Vec3 Vec3::operator ->* (Vec3 v){
	return Vec3(this->y*v.z - this->z*v.y
			, this->x*v.z-this->z*v.x
			, this->x*v.y-this->y*v.x);
}

float Vec3::magnitudeSquared(){
	return (pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
}

bool Vec3::operator==(Vec3 v){
	if((*this - v).magnitudeSquared() < 9.99999944E-11f){
				return true;
	}

	return false;
}

bool Vec3::operator!=(Vec3 v){
		if((*this - v).magnitudeSquared() < 9.99999944E-11f)
		{
			return false;
		}

		return true;
}

Vec3 Vec3::arroba(Vec3 v){
	return Vec3(this->x*v.x,this->y*v.y,this->z*v.z);
}



float Vec3::norm(){
	return sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::normalize(){
	float norm = this->norm();
	return Vec3(this->x/norm, this->y/norm, this->z/norm);
}

float Vec3::dotProduct(Vec3 v){
	return (this->x*v.x + this->y*v.y + this->z*v.z);
}

float Vec3::angle(Vec3 v){
	return acos(this->dotProduct(v) / (this->norm() * v.norm())) * RADIANOS_PARA_GRAUS;
}

string Vec3::toString(){
	stringstream  s;
	s << "|" << x << "|" << y << "|" << z << "|\n";
	return s.str();
}