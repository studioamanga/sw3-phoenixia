/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** drone.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Structures, classes et fonctions liées aux entitées     **
** drones et à leur Intelligence Artificielle              **
**                                                         **
*************************************************************/


cl_drone::cl_drone(void)
{
	NEXT=NULL;
	LAST=NULL;
}

cl_drone::~cl_drone(void)
{
	if(NEXT!=NULL)
	{
		delete NEXT;
		NEXT=NULL;
	}
	if(LAST!=NULL)
	{
		delete LAST;
		LAST=NULL;
	}
}



class cl_crystal : public cl_drone
{
	protected :
		// Angle d'orientation
		float angle;
		// Indice d'effet
		short effet;
		

		// Deplacement du Crystal
		void deplacer(void);
		// IA de l'attente afin de définir le prochain déplacement
		void brainWait(void);

	public :

		cl_crystal(void);
		cl_crystal(type_drone type, float x=0, float y=0, float z=0);
		~cl_crystal(void);

		virtual void Erase(void);
		virtual void Update(void);
		virtual void afficher(cl_model * skin,float yOscil);
		virtual void NewDrone(type_drone type, float x=0, float y=0, float z=0);


	friend class cl_Serie;
};

void cl_crystal::NewDrone(type_drone type, float x, float y, float z)
{
	NEXT=new cl_crystal(type,x,y,z);

	return;
}


cl_crystal::cl_crystal(type_drone type, float x, float y, float z)
{
	this->angle=0;
	this->effet=type.effet;

	// Position et destination dans l'espace
	this->pos->x=x;
	this->pos->y=y;
	this->pos->z=z;

	// Chainon précédent
	//this->LAST=last;
}

cl_crystal::cl_crystal(void)
{
	this->angle=0;
	this->effet=0;

	// Position et destination dans l'espace
	this->pos->x=0;
	this->pos->y=0;
	this->pos->z=0;
}

cl_crystal::~cl_crystal(void)
{
	NEXT=NULL;
}

// Affichage
void cl_crystal::afficher(cl_model * skin, float yOscil)
{
  // Sauvegarde de la matrice courante
  glPushMatrix();
  // Translation vers les positions en x, y et z du shoker
  glTranslated(this->getPos().x, this->getPos().y+yOscil, this->getPos().z);
  // Rotation
  glRotated(this->angle,0,1,0);
  // Affichage du model
  skin->aff();
  // Reprise de la matrice d'origine
  glPopMatrix();

  return;
}


void cl_crystal::Erase(void)
{
	return;
}


// IA de l'attente afin de définir le prochain déplacement
void cl_crystal::brainWait(void)
{
	this->angle+=0.01*GETTIMER;
	if(this->angle>360) this->angle-=360;

	return;
}


void cl_crystal::deplacer(void)
{
	this->angle+=0.01*GETTIMER;
	if(this->angle>360) this->angle-=360;

	return;
}

void cl_crystal::Update()
{
	// On remet à jour le déplacement
	this->deplacer();


	return;
}


