/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
*** particule_engine.cpp **** auteur : Vincent Tourraine ****
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/


// Gestionnaires des générateurs de particules
class ParticuleEngine
{

protected:
  
public:
  bool ForceDead;
  ParticuleEngine* NEXT;
  ParticuleEngine* BACK;

  // Mise à jour du moteur de particules.
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);

  // Doit ont le supprimer ?
  virtual bool IsDead(void);

  ParticuleEngine (void);
  virtual ~ParticuleEngine (void);

};

#include "pexplo.cpp"
#include "ppluie.cpp"
#include "pspark.cpp"
#include "pneige.cpp"
#include "pfumee.cpp"

void ParticuleEngine::Update(void)
{
}

bool ParticuleEngine::IsDead(void)
{
  return false;
}


void ParticuleEngine::Aff(void)
{
}


ParticuleEngine::ParticuleEngine(void)
{
  ForceDead=false;
}

ParticuleEngine::~ParticuleEngine(void)
{
  if(NEXT!=NULL&&ForceDead==true)
    delete NEXT;
}
