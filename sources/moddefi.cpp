
/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** moddefi.cpp **** auteur : Vincent Tourraine ********
**                                                         **
**                                                         **
*************************************************************/

typedef struct missionDefi
{
  char Map     [40];
  char Wing    [40];
  char Nom     [20];
  char Comment [100];
  char Clim;
  int  duree;
};

#define NB_DEFI_MISSION 5
int cursDefiMission=1;

missionDefi MOD_DEFI_MISSIONS [NB_DEFI_MISSION]={{"data/model/cindus.mad","data/model/serv03.mad", "Envol",
						  "Commencer par securiser les alentours de l'astroport.",
						  CLIMAT_NUIT, 300},
						 {"data/model/gorge.mad", "data/model/serv03.mad", "Meandres",
						  "Les conditions climatiques sont sources de dangers, soyez prudent.",
						  CLIMAT_TEMPETE, 300},
						 {"data/model/space.mad", "data/model/shad.mad", "Approche",
						  "L'espace est aussi profond que glacial, nombreux y sont restes a jamais.",
						  CLIMAT_ESPACE, 300},
						 {"data/model/psanct.mad", "data/model/eliar.mad", "Desert",
						  "Les tresors sont bien gardes, et le danger guette ceux qui s'en approchent.",
						  CLIMAT_NORMAL, 500},
						 {"data/model/track.mad", "data/model/shad.mad", "Couloirs",
						  "Soyez le plus rapide a nettoyer les couloirs de cette station spatiale.",
						  CLIMAT_ESPACE, 1200}};
