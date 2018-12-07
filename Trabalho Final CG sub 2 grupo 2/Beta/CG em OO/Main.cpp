/*
 * Main.cpp
 *
 *  Created on: 21 de set de 2018
 *      Author: joao
 */

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
#include "Vector3.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Iluminacao.h"
#include "Camera.h"
#include "Plano.h"
#include "Triangulo.h"
#include "Spot.h"
#include "Quadrilatero.h"
#include "Prisma.h"



using namespace std;

//foto de inicializacao
string nome="sandcastle_rt.tga";


//dimensoes da tela, adaptar com a quantidade de pixels da imagem usada
GLdouble windowWidth  = 512.0;
GLdouble windowHeight = 512.0;

int window;

Vector3 camera=Vector3(-1054,0,0);
Vector3 LoockAt=Vector3(0.0f,-96.0f,300.0f);
Vector3 ViewUp= Vector3(0.0f,150.0f,300.0f);

//CImg fundo;

GLuint* vao;
GLuint* vbo;
GLuint* ibo;

vector<Triangulo> cubo;
vector<Objeto*> cenario;
vector<Fonte_Luminosa*> luzes;

Quadrilatero f1 = Quadrilatero({-200,-200,200},{-200,-200,-200},{200,-200,-200},{200,-200,200},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
Quadrilatero f2 = Quadrilatero({200,200,200},{200,200,-200},{-200,200,-200},{-200,200,200},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
Quadrilatero f3 = Quadrilatero({-200,200,200},{-200,200,-200},{-200,-200,-200},{-200,200,200},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
Quadrilatero f4 = Quadrilatero({200,-200,200},{200,-200,-200},{200,200,-200},{200,200,200},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
Quadrilatero f5 = Quadrilatero({-200,200,200},{-200,-200,200},{200,-200,200},{200,200,200},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
Quadrilatero f6 = Quadrilatero({-200,-200,-200},{-200,200,-200},{200,200,-200},{200,-200,-200},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);

Prisma cap=Prisma(f1,f2,f3,f4,f5,f6);

Plano chao =Plano({0.0f,-256.0f,300.0f},{0,-256,400},{100,-256,300},Texture({0.50,0.16,0.16} , {0.3,0.3,0.3} , {0.3,0.3,0.3}),100);

void LoadObj(char* arquivo, vector<Triangulo> &triangulo , float polimento , Texture textura)
{

	string linha;
	string linhaProcessada;

	Vector3 vec(0,0,0);
	
	vector<vector<unsigned short>> fac;
	
	vector<Vector3> ponto;

	fac.push_back({0, 0});
	fac.push_back({0, 0});
	fac.push_back({0, 0});

	vector<Vector3> referencias;

	ifstream obj(arquivo);

	if (obj.is_open())
	{
		while(getline(obj, linha))
		{
			if(linha[0] == '#' || linha.empty())
			{
				continue;
			}


			if(linha.size() >= 2)
			{
				linhaProcessada = linha.substr(2);
			}

			while(linhaProcessada[0] == ' ')
			{
				linhaProcessada = linhaProcessada.substr(1);
			}


			if(linha[0] == 'g' || linha[0] == 'o')
			{
				//mesh->nome = linhaProcessada;
				continue;
			}
			else if(linha[0] == 'v' && linha[1] == 'n')
			{
				//sscanf(linhaProcessada.c_str(), "%lf %lf %lf\n", &vec.x, &vec.y, &vec.z);

				//mesh->normaisVertices.push_back(vec);
				continue;
			}
			else if(linha[0] == 'v')
			{
				sscanf(linhaProcessada.c_str(), "%lf %lf %lf\n", &vec[0], &vec[1], &vec[2]);

				ponto.push_back(vec);

			}
			else if(linha[0] == 'f')
			{

				sscanf(linhaProcessada.c_str(), "%hi//%hi %hi//%hi %hi//%hi\n", &fac[0][0], &fac[0][1], &fac[1][0], &fac[1][1], &fac[2][0], &fac[2][1]);

				referencias.push_back( Vector3(fac[0][0],fac[1][0],fac[2][0]) );
				

			}

		}

		obj.close();
	}

	for(int k = 0 ; k<referencias.size() ; k++ ){
		triangulo.push_back( Triangulo( ponto[ referencias[k][0]-1 ] , ponto[ referencias[k][1]-1 ] , ponto[ referencias[k][2]-1 ] , textura,polimento ) );
	} 

}

void Desenho(void){

	cout<<"Fazendo imagem"<<endl;
	
	using namespace cimg_library;

	//limpando a tela
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
	
	//pintando o fundo
	CImg<unsigned char> fundo(nome.data());

	for(int i = 0; i < windowWidth; ++i){
		for(int j = 0; j < windowHeight; ++j){
			
			//x e y
			double x = (i  - windowWidth/2);
			double y = (j - windowHeight/2);

			Vector3 Ipix;
			Ipix[0] = (double)fundo(i, windowHeight-j, 0, 0)/255;
			Ipix[1] = (double)fundo(i, windowHeight-j, 0, 1)/255;
			Ipix[2] = (double)fundo(i, windowHeight-j, 0, 2)/255;
			glColor3f(Ipix[0], Ipix[1], Ipix[2]);
			glVertex2f(x, y);
		}
	}
	
	//Plano chao =Plano({0.0f,-256.0f,300.0f},{0,-256,400},{100,-256,300},Texture({0.50,0.16,0.16} , {0.3,0.3,0.3} , {0.3,0.3,0.3}),100);


	
	//levando o cenario para o mundo da camera
	Vector3 aux = camera;
	for(int k=0; k<cenario.size();k++){
		cenario[k]->Transform_Mundo_Camera(camera , LoockAt , ViewUp);
	}

	cap.Transform_Mundo_Camera(camera , LoockAt , ViewUp);
	//levando as luzes para o mundo da camera
	for(int k=0; k<luzes.size(); k++){
		luzes[k]->Transform_Mundo_Camera(camera , LoockAt , ViewUp);	
	}   
	
	chao.Transform_Mundo_Camera(camera , LoockAt , ViewUp);	

	//levando a camera para o seu mundo
	Mundo_Camera(camera,LoockAt,ViewUp,camera);
	

	for(int i = 0; i < windowWidth; ++i)
	{
		for(int j = 0; j < windowHeight; ++j)
		{
			//x e y
			double x = (i  - windowWidth/2);
			double y = (j - windowHeight/2);
			
			//Vetor para armazenar objetos atingidos pelo raio
			vector<Objeto*> objetos_interceptados;

			//Vetor para armazenar as distancias registradas para um raio
			vector<float> distancias;
			
			//variavel que guarda a distancia do raio
			float t;
			
			//vetor de posicionamento da tela (x,y,d)		
			Vector3 point={x,y,150};

			//percorrendo o cenario para saber se o raio intercepta um ponto
			/*
			for(int k=0;k<cenario.size();k++){
				if(cenario[k]->RayIntersects( (point - camera),camera ,&t)){
					distancias.push_back(t);
					objetos_interceptados.push_back(cenario[k]);
				}
				
			}
			*/
			
			if(cap.RayIntersects((point - camera),camera ,&t)){
				for(int k=0;k<cenario.size();k++){
				if(cenario[k]->RayIntersects( (point - camera),camera ,&t)){
					distancias.push_back(t);
					objetos_interceptados.push_back(cenario[k]);
				}
				
				}
			}
			
			if(chao.RayIntersects( (point - camera),camera ,&t)){
					distancias.push_back(t);
					objetos_interceptados.push_back(&chao);
				}
			
			//se o tamanho do meu vetor eh diferente de 0, alguem foi interceptado
			if(distancias.size() != 0){

				//laco para descobrir a menor distancia para saber o que deve ser exibido
				int menor=0;
				for(int k=0 ; k< distancias.size() ; k++){
					if(distancias[menor]>distancias[k]){
						menor=k;
					}
				}

				//calculo de onde esta localizado o ponto que sera exibido (ponto_da_origem_do_raio + direcao_do_raio * distancia)
				Vector3 hitpoint = camera + (point - camera)*distancias[menor];

				
				//vetor que guarda as posicioes do meu vector luzes que estao obstruidos pelos objetos
				vector<int> tem_sombra;

				
				//laco que vai verificar se o raio que sai do hitpoint ate a fonte de luz eh obstruido por algum objeto
				//for(int k=0;k<cenario.size();k++){

					for(int l=0; l<luzes.size(); l++){
						if(cap.RayIntersects((luzes[l]->getPosition() - hitpoint).Normalize(),hitpoint , &t)){
							for(int k=0;k<cenario.size();k++){							
								if(cenario[k]->RayIntersects((luzes[l]->getPosition() - hitpoint).Normalize(),hitpoint , &t)){
								
									//guardar o seu indice l no tem_sombra
									tem_sombra.push_back(l);

								}
							}
						}
						
						if(chao.RayIntersects((luzes[l]->getPosition() - hitpoint).Normalize(),hitpoint , &t)){
							tem_sombra.push_back(l);
						}
						
						//condicional: "esse raio que liga o hitpoint ate a minha luzes[l] esta obstruido?"
					}
				//}
				
				

				//vetor booleano que vai guiar o meu calculo
				vector<bool> sombra;
				for(int k=0 ; k<luzes.size() ; k++){
					sombra.push_back(false);
				}

				//adicionando true nas posicisoes guardadas no tem_sombra 
				for(int k=0 ; k<tem_sombra.size() ; k++){
					sombra[tem_sombra[k]]=true;
				}

				//inicializacao da cor
				Vector3 rgb={0,0,0};
				
				//pegando a normal que sera utilizada
				Vector3 normal=objetos_interceptados[menor]->getNormal(hitpoint);

				//somatorio para a cor
				for(int k=0 ; k<luzes.size() ; k++){
					if(sombra[k]==false){
					
	    				rgb= rgb+ luzes[k]->Iluminacao(camera , hitpoint , normal , objetos_interceptados[menor]->getTexture(),objetos_interceptados[menor]->getPolimento());	
					
					}
				}
				
				//adicionando a componente ambiente que foi armazenada na posicao luzes[0]
				rgb=rgb + luzes[0]->Iluminacao(objetos_interceptados[menor]->getTexture());
				
				glColor3d(rgb[0],rgb[1],rgb[2]);
				
				glVertex2d(x,y);
			}



		}
	}
	cout<<"Fim"<<endl;

	for(int k=0; k<cenario.size();k++){
		cenario[k]->Transform_Camera_Mundo(aux , LoockAt , ViewUp);
	}

	cap.Transform_Camera_Mundo(aux , LoockAt , ViewUp);
	//levando as luzes para o mundo da camera
	for(int k=0; k<luzes.size(); k++){
		luzes[k]->Transform_Camera_Mundo(aux , LoockAt , ViewUp);	
	}   
	chao.Transform_Camera_Mundo(aux , LoockAt , ViewUp);

	glEnd();
	glFlush();
	


}


// Callback do GLUT: Chamado na criação da janela e toda vez que ela for redimensionada
void _Redimensionar(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	// Redefinição do viewport e projeção
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2, w/2, -h/2, h/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glutPostRedisplay();
}

// Callback do GLUT: Eventos de teclado
void _Teclado(unsigned char key, int x, int y)
{
	switch((char)key)
	{
		// ESC
		case 27:
			glutDestroyWindow(window);
			exit(0);
			break;

		case 'w':
			camera={0,0,-1050.0f};
			nome="sandcastle_rt.tga";

			break;
		case 's':
			camera={0.0f,0.0f,1050.0f};
			nome="sandcastle_bk.tga";
			break;

		case 'a':
			camera={1050.0f,0,0};
			nome="sandcastle_lf.tga";
			break;
		case 'd':
			camera={-1054,0,0};
			nome="sandcastle_ft.tga";
			break;
		case 'q':
			camera={0,1050.0f,0};
			nome="sandcastle_dn.tga";
			break;
		case 'e':
			camera={0,-1050.0f,0};
			nome="sandcastle_up.tga";
			break;
	}

	glutPostRedisplay();
}
/*
// Callback do GLUT: Eventos de mouse com algum botão pressionado
void MouseClick (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON: printf("Botao esquerdo.");
                               break;
        case GLUT_RIGHT_BUTTON: printf("Botao direito.");
                               break;
        case GLUT_MIDDLE_BUTTON: printf("Botao do meio.");
                               break;
    }
    x = (x  - windowWidth/2);
    y = (y - windowHeight/2);

		//Vetor para armazenar objetos atingidos pelo raio
	vector<Objeto*> objetos_interceptados;

	//Vetor para armazenar as distancias registradas para um raio
	vector<float> distancias;

	//variavel que guarda a distancia do raio
	float t;

	//vetor de posicionamento da tela (x,y,d)		
	Vector3 point={x,y,150};

	//percorrendo o cenario para saber se o raio intercepta um ponto
	for(int k=0;k<cenario.size();k++){
		if(cenario[k]->RayIntersects( (point - camera),camera ,&t)){
			distancias.push_back(t);
			objetos_interceptados.push_back(cenario[k]);
		}
		
	}

	//se o tamanho do meu vetor eh diferente de 0, alguem foi interceptado
	if(distancias.size() != 0){

		//laco para descobrir a menor distancia para saber o que deve ser exibido
		int menor=0;
		for(int k=0 ; k< distancias.size() ; k++){
			if(distancias[menor]>distancias[k]){
				menor=k;
			}
		}


    if (state == GLUT_DOWN)
        printf("Pressionado na posição: ");
    if (state == GLUT_UP)
        printf("Liberado na posição: ");
    printf("(%d, %d)\n", x,y);
}

// **************************************************
// Função chamada quando o mouse anda sobre a janele
// e NÃO HÁ botão pressionado
// **************************************************

void MouseAndandoNaoPressionado (int x, int y){
    double xo = (x  - windowWidth/2);
	double yo = (y - windowHeight/2);

    printf("Mouse ANDANDO solto na janela. Posição: (%d, %d)\n", x,y);


    LoockAt={y,x,300};

    ViewUp= {y,x+20,300};
    
    glutPostRedisplay();
}

void MouseAndandoPressionado (int x, int y){
    printf("Mouse ANDANDO pressionado na janela. Posição: (%d, %d)\n", x,y);
}
*/
int main(int argc, char *argv[]){
	string object = "Agr.obj";

	//vector<Triangulo> cubo;

	LoadObj("Macaco.obj",cubo ,100,Texture({0.62f,0.62f,0.62f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}) );

	cout<<cubo.size()<<endl;

	cout<<"fundo ok"<<endl;
	//definindo o boneco
	Sphere Snow_Man[9];

		Sphere barriga=Sphere( {0.0f,-96.0f,300.0f}, 160.0f,100 , Texture({0.62f,0.62f,0.62f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
	
		Sphere cabeca=Sphere({0.0f,150.0f,300.0f}, 100.0f ,100, Texture({0.62f,0.62f,0.62f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
	
		Sphere olho_direito=Sphere({-20.0f,150.0f,200.0f}, 8.0f,7 , Texture({0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f}));
	
		Sphere olho_esquerdo=Sphere({20.0f,150.0f,200.0f}, 8.0f ,7, Texture({0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f}));
	
		Sphere nariz=Sphere({0.0f,120.0f,200.0f}, 8.0f ,7, Texture({0.9f,0.2f,0.2f} , {0.9f,0.2f,0.2f} , {0.9f,0.2f,0.2f}));
	
		Sphere b1=Sphere({0.0f,0.0f,170.0f}, 8.0f ,7, Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		Sphere b2=Sphere({0.0f,-30.0f,150.0f}, 8.0f ,7, Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		Sphere b3=Sphere({0.0f,-60.0f,140.0f}, 6.5f ,7, Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		Sphere b4=Sphere({0.0f,-90.0f,137.0f}, 6.0f ,7, Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		
		Snow_Man[0]=cabeca;
		Snow_Man[1]=barriga;
		Snow_Man[2]=olho_direito;
		Snow_Man[3]=olho_esquerdo;
		Snow_Man[4]=nariz;
		Snow_Man[5]=b1;
		Snow_Man[6]=b2;
		Snow_Man[7]=b3;
		Snow_Man[8]=b4;
cout<<"boneco ok"<<endl;
	Sphere Snow_Man2[2];
		Sphere barriga2=Sphere({-300.0f,-96.0f,600.0f}, 160.0f,10 , Texture({0.48f,0.47f,0.13f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
		Sphere cabeca2=Sphere({-300.0f,150.0f,600.0f}, 100.0f ,10, Texture({0.48f,0.47f,0.13f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
		Snow_Man2[0] = barriga2;
		Snow_Man2[1] = cabeca2;
	
	Sphere Snow_Man3[2];
		Sphere barriga3=Sphere({300.0f,-96.0f,600.0f}, 160.0f,150 , Texture({0.98f,0.11f,0.18f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
		Sphere cabeca3=Sphere({300.0f,150.0f,600.0f}, 100.0f,150 , Texture({0.98f,0.11f,0.18f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
		Snow_Man3[0] = barriga3;
		Snow_Man3[1] = cabeca3;
	
	//Definindo o plano infinito
	Plano chao =Plano({0.0f,-256.0f,300.0f},{0,-256,400},{100,-256,300},Texture({0.50,0.16,0.16} , {0.3,0.3,0.3} , {0.3,0.3,0.3}),100);
	
	cout<<"plano ok"<<endl;

	//Defindo o triangulo
	Triangulo lente_direita=Triangulo({-20,150,192},{-20,100,192},{30,125,192},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
	Triangulo lente_esquerda=Triangulo({-20,150,192},{-20,100,192},{-70,125,192},Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
	
	Quadrilatero tv = Quadrilatero({-40,200,200},{-40,400,200},{360,400,300},{360,200,300} ,Texture({0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f} , {0.9f,0.9f,0.2f}),7);
	
	//vetor que guarda elementos do cenario
	//vector<Objeto*> cenario;
	
	
	//Colocando os bonecos no cenario
	for(int k=0;k<9;k++){
		//cenario.push_back(&Snow_Man[k]);
	}

	//cenario.push_back(&Snow_Man2[0]);
	//cenario.push_back(&Snow_Man2[1]);
	//cenario.push_back(&Snow_Man3[0]);
	//cenario.push_back(&Snow_Man3[1]);
	//cenario.push_back(&chao);
	//cenario.push_back(&tv);
	//cenario.push_back(&lente_direita);
	//cenario.push_back(&lente_esquerda);
	
	
	for(int k =0 ; k<cubo.size() ; k++){
		cenario.push_back(&cubo[k]);	
	}
	
	

	//luz ambiente	
    Light_Source sun=Light_Source({300000000000.0f,300000000000.0f,00000.0f},{0.9f,0.9f,0.9f});
    
    //luzes secundarias
    Light_Source post=Light_Source({0000.0f,300000000000.0f,300000000000.0f},{0.9f,0.9f,0.9f});
    Spot upper=Spot({0.0f,350.0f,300.0f},{0.9f,0.9f,0.9f});
	
	//vetor que guarda as fontes luminosas
	//vector<Fonte_Luminosa*> luzes;

	luzes.push_back(&sun);
	luzes.push_back(&post);
	//luzes.push_back(&upper);



	//onde esta a camera , para onde olha e a orientaçao
	//Vector3 LoockAt={0.0f,-96.0f,300.0f};
	//Vector3 ViewUp= {0.0f,150.0f,300.0f};
	
	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow("Snow Man e o Plano infinito com Muitas Luzes");

	glewExperimental = GL_TRUE;

	//Definição de callbacks
	glutReshapeFunc(_Redimensionar);
	glutKeyboardFunc(_Teclado);
	//glutMotionFunc(_Mouse);
	glutDisplayFunc(Desenho);

	// Define as funções de MOUSE
 
    // movimento SEM botão pressionado
    //glutPassiveMotionFunc(MouseAndandoNaoPressionado);

    // movimento COM botão pressionado
   // glutMotionFunc(MouseAndandoPressionado);



    // Click em um botão
   // glutMouseFunc(MouseClick);
	glutMainLoop();
	exit(0);

	
	return 0;
}
