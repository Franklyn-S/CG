#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

GLfloat angle, fAspect;
GLfloat rotX,rotY,rotZ;
GLfloat rotX_ini,rotY_ini,rotZ_ini;
GLfloat obsx,obsy,obsz;
GLfloat obsx_ini,obsy_ini,obsz_ini;
GLfloat x_ini,y_ini;
GLfloat bot;

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 1.0f);

    // Desenha o teapot com a cor corrente (solid)
    glTranslatef(0.0f, 0.0f, -7.0f); // coloca o objeto no meio da tela
    glutSolidTeapot(50.0f);

    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};		 // "cor"
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
    GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);

    angle=45;
}

//função usada para especificar a posição do observador virtual
void PosicionaObservador(void){
    //especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    //inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    //posiciona e orienta o observador
    glTranslatef(-obsx,-obsy,-obsz);
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(angle,fAspect,0.4,500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
    PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
//função callback para eventos de mouse
void GerenciaMouse(int button,int state, int x, int y){
    if(state == GLUT_DOWN){
        //salva os parametros atuais
        x_ini = x;
        y_ini = y;
        obsx_ini = obsx;
        obsy_ini = obsy;
        obsz_ini = obsz;
        rotX_ini = rotX;
        rotY_ini = rotY;
        rotZ_ini = rotZ;
        bot = button;
    }
    else
        bot = -1;
}
//função callback para eventos de movimento do mouse
#define SENS_ROT 5.0
#define SENS_OBS 15.0
#define SENS_TRANSL 30.0

void GerenciaMovim(int x, int y){
    //caso botão esquerdo
    if (bot == GLUT_LEFT_BUTTON){
        //Calcula diferenças
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        //e depois modifica os ângulos
        rotY = rotY_ini - deltax/SENS_ROT;
        rotX = rotX_ini - deltay/SENS_ROT;
    }
   //caso botão direito
    else if (bot == GLUT_RIGHT_BUTTON){
        //calcula diferença
        int deltaz = y_ini - y;
        //e modifica a distancia do observador
        obsz = obsz_ini + deltaz/SENS_OBS;
    }

    //caso botão do meio
    else if(bot == GLUT_MIDDLE_BUTTON){
        //calcula as diferenças
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        //E modifica posições
        obsx = obsx_ini + deltax/SENS_TRANSL;
        obsy = obsy_ini + deltay/SENS_TRANSL;
    }

    PosicionaObservador();
    glutPostRedisplay();

}

// função callback para tratar de eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y){
    switch (tecla) {
        case GLUT_KEY_HOME: if(angle >= 10) angle -=5;
                            break;
    case GLUT_KEY_END: if(angle <= 150) angle +=5;
                        break;
    }

   EspecificaParametrosVisualizacao();
    glutPostRedisplay();

}



// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(864,486);
    glutCreateWindow("Chaleira");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    glutMotionFunc(GerenciaMovim);
    Inicializa();
    glutMainLoop();
}
