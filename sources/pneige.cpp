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


typedef struct NeigeEnt
{
  vertex pos;
  NeigeEnt * NEXT;
  NeigeEnt * BACK;
};

// Gestionnaires des générateurs de particules
class ParticuleNeige : public ParticuleEngine
{

protected:
  NeigeEnt *fEnt;
  NeigeEnt *lEnt;

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
  ~ParticuleNeige (void);

};

void ParticuleNeige::Update(void)
{
  miny=MapColl->Climat->getLiq();

  NeigeEnt *pEE=fEnt;

  while(pEE!=NULL)
    {
      if(pEE->pos.y<miny||pEE->pos.y<(Center->getPos().y-100))
	{
	  NeigeEnt * pOld=pEE;
	  if(pEE==fEnt)
	    fEnt=pEE->NEXT;
	  if(pEE==lEnt)
	    lEnt=pEE->BACK;
	  
	  if(pEE->BACK!=NULL)
	    pEE->BACK->NEXT=pEE->NEXT;
	  if(pEE->NEXT!=NULL)
	    pEE->NEXT->BACK=pEE->BACK;

	  pOld=pEE->NEXT;
	  delete pEE;

	  pEE=pOld;
	  continue;
	}
      else
	{
	  pEE->pos.x;
	  pEE->pos.y-=v*GETTIMER*0.001;
	  pEE->pos.z;
      
	  pEE=pEE->NEXT;
	}
    }
  
  for(int i=0 ; i< (0.07*GETTIMER*intensite) ; i++)
    CreateEnt();
}

bool ParticuleNeige::IsDead(void)
{
  return false;
}

void ParticuleNeige::Aff(void)
{
  NeigeEnt *pEE=fEnt;

  glDisable(GL_TEXTURE_2D);
  
  glColor4f(1,1,1,1);
  
  glBegin(GL_LINES);  
      
  while(pEE!=NULL)
    {
      glVertex3f(pEE->pos.x, pEE->pos.y, pEE->pos.z);
      glVertex3f(pEE->pos.x, pEE->pos.y-0.01, pEE->pos.z);
      
      // printf("%f,%f,%f\n",pEE->pos.x, pEE->pos.y, pEE->pos.z);
      
      pEE=pEE->NEXT;
    }
  glEnd();

  glEnable(GL_TEXTURE_2D);
}

void ParticuleNeige::CreateEnt()
{
  if(lEnt!=NULL)
  {
    lEnt->NEXT=new NeigeEnt;
    lEnt->NEXT->NEXT=NULL;
    lEnt->NEXT->BACK=lEnt;
    lEnt=lEnt->NEXT;
  }
  else
  {
    lEnt=new NeigeEnt;
    lEnt->NEXT=lEnt->BACK=NULL;
    fEnt=lEnt;
  }
  
  float x=RandFloat(Center->getPos().x-100,Center->getPos().x+100), z=RandFloat(Center->getPos().z-100,Center->getPos().z+100), y=RandFloat(-100,100);
  lEnt->pos=vertex(x,Center->getPos().y+100+y,z);
}

ParticuleNeige::ParticuleNeige(ParticuleNeige* pBACK, cl_wing* center, float Intensite)
{
  NEXT=NULL;
  BACK=pBACK;

  lEnt=fEnt=NULL;
  v=2;

  Center=center;

  miny=MapColl->Climat->getPluie();

  intensite=Intensite;

  for(int i=0 ; i< (Intensite*10) ; i++)
    CreateEnt();
}


ParticuleNeige::~ParticuleNeige(void)
{
  NeigeEnt *pEE=fEnt;
  NeigeEnt *pEEd=NULL;
  while(pEE!=NULL)
    {
      pEEd=pEE;
      pEE=pEE->NEXT;
      delete pEEd;
    }
}
