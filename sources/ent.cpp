/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********** ent.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Classes des entités et de ses dérivés : vaisseaux...    **
**                                                         **
*************************************************************/


#define SPHERECOLOR_BLACK 'N'
#define SPHERECOLOR_RED 'R'

// Classe d'une entité
class cl_ent
{

	protected :
		// Position
		vertex *pos;
	public :
		// Fonction d'affichage
		virtual void afficher(void);
		// Connaître la position de l'entité
		vertex getPos(void);
		// Constructeur et destructeur
		cl_ent(void);
		~cl_ent(void);
};

// Retourne sous la forme d'un vertex la position de l'entité
vertex cl_ent::getPos(void)
{
	return *(this->pos);
}

// Structure pour gérer les touches maintenues appuyées
struct cl_input
{
	// Booléennes des touches appuyées
	bool up, down, left, right, goup, godown, shield;
};



// Classe des models
class cl_model
{
private:
  // Nombre d'objets
  int nb_objet;
  // Type d'animation
  char anim;
  // Id vers la texture
  cl_texture **texture;
  // Id vers la skin
  int *skin;
  
public :
  cl_model(char * file, char shape=0, float Rext=0, float Rint=0, int resol=0, char loadtype=LOADTYPE_BMP);
  ~cl_model(void);
  bool aff(void);
};

cl_model * Map;

typedef struct type_drone
{
  char * skin;
  int vitesse;
  int effet;
};

const type_drone SHOKER01={"modelor/shoker.mad",3,-100};
const type_drone CRYSTAL01={"modelor/drone.mad",0,1};

class cl_drone : public cl_ent
{
private :

public :
  // Chainon suivant
  cl_drone * NEXT;
  // Chainon precedent
  cl_drone * LAST;
  
  virtual void Erase(void)=0;
  virtual void afficher(cl_model * skin, float yOscil)=0;
  virtual void NewDrone(type_drone type, float x=0, float y=0, float z=0)=0;
  virtual void Update(void)=0;

  // Constructeur
  cl_drone(void);
  // Destructeur
  ~cl_drone(void);

};

// Classe d'un vaisseau, dérivée d'une entité
class cl_wing : public cl_ent
{
protected :
  // Angle d'orientation sur le plan x/z et angle d'inclinaison dans les virages
  float dir, dirMod;
  // Angle d'inclinaison ( axe y ) et angle d'inclinaison dans les virages
  float inclin, inclinMod;
  // Facteur de vitesse
  float v, Vfactor;
  // Model (skin)
  cl_model *Model;
  cl_model *ShieldModel;
  cl_model *BallModel;
  // Sphere de dégat
  char SphereColor;
  // Armure
  float armure;
  // Rayon
  float rayon;
  // Rayon du shield
  float shield;
  bool affBall;
public :
  // Appliquer des dégats
  void setDegat(float f);
  // Bouclier
  float getShield(bool update=false, bool init=false);
  // Rayon Bouclier
  float getShieldR(void);
  // Gestion des touches agissants sur le vaisseau
  cl_input *input;
  // Fonction d'affichage du vaisseau
  virtual void afficher(void);
  void affTrans(void);
  // Fonction de remise à jour des paramètres de déplacement
  void avancer(void);
  // Accesseur sur l'Armure
  float getArmure(void);
  // Accesseur sur le rayon
  float getRayon(void);
  // Accesseur sur le facteur de vitesse
  float getV(void);
  // Mutateur absolu sur le facteur de vitesse
  void setV(float v1);
  // Accesseur sur l'angle d'orientation
  float getDir(void);
  // Accesseur sur l'angle d'inclinaison
  float getInclin(void);
  // Accesseur sur l'angle d'orientation
  float getDirMod(void);
  // Accesseur sur l'angle d'inclinaison
  float getInclinMod(void);
  // Modification de la sphere de collision
  void setSphere(char color);
  // Controle des données
  void Control(cl_drone* shok, int nb_enn, cl_drone* crys, int nb_crys, float yOsci) throw (ErrDeleteDrone,CollCrystal,RecolCrystal);
  bool exploreWingColl(int id);
  // Controle de la collision glissante
  bool CtrlColl(int id);
  void regulV(void);
  // Constructeur et destructeur
  cl_wing(char * url);
  ~cl_wing(void);
  
  friend class cl_bsp;
};

