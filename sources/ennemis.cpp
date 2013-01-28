/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* ennemis.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Structures, classes et fonctions liées aux entitées     **
** ennemies et à leur Intelligence Artificielle            **
**                                                         **
*************************************************************/



class cl_shoker : public cl_drone
{
protected :
  // Destination
  swVertex dest;
  // Etat ( 'M' : en mouvement ; 'A' : en attente )
  char etat;
  // Angle d'orientation
  float angle;
  // Vitesse de déplacement
  float vit;
  float attente;


  // Deplacement du Shoker
  void deplacer(void);
  // IA de l'attente afin de définir le prochain déplacement
  void brainWait(void);

public :

  cl_shoker(void);
  cl_shoker(char * url, float x=0, float y=0, float z=0);
  ~cl_shoker(void);

  virtual void Erase(void);
  virtual void Update(void);
  virtual void afficher(cl_model * skin,float yOscil);
  virtual void NewDrone(char * url, float x=0, float y=0, float z=0);

  friend class cl_Serie;
};

void cl_shoker::NewDrone(char * url, float x, float y, float z)
{
  NEXT=new cl_shoker(url,x,y,z);

  return;
}


cl_shoker::cl_shoker(char * url, float x, float y, float z)
{
  // Etat en attente
  this->etat='A';
  this->angle=0;
  this->attente=-100;

  // Position et destination dans l'espace
  this->pos->x=this->dest.x=x;
  this->pos->y=this->dest.y=y;
  this->pos->z=this->dest.z=z;

  // Affectation de la vitesse
  this->vit=getRealFromMadShoker(url, 'V');

  // Chainon précédent
  //this->LAST=last;
}

cl_shoker::cl_shoker(void)
{
  // Etat en attente
  this->etat='A';
  this->angle=0;
  this->attente=-100;

  // Position et destination dans l'espace
  this->pos->x=this->dest.x=0;
  this->pos->y=this->dest.y=0;
  this->pos->z=this->dest.z=0;

  // Affectation de la vitesse
  this->vit=1;
}

cl_shoker::~cl_shoker(void)
{
  NEXT=NULL;
}

// Affichage
void cl_shoker::afficher(cl_model * skin, float yOscil=0)
{
  // Sauvegarde de la matrice courante
  glPushMatrix();
  // Translation vers les positions en x, y et z du shoker
  glTranslated(this->getPos().x, this->getPos().y, this->getPos().z);
  // Rotation d'attente
  if(this->etat=='A')
    {
      glRotated(this->angle,0,1,0);
    }
  // Affichage du model
  skin->aff();
  // Reprise de la matrice d'origine
  glPopMatrix();

  return;
}


void cl_shoker::Erase(void)
{
  return;
}


// IA de l'attente afin de définir le prochain déplacement
void cl_shoker::brainWait(void)
{
  this->angle+=GETTIMER*0.01;
  if(this->angle>360) this->angle-=360;

  if(cursMod==MOD_EXPLORATION)
    return;

  if(this->attente<=0)
    {
      this->attente+=GETTIMER*0.005;
    }
  else
    {
      if(MapColl->explorer(fly->getPos(),this->getPos(),3))
	{
	  this->attente=-50;
	}
      else
	{
	  this->dest.x=fly->getPos().x;
	  this->dest.y=fly->getPos().y;
	  this->dest.z=fly->getPos().z;
	  this->etat='M';
	}
    }

  return;
}


void cl_shoker::deplacer(void)
{
  // s'il s'agit d'une exploration, on le laisse en attente
  if(cursMod==MOD_EXPLORATION)
    this->etat='A';

  // On ne fait rien s'il n'est pas en déplacement
  if(this->etat!='M')
    {
      if(this->etat=='A')
	this->brainWait();
      return;
    }

  // On se dirige vers la destination
  if(this->pos->x<this->dest.x)
    {
      pos->x+=this->vit*GETTIMER*0.005;
    }
  if(this->pos->y<this->dest.y)
    {
      pos->y+=this->vit*GETTIMER*0.005;
    }
  if(this->pos->z<this->dest.z)
    {
      pos->z+=this->vit*GETTIMER*0.005;
    }
  if(this->pos->x>this->dest.x)
    {
      pos->x-=this->vit*GETTIMER*0.005;
    }
  if(this->pos->y>this->dest.y)
    {
      pos->y-=this->vit*GETTIMER*0.005;
    }
  if(this->pos->z>this->dest.z)
    {
      pos->z-=this->vit*GETTIMER*0.005;
    }

  // Si on est arrivé on passe en mode 'attente'
  if( this->pos->x+this->vit>this->dest.x && this->pos->x-this->vit<this->dest.x && this->pos->y+this->vit>this->dest.y &&this->pos->y-this->vit<this->dest.y &&this->pos->z+this->vit>this->dest.z &&this->pos->z-this->vit<this->dest.z)
    {
      this->etat='A';
      this->attente=(fly->getPos().x-this->pos->x)+ (fly->getPos().y-this->pos->y)+(fly->getPos().z-this->pos->z);
      if(this->attente<=0) this->attente=-this->attente;
    }

  return;
}

void cl_shoker::Update()
{
	// On remet à jour le déplacement
	this->deplacer();

	return;
}


