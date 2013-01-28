/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** graphj.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives à l'affichage en général, à la      **
** gestion du clavier, ou à l'initialisation des données   **
** globales.                                               **
**                                                         **
*************************************************************/


float fogEffect(char fogTo, float vit);
void affTexLiq(float x_1, float x_2, float z_1, float z_2, float y_, float t_1, float t_2,  float ym1, float ym2, float ym3, float ym4, float tm);
void Aff_map(void);
void Aff_2D(void);


// Fonction d'affichage de la scène
void DisplayJ(void)
{  
  float BackColor[3]={MapColl->Climat->getR(),MapColl->Climat->getG(),MapColl->Climat->getB()};
  // Nettoyage du tampon ( par la couleur noire )
  glClearColor(BackColor[0],BackColor[1],BackColor[2],1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  
  // Réglages relatifs à la lumière
  static int LightPos[4]={0,100,0,1};
  static int MatSpec[4]={1,1,1,120};
  if(LIGHTON)
    {
      glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
      glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,120);
      glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    }
  
  // Réinitialisation de la matrice de vue
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  // Configuration de la caméra ( position, orientation et cadrage )
  if(VIEWEXT)
    gluLookAt(fly->getPos().x-(Cos(fly->getDir()+VIEWa1)*10*VIEWz)*Cos(valAbs(fly->getInclin()+VIEWa2)), 
	      fly->getPos().y-(Sin(fly->getInclin()-7+VIEWa2)*10*VIEWz), 
	      fly->getPos().z+(Sin(fly->getDir()+VIEWa1)*10*VIEWz)*Cos(valAbs(fly->getInclin()+VIEWa2)),
	      fly->getPos().x, 
	      fly->getPos().y, 
	      fly->getPos().z,
	      0, 1, 0);
  else
    gluLookAt(fly->getPos().x,
	      fly->getPos().y,
	      fly->getPos().z,
	      fly->getPos().x+(Cos(fly->getDir()+VIEWa1)*10*VIEWz)*Cos(valAbs(fly->getInclin()+VIEWa2)),
	      fly->getPos().y+(Sin(fly->getInclin()-7+VIEWa2)*10*VIEWz),
	      fly->getPos().z-(Sin(fly->getDir()+VIEWa1)*10*VIEWz)*Cos(valAbs(fly->getInclin()+VIEWa2)),
	      0, 1, 0);

  glDepthMask(GL_TRUE);

  // Affichage du vaisseau
  if(VIEWEXT)
    fly->afficher();

  // Affichage de la map
  Aff_map();

  glDepthMask(GL_FALSE);

  Particule->Aff();
  MapColl->affLiquid();
  fly->affTrans();

  glDepthMask(GL_TRUE);
  
  Aff_2D();
  
  // Inversion des buffers ( multi-buffering )
  glutSwapBuffers();


  return;
}

float fogEffect(char fogTo='0' , float vit=-9999)
{
  static float fogEff=1, vitEff=1;
  static char fogEffTo='0';
  bool modifer=false;

  if(fogTo!='0')
     fogEffTo=fogTo;
  if(vit!=-9999)
    vitEff=vit;

  if(fogEffTo=='u')
    {
      fogEff+=0.01*GETTIMER*vitEff;
      if(fogEff>1)
	{
	  fogEff=1;
	  fogTo='0';
	}
      modifer=true;
    }
  if(fogEffTo=='d')
    {
      fogEff-=0.01*GETTIMER*vitEff;
      if(fogEff<=0)
	{
	  fogEff=0.00001;
	  fogTo='0';
	}
      modifer=true;
    }

  if(modifer!=true)
    return -1;
  return fogEff;
}