// Déclaration du pointeur vers le vaisseau principal
cl_wing* fly;

#include "part.cpp"

#define NOSHIELD -999

float cl_wing::getShield(bool update, bool init)
{
  static float shield=NOSHIELD;
  if(init)
    shield=-1;
  if(update && shield!=NOSHIELD)
    {
      shield+=GETTIMER*0.002;
      if(shield>1)
	shield=NOSHIELD;
    }

  if(shield==NOSHIELD)
    return NOSHIELD;
  return ((shield*shield*shield)+1);
}

float cl_wing::getArmure(void)
{
  return this->armure;
}

float cl_wing::getRayon(void)
{
  return this->rayon;
}

float cl_wing::getShieldR(void)
{
  return this->shield;
}

void cl_wing::setDegat(float f)
{
  this->armure-=f;
  return;
}


bool cl_wing::exploreWingColl(int id)
{
  int target=1;
  if(MapColl->Noeud[id]->axe!='0')
    {
      if(MapColl->Noeud[id]->axe=='x')
	{
	  if(this->pos->x<MapColl->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      target=(id*2)+1;
	    }
	}
      if(MapColl->Noeud[id]->axe=='y')
	{
	  if(this->pos->y<MapColl->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      target=(id*2)+1;
	    }
	}
      if(MapColl->Noeud[id]->axe=='z')
	{
	  if(this->pos->z<MapColl->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      target=(id*2)+1;
	    }
	}
      // Si la destination est simple...
      if(this->exploreWingColl(target)==true)
	return true;  
    }
  else
    {
      if(this->CtrlColl(id)==true)
	{
	  return true;
	}
    }

  return false;
}

bool cl_wing::CtrlColl(int id)
{
  for(int y=0 ; y<MapColl->Noeud[id]->nb_face ; y++)
    {
	  vertex vTriangle[3]={MapColl->Noeud[id]->face[y].t[0], MapColl->Noeud[id]->face[y].t[1], MapColl->Noeud[id]->face[y].t[2]};

	  vertex vNormal=Normal(vTriangle);
	  float distance=0.0f;
	  int classification=ClassifySphere(*(this->pos),vNormal,vTriangle[0],rayon,distance);
	  if(classification==INTERSECTS)
	    {
	      vertex vOffset=vNormal*distance;
	      vertex vIntersection=*(this->pos)-vOffset;
	      if(InsidePolygon(vIntersection,vTriangle,3) || EdgeSphereCollision(*(this->pos), vTriangle, 3, rayon/2))
		{
		  vOffset=GetCollisionOffset(vNormal,rayon,distance);
		  *(this->pos)=*(this->pos)+vOffset;
		  this->setSphere(SPHERECOLOR_BLACK);
		  BufferColor[0]=1.0f;
		  BufferColor[1]=0.0f;
		  BufferColor[2]=0.0f;
		  BufferColor[3]=1.0f;

		  this->armure-=0.003*GETTIMER;
		  affBall=true;
		}
	    }
	}
  static float LiqColor[4]={getRealFromMadMap(MAPURL,'K',1),getRealFromMadMap(MAPURL,'K',2),getRealFromMadMap(MAPURL,'K',3),getRealFromMadMap(MAPURL,'K',4)};
  if(this->pos->y<(MapColl->Climat->getLiq()-(MapColl->Climat->getVarLiq()/2)))
    {
      BufferColor[0]=1;//LiqColor[0];
      BufferColor[1]=0;//LiqColor[1];
      BufferColor[2]=0;//LiqColor[2];
      BufferColor[3]=1;//LiqColor[3];
    }
  
  return true;
}

