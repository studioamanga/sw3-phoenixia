/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** graphj.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives � l'affichage en g�n�ral, � la      **
** gestion du clavier, ou � l'initialisation des donn�es   **
** globales.                                               **
**                                                         **
*************************************************************/



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

// Fonction d'affichage de la map
void Aff_map(void) // Identifiant permettant de sp�cifier la map
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

CTimer TisT;

// Gestion d'initialisation globale
void InitJ(void)
{
  Particule= new ParticuleManager;
  printf("  [OK] Moteur � Particule initialis�\n");

  // Chargement des textures � partir des fichiers
  Map=new cl_model(MAPURL);

  // Allocation m�moire de la classe 'wing' du vaisseau principal
  fly=new cl_wing(WINGURL);

  TisT.Init();
  // Allocation m�moire de la classe 'bsp' des collisions de la map
  MapColl=new cl_bsp(MAPURL);

  // Textures des mask
  tmask=new cl_texture("./data/texture/interf/mask.bmp");
  tcache=new cl_texture("./data/texture/interf/m1.tga");

  char *urlLT=getStrFromMadMap(MAPURL,'L',1);
  tLiquid=new cl_texture(urlLT);
  delete urlLT;

  // Initialisation des drones Shoker
  try
    {
      int nbDrone=getNbFromMadMap(MAPURL,'S');
      type_drone *ts=new type_drone[nbDrone];
      vertex *tPos=new vertex[nbDrone];
      for(int i=0 ; i<nbDrone ; i++)
	{
	  ts[i]=SHOKER01;
	  tPos[i]=getVertexFromMadMap(MAPURL,'S',i+1);
	}
      Shokers= new cl_Serie('S',nbDrone,ts,tPos);
      delete tPos;
      delete ts;

      // Initialisation des drones Crystal
      nbDrone=getNbFromMadMap(MAPURL,'D');
      ts=new type_drone[nbDrone];
      tPos=new vertex[nbDrone];
      for(int i=0 ; i<nbDrone ; i++)
	{
	  ts[i]=CRYSTAL01;
	  tPos[i]=getVertexFromMadMap(MAPURL,'D',i+1);
	}
      Crystals= new cl_Serie('C',nbDrone,ts,tPos);
    }
  catch(...)
    {
      printf(" [!]Erreur dans l'initialisation des Drones\n");
      exit(0);
    }
	

  float BackColor[4]={MapColl->Climat->getR(),MapColl->Climat->getG(),MapColl->Climat->getB(),1.0};

  // Param�trage du brouillard
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, BackColor);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, MapColl->Climat->getFog());
  glFogf(GL_FOG_END, MapColl->Climat->getFog()+500);
  // Activation du brouillard
  glEnable(GL_FOG);

  if(MapColl->Climat->IsPluie())
    Particule->AddPluie(fly,50);
  if(MapColl->Climat->IsNeige())
    Particule->AddNeige(fly,40);

  //Particule->AddFumee(fly, vertex(1.5,-30,10), 0.25, "data/texture/part/serv03.tga", 200);
  //Particule->AddFumee(fly, vertex(1.5,30,10), 0.25, "data/texture/part/serv03.tga", 200);
  //Particule->AddFumee(fly, vertex(1.5,0,-10), 0.25, "data/texture/part/serv03.tga", 200);
  Particule->AddFumee(fly, vertex(1.5,0,0), 0.5, "data/texture/part/serv03.tga", 250);

  TIMElast=TIMEcur=GETTIME;
  //fly->getShield(true,true);

  return;
}