void Aff_2D(void)
{
  // ************** Mask

  static int orientClock=0;
  static bool isInit=false;
  static float tarX, tarY, tarZ;
  orientClock+=GETTIMER;
  if(orientClock>6000)
    {
      orientClock=0;
      isInit=false;
    }
  float aDirTarget=0, aInclinTarget=0;
  if(orientClock==0 && Shokers->nbDrones>0)
    {
      float nearest=-1, nearX, nearY, nearZ;
      // Déterminer le Shoker le plus proche
      cl_drone * shoker=Shokers->Drones;
      for(int i=0 ; i<Shokers->nbDrones ; i++)
	{
	  float cx=shoker->getPos().x, cy=shoker->getPos().y, cz=shoker->getPos().z;
	  float distCur=sqrt(cx*cx+cy*cy+cz*cz);
	  if(nearest==-1 || distCur<nearest)
	    {
	      nearest=distCur;
	      nearX=cx;
	      nearY=cy;
	      nearZ=cz;
	    }
	  shoker=shoker->NEXT;
	}
      tarX=nearX;
      tarY=nearY;
      tarZ=nearZ;
     
      //printf("  %f>%f - %f/%f\n",fly->getDir(),aDirTarget,fly->getInclin(),aInclinTarget);
    }
  if( isInit==false && orientClock>3000 && Crystals->nbDrones>0)
    {
      float nearest=-1, nearX, nearY, nearZ;
      // Déterminer le Drone le plus proche
      cl_drone * drone=Crystals->Drones;
      for(int i=0 ; i<Crystals->nbDrones ; i++)
	{
	  float cx=drone->getPos().x, cy=drone->getPos().y, cz=drone->getPos().z;
	  float distCur=sqrt(cx*cx+cy*cy+cz*cz);
	  if(nearest==-1 || distCur<nearest)
	    {
	      nearest=distCur;
	      nearX=cx;
	      nearY=cy;
	      nearZ=cz;
	    }
	  drone=drone->NEXT;
	}
      tarX=nearX;
      tarY=nearY;
      tarZ=nearZ;

      isInit=true;    
    }

  aDirTarget=atan2(tarZ-(fly->getPos().z), tarX-(fly->getPos().x))*57.2975;
  aInclinTarget=atan2(tarY-(fly->getPos().y), sqrt((tarX-fly->getPos().x)*(tarX-fly->getPos().x)+(tarZ-fly->getPos().z)*(tarZ-fly->getPos().z)))*57.2975;

  aDirTarget+=180;

  OrthoMode(0,0,SCREEN_X,SCREEN_Y);
  glColor4f(1,1,1,1);

  //glScaled(3,3,3);

  glDisable(GL_DEPTH_TEST);
  if(LIGHTON)
    glDisable(GL_LIGHTING);
  glBlendFunc(GL_DST_COLOR,GL_ZERO);

  float _169mod=0;
  if(wideScr()>0)
    {
      _169mod=SCREEN_Y*0.2*wideScr()/100;

      glLoadIdentity();
      glColor4f(0,0,0,1);
      glBegin(GL_QUADS);  
      glVertex2f(0,0);
      glVertex2f(0, _169mod);
      glVertex2f(SCREEN_X, _169mod);
      glVertex2f(SCREEN_X,0);

      glVertex2f(0,SCREEN_Y-_169mod);
      glVertex2f(0,SCREEN_Y);
      glVertex2f(SCREEN_X,SCREEN_Y);
      glVertex2f(SCREEN_X,SCREEN_Y-_169mod);
      glEnd();

      glColor4f(1,1,1,1);
    }

  glEnable(GL_BLEND);


  tmask->setTexture();
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,_169mod);
  glTexCoord2f(0.0f, 0.5f);
  glVertex2f(0,SCREEN_Y/4+_169mod);
  glTexCoord2f(1.0f, 0.5f);
  glVertex2f(SCREEN_X/2,SCREEN_Y/4+_169mod);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(SCREEN_X/2,_169mod);


  glTexCoord2f(0.78f, 0.82f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y*0.8-_169mod);
  glTexCoord2f(1.0f, 0.82f);
  glVertex2f(SCREEN_X,SCREEN_Y*0.8-_169mod);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(SCREEN_X,SCREEN_Y-_169mod);
  glTexCoord2f(0.78f, 1.0f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y-_169mod); 
  glEnd();
  
 
  static float LiqColor[4]={getRealFromMadMap(MAPURL,'K',1),getRealFromMadMap(MAPURL,'K',2),getRealFromMadMap(MAPURL,'K',3),getRealFromMadMap(MAPURL,'K',4)};
   
  if(fly->getPos().y<(MapColl->Climat->getLiq()-(MapColl->Climat->getVarLiq()/2)))
    {
      glLoadIdentity();
      glColor4f(LiqColor[0],LiqColor[1],LiqColor[2],LiqColor[3]);
      glBegin(GL_QUADS);  
      glVertex2f(0,_169mod);
      glVertex2f(0,SCREEN_Y-_169mod);
      glVertex2f(SCREEN_X,SCREEN_Y-_169mod);
      glVertex2f(SCREEN_X,_169mod);
      glEnd();
    }


  glBlendFunc(GL_ONE,GL_ONE);
  tcache->setTexture();


  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,_169mod);
  glTexCoord2f(0.0f, 0.5f);
  glVertex2f(0,SCREEN_Y/4+_169mod);
  glTexCoord2f(1.0f, 0.5f);
  glVertex2f(SCREEN_X/2,SCREEN_Y/4+_169mod);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(SCREEN_X/2,_169mod);

  glTexCoord2f(0.78f, 0.82f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y*0.8-_169mod);
  glTexCoord2f(1.0f, 0.82f);
  glVertex2f(SCREEN_X,SCREEN_Y*0.8-_169mod);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(SCREEN_X,SCREEN_Y-_169mod);
  glTexCoord2f(0.78f, 1.0f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y-_169mod); 

  glEnd();

  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //  glColor4f(1,0,0,1);

  float fRot=((360*MapColl->TIMEactu)/MapColl->TIMEmax);
  glPushMatrix();
  glTranslatef(SCREEN_X*0.92,SCREEN_Y*0.92-_169mod,0);
  glPushMatrix();
  glRotatef(fRot,0,0,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.9f, 0.7f);
  glVertex2f(-SCREEN_X*0.05,-SCREEN_Y*0.05);
  glTexCoord2f(1.0f, 0.7f);
  glVertex2f(SCREEN_X*0.05,-SCREEN_Y*0.05);
  glTexCoord2f(1.0f, 0.6f);
  glVertex2f(SCREEN_X*0.05,SCREEN_Y*0.05);
  glTexCoord2f(0.9f, 0.6f);
  glVertex2f(-SCREEN_X*0.05,SCREEN_Y*0.05);
  glEnd();

  glPopMatrix();
  
 
  glRotatef(fRot*10,0,0,1);
  static float Rotr=-0.6;
  glScalef(Rotr*Rotr+0.5,Rotr*Rotr+0.5,Rotr*Rotr+0.5);
  Rotr+=0.02;
  if(Rotr>0.6)
    Rotr=-0.6;
  glBegin(GL_QUADS);
  glTexCoord2f(0.9f, 0.8f);
  glVertex2f(-SCREEN_X*0.05,-SCREEN_Y*0.05);
  glTexCoord2f(1.0f, 0.8f);
  glVertex2f(SCREEN_X*0.05,-SCREEN_Y*0.05);
  glTexCoord2f(1.0f, 0.7f);
  glVertex2f(SCREEN_X*0.05,SCREEN_Y*0.05);
  glTexCoord2f(0.9f, 0.7f);
  glVertex2f(-SCREEN_X*0.05,SCREEN_Y*0.05);
  glEnd();
  glPopMatrix();

  glColor4f(1,1,1,1);

  glPushMatrix();
  float CrRatio=( 1-(float(MapColl->NbCrystals) / float(MapColl->TotalCrystals)) );
  if(CrRatio<0) CrRatio=0;
  glTranslatef(SCREEN_X*0.02,SCREEN_Y*0.21+_169mod,0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.17, 1.0);
  glVertex2f(0,0);
  glTexCoord2f(0.41, 1.0);
  glVertex2f(SCREEN_X*0.12,0);
  glTexCoord2f(0.41, 1.0-(0.36*CrRatio));
  glVertex2f(SCREEN_X*0.12,-(SCREEN_Y*0.18*CrRatio));
  glTexCoord2f(0.17, 1.0-(0.36*CrRatio));
  glVertex2f(0,-(SCREEN_Y*0.18*CrRatio));
  glEnd();
  glPopMatrix();

  glPushMatrix();
  float ArRatio=( (fly->getArmure()) / 100 );
  if(ArRatio<0) ArRatio=0;
  glTranslatef(SCREEN_X*0.185,SCREEN_Y*0.025+_169mod,0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.41f, 0.8f);
  glVertex2f(0,0);
  glTexCoord2f(0.41f, 1.0f);
  glVertex2f(0,SCREEN_Y*0.1);
  glTexCoord2f(0.41f+(0.33*ArRatio), 1.0f);
  glVertex2f(SCREEN_X*0.165*ArRatio,SCREEN_Y*0.1);
  glTexCoord2f(0.41f+(0.33*ArRatio), 0.8f);
  glVertex2f(SCREEN_X*0.165*ArRatio,0);
  glEnd();
  glPopMatrix();

  //glColor4f(1,1,1,1);
  //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  float fMTCS=SCREEN_X/25;

  glTranslatef(SCREEN_X*0.2,(SCREEN_Y/2)*0.363+_169mod,0);

  if(orientClock<=3000 && Shokers->nbDrones>0)
    {
      glColor4f(1,0,0,1);
      glPushMatrix();
      glRotated(aDirTarget,0,0,1);
      glBegin(GL_QUADS);
      glTexCoord2f(0.039f, 0.535f);
      glVertex2f(-fMTCS,-fMTCS);
      glTexCoord2f(0.039f, 0.684f);
      glVertex2f(-fMTCS,fMTCS);
      glTexCoord2f(0.18f, 0.684f);
      glVertex2f(fMTCS,fMTCS);
      glTexCoord2f(0.18f, 0.535f);
      glVertex2f(fMTCS,-fMTCS);

      glEnd();
      glPopMatrix();

      glColor4f(1,1,1,1);
    }
  else
    if( Crystals->nbDrones>0 )
      {
	glColor4f(0,1,0,1);
	glPushMatrix();
	glRotated(aDirTarget,0,0,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.039f, 0.535f);
	glVertex2f(-fMTCS,-fMTCS);
	glTexCoord2f(0.039f, 0.684f);
	glVertex2f(-fMTCS,fMTCS);
	glTexCoord2f(0.18f, 0.684f);
	glVertex2f(fMTCS,fMTCS);
	glTexCoord2f(0.18f, 0.535f);
	glVertex2f(fMTCS,-fMTCS);

	glEnd();
	glPopMatrix();

	glColor4f(1,1,1,1);
      }


  glPushMatrix();
  glRotated(-fly->getDir()+180,0,0,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.039f, 0.535f);
  glVertex2f(-fMTCS,-fMTCS);
  glTexCoord2f(0.039f, 0.684f);
  glVertex2f(-fMTCS,fMTCS);
  glTexCoord2f(0.18f, 0.684f);
  glVertex2f(fMTCS,fMTCS);
  glTexCoord2f(0.18f, 0.535f);
  glVertex2f(fMTCS,-fMTCS);

  glEnd();
  glPopMatrix();

  glTranslatef((SCREEN_X/2)*0.14,0,0);

  if(orientClock<=3000 && Shokers->nbDrones>0)
    {
      glColor4f(1,0,0,1);
      glPushMatrix();
      glRotated(-aInclinTarget-90,0,0,1);
      glBegin(GL_QUADS);

      glTexCoord2f(0.02f, 0.754f);
      glVertex2f(-fMTCS,-fMTCS);
      glTexCoord2f(0.02f, 0.91f);
      glVertex2f(-fMTCS,fMTCS);
      glTexCoord2f(0.18f, 0.91f);
      glVertex2f(fMTCS,fMTCS);
      glTexCoord2f(0.18f, 0.754f);
      glVertex2f(fMTCS,-fMTCS);

      glEnd();
      glPopMatrix();

      glColor4f(1,1,1,1);
    }
  else
    if(Crystals->nbDrones>0)
      {
	glColor4f(0,1,0,1);
	glPushMatrix();
	glRotated(-aInclinTarget-90,0,0,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.02f, 0.754f);
	glVertex2f(-fMTCS,-fMTCS);
	glTexCoord2f(0.02f, 0.91f);
	glVertex2f(-fMTCS,fMTCS);
	glTexCoord2f(0.18f, 0.91f);
	glVertex2f(fMTCS,fMTCS);
	glTexCoord2f(0.18f, 0.754f);
	glVertex2f(fMTCS,-fMTCS);

	glEnd();
	glPopMatrix();

	glColor4f(1,1,1,1);
      }


  glPushMatrix();
  glRotated(-fly->getInclin()-90,0,0,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.039f, 0.754f);
  glVertex2f(-fMTCS,-fMTCS);
  glTexCoord2f(0.039f, 0.91f);
  glVertex2f(-fMTCS,fMTCS);
  glTexCoord2f(0.18f, 0.91f);
  glVertex2f(fMTCS,fMTCS);
  glTexCoord2f(0.18f, 0.754f);
  glVertex2f(fMTCS,-fMTCS);

  glEnd();
  glPopMatrix();

  Fonter.Couleur(1,1,1);
  Fonter.Print(10, int(SCREEN_Y-40-_169mod), fly->getWeaponStr());
  if(fly->getWeaponFire()>=0)
    Fonter.Print(10, int(SCREEN_Y-20-_169mod), "%d", fly->getWeaponFire());

  char sTime[20];
  sprintf(sTime,"%d:%d",int(MapColl->TIMEactu/1000)%60,int(MapColl->TIMEactu/10)%60);
  Fonter.Print(int(SCREEN_X-100), int(SCREEN_Y-40-_169mod), sTime);

  if(gamePause)
    {
      Fonter.Print(FONT_POSITION_CENTRE, int(SCREEN_Y/2-40), "Jeu en Pause");
      Fonter.Print(FONT_POSITION_CENTRE, int(SCREEN_Y/2),    "Continuer");
      Fonter.Print(FONT_POSITION_CENTRE, int(SCREEN_Y/2+20), "Quitter la Mission");
      Fonter.Couleur(1,0,0);
      if(gamePauseQuit)
	Fonter.Print(FONT_POSITION_CENTRE, int(SCREEN_Y/2+20), "Quitter la Mission");
      else
	Fonter.Print(FONT_POSITION_CENTRE, int(SCREEN_Y/2),    "Continuer");
      Fonter.Couleur(1,1,1);
    }

  if(menuCommentTime>0)
    {
      menuCommentTime-=GETTIMER;
      Fonter.Print(FONT_POSITION_CENTRE, int(SCREEN_Y-_169mod), menuComment);

    }

  glColor4f(1,1,1,1);

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  if(LIGHTON)
    glEnable(GL_LIGHTING);
  glEnable(GL_FOG);

  PerspectiveMode();

  return;
}

