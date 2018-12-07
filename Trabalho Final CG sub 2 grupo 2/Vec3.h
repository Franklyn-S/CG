#ifndef VEC3_HPP
#define VEC3_HPP
#include <string>
using namespace std;
class Vec3{

//using namespace std;
private:
	float x,y,z;
public:
	
	Vec3();
	Vec3 (float  x, float y, float z);

	float& operator [] (int id);
	Vec3 operator + (Vec3 v);
	void operator = (Vec3 v);
	Vec3 operator -  (Vec3 v);
	//Faz a operação dentro do próprio vértice
	void operator *=  (float escalar);
	//Retorna outro vértice com a soma
	Vec3 operator  *  (float escalar);
	
	void operator /= (float escalar);

	Vec3 operator / (float escalar);
	
	// Operação de produto vetorial é vetor ->* vetor2
	Vec3 operator ->* (Vec3 v);

	float magnitudeSquared();

	bool operator ==(Vec3);
	bool operator !=(Vec3);

	//para calculo das cores
	Vec3 arroba(Vec3 v);
	

	float norm();
	Vec3 normalize();

	float dotProduct(Vec3 v);

	float angle(Vec3 v);
	string toString();
	

};

#endif // VEC3_HPP
