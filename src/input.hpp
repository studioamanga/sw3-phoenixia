/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** input.hpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives aux entrées clavier souris.         **
**                                                         **
*************************************************************/

#define INPUT_KEY_ENTER 13
#define INPUT_KEY_BACK  8
#define INPUT_KEY_ECHAP 27
#define INPUT_KEY_UP    GLUT_KEY_UP
#define INPUT_KEY_DOWN  GLUT_KEY_DOWN


enum
  {
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_TLEFT,
    INPUT_TRIGHT,
    INPUT_FULLS,
    INPUT_SHIELD,
    INPUT_ACCEL,
    INPUT_DECELL,
    INPUT_ZOOML,
    INPUT_ZOOMR,
    INPUT_ZOOMUP,
    INPUT_ZOOMDO,
    INPUT_ZOOMIN,
    INPUT_ZOOMOUT,
    INPUT_EXPLO,
    INPUT_LIGHT,
    INPUT_NEXTVIEW,
    INPUT_WIDESCR,
    INPUT_EXIT,
    INPUT_OK,
    INPUT_SHOOT,
    INPUT_WEAP1,
    INPUT_WEAP2,
    INPUT_WEAP3,
    INPUT_WEAP4,
    INPUT_WEAP5,
    INPUT_WEAP6,
    INPUT_WEAP7,
    INPUT_WEAP8,
    INPUT_WEAP9,
    INPUT_WEAPNEXT,
    INPUT_WEAPBACK,
    NB_INPUT
  };

char myInput [NB_INPUT]={'z','s','q','d','a','e','f',' ','1','2','4','6','8','5','+','-','*','l','v','w','x',INPUT_KEY_ENTER,'0','&','é','"','\'','(','-','è','_','ç','9','7'};


void KeyboardM(unsigned char key, int x, int y);
void KeyboardJ(unsigned char key, int x, int y);
void KeyboardUpM(unsigned char key, int x, int y);
void KeyboardUpJ(unsigned char key, int x, int y);
char * getInputAction(int key);
char * getInputKey(int key);
bool setInputNewKey(char key);
