/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
**** particule_fumee.cpp **** auteur : Vincent Tourraine ****
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/


typedef struct FumeeEnt
{
  vertex pos;
  vertex dir;
  float lifetimer;
  int speed;
  FumeeEnt * NEXT;
  FumeeEnt * BACK;
};

// Gestionnaires des générateurs de particules
class ParticuleFumee : public ParticuleEngine
{

protected:
  FumeeEnt *fEnt;
  FumeeEnt *lEnt;

  cl_texture *Text;

  float size;
  cl_wing * source;
  vertexPol from;
  float lifetime;
  bool black;

public:
   
  // Mise à jour du moteur de particules
  virtual void Update (void);
  // Affichage des particules du moteur
  virtual void Aff(void);
  // Doit on le détruire ?
  virtual bool IsDead(void);

  void CreateEnt(void);

  ParticuleFumee (ParticuleFumee* pBACK, cl_wing* theFly, vertex From, float Size, char*Texture, float LifeTime, bool black);
  ~ParticuleFumee (void);

};

float FFF=0.00015;

void ParticuleFumee::Update(void)
{
  FumeeEnt *pEE=fEnt;
  float v=GETTIMER*FACT_DEPL*source->getV();
  while(pEE!=NULL)
    {
      pEE->lifetimer-=GETTIMER;
      if(pEE->lifetimer<0)
	{
	  FumeeEnt * pOld=pEE;
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
	  pEE->pos.x+=pEE->dir.x*v*pEE->speed;
	  pEE->pos.y+=pEE->dir.y*v*pEE->speed;
	  pEE->pos.z+=pEE->dir.z*v*pEE->speed;

	  pEE=pEE->NEXT;
	}
    }

  if(source->getV()>=0)
    for(int i=0 ; i<int(0.8*GETTIMER) ; i++) // 0.8
      CreateEnt();
}

bool ParticuleFumee::IsDead(void)
{
  return false;
}


void ParticuleFumee::Aff(void)
{
  FumeeEnt *pEE=fEnt;

  glEnable(GL_BLEND);
  if(black)
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  else
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  //glDisable(GL_DEPTH_TEST);

  Text->setTexture();

  glBegin(GL_QUADS);  
      
  while(pEE!=NULL)
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

      //printf("%f,%f,%f\n",pEE->pos.x, pEE->pos.y, pEE->pos.z);
      
      pEE=pEE->NEXT;
    }
  glEnd();

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
}


void ParticuleFumee::CreateEnt(void)
{
  if(lEnt!=NULL)
  {
    lEnt->NEXT=new FumeeEnt;
    lEnt->NEXT->NEXT=NULL;
    lEnt->NEXT->BACK=lEnt;
    lEnt=lEnt->NEXT;
  }
  else
  {
    lEnt=new FumeeEnt;
    lEnt->NEXT=lEnt->BACK=NULL;
    fEnt=lEnt;
  }
  
  int rAd=RandInt(10,-10);
  int rAi=RandInt(10,-10);

  lEnt->dir=vertex(-(Cos(source->getDirMod()+rAd))*Sin(valAbs(source->getInclinMod()+rAi)),
		   -(Sin(source->getInclinMod()+rAi)),
		   +(Sin(source->getDirMod()+rAd))*Cos(valAbs(source->getInclinMod()+rAi)));

  
  float posX, posY, posZ;

  posX=-(Cos(source->getDirMod()+ from.aDir)*from.rayon)*Cos(valAbs(source->getInclinMod()+from.aInclin));
  posY=-(Sin(source->getInclinMod()+from.aInclin)*from.rayon);
  posZ=(Sin(source->getDirMod()+ from.aDir)*from.rayon)*Cos(valAbs(source->getInclinMod()+from.aInclin));

  // rotation en Z
  //posY=-Sin(source->getInclinMod()+from.aInclin)*from.rayon;
  //posX=-Cos(source->getInclinMod()+from.aInclin)*from.rayon;
  //posZ=Sin( from.aDir)*from.rayon;
  
  // rotation en Y
  //float newrayon=sqrt(posX*posX + posZ*posZ);
  //posX=-Cos(source->getDirMod())*newrayon;

  posX+=source->getPos().x;
  posZ+=source->getPos().z;
  posY+=source->getPos().y;

  lEnt->pos=vertex(posX,posY,posZ);

  lEnt->lifetimer=RandFloat(0,lifetime);
  lEnt->speed=RandInt(0,2);
}

ParticuleFumee::ParticuleFumee(ParticuleFumee* pBACK, cl_wing* theFly, vertex From, float Size, char*Texture, float LifeTime, bool black)
{
  NEXT=NULL;
  BACK=pBACK;

  lEnt=fEnt=NULL;
  this->black=black;

  source=theFly;

  from.rayon=From.x;
  from.aDir=From.y;
  from.aInclin=From.z;

  size=Size;
  lifetime=LifeTime;

  Text=new cl_texture(Texture,LOADTYPE_TGA32);

  for(int i=0 ; i<15 ; i++)
    CreateEnt();
}


ParticuleFumee::~ParticuleFumee(void)
{
  FumeeEnt *pEE=fEnt;
  FumeeEnt *pEEd=NULL;
  while(pEE!=NULL)
    {
      pEEd=pEE;
      pEE=pEE->NEXT;
      delete pEEd;
    }
  delete Text;
}