// Fonction d'affichage de la sc�ne
void DisplayJ(void)
{  
  float BackColor[3]={MapColl->Climat->getR(),MapColl->Climat->getG(),MapColl->Climat->getB()};
  // Nettoyage du tampon ( par la couleur noire )
  glClearColor(BackColor[0],BackColor[1],BackColor[2],1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  
  // R�glages relatifs � la lumi�re
  static int LightPos[4]={0,100,0,1};
  static int MatSpec[4]={1,1,1,120};
  if(LIGHTON)
    {
      glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
      glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,120);
      glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    }
  
  // R�initialisation de la matrice de vue
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  // Configuration de la cam�ra ( position, orientation et cadrage )
  gluLookAt(fly->getPos().x-(Cos(fly->getDir()+VIEWa1)*10*VIEWz)*Cos(valAbs(fly->getInclin()+VIEWa2)), 
	    fly->getPos().y-(Sin(fly->getInclin()-7+VIEWa2)*10*VIEWz), 
	    fly->getPos().z+(Sin(fly->getDir()+VIEWa1)*10*VIEWz)*Cos(valAbs(fly->getInclin()+VIEWa2)),
	    fly->getPos().x, 
	    fly->getPos().y, 
	    fly->getPos().z,
	    0, 1, 0);

  glDepthMask(GL_TRUE);

  // Affichage du vaisseau
  fly->afficher();

  // Affichage de la map
  Aff_map();

  glDepthMask(GL_FALSE);

  Particule->Aff();
  MapColl->affLiquid();
  fly->affTrans();

  glDepthMask(GL_TRUE);
  
  // ************** Mask
  OrthoMode(0,0,SCREEN_X,SCREEN_Y);
  glColor4f(1,1,1,1);
  
  glDisable(GL_DEPTH_TEST);
  if(LIGHTON)
    glDisable(GL_LIGHTING);
  glBlendFunc(GL_DST_COLOR,GL_ZERO);


  glEnable(GL_BLEND);

  

  tmask->setTexture();
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,0);
  glTexCoord2f(0.0f, 0.5f);
  glVertex2f(0,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.5f);
  glVertex2f(SCREEN_X/2,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(SCREEN_X/2,0);


  glTexCoord2f(0.78f, 0.82f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y*0.8);
  glTexCoord2f(1.0f, 0.82f);
  glVertex2f(SCREEN_X,SCREEN_Y*0.8);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(SCREEN_X,SCREEN_Y);
  glTexCoord2f(0.78f, 1.0f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y); 
  glEnd();
  
 
  static float LiqColor[4]={getRealFromMadMap(MAPURL,'K',1),getRealFromMadMap(MAPURL,'K',2),getRealFromMadMap(MAPURL,'K',3),getRealFromMadMap(MAPURL,'K',4)};
   
  if(fly->getPos().y<(MapColl->Climat->getLiq()-(MapColl->Climat->getVarLiq()/2)))
    {
      glLoadIdentity();
      glColor4f(LiqColor[0],LiqColor[1],LiqColor[2],LiqColor[3]);
      glBegin(GL_QUADS);  
      glVertex2f(0,0);
      glVertex2f(0,SCREEN_Y);
      glVertex2f(SCREEN_X,SCREEN_Y);
      glVertex2f(SCREEN_X,0);
      glEnd();
    }
  

  glBlendFunc(GL_ONE,GL_ONE);
  tcache->setTexture();


  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,0);
  glTexCoord2f(0.0f, 0.5f);
  glVertex2f(0,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.5f);
  glVertex2f(SCREEN_X/2,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(SCREEN_X/2,0);

  glTexCoord2f(0.78f, 0.82f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y*0.8);
  glTexCoord2f(1.0f, 0.82f);
  glVertex2f(SCREEN_X,SCREEN_Y*0.8);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(SCREEN_X,SCREEN_Y);
  glTexCoord2f(0.78f, 1.0f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y); 

  glEnd();

  glColor4f(1,0,0,1);

  float fRot=((360*MapColl->TIMEactu)/MapColl->TIMEmax);
  glPushMatrix();
  glTranslatef(SCREEN_X*0.92,SCREEN_Y*0.92,0);
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
  glTranslatef(SCREEN_X*0.02,SCREEN_Y*0.21,0);
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
  glTranslatef(SCREEN_X*0.185,SCREEN_Y*0.025,0);
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

  glColor4f(1,0,0,1);

  glTranslatef(SCREEN_X*0.2,(SCREEN_Y/2)*0.363,0);
  glPushMatrix();
  glRotated(-fly->getDir()+180,0,0,1);
  glBegin(GL_QUADS);
  float fMTCS=SCREEN_X/25;

  glTexCoord2f(0.02f, 0.50f);
  glVertex2f(-fMTCS,-fMTCS);

  glTexCoord2f(0.02f, 0.70f);
  glVertex2f(-fMTCS,fMTCS);

  glTexCoord2f(0.18f, 0.70f);
  glVertex2f(fMTCS,fMTCS);

  glTexCoord2f(0.18f, 0.50f);
  glVertex2f(fMTCS,-fMTCS);

  glEnd();
  glPopMatrix();
  glTranslatef((SCREEN_X/2)*0.14,0,0);
  glPushMatrix();
  glRotated(-fly->getInclin()-90,0,0,1);
  glBegin(GL_QUADS);
  
  glTexCoord2f(0.02f, 0.77f);
  glVertex2f(-fMTCS,-fMTCS);

  glTexCoord2f(0.02f, 0.97f);
  glVertex2f(-fMTCS,fMTCS);

  glTexCoord2f(0.18f, 0.97f);
  glVertex2f(fMTCS,fMTCS);

  glTexCoord2f(0.18f, 0.77f);
  glVertex2f(fMTCS,-fMTCS);

  glEnd();
  glPopMatrix();
   
  glColor4f(1,1,1,1);

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  if(LIGHTON)
    glEnable(GL_LIGHTING);
  glEnable(GL_FOG);

  PerspectiveMode();


  // Inversion des buffers ( multi-buffering )
  glutSwapBuffers();


  return;
}

// Fonction de remise � jour
void IdleJ(void)
{
  // Actualisation du TIMER
  //printf("%d\n",GETTIMER);
  TIMElast=TIMEcur;
  TIMEcur=GETTIME;

  // G�rer l'avancement du vaisseau
  fly->avancer();

  // Controler l'�tat du vaisseau
  try
    {
      fly->Control(Shokers->Drones,Shokers->nbDrones,Crystals->Drones,Crystals->nbDrones,(Crystals->yOsc*Crystals->yOsc)-2);
    }
  // Si il rencontre un Shoker
  catch(ErrDeleteDrone Err)
    {
      fly->setDegat(50);
      printf("[*] Collision avec Shoker !\n");
      Shokers->Delete(Err.id);
    }
  // Si il collecte un Crystal
  catch(RecolCrystal Err)
    {
      printf("[*] Crystal recolte\n");
      Crystals->Delete(Err.id);
    }
  // Si il rencontre un Crystal
  catch(CollCrystal Err)
    {
      fly->setDegat(35);
      printf("[*] Collision avec un Crystal\n");
      Crystals->Delete(Err.id);
    }
  catch(...)
    {
      //
    }

  MapColl->Climat->Update();
  MapColl->TIMEupdate();

  cl_drone*p=Shokers->Drones;
  for(int i=0 ; i<Shokers->nbDrones ; i++)
    {
      p->Update();
      p=p->NEXT;
    }
  cl_drone*c=Crystals->Drones;
  for(int i=0 ; i<Crystals->nbDrones ; i++)
    {
      c->Update();
      c=c->NEXT;
    }

  Particule->Update();

  // Forcer le reDisplay
  glutPostRedisplay();

  return;
}
