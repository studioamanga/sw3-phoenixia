/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** pfumee.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Classe du moteur de particule.                          **
**                                                         **
*************************************************************/


typedef struct FumeeEnt
{
  swVertex pos;
  swVertex dir;
  float lifetimer;
  int speed;
  bool Is;
};

// Gestionnaires des générateurs de particules
class ParticuleFumee : public ParticuleEngine
{

protected:
  FumeeEnt * Ent;
  int nbEnt;
  int maxEnt;

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

  ParticuleFumee (ParticuleFumee* pBACK, cl_wing* theFly, swVertex From, float Size, char*Texture, float LifeTime, bool black);
  virtual ~ParticuleFumee (void);

};

//float FFF=0.00015;

void ParticuleFumee::Update(void)
{
  float v=GETTIMER*FACT_DEPL*source->getV();

  for(int iE=0, nE=0 ; nE<nbEnt ; iE++)
    {
      if(Ent[iE].Is)
	{
	  Ent[iE].lifetimer-=GETTIMER;
	  if(Ent[iE].lifetimer<0)
	    {
	      Ent[iE].Is=false;
	      nbEnt--;
	      continue;
	    }
	  else
	    {
	      Ent[iE].pos.x+=Ent[iE].dir.x*v*Ent[iE].speed;
	      Ent[iE].pos.y+=Ent[iE].dir.y*v*Ent[iE].speed;
	      Ent[iE].pos.z+=Ent[iE].dir.z*v*Ent[iE].speed;
	      nE++;
	    }
	}
    }

  if(black || source->getV()>=0)
    for(int i=0 ; i<int(0.8*GETTIMER) ; i++) // 0.8
      CreateEnt();
}

bool ParticuleFumee::IsDead(void)
{
  if(Disp==DISP_MENU)
    return true;
  return false;
}


void ParticuleFumee::Aff(void)
{
  //glEnable(GL_BLEND);
  if(black)
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  else
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  //glDisable(GL_DEPTH_TEST);

  Text->setTexture();

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
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
}


void ParticuleFumee::CreateEnt(void)
{
  int rAd=RandInt(10,-10);
  int rAi=RandInt(10,-10);
  
  float posX, posY, posZ;

  posX=-(Cos(source->getDirMod()+ from.aDir)*from.rayon)*Cos(valAbs(source->getInclinMod()+from.aInclin));
  posY=-(Sin(source->getInclinMod()+from.aInclin)*from.rayon);
  posZ=(Sin(source->getDirMod()+ from.aDir)*from.rayon)*Cos(valAbs(source->getInclinMod()+from.aInclin));


  posX+=source->getPos().x;
  posZ+=source->getPos().z;
  posY+=source->getPos().y;

  for(int iE=0 ;; iE++)
    {
      if(!Ent[iE].Is)
	{
	  Ent[iE].pos=swVertex(posX,posY,posZ);
	  Ent[iE].dir=swVertex(-(Cos(source->getDirMod()+rAd))*Sin(valAbs(source->getInclinMod()+rAi)),
			       -(Sin(source->getInclinMod()+rAi)),
			       +(Sin(source->getDirMod()+rAd))*Cos(valAbs(source->getInclinMod()+rAi)));
	  Ent[iE].lifetimer=RandFloat(0,lifetime);
	  Ent[iE].speed=RandInt(0,2);
	  Ent[iE].Is=true;
	  break;
	}
    }
  nbEnt++;
  if(nbEnt>(maxEnt-10))
    {
      int raz=maxEnt;
      maxEnt+=30;
      Ent=(FumeeEnt*)realloc(Ent,sizeof(FumeeEnt)*maxEnt);
      for( ; raz<maxEnt ; raz++)
	Ent[raz].Is=false;
    }
}

ParticuleFumee::ParticuleFumee(ParticuleFumee* pBACK, cl_wing* theFly, swVertex From, float Size, char*Texture, float LifeTime, bool black)
{
  NEXT=NULL;
  BACK=pBACK;

  this->black=black;

  nbEnt=0;
  maxEnt=50;

  Ent=(FumeeEnt*)malloc(sizeof(FumeeEnt)*maxEnt);

  for(int raz=0 ; raz<maxEnt ; raz++)
    Ent[raz].Is=false;

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
  free(Ent);
  delete Text;
}
