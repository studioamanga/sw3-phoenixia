/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** part.cpp **** auteur : Vincent Tourraine ***********
**                                                         **
** Classe du manager de moteur de particule.               **
**                                                         **
*************************************************************/

#include "pengine.cpp"



// Gestionnaires des générateurs de particules
class ParticuleManager
{

private:
  ParticuleEngine* fEngine;
  ParticuleEngine* lEngine;
public:
   
  // Mise à jour du gestionnaire de générateurs de particules.
  void Update (void);
  // Affichage des particules des moteur
  void Aff(void);

  // Ajouter une explosion
  bool AddExplosion(vertex To, float Intensite);
  // Ajouter une fumée
  bool AddFumee(cl_wing* theFly, vertex From, float Size, char* Texture, float LifeTime, bool black=false);
  // Ajouter une pluie
  bool AddPluie(cl_wing* center, float Intensite);
  // Ajouter de la neige
  bool AddNeige(cl_wing* center, float Intensite);

  // Constructeur & Destructeur
  ParticuleManager (void);
  ~ParticuleManager (void);

};

ParticuleManager* Particule=NULL;

void ParticuleManager::Update(void)
{
  ParticuleEngine *pPE=fEngine;

  while(pPE!=NULL)
    {
      if(pPE->IsDead())
	{
	  ParticuleEngine * pOld=pPE;
	  if(pPE==fEngine)
	    fEngine=pPE->NEXT;
	  if(pPE==lEngine)
	    lEngine=pPE->BACK;
	  
	  if(pPE->BACK!=NULL)
	    pPE->BACK->NEXT=pPE->NEXT;
	  if(pPE->NEXT!=NULL)
	    pPE->NEXT->BACK=pPE->BACK;

	  pOld=pPE->NEXT;
	  delete pPE;

	  pPE=pOld;
	  continue;
	}
      else
	{
	  pPE->Update();
	  pPE=pPE->NEXT;
	}
    }
}

void ParticuleManager::Aff(void)
{
  if(LIGHTON)
    glDisable(GL_LIGHTING);
  ParticuleEngine *pPE=fEngine;

  while(pPE!=NULL)
    {
      pPE->Aff();
      pPE=pPE->NEXT;
    }
  if(LIGHTON)
    glEnable(GL_LIGHTING);
}


bool ParticuleManager::AddExplosion(vertex To, float Intensite)
{
  if(lEngine!=NULL)
  {
    lEngine->NEXT=new ParticuleExplosion(NULL,To,Intensite,0.5);
    lEngine->NEXT->BACK=lEngine;
    lEngine=lEngine->NEXT;
    lEngine->NEXT=new ParticuleExplosion(NULL,To,Intensite*1.5,0.8, true);
    lEngine->NEXT->BACK=lEngine;
    lEngine=lEngine->NEXT;
  }
  else
  {
    lEngine=new ParticuleExplosion(NULL,To,Intensite,0.5);
    fEngine=lEngine;
    lEngine->NEXT=new ParticuleExplosion(NULL,To,Intensite*1.5,0.8, true);
    lEngine->NEXT->BACK=lEngine;
    lEngine=lEngine->NEXT;
  }

  return true;
}


bool ParticuleManager::AddFumee(cl_wing* theFly, vertex From, float Size, char * Texture, float LifeTime, bool black)
{
  if(lEngine!=NULL)
  {
    lEngine->NEXT=new ParticuleFumee(NULL,theFly,From,Size,Texture,LifeTime, black);
    lEngine->NEXT->BACK=lEngine;
    lEngine=lEngine->NEXT;
  }
  else
  {
    lEngine=new ParticuleFumee(NULL,theFly,From,Size,Texture,LifeTime, black);
    fEngine=lEngine;
  }

  return true;
}



bool ParticuleManager::AddNeige(cl_wing* center,float Intensite)
{
  if(lEngine!=NULL)
  {
    lEngine->NEXT=new ParticuleNeige(NULL,center,Intensite);
    lEngine->NEXT->BACK=lEngine;
    lEngine=lEngine->NEXT;
  }
  else
  {
    lEngine=new ParticuleNeige(NULL,center,Intensite);
    fEngine=lEngine;
  }

  return true;
}

bool ParticuleManager::AddPluie(cl_wing* center,float Intensite)
{
  if(lEngine!=NULL)
  {
    lEngine->NEXT=new ParticulePluie(NULL,center,Intensite);
    lEngine->NEXT->BACK=lEngine;
    lEngine=lEngine->NEXT;
  }
  else
  {
    lEngine=new ParticulePluie(NULL,center,Intensite);
    fEngine=lEngine;
  }

  return true;
}

ParticuleManager::ParticuleManager(void)
{
  fEngine=NULL;
  lEngine=NULL;
}

ParticuleManager::~ParticuleManager(void)
{
  if(fEngine!=NULL)
    delete fEngine;
}