// Controle des données
void cl_wing::Control(cl_drone* shok, int nb_enn, cl_drone* crys, int nb_crys, float yOsci=0) throw (ErrDeleteDrone, CollCrystal, RecolCrystal)
{
  static bool isdead=false;
	
  if(this->armure<=0)
    {
      if(isdead==false)
	{
	  printf("You're a dead man now   X(\n");
	  Particule->AddFumee(fly, vertex(0,0,0), 1, "data/texture/part/fumee.tga", 1000, true);
	}
      isdead=true;
      //glColor3d(1,0,0);
    }
  
  // Verifier les eventuelles collisions avec Shoker
  cl_drone * shoker=shok;
  for(int i=0 ; i<nb_enn ; i++)
    {
      vertex polyColl[4];
      polyColl[0].x=shoker->getPos().x+2;
      polyColl[0].y=shoker->getPos().y;
      polyColl[0].z=shoker->getPos().z+2;
      polyColl[1].x=shoker->getPos().x-2;
      polyColl[1].y=shoker->getPos().y;
      polyColl[1].z=shoker->getPos().z+2;
      polyColl[2].x=shoker->getPos().x-2;
      polyColl[2].y=shoker->getPos().y;
      polyColl[2].z=shoker->getPos().z-2;
      polyColl[3].x=shoker->getPos().x+2;
      polyColl[3].y=shoker->getPos().y;
      polyColl[3].z=shoker->getPos().z-2;
      
      if(SpherePolygonCollision(polyColl, *(this->pos), 4, rayon))
	{
	  Particule->AddExplosion(shoker->getPos(),30);
	  affBall=true;
	  throw ErrDeleteDrone(i);
	}
      
      shoker=shoker->NEXT;
    }

  
  // Verifier les eventuelles destruction de Crystal par Shield
  vertex v0= this->getPos();
  float f0=this->getShield(false,false);
  float a0=this->getDir();
  float a1=this->getInclin();
  
  if(f0!=NOSHIELD)
    {
      f0=f0*this->getShieldR();
      
      cl_drone * crystal=crys;
      for(int i=0 ; i<nb_crys ; i++)
	{     
	  vertex polygColl[4];
	  polygColl[0].x=v0.x+(Cos(-a0+90)*f0);
	  polygColl[0].y=v0.y;
	  polygColl[0].z=v0.z+(Sin(-a0+90)*f0);
	  polygColl[1].x=v0.x+(Cos(-a0+30)*f0*Cos(a1));
	  polygColl[1].y=v0.y+(Sin(a1)*f0);
	  polygColl[1].z=v0.z+(Sin(-a0+30)*f0*Cos(a1));
	  polygColl[2].x=v0.x+(Cos(-a0-30)*f0*Cos(a1));
	  polygColl[2].y=v0.y+(Sin(a1)*f0);
	  polygColl[2].z=v0.z+(Sin(-a0-30)*f0*Cos(a1));
	  polygColl[3].x=v0.x+(Cos(-a0-90)*f0);
	  polygColl[3].y=v0.y;
	  polygColl[3].z=v0.z+(Sin(-a0-90)*f0);

	  vertex vC=crystal->getPos();
	  if(SpherePolygonCollision(polygColl, vC, 4, 2/*rayon drone*/))
	    {
	      MapColl->NbCrystals--;
	      Particule->AddExplosion(crystal->getPos(),15);
	      throw RecolCrystal(i);
	    }

	  
	  polygColl[0].x=v0.x+(Cos(-a0-90)*f0);
	  polygColl[0].y=v0.y;
	  polygColl[0].z=v0.z+(Sin(-a0-90)*f0);
	  polygColl[1].x=v0.x+(Cos(-a0-150)*f0*Cos(a1));
	  polygColl[1].y=v0.y-(Sin(a1)*f0);
	  polygColl[1].z=v0.z+(Sin(-a0-150)*f0*Cos(a1));
	  polygColl[2].x=v0.x+(Cos(-a0+150)*f0*Cos(a1));
	  polygColl[2].y=v0.y-(Sin(a1)*f0);
	  polygColl[2].z=v0.z+(Sin(-a0+150)*f0*Cos(a1));
	  polygColl[3].x=v0.x+(Cos(-a0+90)*f0);
	  polygColl[3].y=v0.y;
	  polygColl[3].z=v0.z+(Sin(-a0+90)*f0);
	  
	  if(SpherePolygonCollision(polygColl, vC, 4, 2))
	    {
	      MapColl->NbCrystals--;
	      Particule->AddExplosion(crystal->getPos(),15);
	      affBall=true;
	      throw RecolCrystal(i);
	    }
	  
	  crystal=crystal->NEXT;
	}
    }

  // Verifier les eventuelles collisions avec Crystal
  cl_drone * crystal=crys;
  for(int i=0 ; i<nb_crys ; i++)
    {
      vertex polyColl[4];
      polyColl[0].x=crystal->getPos().x+2;
      polyColl[0].y=crystal->getPos().y;
      polyColl[0].z=crystal->getPos().z+2;
      polyColl[1].x=crystal->getPos().x-2;
      polyColl[1].y=crystal->getPos().y;
      polyColl[1].z=crystal->getPos().z+2;
      polyColl[2].x=crystal->getPos().x-2;
      polyColl[2].y=crystal->getPos().y;
      polyColl[2].z=crystal->getPos().z-2;
      polyColl[3].x=crystal->getPos().x+2;
      polyColl[3].y=crystal->getPos().y;
      polyColl[3].z=crystal->getPos().z-2;

      if(SpherePolygonCollision(polyColl, *(this->pos), 4, rayon))
	{
	  MapColl->NbCrystals--;
	  Particule->AddExplosion(crystal->getPos(),15);
	  affBall=true;
	  throw CollCrystal(i);
	}

      crystal=crystal->NEXT;
    }
  return;
}


