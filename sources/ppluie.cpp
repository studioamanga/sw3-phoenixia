/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* ppluie.cpp **** auteur : Vincent Tourraine ********
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/

#define NB_PLUIE_FREE 100

typedef struct PluieEnt
{
  swVertex pos;
  bool Is;
};

// Gestionnaires des générateurs de particules
class ParticulePluie : public ParticuleEngine
{
protected:
  PluieEnt * Ent;
  int tabFree[NB_PLUIE_FREE];
  int nbFree;
  int nbEnt;
  int maxEnt;

  float miny,v;

  cl_wing * Center;

public:
 
  // Mise à jour du moteur de particules
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);
  // Doit on le détruire ?
  virtual bool IsDead(void);

  void CreateEnt();

  ParticulePluie (ParticulePluie* pBACK, cl_wing* center, float Intensite);
  virtual ~ParticulePluie (void);

};

void ParticulePluie::Update(void)
{
  miny=MapColl->Climat->getLiq();

  this->nbFree=0;
  //printf("%d\n",nbEnt);

  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      // Si la particule existe on l'update
      if(Ent[iE].Is)
	{
	  if(Ent[iE].pos.y<miny||Ent[iE].pos.y<(Center->getPos().y-100))
	    {
	      Ent[iE].Is=false;
	      nbEnt--;
	      continue;
	    }
	  else
	    {
	      Ent[iE].pos.y-=v*GETTIMER*0.02;
	      nE++;
	    }
	}
      // sinon on la stocke comme libre
      else
	{
	  if(this->nbFree<(NB_PLUIE_FREE-1))
	    {
	      this->tabFree[this->nbFree]=iE;
	      this->nbFree++;
	    }
	}
    }
  for(int i=0 ; i< int(0.1*GETTIMER*MapColl->Climat->getPluie()) ; i++)
    CreateEnt();
}

bool ParticulePluie::IsDead(void)
{
  return false;
}

void ParticulePluie::Aff(void)
{
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glColor4f(0.3,0.3,1,0.2);
  
  glBegin(GL_LINES);  
      
  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  glVertex3f(Ent[iE].pos.x, Ent[iE].pos.y, Ent[iE].pos.z);
	  glVertex3f(Ent[iE].pos.x, Ent[iE].pos.y-8, Ent[iE].pos.z);
	  nE++;
	}
    }
  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

void ParticulePluie::CreateEnt()
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
      Ent=(PluieEnt*)realloc(Ent,sizeof(PluieEnt)*maxEnt);
      for( ; raz<maxEnt ; raz++)
	Ent[raz].Is=false;
    }
}

ParticulePluie::ParticulePluie(ParticulePluie* pBACK, cl_wing* center, float Intensite)
{
  NEXT=NULL;
  BACK=pBACK;

  v=40;

  nbEnt=0;
  maxEnt=100;

  Ent=(PluieEnt*)malloc(sizeof(PluieEnt)*maxEnt);

  for(int raz=0 ; raz<maxEnt ; raz++)
    Ent[raz].Is=false;

  Center=center;

  this->nbFree=0;

  for(int i=0 ; i< (Intensite*10) ; i++)
    CreateEnt();
}


ParticulePluie::~ParticulePluie(void)
{
  free(Ent);
}
