/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* def.hpp **** auteur : Vincent Tourraine ***********
**                                                         **
**                                                         **
*************************************************************/

typedef struct coord
{
	float x,y,z;
};

typedef struct vertex
{
	coord p, text;
};

typedef struct surface
{
	char surfacetype; 
	char texture[50];
	int nb_vertices;
	vertex ** vertices;
};

// Collision vertex format
typedef struct Cvf
{
	coord t[3];
};

typedef struct sClimat
{
  char type;
};

typedef struct model
{
  float taille, vit, armure, att, dir;
  char anim;
  int nb_surface;
  surface ** mod;
  int nbColl;
  Cvf*Coll;
  coord Tir1, Tir2;
  char descript[100];
  char name[20];

  int nbClimat, nbDrone, nbShoker;
  sClimat* Climat;
  coord * Drone;
  coord * Shoker;
  coord depart;

  char type;
  char urlDrone[50];
  char urlShoker[50];
  char urlLiq[50];
  float yLiq, yLiqMin, yLiqMax;
  float colorLiq[4];
  float Limits[6];

  char tagW, tagM, tagD, tagS;
};

model *M3D;