// Fonction d'affichage de la map
void Aff_map(void) // Identifiant permettant de spécifier la map
{
  // Sauvegarde de la matrice courante
  glPushMatrix();
  Map->aff();
  // Reprise de la matrice d'origine
  glPopMatrix();


  // Affichage des shokers
  Shokers->afficher();

  // Affichage des crystaux
  Crystals->afficher();


  float fogEffFact=fogEffect();
  if(fogEffFact!=-1)
    {
      glFogf(GL_FOG_START, MapColl->Climat->getFog()*fogEffFact);
      glFogf(GL_FOG_END, (MapColl->Climat->getFog()+500)*fogEffFact);
      glEnable(GL_FOG);
    }
	

  return;
}

void affTexLiq(float x_1, float x_2, float z_1, float z_2, float y_, float t_1, float t_2,  float ym1, float ym2, float ym3, float ym4, float tm)
{
  glTexCoord2f(0.0f+tm, t_2+tm);
  glVertex3f(x_1,y_-ym1*ym1,z_1);
  glTexCoord2f(0.0f+tm, 0.0f+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym2*ym2,z_1);
  glTexCoord2f(t_1+tm, 0.0f+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym3*ym3,z_1+((z_2-z_1)/2));
  glTexCoord2f(t_1+tm, t_2+tm);
  glVertex3f(x_1,y_-ym4*ym4,z_1+((z_2-z_1)/2));

  glTexCoord2f(0.0f+tm, t_2+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym2*ym2,z_1);
  glTexCoord2f(0.0f+tm, 0.0f+tm);
  glVertex3f(x_2,y_-ym1*ym1,z_1);
  glTexCoord2f(t_1+tm, 0.0f+tm);
  glVertex3f(x_2,y_-ym4*ym4,z_1+((z_2-z_1)/2));
  glTexCoord2f(t_1+tm, t_2+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym3*ym3,z_1+((z_2-z_1)/2));

  glTexCoord2f(0.0f+tm, t_2+tm);
  glVertex3f(x_1,y_-ym4*ym4,z_1+((z_2-z_1)/2));
  glTexCoord2f(0.0f+tm, 0.0f+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym3*ym3,z_1+((z_2-z_1)/2));
  glTexCoord2f(t_1+tm, 0.0f+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym2*ym2,z_2);
  glTexCoord2f(t_1+tm, t_2+tm);
  glVertex3f(x_1,y_-ym1*ym1,z_2);

  glTexCoord2f(0.0f+tm, t_2+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym3*ym3,z_1+((z_2-z_1)/2));
  glTexCoord2f(0.0f+tm, 0.0f+tm);
  glVertex3f(x_2,y_-ym4*ym4,z_1+((z_2-z_1)/2));
  glTexCoord2f(t_1+tm, 0.0f+tm);
  glVertex3f(x_2,y_-ym1*ym1,z_2);
  glTexCoord2f(t_1+tm, t_2+tm);
  glVertex3f(x_1+((x_2-x_1)/2),y_-ym2*ym2,z_2);

  return;
}

