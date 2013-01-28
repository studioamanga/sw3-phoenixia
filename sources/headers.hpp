/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* headers.hpp **** auteur : Vincent Tourraine *********
**                                                         **
** Ensemble des inclusions de fichier et des déclarations  **
** ou prototypes des variables ou fonctions globales.      **
**                                                         **
*************************************************************/

// Inclusions génériques
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
// Inclusions relatives à OpenGL
#include <GL/glut.h>
#include <GL/gl.h>

using namespace std;

//#define Tfact 1.

#define PI 3.1415926535897932

#define BEHIND      0
#define INTERSECTS  1
#define FRONT       2
#define SCREEN_X    800
#define SCREEN_Y    600
char MAPURL[50];
int MAPCLIMAT=1;
#define WINGURL "./modelor/serv03.mad"
#define GETTIME glutGet(GLUT_ELAPSED_TIME)
long int TIMElast, TIMEcur;
#define GETTIMER (TIMEcur-TIMElast)
bool ISARB=true;

#define FACT_ACCEL 0.001
#define FACT_DECEL FACT_ACCEL*1.5
#define FACT_BRAQ 0.01
#define FACT_DEPL 0.003


// Prototypes des fonctions principales
void Init(void);
void Display(void);
void Reshape(int,int);
void Idle(void);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Aff_map(void);
int LoadBMP(char *File);
void eXit(void);


// Déclarations des variables globales
float BufferColor[4]={1.0f, 1.0f, 1.0f, 1.0f};
bool LIGHTON=false;
#define DISP_MENU 0
#define DISP_JEU 1
int Disp=DISP_MENU;

// Inclusion des autres sources nécessaires au projet
#include "timer.cpp"
#include "climat.cpp"
#include "except.cpp"
#include "vector.cpp"
#include "texture.cpp"
#include "inout.cpp"
#include "bsp.cpp"
//#include "part.cpp" est déclaré dans ent.cpp
#include "ent.cpp"
#include "drone.cpp"
#include "ennemis.cpp"
#include "serie.cpp"
#include "graph.cpp"
#include "input.cpp"
#include "maths.cpp"



