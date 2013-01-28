/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
** particule_explosion.cpp **** auteur : Vincent Tourraine **
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/


typedef struct ExplosionEnt
{
  vertex pos;
  vertex dir;
  char speed;
  ExplosionEnt * NEXT;
  ExplosionEnt * BACK;
};

// Gestionnaires des générateurs de particules
class ParticuleExplosion : public ParticuleEngine
{

protected:
  ExplosionEnt *fEnt;
  ExplosionEnt *lEnt;

  cl_texture *Text;

  float size;
  bool black;

public:

  CTimer LifeTime;
   
  // Mise à jour du moteur de particules
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);
  // Doit on le détruire ?
  virtual bool IsDead(void);

  void CreateEnt(vertex To);

  ParticuleExplosion (ParticuleExplosion* pBACK, vertex TO, float Intensite, float Size, bool black);
  ~ParticuleExplosion (void);

};

#define EXPLOLIFE 1500
void ParticuleExplosion::Update(void)
{
  float t=LifeTime.GetTime();
  if(black==true && t<(EXPLOLIFE/2))
    return;
  t=t*t;
  ExplosionEnt *pEE=fEnt;
  float v=GETTIMER*0.004*(EXPLOLIFE-t)/EXPLOLIFE;
  if(black)
    {
      v*=1.7;
    }
  while(pEE!=NULL)
    {
      float vS=float(pEE->speed)/5000;
      pEE->pos.x+=pEE->dir.x*v*vS;
      pEE->pos.y+=pEE->dir.y*v*vS;
      pEE->pos.z+=pEE->dir.z*v*vS;
      
      pEE=pEE->NEXT;
    }
}

bool ParticuleExplosion::IsDead(void)
{
  if(LifeTime.GetTime()>EXPLOLIFE)
    return true;
  return false;
}

void ParticuleExplosion::Aff(void)
{
  ExplosionEnt *pEE=fEnt;
 
  float t=LifeTime.GetTime();
  if(black==true && t<(EXPLOLIFE/2))
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
      
  while(pEE!=NULL)
    {
      if(ISARB)
	glVertex3f (pEE->pos.x-size, pEE->pos.y, pEE->pos.z);
      else
	{
	  glTexCoord2f(0.0,0.0 );
	  glVertex3f(pEE->pos.x-size, pEE->pos.y-size, pEE->pos.z);
	  glTexCoord2f(0.0,1.0 );
	  glVertex3f(pEE->pos.x-size, pEE->pos.y+size, pEE->pos.z);
	  glTexCoord2f(1.0,1.0 );
	  glVertex3f(pEE->pos.x+size, pEE->pos.y+size, pEE->pos.z);
	  glTexCoord2f(1.0,0.0 );
	  glVertex3f(pEE->pos.x+size, pEE->pos.y-size, pEE->pos.z);

	  glVertex3f(pEE->pos.x-size, pEE->pos.y, pEE->pos.z-size);
	  glTexCoord2f(1.0,1.0 );
	  glVertex3f(pEE->pos.x-size, pEE->pos.y, pEE->pos.z+size);
	  glTexCoord2f(0.0,1.0 );
	  glVertex3f(pEE->pos.x+size, pEE->pos.y, pEE->pos.z+size);
	  glTexCoord2f(0.0,0.0 );
	  glVertex3f(pEE->pos.x+size, pEE->pos.y, pEE->pos.z-size);

	  glVertex3f(pEE->pos.x, pEE->pos.y-size, pEE->pos.z-size);
	  glTexCoord2f(0.0,1.0 );
	  glVertex3f(pEE->pos.x, pEE->pos.y+size, pEE->pos.z-size);
	  glTexCoord2f(1.0,1.0 );
	  glVertex3f(pEE->pos.x, pEE->pos.y+size, pEE->pos.z+size);
	  glTexCoord2f(1.0,0.0 );
	  glVertex3f(pEE->pos.x, pEE->pos.y-size, pEE->pos.z+size);
	}
      // printf("%f,%f,%f\n",pEE->pos.x, pEE->pos.y, pEE->pos.z);
      
      pEE=pEE->NEXT;
    }
  glEnd();

  glDisable (GL_POINT_SPRITE_ARB);
  glDisable(GL_BLEND);
  glEnable (GL_DEPTH_TEST);
}

void ParticuleExplosion::CreateEnt(vertex To)
{
  if(lEnt!=NULL)
  {
    lEnt->NEXT=new ExplosionEnt;
    lEnt->NEXT->NEXT=NULL;
    lEnt->NEXT->BACK=lEnt;
    lEnt=lEnt->NEXT;
  }
  else
  {
    lEnt=new ExplosionEnt;
    lEnt->NEXT=lEnt->BACK=NULL;
    fEnt=lEnt;
  }
  
  float RanDir=RandFloat(-M_PI,M_PI), RanInc=RandFloat(-M_PI,M_PI);
  int RanI=RandInt(2,10);
  lEnt->speed=RanI;
  lEnt->dir=vertex(cos(RanDir),sin(RanDir),cos(RanInc));
  lEnt->pos=To;
}

ParticuleExplosion::ParticuleExplosion(ParticuleExplosion* pBACK, vertex To, float Intensite, float Size, bool black=false)
{
  NEXT=NULL;
  BACK=pBACK;

  lEnt=fEnt=NULL;

  size=Size;
  this->black=black;

  LifeTime.Init();

  if(black)
    Text=new cl_texture("./data/texture/part/fumee.tga",LOADTYPE_TGA32);
  else
    Text=new cl_texture("./data/texture/part/explo.tga",LOADTYPE_TGA32);
    

  for(int i=0 ; i< (Intensite*40) ; i++)
    CreateEnt(To);
}


ParticuleExplosion::~ParticuleExplosion(void)
{
  ExplosionEnt *pEE=fEnt;
  ExplosionEnt *pEEd=NULL;
  while(pEE!=NULL)
    {
      pEEd=pEE;
      pEE=pEE->NEXT;
      delete pEEd;
    }
  delete Text;
}
