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

#define Tfact 1.

#define PI 3.1415926535897932                   // This is our famous PI


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

// These constants are used as return values from ClassifySphere().  Depending
// on where the sphere lies in accordance with the plane being checked, these
// will allow us to label if the sphere is in front, behind or intersecting the plane.

#define BEHIND      0   // This is returned if the sphere is completely behind the plane
#define INTERSECTS  1   // This is returned if the sphere intersects the plane
#define FRONT       2   // This is returned if the sphere is completely in front of the plane


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
GLuint text_shoker;
int id_shokerPIQ, id_shokerCOR;
int angle;
float FogColor[4]={0.75f, 0.7f, 0.0f, 1.0f};

// Inclusion des autres sources nécessaires au projet
#include "vector.cpp"
#include "bsp.cpp"
#include "ent.cpp"
#include "ennemis.cpp"
#include "graph.cpp"
#include "models.cpp"
#include "maths.cpp"

