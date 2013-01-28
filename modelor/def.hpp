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

typedef struct model
{
	float taille, vit, armure, att, dir;
	char anim;
	int nb_surface;
	surface ** mod;
};

model *M3D;

