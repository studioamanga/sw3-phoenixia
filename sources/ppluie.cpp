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


typedef struct PluieEnt
{
  vertex pos;
  PluieEnt * NEXT;
  PluieEnt * BACK;
};

// Gestionnaires des générateurs de particules
class ParticulePluie : public ParticuleEngine
{

protected:
  PluieEnt *fEnt;
  PluieEnt *lEnt;

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
  ~ParticulePluie (void);

};

void ParticulePluie::Update(void)
{
  miny=MapColl->Climat->getLiq();

  PluieEnt *pEE=fEnt;

  while(pEE!=NULL)
    {
      if(pEE->pos.y<miny||pEE->pos.y<(Center->getPos().y-100))
	{
	  PluieEnt * pOld=pEE;
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
	  pEE->pos.y-=v*GETTIMER*0.02;
	  pEE->pos.z;
      
	  pEE=pEE->NEXT;
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
  PluieEnt *pEE=fEnt;

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glColor4f(0.3,0.3,1,0.2);
  
  glBegin(GL_LINES);  
      
  while(pEE!=NULL)
    {
      glVertex3f(pEE->pos.x, pEE->pos.y, pEE->pos.z);
      glVertex3f(pEE->pos.x, pEE->pos.y-8, pEE->pos.z);
      
      // printf("%f,%f,%f\n",pEE->pos.x, pEE->pos.y, pEE->pos.z);
      
      pEE=pEE->NEXT;
    }
  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

void ParticulePluie::CreateEnt()
{
  if(lEnt!=NULL)
  {
    lEnt->NEXT=new PluieEnt;
    lEnt->NEXT->NEXT=NULL;
    lEnt->NEXT->BACK=lEnt;
    lEnt=lEnt->NEXT;
  }
  else
  {
    lEnt=new PluieEnt;
    lEnt->NEXT=lEnt->BACK=NULL;
    fEnt=lEnt;
  }
  
  float x=RandFloat(Center->getPos().x-100,Center->getPos().x+100), z=RandFloat(Center->getPos().z-100,Center->getPos().z+100), y=RandFloat(-100,100);
  lEnt->pos=vertex(x,Center->getPos().y+100+y,z);
}

ParticulePluie::ParticulePluie(ParticulePluie* pBACK, cl_wing* center, float Intensite)
{
  NEXT=NULL;
  BACK=pBACK;

  lEnt=fEnt=NULL;
  v=40;

  Center=center;
  
  for(int i=0 ; i< (Intensite*10) ; i++)
    CreateEnt();
}


ParticulePluie::~ParticulePluie(void)
{
  PluieEnt *pEE=fEnt;
  PluieEnt *pEEd=NULL;
  while(pEE!=NULL)
    {
      pEEd=pEE;
      pEE=pEE->NEXT;
      delete pEEd;
    }
}