// Modification de la sphere de collision
void cl_wing::setSphere(char color)
{
	this->SphereColor=color;

	return;
}


// Constructeur de la classe d'entité
cl_ent::cl_ent(void)
{
	// Allocation mémoire du vertex dynamique de position
	pos=new vertex;
	// Donner une position à l'origine
	pos->x=0;
	pos->y=0;
	pos->z=0;
}

// Destructeur de la classe d'entité
cl_ent::~cl_ent(void)
{
	// Liberation du vertex de position
	delete pos;
}

void cl_ent::afficher(void)
{
	return;
}

// Accesseur sur le facteur de vitesse du vaisseau
float cl_wing::getV(void)
{
	return this->v;
}

// Mutateur sur le facteur de vitesse du vaisseau
void cl_wing::setV(float v1)
{
	this->v=v1;
	if(this->v>this->Vfactor) this->v=Vfactor;
	if(this->v<this->Vfactor/(-4)) this->v=this->Vfactor/(-4);
	return;
}

// Accesseur sur l'angle de direction du vaisseau
float cl_wing::getDir(void)
{
	return this->dir;
}

// Accesseur sur l'angle d'inclinaison du vaisseau
float cl_wing::getInclin(void)
{
	return this->inclin;
}

// Accesseur sur l'angle de direction du vaisseau
float cl_wing::getDirMod(void)
{
	return (this->dir+this->dirMod);
}

// Accesseur sur l'angle d'inclinaison du vaisseau
float cl_wing::getInclinMod(void)
{
	return (this->inclin+this->inclinMod);
}


// Fonction d'affichage du vaisseau dans la map
void cl_wing::afficher(void)
{
	// Sauvegarde de la matrice courante
	glPushMatrix();
	// Translation vers les positions en x, y et z du vaisseau
	glTranslated(this->getPos().x,this->getPos().y,this->getPos().z);
	// Rotation autour de y pour la direction
	glRotated(this->dir+this->dirMod,0,1,0);
	// Rotation autour de z pour l'inclinaison
	glRotated(this->inclin+this->inclinMod,0,0,1);
	// Affichage du model du vaisseau
	Model->aff();
	// Reprise de la matrice d'origine
	glPopMatrix();

	return;
}

void cl_wing::affTrans(void)
{
  float s=getShield(true,false);

  static float ballRot=0;
  ballRot+=0.001*GETTIMER;
  if(ballRot>360)
    ballRot-=360;

  if(s!=NOSHIELD || affBall)
    {
      // Sauvegarde de la matrice courante
      glPushMatrix();
      // Translation vers les positions en x, y et z du vaisseau
      glTranslated(this->getPos().x,this->getPos().y,this->getPos().z);
      // Rotation autour de y pour la direction
      glRotated(this->dir+this->dirMod,0,1,0);
      // Rotation autour de z pour l'inclinaison
      glRotated(this->inclin+this->inclinMod,0,0,1);
	
    
      if(LIGHTON)
	glDisable(GL_LIGHTING);
      glDisable(GL_FOG);
      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glColor4f(1,1,1,1);
      if(affBall)
	{
	  glRotated(ballRot,0,1,0);
	  BallModel->aff();
	  affBall=false;
	}
      if(s!=NOSHIELD)
	{
	  glScalef(s,s,s);
	  ShieldModel->aff();
	}
      glDisable(GL_BLEND);
      if(LIGHTON)
	glEnable(GL_LIGHTING);
      glEnable(GL_FOG);
 
      // Reprise de la matrice d'origine
      glPopMatrix();
    }

  return;
}

