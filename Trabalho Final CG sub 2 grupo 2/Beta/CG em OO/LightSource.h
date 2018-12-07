/*
 * LightSource.h
 *
 *  Created on: 26 de set de 2018
 *      Author: joao
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_
#include "Vector3.h"
#include "Fonte_Luminosa.h"

class Light_Source: public Fonte_Luminosa {
public://informacoes das fontes luminosas

	Light_Source(Vector3 position,Vector3 color);

	Vector3 position={0,0,0};
	Vector3 getPosition();

	Vector3 color={0,0,0};
	Vector3 getColor();

	Vector3 Iluminacao(Vector3 observer , Vector3 Point_Object , Vector3 Normal_Of_Face , Texture Texture_Object , float polimento);
	Vector3 Iluminacao(Texture textura);
	
	void Transform_Camera_Mundo(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);
	void Transform_Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp);

	Vector3 Generate_L_Vector(Vector3 Point_Object);
	Vector3 Generate_V_Vector(Vector3 Point_Object, Vector3 observer);
	Vector3 Generate_R_Vector(Vector3 l,Vector3 n);

	Vector3 Idif(Vector3 Texture_Object , Vector3 l , Vector3 n);
	Vector3 Iesp(Vector3 Texture_Object , Vector3 r , Vector3 v, int m);


};

#endif /* LIGHTSOURCE_H_ */
