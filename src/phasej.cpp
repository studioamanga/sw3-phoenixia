/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** phasej.cpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/


bool gamePause=false;
bool gamePauseQuit=false;

// Gestion d'initialisation globale
void InitJ(void)
{
  if(Particule)
    {
      delete Particule;
      Particule= new ParticuleManager;
      logOut("  [OK] Moteur à Particule initialisé\n");
    }
  // Chargement des textures à partir des fichiers
  Map=new cl_model(MAPURL);

  // Allocation mémoire de la classe 'wing' du vaisseau principal
  fly=new cl_wing(WINGURL);

  // Allocation mémoire de la classe 'bsp' des collisions de la map
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
      swVertex *tPos=new swVertex[nbDrone];
      for(int i=0 ; i<nbDrone ; i++)
	{
	  tPos[i]=getVertexFromMadMap(MAPURL,'S',i+1);
	}
      Shokers= new cl_Serie('S',nbDrone,tPos);
      delete tPos;

      // Initialisation des drones Crystal
      nbDrone=getNbFromMadMap(MAPURL,'D');
      tPos=new swVertex[nbDrone];
      for(int i=0 ; i<nbDrone ; i++)
	{
	  tPos[i]=getVertexFromMadMap(MAPURL,'D',i+1);
	}
      Crystals= new cl_Serie('C',nbDrone,tPos);
      delete tPos;
    }
  catch(...)
    {
      logOut(" [!]Erreur dans l'initialisation des Drones\n");
      exit(0);
    }
	

  float BackColor[4]={MapColl->Climat->getR(),MapColl->Climat->getG(),MapColl->Climat->getB(),1.0};

  // Paramètrage du brouillard
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

  //Particule->AddFumee(fly, swVertex(1.5,0,0), 0.5, "data/texture/part/serv03.tga", 2);//250

  clSoundMan * Sound=clSoundMan::Create();
  /*signed char rCD=FSOUND_CD_Play(0,0);
  if(rCD==FMOD_ERR_CDDEVICE || FSOUND_CD_GetNumTracks(0)==0)
    Sound->JouerStream (MUSIC_THEME, CANAL_MUSIQUE, true);
  else
    {
      Sound->CtrlMusicActive(true);
      FSOUND_CD_SetPlayMode(0, FSOUND_CD_PLAYCONTINUOUS);
      printf("Lecture du CD, %d pistes\n", FSOUND_CD_GetNumTracks(0));
    }
  */
  Sound->JouerStream (SOUND_WING, CANAL_JOUEUR, true);

  TIMElast=TIMEcur=GETTIME;
   
  switch(cursMod)
    {
    case MOD_DEFI :
      menuSetComment(MOD_DEFI_MISSIONS[cursDefiMission-1].Comment,5000);
      break;
    case MOD_EXPLORATION :
    default :
      char * inf=getStrFromMadMap(MAPURL,'F',1);
      menuSetComment(inf,5000);
      delete inf;
    }

  return;
}


// Fonction de remise à jour
void IdleJ(void)
{
  TIMElast=TIMEcur;
  TIMEcur=GETTIME;
  MapColl->TIMEupdate();    

  if(MapColl->isFinish())
    {
      menuSetComment("Le temps imparti est ecoule. Votre mission s'arrete ici et maintenant.",1000000);
      gamePause=false;
      wideScr(true);
      glutPostRedisplay();
      return;
    }

  if(!gamePause)
    {
      wideScr(true);

      // Gérer l'avancement du vaisseau
      fly->avancer();

      // Controler l'état du vaisseau
      try
	{
	  fly->Control(Shokers->Drones,Shokers->nbDrones,Crystals->Drones,Crystals->nbDrones,(Crystals->yOsc*Crystals->yOsc)-2);
	}
      // Si il rencontre un Shoker
      catch(ErrDeleteDrone Err)
	{
	  fly->setDegat(Shokers->effet);
	  menuSetComment("[!] Collision avec un Shoker [!]", 3000);
	  Shokers->Delete(Err.id);
	}
      // Si il collecte un Crystal
      catch(RecolCrystal Err)
	{
	  menuSetComment("[*] Crystal recolte [*]", 3000);
	  Crystals->Delete(Err.id);
	}
      // Si il rencontre un Crystal
      catch(CollCrystal Err)
	{
	  fly->setDegat(Crystals->effet);
	  menuSetComment("[!] Collision avec un Crystal [!]", 3000);
	  Crystals->Delete(Err.id);
	}
      catch(...)
	{
	  //
	}

      MapColl->Climat->Update();

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

    }
  // Forcer le reDisplay
  glutPostRedisplay();

  return;
}

void DelJ(void)
{
  if(fly)
    {
      delete fly;
      fly=NULL;
    }
  if(Map)
    {
      delete Map;
      Map=NULL;
    }
  if(MapColl)
    {
      delete MapColl;
      MapColl=NULL;
    }
  if(Shokers)
    {
      delete Shokers;
      Shokers=NULL;
    }
  if(Crystals)
    {
      delete Crystals;
      Crystals=NULL;
    }
  if(tmask)
    {
      delete tmask;
      tmask=NULL;
    }
  if(tcache)
    {
      delete tcache;
      tcache=NULL;
    }
  if(tLiquid)
    {
      delete tLiquid;
      tLiquid=NULL;
    }
}
