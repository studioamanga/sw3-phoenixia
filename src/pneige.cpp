/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* pneige.cpp **** auteur : Vincent Tourraine ********
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/

#define NB_NEIGE_FREE 150

typedef struct NeigeEnt
{
  swVertex pos;
  bool Is;
};

// Gestionnaires des générateurs de particules
class ParticuleNeige : public ParticuleEngine
{

protected:
  NeigeEnt * Ent;
  int tabFree[NB_NEIGE_FREE];
  int nbFree;
  int nbEnt;
  int maxEnt;

  cl_wing* Center;

  float miny,intensite,v;

public:
 
  // Mise à jour du moteur de particules
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);
  // Doit on le détruire ?
  virtual bool IsDead(void);

  void CreateEnt();

  ParticuleNeige (ParticuleNeige* pBACK, cl_wing* center, float Intensite);
  virtual ~ParticuleNeige (void);

};

void ParticuleNeige::Update(void)
{
  miny=MapColl->Climat->getLiq();

  this->nbFree=0;
  //printf("%d\n",nbEnt);
  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  if(Ent[iE].pos.y<miny || Ent[iE].pos.y<(Center->getPos().y-100))
	    {
	      Ent[iE].Is=false;
	      nbEnt--;
	      continue;
	    }
	  else
	    {
	      Ent[iE].pos.y-=v*GETTIMER*0.006;
	      nE++;
	    }
	}
      // sinon on la stocke comme libre
      else
	{
	  if(this->nbFree<(NB_NEIGE_FREE-1))
	    {
	      this->tabFree[this->nbFree]=iE;
	      this->nbFree++;
	    }
	}
    }

  for(int i=0 ; i< (0.1*GETTIMER*MapColl->Climat->getPluie()) ; i++)
    CreateEnt();
}

bool ParticuleNeige::IsDead(void)
{
  return false;
}

void ParticuleNeige::Aff(void)
{
  glDisable(GL_TEXTURE_2D);
  
  glColor4f(1,1,1,1);
  
  glBegin(GL_POINTS);  

  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  glVertex3f(Ent[iE].pos.x, Ent[iE].pos.y, Ent[iE].pos.z);
	  nE++;
	}
    }
  glEnd();

  glEnable(GL_TEXTURE_2D);
}

void ParticuleNeige::CreateEnt()
{
  int iE=0;
  // Si l'id d'un emplacement libre est stocké, on le prend
  if(this->nbFree>0)
    {
      this->nbFree--;
      iE=this->tabFree[this->nbFree];
    }
  // sinon on en recherche un
  else
    for( ;; iE++)
      if(!Ent[iE].Is)
	break;

  float x=RandFloat(Center->getPos().x-100,Center->getPos().x+100), z=RandFloat(Center->getPos().z-100,Center->getPos().z+100), y=RandFloat(-100,100);
  Ent[iE].pos=swVertex(x,Center->getPos().y+100+y,z);
  Ent[iE].Is=true;

  nbEnt++;
  if(nbEnt>(maxEnt-10))
    {
      int raz=maxEnt;
      maxEnt+=500;
      Ent=(NeigeEnt*)realloc(Ent,sizeof(NeigeEnt)*maxEnt);
      for( ; raz<maxEnt ; raz++)
	Ent[raz].Is=false;
    }
}

ParticuleNeige::ParticuleNeige(ParticuleNeige* pBACK, cl_wing* center, float Intensite)
{
  NEXT=NULL;
  BACK=pBACK;

  v=2;

  Center=center;

  nbEnt=0;
  maxEnt=100;

  Ent=(NeigeEnt*)malloc(sizeof(NeigeEnt)*maxEnt);

  for(int raz=0 ; raz<maxEnt ; raz++)
    Ent[raz].Is=false;

  miny=MapColl->Climat->getPluie();

  intensite=Intensite;

  this->nbFree=0;

  for(int i=0 ; i< (Intensite*10) ; i++)
    CreateEnt();
}


ParticuleNeige::~ParticuleNeige(void)
{
  free(Ent);
}