void cl_wing::regulV(void)
{
  if(this->getV()>1)
    {
      this->setV(this->getV()-(GETTIMER*FACT_DECEL*0.2*this->Vfactor));
      if(this->getV()<1)
	this->setV(1);
    }
  else
    {
      this->setV(this->getV()+(GETTIMER*FACT_ACCEL*0.5*this->Vfactor));
      if(this->getV()>1)
	this->setV(1);
    }
  
  return;
}

// Fonction de remise à jour des positions du vaisseau en fonction des touches pressées
void cl_wing::avancer(void)
{
  static bool forUp=false, forDown=false, forRight=false, forLeft=false;
  bool Force=false;
  if(MapColl->IsTop(this->pos->y) && (this->inclin>0) )
  {
    forDown=false;
    forUp=true;
    Force=true;
  }
  if(MapColl->IsBottom(this->pos->y) && (this->inclin<0) )
  {
    forUp=false;
    forDown=true;
    Force=true;
  }
  
  if(MapColl->IsUp(this->pos->x) && (this->dir<90) )
  {
    forRight=false;
    forLeft=true;
    Force=true;
  }
  if(MapColl->IsUp(this->pos->x) && (this->dir>=270) )
  {
    forRight=true;
    forLeft=false;
    Force=true;
  }
  
  if(MapColl->IsDown(this->pos->x) && (this->dir>90) && (this->dir<180) )
  {
    forRight=true;
    forLeft=false;
    Force=true;
  }
  if(MapColl->IsDown(this->pos->x) && (this->dir>=180) && (this->dir<270) )
  {
    forRight=false;
    forLeft=true;
    Force=true;
  }

  if(MapColl->IsRight(this->pos->z) && (this->dir>=270) )
  {
    forRight=false;
    forLeft=true;
    Force=true;
  }
  if(MapColl->IsRight(this->pos->z) && (this->dir>180) && (this->dir<270) )
  {
    forRight=true;
    forLeft=false;
    Force=true;
  }
  
  if(MapColl->IsLeft(this->pos->z) && (this->dir>90) && (this->dir<180) )
  {
    forRight=false;
    forLeft=true;
    Force=true;
  }
  if(MapColl->IsLeft(this->pos->z) && (this->dir<=90) )
  {
    forRight=true;
    forLeft=false;
    Force=true;
  }

  if(Force==false)
    {
      forUp=false;
      forDown=false;
      forRight=false;
      forLeft=false;
    }
  
  if(this->input->goup==true)
    this->setV(this->getV()+(GETTIMER*FACT_ACCEL*this->Vfactor));
  else
    if(this->input->godown==true)
      this->setV(this->getV()-(GETTIMER*FACT_DECEL*this->Vfactor));
    else
      regulV();
  

  if( (this->input->up==true && forDown==false ) || forUp==true )
    {	// Touche 'haut'
      this->inclin-=5*GETTIMER*FACT_BRAQ;           // On ajuste l'angle de braquage
      if(this->inclin<-90) inclin=-90;         // On pose la limite
      this->inclinMod-=GETTIMER*FACT_BRAQ;          // On ajuste l'angle d'inclinaison
      if(this->inclinMod<-10) inclinMod=-10;   // On pose la limite
    }
  // Sinon on réajuste l'angle d'inclinaison
  else{  if(this->inclinMod<0) this->inclinMod++;  if(this->inclinMod<0) this->inclinMod++; }
  
  if( ( this->input->down==true && forUp==false ) || forDown==true )
    {	// Touche 'bas'
      this->inclin+=5*GETTIMER*FACT_BRAQ;	// On ajuste l'angle de braquage
      if(this->inclin>90) inclin=90; // On pose la limite
      this->inclinMod+=GETTIMER*FACT_BRAQ;	// On ajuste l'angle d'inclinaison
      if(this->inclinMod>10) inclinMod=10; // On pose la limite
    }
  // Sinon on réajuste l'angle d'inclinaison
  else { if(this->inclinMod>0) this->inclinMod--; if(this->inclinMod>0) this->inclinMod--; }
  
  if( (this->input->left==true && forRight==false ) || forLeft==true )
    {	// Touche 'gauche'
      this->dir+=5*GETTIMER*FACT_BRAQ;		// On ajuste l'angle de braquage
      if(this->dir>=360) dir-=360; // On pose la limite
      this->dirMod+=GETTIMER*FACT_BRAQ;	// On ajuste l'angle d'inclinaison
      if(this->dirMod>=15) dirMod=15; // On pose la limite
    }
  // Sinon on réajuste l'angle d'inclinaison
  else { if(this->dirMod>0) this->dirMod--; if(this->dirMod>0) this->dirMod--; }
  
  if( (this->input->right==true && forLeft==false ) || forRight==true )
    {	// Touche 'droite'
      this->dir-=5*GETTIMER*FACT_BRAQ;		// On ajuste l'angle de braquage
      if(this->dir<=0) dir+=360; // On pose la limite
      this->dirMod-=GETTIMER*FACT_BRAQ;	// On ajuste l'angle d'inclinaison
      if(this->dirMod<=-15) dirMod=-15; // On pose la limite
    }
  // Sinon on réajuste l'angle d'inclinaison
  else { if(this->dirMod<0) this->dirMod++; if(this->dirMod<0) this->dirMod++; }
  


  // On remet à jour la position en y par rapport à l'angle d'inclinaison
  pos->y=this->v*Sin(inclin)*GETTIMER*FACT_DEPL+this->pos->y;
  
  // On remet à jour les positions en x et z par rapport à l'angle de direction
  pos->x=this->pos->x+this->v*Cos(dir)*Cos(valAbs(inclin))*GETTIMER*FACT_DEPL;
  pos->z=this->pos->z-this->v*Sin(dir)*Cos(valAbs(inclin))*GETTIMER*FACT_DEPL;
  
  

  this->exploreWingColl(1);


  if( (this->pos->x) > (MapColl->MapLimits[MAPLIMITSUP]-100) )
    {
      this->pos->x=MapColl->MapLimits[MAPLIMITSUP]-100;
    }
  if( (this->pos->x) < (MapColl->MapLimits[MAPLIMITSDOWN]+100) )
    {
      this->pos->x=MapColl->MapLimits[MAPLIMITSDOWN]+100;
    }

  if( (this->pos->y) > (MapColl->MapLimits[MAPLIMITSTOP]-100) )
    {
      this->pos->y=MapColl->MapLimits[MAPLIMITSTOP]-100;
    }
  if( (this->pos->y) < (MapColl->MapLimits[MAPLIMITSBOTTOM]+100) )
    {
      this->pos->y=MapColl->MapLimits[MAPLIMITSBOTTOM]+100;
    }

  if( (this->pos->z) > (MapColl->MapLimits[MAPLIMITSRIGHT]-100) )
    {
      this->pos->z=MapColl->MapLimits[MAPLIMITSRIGHT]-100;
    }
  if( (this->pos->z) < (MapColl->MapLimits[MAPLIMITSLEFT]+100) )
    {
      this->pos->z=MapColl->MapLimits[MAPLIMITSLEFT]+100;
    }
	
  return;
}

