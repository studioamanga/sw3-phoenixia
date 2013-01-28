/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* main.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Contient la fonction main qui s'occupe de démarrer le   **
** programme, d'initialiser OpenGL et toutes les variables **
** nécessaires, avant d'entrer dans la boucle principale   **
** de jeu.                                                 **
**                                                         **
*************************************************************/
 
#include "headers.hpp"


int main(int argc, char**argv)
{
  logOut("\n        [SW3::PHOENIXIA]\n");
  logOut("        by[studio AMANgA]@[http://studioamanga.free.fr]\n\n\n");


  // Initialisation d'OpenGL et création de la fenêtre
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
  glutSpecialFunc(Special);
  // Activation de la fonction de rendu
  glutDisplayFunc(Display);
  // Activation des fonctions de remise à jour
  glutReshapeFunc(Reshape);
  glutIdleFunc(Idle);

  logOut("  [OK] Initialisation terminée\n");

  // Entrée dans la boucle principale
  glutMainLoop();

  return 0;
}

// Fonction de sortie du programme
void eXit(void)
{
  // Sauvegarde des configurations
  SaveCfg();
  // Destruction des objets dynamiques
  // destruction du menu
  if(SkinMenu)
    delete SkinMenu;
  //
  DelJ();

  if(Particule)
    delete Particule;

  if(mapDetail)
    {
      for(int iM=0 ; iM<nbMaps ; iM++)
	{
	  delete mapDetail[iM].tabClimat;
	}
      free(mapDetail);
    }

  clAvaMan::Kill();

  clSoundMan::Kill();

  // Sortie du programme
  logOut("\n  [OK] Destruction terminée ( time : %d )\n\n");//,int(TisT.GetTime()));
  logOut("  sw3..phoenixia(v0.4b)\n\n");

  exit(0);

  return;

}

