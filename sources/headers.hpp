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
// Inclusions relatives à OpenGL
#include <GL/glut.h>
#include <GL/gl.h>

#define Tfact 0.1

// Prototypes des fonctions principales
void Init(void);
void Display(void);
void Reshape(int,int);
void Idle(void);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Init_Models(void);
void Aff_map(char id);
int LoadBMP(char *File);

// Déclarations des variables globales
GLuint text_shoker, text_ciel, text_spatioport, text_hlm, text_sol, text_tunnel;
int id_shokerPIQ, id_shokerCOR, id_hlm, id_ciel, id_spatioport, id_sol, id_tunnel;
int angle;
float FogColor[4]={0.8f, 0.8f, 1.0f, 1.0f};

// Inclusion des autres sources nécessaires au projet
#include "vector.cpp"
#include "ent.cpp"
#include "graph.cpp"
#include "models.cpp"