// Constructeur de la classe de vaisseau
cl_wing::cl_wing(char * url)
{
  // Mise à zéro des angles de direction et d'inclinaison
  this->dir=this->inclin=this->dirMod=this->inclinMod=0;
  // Chargement du facteur de vitesse
  try
    {
      this->pos->x=getRealFromMadMap(MAPURL,'P',1);
      this->pos->y=getRealFromMadMap(MAPURL,'P',2);
      this->pos->z=getRealFromMadMap(MAPURL,'P',3);
    }
  catch(ErrFile Err)
    {
      this->pos->x=this->pos->y=this->pos->z=0;
    }
  catch(...)
    {
    }

  this->v=1;
  this->Vfactor=10;

  // Déclaration de la classe qui gère les touches pressées
  input=new cl_input;
  // Toutes les touches sont supposées relachées
  input->goup=false;
  input->godown=false;
  input->down=false;
  input->left=false;
  input->right=false;

  SphereColor='0';

  armure=100;
  rayon=2.8;
  shield=5;
  affBall=false;

  Model=new cl_model(url);
  ShieldModel=new cl_model("./data/texture/effect/shield.tga", 'S', shield, shield*0.33, 25, LOADTYPE_TGA32);
  BallModel=new cl_model("./data/texture/effect/ball.tga", 'U', rayon, 1, 20, LOADTYPE_TGA32);

}

// Destructeur de la classe de vaisseau
cl_wing::~cl_wing(void)
{
  delete input;
  delete Model;
  delete ShieldModel;
  delete BallModel;
}

