//includes do c++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

//include da imagem
#include "CImg.h"

//includes do GL
#include <GL/glew.h>
#include <GL/glut.h>
# include <GL/freeglut.h>

//arquivos usados
#include "Vec3.h"
#include "LightSource.h"
//#include "Sphere.h"
#include "Ilumination.h"
#include "Camera.h"
#include "Plan.h"
#include "Triangle.h"
//#include "Spot.h"
//#include "Quadrilatero.h"
//#include "Prisma.h"

using namespace std;

string picture = "CubeMap-PiazzaDelPopolo2/front.jpg";

//dimensoes da tela, adaptar com a quantidade de pixels da imagem usada
GLdouble windowWidth  = 2048.0;
GLdouble windowHeight = 2048.0;

int window;

Vec3 camera = Vec3(-1054,0,0);
Vec3 lookAt = Vec3(0,-96,300);
Vec3 viewUp = Vec3(0,150,300);

vector<Triangle> obj;
vector<Objeto*> scenery;
vector<Light*> lights;

Plano ground = Plan({0,-256,300},{0,-256,400},{100,-256,300},100);


void LoadObj(char* arquivo, vector<Triangle> &triangles, float polishing, Texture t){
	string line, processedLine;

	Vec3 vec = Vec3(0,0,0); //Vector3 vec(0,0,0);

	vector<vector<unsigned short>> fac;

	vector<Vec3> point;

	fac.push_back({0,0});
	fac.push_back({0,0});
	fac.push_back({0,0});

	vector<Vec3> vecReferences;
	vector<Vec3> texturesReferences;

	ifstream obj(arquivo);

	if(obj.is_open()){
		while(getline(obj, line)){
			if(line[0] == '#' || line.empty()) continue;
			if(line.size() >= 2) processedLine = line.substr(2);
			while(processedLine[0] == ' ') processedLine = processedLine.substr(1);
			if (line[0] == 'g' && line[1] == 'o') continue;
			if (line[0] == 'v' && line[1] == 'n') continue;
			if (line[0] == 'v'){
				sscanf(processedLine.c_str(), "%lf %lf %lf\n", &vec[0], &vec[1], &vec[2]);
				point.push_back(vec);
			};
			if(line[0] == f){
				sscanf(processedLine.c_str(), "%hi//%hi %hi//%hi %hi//%hi", &fac[0][0], &fac[0][1], &fac[1][0], &fac[1][1], &fac[2][0], &fac[2][1]);
				vecReferences.push_back(Vec3(fac[0][0], fac[1][0], fac[2][0]));
				texturesReferences.push_back(Vec3(fac[0][1], fac[1][1], fac[2][1]));
			}
		}
		obj.close();
	}
	for(int k = 0; k <vecReferences.size()){
		triangles.push_back(Triangle(point[vecReferences[k][0]-1], point[vecReferences[k][1]-1], point[vecReferences[k][2]-1], t, polishing))
	}
}


void DrawScene(void){
	cout << "Loading image..." <<endl;
	using namespace cimg_library;

	//limpando a tela
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	CImg<unsigned char> fundo(picture.data());

	//Pintando o fundo
	for (int i = 0; i < windowWidth; i++){
		for (int j = 0; j < windowHeight; j++){

			double x, y;
			x = (i - windowWidth/2);
			y = (j - windowHeight/2);

			Vec3 Ipix;
			Ipix[0] = (double)fundo(i, windowHeight-j, 0, 0)/255;
			Ipix[1] = (double)fundo(i, windowHeight-j, 0, 1)/255;
			Ipix[2] = (double)fundo(i, windowHeight-j, 0, 2)/255;
			glColor3f(Ipix[0], Ipix[1], Ipix[2]);
			glVertex2f(x,y);
		}
	}

	//levando o cenário para as coordenadas de câmera
	Vec3 aux = camera;
	for (int k = 0; k < scenery.size(); k++){
		scenery[k]->worldCamera(camera, lookAt, viewUp);
	}

	//levando as luzes para as coordenadas de câmera
	for (int k = 0; k < lights.size(); k++){
		lights[k]->worldCamera(camera, lookAt, viewUp);
	}	

	ground.worldCamera(camera, lookAt, viewUp);
	//levando a câmera para as coordenadas de câmera
	camera_World(camera, lookAt, viewUp, camera);

	for (int i = 0; i < windowWidth; i++){
		for (int j = 0; j < windowHeight; j++){

			double x, y;
			x = (i - windowWidth/2);
			y = (j - windowHeight/2);

			//vetor de objetos atingidos pelo raio
			vector<Object*> interceptedObjs
			//vetor que guarda a dinstancia do ray
			vector<float> distances;
			float t;

			Vec3 point = {x, y, 150};


			for(int k=0;k<scenery.size();k++){
				if(scenery[k]->RayIntersects( (point - camera),camera ,&t)){
					distances.push_back(t);
					interceptedObjs.push_back(scenery[k]);
				}
				
			}

			if(ground.RayIntersects((point - camera), camera, &t)){
				distances.push_back(t);
				interceptedObjs.push_back(&ground);
			}

			if(distances.size() != 0){ //interceptei alguém
				int menor = 0;
				//laço para descobrir a menor distância
				for (int i = 0; i < distances.size(); i++){
					if(distances[menor] > distances[k]){
						menor = k;
					}
				}
				//calculo do ponto a ser exibido (ponto de origem do raio + direção do raio * distância)
				Vec3 hitPoint = camera + (point-camera)*distances[menor];

				//vetor que guarda as posições 
				vector<int> haveShadow;

				for (int l = 0; l < lights.size(); l++)
				{
					/* code */
				}

			}


		}
	}
}