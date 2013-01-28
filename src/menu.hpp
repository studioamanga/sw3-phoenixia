/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* menu.hpp **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

#define MENU_MAIN 1
#define MENU_NEW  2

#define MENU_LINK_QUIT      (-1)
#define MENU_LINK_NONE      0
#define MENU_LINK_TOMAIN    1
#define MENU_LINK_TOAVA     2
#define MENU_LINK_TONEW     3
#define MENU_LINK_TOOPT     4
#define MENU_LINK_TOINPUT1  5
#define MENU_LINK_TOINPUT2  6
#define MENU_LINK_TOINPUT3  7
#define MENU_LINK_NEXTAVA   10
#define MENU_LINK_NEXTMOD   11
#define MENU_LINK_NEXTWING  12
#define MENU_LINK_NEXTMAP   13
#define MENU_LINK_NEXTCLIM  14
#define MENU_LINK_NEXTDETL  15
#define MENU_LINK_NEXTDEFI  16
#define MENU_LINK_NEXTRESOL 17
#define MENU_LINK_MUSIC     18
#define MENU_LINK_NOISE     19
#define MENU_LINK_NEWAVA    20
#define MENU_LINK_DELAVA    21
#define MENU_LINK_START     30
#define MENU_LINK_INPUT     40
#define MENU_LINK_INPUT_DECALAGE 60
#define MENU_LINK_INPUP          (INPUT_UP       + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPDOWN        (INPUT_DOWN     + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPLEFT        (INPUT_LEFT     + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPRIGHT       (INPUT_RIGHT    + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPTLEFT       (INPUT_TLEFT    + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPTRIGHT      (INPUT_TRIGHT   + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPACCEL       (INPUT_ACCEL    + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPDECELL      (INPUT_DECELL   + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPSHIELD      (INPUT_SHIELD   + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPNEXTVIEW    (INPUT_NEXTVIEW + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPWIDESCR     (INPUT_WIDESCR  + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPEXIT        (INPUT_EXIT     + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPSHOOT       (INPUT_SHOOT    + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPNEXTWEAP    (INPUT_WEAPNEXT + MENU_LINK_INPUT_DECALAGE)
#define MENU_LINK_INPBACKWEAP    (INPUT_WEAPBACK + MENU_LINK_INPUT_DECALAGE)

char inputStr[50];
int idInputStr=0, maxInputStr=20;


//int idMenu=MENU_MAIN;

int cursMenu=1, cursMenuMax=6;
char menuComment [100];
int  menuCommentTime=0;

struct mapDet
{
  char nom[30];
  char name[20];
  int nbClimat;
  char * tabClimat;
};
mapDet * mapDetail=NULL;
int nbMaps=0;
int curMap=0, curClim=0;

struct wingDet
{
  char nom[30];
  char name[20];
};
wingDet * wingDetail=NULL;
int nbWings=0, curWing=0;

typedef struct sMenu
{
  char MENU_TAB [8][25];
  int  MENU_Y   [8];
  char MENU_LINK[8];
  int  MENU_SIZE;
};

sMenu MAIN_MENU={{"> Avatar :",
		  "[AVA]",
		  "> Nouvelle Partie",
		  "[MOD]",
		  "> Options",
		  "> Quitter"},
		 {-80,-60,-20,0,40,60},
		 {MENU_LINK_TOAVA,
		  MENU_LINK_NEXTAVA,
		  MENU_LINK_TONEW,
		  MENU_LINK_NEXTMOD,
		  MENU_LINK_TOOPT,
		  MENU_LINK_QUIT},
		 6};
sMenu AVA_MENU={{"Avatar",
		 "> Creer un Avatar :",
		 "[INPUT]",
		 "> Supprimer un Avatar :",
		 "[AVA]",
		 "> Retour"},
		{-90,-50,-30,10,30,70},
		{MENU_LINK_NONE,
		 MENU_LINK_NEWAVA,
		 MENU_LINK_INPUT,
		 MENU_LINK_DELAVA,
		 MENU_LINK_NEXTAVA,
		 MENU_LINK_TOMAIN},
		6};
sMenu OPT_MENU={{"Options",
		 "[DETLEVEL]",
		 "[RESOL]",
		 "[SONMUS]",
		 "[SONNOI]",
		 "> Reglage du Clavier",
		 "> Retour"},
		{-110, -70,-50,-10,10,50,90},
		{MENU_LINK_NONE,
		 MENU_LINK_NEXTDETL,
		 MENU_LINK_NEXTRESOL,
		 MENU_LINK_MUSIC,
		 MENU_LINK_NOISE,
		 MENU_LINK_TOINPUT1,
		 MENU_LINK_TOMAIN},
		7};
sMenu WIN_MENU={{"Mission accomplie..",
		 "[SCORES]",
		 "[SCORE1]",
		 "[SCORE2]",
		 "[SCORE3]",
		 "[SCORE4]",
		 "[SCORE5]",
		 "> Retour"},
		{-105,-65,-35,-15,5,25,45,85},
		{MENU_LINK_NONE,
		 MENU_LINK_NONE,
		 MENU_LINK_NONE,
		 MENU_LINK_NONE,
		 MENU_LINK_NONE,
		 MENU_LINK_NONE,
		 MENU_LINK_NONE,
		 MENU_LINK_TOMAIN},
		8};
sMenu NEW_MENU={{"Vaisseau :",
		 "[WING]",
		 "Map :",
		 "[MAP]",
		 "Climat :",
		 "[CLIM]",
		 "> Confirmer",
		 "> Retour"},
		{-110,-90,-50,-30,10,30,70,90},
		{MENU_LINK_NONE,
		 MENU_LINK_NEXTWING,
		 MENU_LINK_NONE,
		 MENU_LINK_NEXTMAP,
		 MENU_LINK_NONE,
		 MENU_LINK_NEXTCLIM,
		 MENU_LINK_START,
		 MENU_LINK_TOMAIN},
		8};

sMenu INP1_MENU={{"Reglages du Clavier :",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "> Suivant"},
		 {-100,-60,-40,-20,0,20,40,80},
		 {MENU_LINK_NONE,
		  MENU_LINK_INPUP,
		  MENU_LINK_INPDOWN,
		  MENU_LINK_INPLEFT,
		  MENU_LINK_INPRIGHT,
		  MENU_LINK_INPTLEFT,
		  MENU_LINK_INPTRIGHT,
		  MENU_LINK_TOINPUT2},
		 8};
sMenu INP2_MENU={{"[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "[KEYINP]",
		  "> Retour aux Options"},
		 {-90,-70,-50,-30,-10,10,30,70},
		 {MENU_LINK_INPACCEL,
		  MENU_LINK_INPDECELL,
		  MENU_LINK_INPSHIELD,
		  MENU_LINK_INPSHOOT,
		  MENU_LINK_INPNEXTWEAP,
		  MENU_LINK_INPBACKWEAP,
		  MENU_LINK_INPNEXTVIEW,
		  MENU_LINK_TOOPT},
		 8};

sMenu DEFI_MENU={{"Defi",
		  "Mission",
		  "[DEFI]",
		  "> Confirmer",
		  "> Retour"},
		 {-70,-30,-10,30,50},
		 {MENU_LINK_NONE,
		  MENU_LINK_NONE,
		  MENU_LINK_NEXTDEFI,
		  MENU_LINK_START,
		  MENU_LINK_TOMAIN},
		 5};



//sMenu * curMenu=&MAIN_MENU;
sMenu * curMenu=NULL;

void printMenuLine(int id);

