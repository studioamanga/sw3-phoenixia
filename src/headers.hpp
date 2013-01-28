/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* headers.hpp **** auteur : Vincent Tourraine *********
**                                                         **
** Ensemble des inclusions de fichier et des dÈclarations  **
** ou prototypes des variables ou fonctions globales.      **
**                                                         **
*************************************************************/

#define SW3_VERSION 0.4

// Inclusions gÈnÈriques
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
// Inclusions relatives ‡ OpenGL
//#include <GL/glut.h>
//#include <GL/gl.h>
#include <GLUT/glut.h>

using namespace std;

//#define Tfact 1.

#define PI 3.1415926535897932

#define BEHIND      0
#define INTERSECTS  1
#define FRONT       2

int SCREEN_X    = 800;
int SCREEN_Y    = 600;
bool SCREEN_FULL= false;
bool LOG=true;
int NIV_DETAIL = 2;
char MAPURL    [50] = "data/model/psanct.mad";
char MAPCLIMAT      = '0';
char WINGURL   [50] =  "data/model/shad.mad";
#define FILE_TEXTURE_FONT "data/texture/font/base.tga"
#define GETTIME glutGet(GLUT_ELAPSED_TIME)
long int TIMElast=0, TIMEcur=0;
#define GETTIMER (TIMEcur-TIMElast)
bool ISARB=true;
bool VIEWEXT=true;

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
void Special(int key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Aff_map(void);
int LoadBMP(char *File);
void eXit(void);
void InitJ(void);
void DelJ(void);
void logOut(char * str);
char * getClimatName(char clim);
int wideScr(bool upd=false, bool chg=false);
void FinPartie(void);
void SaveCfg(void);
void LoadCfg(void);
void setScore(void);
char * getScore(int rank);
void menuSetComment(char*str,int timeLong);
void affPoint(float x, float y, float z, float rayon);


// DÈclarations des variables globales
float BufferColor[4]={1.0f, 1.0f, 1.0f, 1.0f};
bool LIGHTON=false;
#define DISP_MENU 0
#define DISP_JEU 1
int Disp=DISP_MENU;

// Inclusion des autres sources nÈcessaires au projet
#include "input.hpp"
#include "sound.cpp"
#include "climat.cpp"
#include "mod.cpp"
#include "ava.cpp"
#include "avaman.cpp"
#include "except.cpp"
#include "vector.cpp"
#include "texture.cpp"
#include "inout.cpp"
#include "bsp.cpp"
#include "weapon.hpp"
//#include "part.cpp" est dÈclarÈ dans ent.cpp
#include "ent.cpp"
#include "drone.cpp"
#include "ennemis.cpp"
#include "serie.cpp"
#include "weapon.cpp"
#include "font.cpp"
#include "menu.cpp"
#include "jeu.cpp"
#include "graph.cpp"
#include "input.cpp"
#include "maths.cpp"
#include "cfg.cpp"
#include "score.cpp"
