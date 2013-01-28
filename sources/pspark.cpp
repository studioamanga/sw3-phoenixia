/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* pspark.cpp **** auteur : Vincent Tourraine ********
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/


typedef struct SparkEnt
{
  swVertex pos;
  float aDir, aInclin;
  bool Is;
};

// Gestionnaires des générateurs de particules
class ParticuleSpark : public ParticuleEngine
{

protected:
  SparkEnt * Ent;
  int nbEnt;
  int maxEnt;

public:

  float LifeTime;
   
  // Mise à jour du moteur de particules
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);
  // Doit on le détruire ?
  virtual bool IsDead(void);

  void CreateEnt(swVertex To);

  ParticuleSpark(ParticuleSpark* pBACK, swVertex TO, float Intensite);
  virtual ~ParticuleSpark(void);

};

#define SPARKLIFE 500
void ParticuleSpark::Update(void)
{
  LifeTime-=GETTIMER;
  float v=GETTIMER*0.0002*sqrt(LifeTime);
  float abaissement=0.006*GETTIMER;

  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  float incMod=Ent[iE].aInclin;//+(M_PI/2);
	  Ent[iE].pos.x+=(cos(Ent[iE].aDir)*cos(valAbs(incMod))*v);
	  Ent[iE].pos.y+=(sin(incMod)*v);
	  Ent[iE].pos.z-=(sin(Ent[iE].aDir)*cos(valAbs(incMod))*v);

	  Ent[iE].aInclin-=abaissement;
	  if(Ent[iE].aInclin < (-M_PI))
	    Ent[iE].aInclin=(-M_PI);
	  nE++;
	}
    }
}

bool ParticuleSpark::IsDead(void)
{
  if(LifeTime<0)
    return true;
  return false;
}

#define SPARK_LONG (0.5)

void ParticuleSpark::Aff(void)
{
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glColor4f(0.8,0.8,0.8,0.2);
  
  glBegin(GL_LINES);  
      
  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  swVertex proj(Ent[iE].pos.x+(cos(Ent[iE].aDir)*cos(valAbs(Ent[iE].aInclin)*SPARK_LONG)),
			Ent[iE].pos.y+(sin(Ent[iE].aInclin)*SPARK_LONG),
			Ent[iE].pos.z-(sin(Ent[iE].aDir)*cos(valAbs(Ent[iE].aInclin))*SPARK_LONG));
	  glVertex3f(Ent[iE].pos.x, Ent[iE].pos.y, Ent[iE].pos.z);
	  glVertex3f(proj.x, proj.y, proj.z);
	  nE++;
	}
    }
  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

void ParticuleSpark::CreateEnt(swVertex To)
{
  float RanDir=RandFloat(-M_PI,M_PI), RanInc=RandFloat(-M_PI/2,M_PI/2);

  for(int iE=0 ;; iE++)
    {
      if(!Ent[iE].Is)
	{
	  Ent[iE].pos=To;
	  Ent[iE].aDir=RanDir;
	  Ent[iE].aInclin=RanInc;
	  Ent[iE].Is=true;
	  break;
	}
    }
  nbEnt++;
  if(nbEnt>(maxEnt-1))
    {
      int raz=maxEnt;
      maxEnt+=50;
      Ent=(SparkEnt*)realloc(Ent,sizeof(SparkEnt)*maxEnt);
      for( ; raz<maxEnt ; raz++)
	Ent[raz].Is=false;
    }
}

ParticuleSpark::ParticuleSpark(ParticuleSpark* pBACK, swVertex To, float Intensite)
{
  NEXT=NULL;
  BACK=pBACK;


  nbEnt=0;
  maxEnt=int(Intensite*40+3);

  Ent=(SparkEnt*)malloc(sizeof(SparkEnt)*maxEnt);

  for(int raz=0 ; raz<maxEnt ; raz++)
    Ent[raz].Is=false;

  LifeTime=SPARKLIFE;


  for(int i=0 ; i< (Intensite*10) ; i++)
    CreateEnt(To);
}


ParticuleSpark::~ParticuleSpark(void)
{
  free (Ent);
}
