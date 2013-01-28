/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* madDef.hpp **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

#define TYPE_SKYBOX 'S'
#define TYPE_OBJET 'O'
#define TYPE_LANDER 'L'

#define MAD_ID 136

typedef struct
{
  float x, y, z, tx, ty;
}Vertex;

typedef struct
{
  float x, y, z;
}Vertex3f;

typedef struct
{
  char texture[50];
  char typeSurf;

  int nbVertices;

  Vertex * Vertices;
}sObjet;

typedef struct
{
  int nbObjets;
  sObjet * Objets;

  int nbTag;
  char Tag;
  // Tag
  int nbClimats;
  char* Climats;
  char Drone[50];
  int nbDrones;
  Vertex3f * Drones;
  char Shoker[50];
  int nbShokers;
  Vertex3f * Shokers;
  Vertex3f Depart;
  float Liq, LiqMin, LiqMax;
  char LiqTexture[50];
  float LiqR, LiqG, LiqB, LiqAlpha;
  float LimitXMin, LimitXMax, LimitYMin, LimitYMax, LimitZMin, LimitZMax;
  char Description[100];
  int Weapons[10];
  //

  char typeAnim;

  char Nom[20];
  char Url[201];

}madModel;

#include "madLoad.h"
#include "madSave.h"
#include "madShape.h"

void delMadModel(madModel * mad)
{
  if(mad->nbObjets>0)
    {
      int i=0;
      for(i=0 ; i<mad->nbObjets ; i++)
	free(mad->Objets[i].Vertices);
    }
  free(mad->Objets);
  switch(mad->Tag)
    {
    case 'M':
      free(mad->Climats);
      free(mad->Drones);
      free(mad->Shokers);
      break;
    case 'W' :
      free(mad->Drones);
      free(mad->Shokers);
      break;
    };
  free(mad);

  mad=NULL;
}