// Affichage du Liquid
void cl_bsp::affLiquid(void)
{
  float varLiq=this->Climat->getVarLiq();

  static bool isInit=false;
  static float __t1,__t2,texmod=0,yMod1=-varLiq,yMod2=-(varLiq/2),yMod3=varLiq/2,yMod4=varLiq;
  if(isInit==false)
    {
      __t1=2;
      __t2=2;
      isInit=true;
    }

  // glDisable(GL_FOG);
  glEnable(GL_BLEND);
  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  tLiquid->setTexture();

  if(!gamePause)
    {
      yMod1+=0.001*GETTIMER;
      if(yMod1>varLiq)
	yMod1=-varLiq;
      yMod2+=0.001*GETTIMER;
      if(yMod2>varLiq)
	yMod2=-varLiq;
      yMod3+=0.001*GETTIMER;
      if(yMod3>varLiq)
	yMod3=-varLiq;
      yMod4+=0.001*GETTIMER;
      if(yMod4>varLiq)
	yMod4=-varLiq;
    }
  /*
    glBegin(GL_QUADS);
    affTexLiq(this->MapLimitsGraph[MAPLIMITSUP], this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2),this->MapLimitsGraph[MAPLIMITSRIGHT], this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
    affTexLiq(this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2), this->MapLimitsGraph[MAPLIMITSDOWN],this->MapLimitsGraph[MAPLIMITSRIGHT], this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
    affTexLiq(this->MapLimitsGraph[MAPLIMITSUP], this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2),this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->MapLimitsGraph[MAPLIMITSLEFT], this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
    affTexLiq(this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2), this->MapLimitsGraph[MAPLIMITSDOWN],this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->MapLimitsGraph[MAPLIMITSLEFT], this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
    glEnd();*/
  glBegin(GL_QUADS);
  affTexLiq(this->MapLimitsGraph[MAPLIMITSUP], this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2),this->MapLimitsGraph[MAPLIMITSRIGHT], this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
  affTexLiq(this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2), this->MapLimitsGraph[MAPLIMITSDOWN],this->MapLimitsGraph[MAPLIMITSRIGHT], this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
  affTexLiq(this->MapLimitsGraph[MAPLIMITSUP], this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2),this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->MapLimitsGraph[MAPLIMITSLEFT], this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
  affTexLiq(this->MapLimitsGraph[MAPLIMITSDOWN]+(this->getSizeX()/2), this->MapLimitsGraph[MAPLIMITSDOWN],this->MapLimitsGraph[MAPLIMITSLEFT]+(this->getSizeZ()/2), this->MapLimitsGraph[MAPLIMITSLEFT], this->Climat->getLiq(), __t1, __t2, yMod1, yMod2, yMod3, yMod4, texmod);
  glEnd();

  glDisable(GL_BLEND);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  texmod+=0.00005*GETTIMER*(this->Climat->getVarLiq()/2);
  if(texmod>=1)
    texmod=0;


  return;
}
