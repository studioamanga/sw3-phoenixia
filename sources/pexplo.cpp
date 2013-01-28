/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* pexplo.cpp **** auteur : Vincent Tourraine ********
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/


typedef struct ExplosionEnt
{
  swVertex pos;
  swVertex dir;
  char speed;
  bool Is;
};

// Gestionnaires des générateurs de particules
class ParticuleExplosion : public ParticuleEngine
{

protected:
  ExplosionEnt * Ent;
  int nbEnt;
  int maxEnt;

  cl_texture *Text;

  float size;
  bool black;

public:

  float LifeTime;
   
  // Mise à jour du moteur de particules
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);
  // Doit on le détruire ?
  virtual bool IsDead(void);

  void CreateEnt(swVertex To);

  ParticuleExplosion (ParticuleExplosion* pBACK, swVertex TO, float Intensite, float Size, bool black);
  virtual ~ParticuleExplosion (void);

};

#define EXPLOLIFE 1500
void ParticuleExplosion::Update(void)
{
  LifeTime-=GETTIMER;
  float t=LifeTime;
  if(black==true && t>(EXPLOLIFE/2))
    return;
  float v=GETTIMER*0.4*sqrt(t);
  if(black)
    {
      v*=1.7;
    }

  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  float vS=float(Ent[iE].speed)/5000;
	  Ent[iE].pos.x+=Ent[iE].dir.x*v*vS;
	  Ent[iE].pos.y+=Ent[iE].dir.y*v*vS;
	  Ent[iE].pos.z+=Ent[iE].dir.z*v*vS;
	  nE++;
	}
    }
}

bool ParticuleExplosion::IsDead(void)
{
  if(LifeTime<0)
    return true;
  return false;
}

void ParticuleExplosion::Aff(void)
{
  if(black==true && LifeTime>(EXPLOLIFE/2))
    return;

  glColor4f(1,1,1,0.5);
  Text->setTexture();

  glEnable(GL_BLEND);
  if(black)
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  else
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  //  glDisable (GL_DEPTH_TEST);

  if(ISARB)
    {
      glEnable (GL_POINT_SPRITE_ARB);
      glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
      glPointSize (100);
      glBegin (GL_POINTS);
    }

  else
    glBegin(GL_QUADS);  
      
  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    if(Ent[iE].Is)
      {
	affPoint(Ent[iE].pos.x, Ent[iE].pos.y, Ent[iE].pos.z, size);
	nE++;
      }
  glEnd();

  glDisable (GL_POINT_SPRITE_ARB);
  glPointSize (1);
  glDisable(GL_BLEND);
  glEnable (GL_DEPTH_TEST);
}

void ParticuleExplosion::CreateEnt(swVertex To)
{
  float RanDir=RandFloat(-M_PI,M_PI), RanInc=RandFloat(-M_PI,M_PI);

  for(int iE=0 ;; iE++)
    {
      if(!Ent[iE].Is)
	{
	  Ent[iE].pos=To;
	  Ent[iE].dir=swVertex(cos(RanDir),sin(RanDir),cos(RanInc));
	  Ent[iE].speed=RandInt(2,10);
	  Ent[iE].Is=true;
	  break;
	}
    }
  nbEnt++;
  if(nbEnt>(maxEnt-1))
    {
      int raz=maxEnt;
      maxEnt+=50;
      Ent=(ExplosionEnt*)realloc(Ent,sizeof(ExplosionEnt)*maxEnt);
      for( ; raz<maxEnt ; raz++)
	Ent[raz].Is=false;
    }
}

ParticuleExplosion::ParticuleExplosion(ParticuleExplosion* pBACK, swVertex To, float Intensite, float Size, bool black=false)
{
  NEXT=NULL;
  BACK=pBACK;

  size=Size;
  this->black=black;

  nbEnt=0;
  maxEnt=int(Intensite*40+3);

  Ent=(ExplosionEnt*)malloc(sizeof(ExplosionEnt)*maxEnt);

  for(int raz=0 ; raz<maxEnt ; raz++)
    Ent[raz].Is=false;

  LifeTime=EXPLOLIFE;

  if(black)
    Text=new cl_texture("./data/texture/part/fumee.tga",LOADTYPE_TGA32);
  else
    Text=new cl_texture("./data/texture/part/explo.tga",LOADTYPE_TGA32);
    

  for(int i=0 ; i< (Intensite*40) ; i++)
    CreateEnt(To);
}


ParticuleExplosion::~ParticuleExplosion(void)
{
  free (Ent);
  delete Text;
}
