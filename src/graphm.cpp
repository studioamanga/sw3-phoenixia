/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** graphm.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives � l'affichage en g�n�ral, � la      **
** gestion du clavier, ou � l'initialisation des donn�es   **
** globales.                                               **
**                                                         **
*************************************************************/


// Fonction d'affichage de la sc�ne
void DisplayM(void)
{  
  static float rotMenu=0;
  // Nettoyage du tampon ( par la couleur noire )
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // R�initialisation de la matrice de vue
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  // Configuration de la cam�ra ( position, orientation et cadrage )
  gluLookAt(1,0,0,
	    0,0,0,
	    0,1,0);

  glDepthMask(GL_TRUE);

  //3d
  rotMenu+=GETTIMER*0.0005;
  glRotated(90,1,0,0);
  glRotated(rotMenu,0,1,0);
  SkinMenu->aff();


  
  // ************** Mask
  //glDepthMask(GL_FALSE);

  OrthoMode(0,0,SCREEN_X,SCREEN_Y);

  affMenuTxt();

  PerspectiveMode();

  // Inversion des buffers ( multi-buffering )
  glutSwapBuffers();


  return;
}
