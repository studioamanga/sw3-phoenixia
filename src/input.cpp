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

void Special(int key, int x, int y)
{
  clSoundMan * Sound=clSoundMan::Create();
  Sound->JouerStream (SOUND_TOUCHE, CANAL_BRUITS, false);
  switch(Disp)
    {
    case DISP_JEU :
      if(gamePause)
	{
	  if(key==INPUT_KEY_UP || key==INPUT_KEY_DOWN)
	    gamePauseQuit=!gamePauseQuit;
	}
      break;
    case DISP_MENU : 
      if(curMenu==NULL)
	return;
      if( curMenu->MENU_LINK[cursMenu-1]>= MENU_LINK_INPUP && curMenu->MENU_LINK[cursMenu-1]<= MENU_LINK_INPBACKWEAP && idInputStr==-1)
	{
	  menuSetComment("Impossible d'utiliser cette touche.",3000);
	  idInputStr=0;
	  return;
	}
      if(key==INPUT_KEY_UP)
	{
	  do
	    {
	      cursMenu--;
	      if(cursMenu<1)
		cursMenu=cursMenuMax;
	    }
	  while(curMenu->MENU_LINK[cursMenu-1]==MENU_LINK_NONE);
	}
      if(key==INPUT_KEY_DOWN)
	{
	  do
	    {
	      cursMenu++;
	      if(cursMenu>cursMenuMax)
		cursMenu=1;
	    }
	  while(curMenu->MENU_LINK[cursMenu-1]==MENU_LINK_NONE);
	}

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
  clSoundMan * Sound=clSoundMan::Create();
  Sound->JouerStream (SOUND_TOUCHE, CANAL_BRUITS, false);
  if(curMenu==NULL)
    return;
  if( curMenu->MENU_LINK[cursMenu-1]>= MENU_LINK_INPUP && curMenu->MENU_LINK[cursMenu-1]<= MENU_LINK_INPBACKWEAP && idInputStr==-1)
    {
      if(setInputNewKey(key))
	menuSetComment("Changements effectues.",3000);
      else
	menuSetComment("Cette touche est deja utilisee.",3000);
      idInputStr=0;
      return;
    }
  if(curMenu->MENU_LINK[cursMenu-1]==MENU_LINK_INPUT )
    {
      if(key==INPUT_KEY_ECHAP || key==INPUT_KEY_ENTER)
	cursMenu--;
      else
	if(key==INPUT_KEY_BACK)
	  {
	    inputStr[idInputStr-1]='\0';
	    idInputStr--;
	    if(idInputStr==-1)
	      idInputStr=0;
	    return;
	  }
	else
	  if( (key>='a' && key<='z') || (key>='A' && key<='Z') || (key>='1' && key<='9') && idInputStr<maxInputStr )
	    {
	      inputStr[idInputStr]=key;
	      idInputStr++;
	      inputStr[idInputStr]='\0';
	      return;
	    }
    }

   if(key==myInput[INPUT_OK])
    {
      Sound->JouerStream (SOUND_VALID, CANAL_BRUITS, false);
      menuOK();
      return;
    }

  if(key==myInput[INPUT_EXIT]) eXit();

  //printf("%c : %d\n", key, key);
	
  return;
}

// Fonction pour gérer le relachement des touches du clavier
void KeyboardUpM(unsigned char key, int x, int y)
{
  if(curMenu==NULL)
    return;
  return;
}

// Fonction pour gérer l'appui de touche du clavier
void KeyboardJ(unsigned char key, int x, int y)
{
  clSoundMan * Sound=clSoundMan::Create();
  if(MapColl->isFinish())
    {
      if(key==myInput[INPUT_OK] || key==INPUT_KEY_ECHAP)
	FinPartie();
    }
  else
    if(gamePause)
      {
	if(key==myInput[INPUT_OK])
	  {
	    Sound->JouerStream (SOUND_VALID, CANAL_BRUITS, false);
	    if(gamePauseQuit)
	      {
		gamePauseQuit=false;
		gamePause=false;
		FinPartie();
	      }
	    else
	      gamePause=false;
	  }
      }
    else
      {
	if(key==myInput[INPUT_UP])
	  {
	    fly->input->up=true;
	    Sound->JouerStream (SOUND_VIRAGE, CANAL_BRUITS, false);
	  }
	if(key==myInput[INPUT_DOWN])
	  {
	    fly->input->down=true;
	    Sound->JouerStream (SOUND_VIRAGE, CANAL_BRUITS, false);
	  }
	if(key==myInput[INPUT_LEFT])
	  {
	    fly->input->left=true;
	    Sound->JouerStream (SOUND_VIRAGE, CANAL_BRUITS, false);
	  }
	if(key==myInput[INPUT_RIGHT])
	  {
	    fly->input->right=true;
	    Sound->JouerStream (SOUND_VIRAGE, CANAL_BRUITS, false);
	  }
	if(key==myInput[INPUT_TLEFT])
	  {
	    fly->input->transleft=true;
	    Sound->JouerStream (SOUND_VIRAGE, CANAL_BRUITS, false);
	  }
	if(key==myInput[INPUT_TRIGHT])
	  {
	    fly->input->transright=true;
	    Sound->JouerStream (SOUND_VIRAGE, CANAL_BRUITS, false);
	  }
	if(key==myInput[INPUT_SHOOT])
	    fly->input->shoot=true;
	if(key==myInput[INPUT_SHIELD])
	  {
	    fly->input->shield=true;
	    fly->getShield(false,true);
	    Sound->JouerStream (SOUND_SHIELD, CANAL_ARME, false);
	  }

	// Actualisation des variables input pour la vitesse du vaisseau
	if(key==myInput[INPUT_ACCEL])
	  fly->input->goup=true;
	if(key==myInput[INPUT_DECELL])
	  fly->input->godown=true;

	if(key==myInput[INPUT_WEAPNEXT])
	  fly->setCurWeapon(fly->getCurWeapon()+1);
	if(key==myInput[INPUT_WEAPBACK])
	  fly->setCurWeapon(fly->getCurWeapon()-1);
	if(key==myInput[INPUT_WEAP1])
	  fly->setCurWeapon(0);
	if(key==myInput[INPUT_WEAP2])
	  fly->setCurWeapon(1);
	if(key==myInput[INPUT_WEAP3])
	  fly->setCurWeapon(2);
	if(key==myInput[INPUT_WEAP4])
	  fly->setCurWeapon(3);
	if(key==myInput[INPUT_WEAP5])
	  fly->setCurWeapon(4);
	if(key==myInput[INPUT_WEAP6])
	  fly->setCurWeapon(5);
	if(key==myInput[INPUT_WEAP7])
	  fly->setCurWeapon(6);
	if(key==myInput[INPUT_WEAP8])
	  fly->setCurWeapon(7);
	if(key==myInput[INPUT_WEAP9])
	  fly->setCurWeapon(8);
      }

  if(key==myInput[INPUT_NEXTVIEW]) VIEWEXT=!VIEWEXT;

  if(key==myInput[INPUT_FULLS]) 
    {
      if(SCREEN_FULL)
	glutReshapeWindow(SCREEN_X,SCREEN_Y);
      else
	glutFullScreen();	
      SCREEN_FULL=!SCREEN_FULL;
    }

  // Réglage du zoom
  //if(key=='-') fogEffect('d',0.2);
  //if(key=='+') fogEffect('u',0.2);

  if(key==myInput[INPUT_ZOOML]) VIEWa1+=5;
  if(key==myInput[INPUT_ZOOMR]) VIEWa1-=5;
  if(key==myInput[INPUT_ZOOMUP]) VIEWa2+=5;
  if(key==myInput[INPUT_ZOOMDO]) VIEWa2-=5;
  if(key==myInput[INPUT_ZOOMIN]) VIEWz+=0.1;
  if(key==myInput[INPUT_ZOOMOUT]) VIEWz-=0.1;
  if(key==myInput[INPUT_EXPLO]) Particule->AddSpark(fly->getPos()+swVertex(0,3,0),30);

  if(key==myInput[INPUT_WIDESCR])
    wideScr(false,true);

  if(key==myInput[INPUT_LIGHT]) 
    {
      LIGHTON=!LIGHTON;
      if(LIGHTON)
	glEnable(GL_LIGHTING);
      else
	glDisable(GL_LIGHTING);
    }

  if(key==INPUT_KEY_ECHAP)
    gamePause=!gamePause;
  // Sortie du programme
  if(key==myInput[INPUT_EXIT])
    eXit();

  return;
}

// Fonction pour gérer le relachement des touches du clavier
void KeyboardUpJ(unsigned char key, int x, int y)
{
  if(gamePause)
    {
    }

  else
    {
      // Actualisation des variables input pour le déplacement du vaisseau
      if(key==myInput[INPUT_UP])      fly->input->up=false;
      if(key==myInput[INPUT_DOWN])    fly->input->down=false;
      if(key==myInput[INPUT_LEFT])    fly->input->left=false;
      if(key==myInput[INPUT_RIGHT])   fly->input->right=false;
      if(key==myInput[INPUT_ACCEL])   fly->input->goup=false;
      if(key==myInput[INPUT_DECELL])  fly->input->godown=false;
      if(key==myInput[INPUT_SHIELD])  fly->input->shield=false;
      if(key==myInput[INPUT_TLEFT])   fly->input->transleft=false;
      if(key==myInput[INPUT_TRIGHT])  fly->input->transright=false;

      if(key==myInput[INPUT_SHOOT]) fly->input->shoot=false;
    }

  return;
}

char * getInputAction(int key)
{
  char * s=new char[20];
  switch(key)
    {
    case MENU_LINK_INPUP :
      strcpy(s,"Elever");
      break;
    case MENU_LINK_INPDOWN :
      strcpy(s,"Descendre");
      break;
    case MENU_LINK_INPLEFT :
      strcpy(s,"Pivoter a Gauche");
      break;
    case MENU_LINK_INPRIGHT :
      strcpy(s,"Pivoter a Droite");
      break;
    case MENU_LINK_INPTLEFT :
      strcpy(s,"Slide Gauche");
      break;
    case MENU_LINK_INPTRIGHT :
      strcpy(s,"Slide Droit");
      break;
    case MENU_LINK_INPACCEL :
      strcpy(s,"Accelerer");
      break;
    case MENU_LINK_INPDECELL :
      strcpy(s,"Decelerer");
      break;
    case MENU_LINK_INPSHIELD :
      strcpy(s,"Shield");
      break;
    case MENU_LINK_INPNEXTVIEW :
      strcpy(s,"Changer de Vue");
      break;
    case MENU_LINK_INPWIDESCR :
      strcpy(s,"Wide Screen");
      break;
    case MENU_LINK_INPEXIT :
      strcpy(s,"Quitter");
      break;
    case MENU_LINK_INPSHOOT :
      strcpy(s,"Tirer");
      break;
    case MENU_LINK_INPNEXTWEAP :
      strcpy(s,"Arme Suivante");
      break;
    case MENU_LINK_INPBACKWEAP :
      strcpy(s,"Arme Precedente");
      break;
    }

  return s;
}

char * getInputKey(int key)
{
  char * s=new char[20];
  //  strcpy(s,key);
  s[0]=char(key);
  s[1]='\0';

  if(key==' ')
    strcpy(s,"Espace");

  return s;
}

bool setInputNewKey(char key)
{
  // controle que la touche n'est pas deja utilisee
  for(int i=0 ; i<NB_INPUT ; i++ )
    if(myInput[i]==key)
      return false;

  myInput[curMenu->MENU_LINK[cursMenu-1]-MENU_LINK_INPUT_DECALAGE]=key;
  return true;
}
