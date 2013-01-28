/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* main.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Contient la fonction main qui s'occupe de d�marrer le   **
** programme, d'initialiser OpenGL et toutes les variables **
** n�cessaires, avant d'entrer dans la boucle principale   **
** de jeu.                                                 **
**                                                         **
*************************************************************/
 
#include "sources/headers.hpp"



int main(int argc, char**argv)
{
  printf("\n        [SW3::PHOENIXIA]\n");
  printf("        by[studio AMANgA]@[http://studioamanga.free.fr]\n\n\n");


  // Initialisation d'OpenGL et cr�ation de la fen�tre
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_X,SCREEN_Y);
  glutInitWindowPosition(10,10);
  glutCreateWindow("SW3::PHOENIXIA");
  // Initialisation des variables
  Init();

  // Activation de la gestion du clavier
  glutKeyboardFunc(Keyboard);
  glutKeyboardUpFunc(KeyboardUp);
  // Activation de la fonction de rendu
  glutDisplayFunc(Display);
  // Activation des fonctions de remise � jour
  glutReshapeFunc(Reshape);
  glutIdleFunc(Idle);

  printf("  [OK] Initialisation termin�e\n");

  // Entr�e dans la boucle principale
  glutMainLoop();

  return 0;
}

// Fonction de sortie du programme
void eXit(void)
{
  // Destruction des objets dynamiques
  if(fly)
    delete fly;
  if(Map)
    delete Map;
  if(MapColl)
    delete MapColl;
  if(Shokers)
    delete Shokers;
  if(Crystals)
    delete Crystals;

  if(tmask)
    delete tmask;
  if(tcache)
    delete tcache;
  if(tLiquid)
    delete tLiquid;

  if(Particule)
    delete Particule;

  // Sortie du programme
  printf("\n  [OK] Destruction termin�e ( time : %d )\n\n",TisT.GetTime());
  printf("  sw3..phoenixia(v0.3b)\n\n");

  exit(0);

  return;

}

