/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** input.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives aux entrées clavier souris.         **
**                                                         **
*************************************************************/

void KeyboardM(unsigned char key, int x, int y);
void KeyboardJ(unsigned char key, int x, int y);
void KeyboardUpM(unsigned char key, int x, int y);
void KeyboardUpJ(unsigned char key, int x, int y);

// Fonction pour gérer l'appui de touche du clavier
void Keyboard(unsigned char key, int x, int y)
{
  switch(Disp)
    {
    case DISP_JEU :
      KeyboardJ(key,x,y);
      break;
    case DISP_MENU :
      KeyboardM(key,x,y);
      break;
    }

  return;
}

// Fonction pour gérer le relachement des touches du clavier
void KeyboardUp(unsigned char key, int x, int y)
{
  switch(Disp)
    {
    case DISP_JEU :
      KeyboardUpJ(key,x,y);
      break;
    case DISP_MENU :
      KeyboardUpM(key,x,y);
      break;
    }

  return;
}

// Fonction pour gérer l'appui de touche du clavier
void KeyboardM(unsigned char key, int x, int y)
{
  // Sortie du programme
  if(key=='x') eXit();
	
	
  return;
}

// Fonction pour gérer le relachement des touches du clavier
void KeyboardUpM(unsigned char key, int x, int y)
{

  return;
}

// Fonction pour gérer l'appui de touche du clavier
void KeyboardJ(unsigned char key, int x, int y)
{
  // Actualisation des variables input pour le déplacement du vaisseau
  if(key=='z') fly->input->up=true;
  if(key=='s') fly->input->down=true;
  if(key=='q') fly->input->left=true;
  if(key=='d') fly->input->right=true;

  if(key=='f') glutFullScreen();
  //if(key=='g') glutWindowedScreen();

  if(key==' ') 
    {
      fly->input->shield=true;
      fly->getShield(false,true);
    }

  // Actualisation des variables input pour la vitesse du vaisseau
  if(key=='1') fly->input->goup=true; 
  if(key=='2') fly->input->godown=true; 

  // Réglage du zoom
  if(key=='-') { FFF-=0.0001; printf("%f\n",FFF); }
  if(key=='+') { FFF+=0.0001; printf("%f\n",FFF); }
  //if(key=='-') fogEffect('d',0.2);
  //if(key=='+') fogEffect('u',0.2);
  if(key=='4') VIEWa1+=5;
  if(key=='6') VIEWa1-=5;
  if(key=='8') VIEWa2+=5;
  if(key=='5') VIEWa2-=5;
  if(key=='7') VIEWz+=0.1;
  if(key=='9') VIEWz-=0.1;
  if(key=='*') Particule->AddExplosion(fly->getPos(),10);

  if(key=='l') 
    {
      LIGHTON=!LIGHTON;
      if(LIGHTON)
	glEnable(GL_LIGHTING);
      else
	glDisable(GL_LIGHTING);
    }

  // Sortie du programme
  if(key=='x') eXit();
	
	
  return;
}

// Fonction pour gérer le relachement des touches du clavier
void KeyboardUpJ(unsigned char key, int x, int y)
{
  // Actualisation des variables input pour le déplacement du vaisseau
  if(key=='z') fly->input->up=false;
  if(key=='s') fly->input->down=false;
  if(key=='q') fly->input->left=false;
  if(key=='d') fly->input->right=false;
  if(key=='1') fly->input->goup=false;
  if(key=='2') fly->input->godown=false;
  if(key==' ') fly->input->shield=false;

  return;
}
