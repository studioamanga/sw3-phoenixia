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
		vertex dest;
		// Etat ( 'M' : en mouvement ; 'A' : en attente )
		char etat;
		// Angle d'orientation
		float angle;
		// Indice d'effet
		float effet;
		// Vitesse de déplacement
		int vit;


		// Deplacement du Shoker
		void deplacer(void);
		// IA de l'attente afin de définir le prochain déplacement
		void brainWait(void);

	public :

		cl_shoker(void);
		cl_shoker(type_drone type, float x=0, float y=0, float z=0);
		~cl_shoker(void);

		virtual void Erase(void);
		virtual void Update(void);
		virtual void afficher(cl_model * skin,float yOscil);
		virtual void NewDrone(type_drone type, float x=0, float y=0, float z=0);


	friend class cl_Serie;
};

void cl_shoker::NewDrone(type_drone type, float x, float y, float z)
{
	NEXT=new cl_shoker(type,x,y,z);


	return;
}


cl_shoker::cl_shoker(type_drone type, float x, float y, float z)
{
	// Etat en attente
	this->etat='A';
	this->angle=0;
	this->effet=type.effet;

	// Position et destination dans l'espace
	this->pos->x=this->dest.x=x;
	this->pos->y=this->dest.y=y;
	this->pos->z=this->dest.z=z;

	// Affectation de la vitesse
	this->vit=type.vitesse;

	// Chainon précédent
	//this->LAST=last;
}

cl_shoker::cl_shoker(void)
{
	// Etat en attente
	this->etat='A';
	this->angle=0;
	this->effet=-100;

	// Position et destination dans l'espace
	this->pos->x=this->dest.x=0;
	this->pos->y=this->dest.y=0;
	this->pos->z=this->dest.z=0;

	// Affectation de la vitesse
	this->vit=3;
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
	if(this->effet<=0)
	{
		effet+=GETTIMER*0.005;
	}
	else
	{
		if(MapColl->explorer(fly->getPos(),this->getPos(),3))
	      	{
			effet=-50;
		}
		else
		{
			this->dest.x=fly->getPos().x;
			this->dest.y=fly->getPos().y;
			this->dest.z=fly->getPos().z;
			this->etat='M';
		}
	}

	this->angle+=GETTIMER*0.01;
	if(this->angle>360) this->angle-=360;

	return;
}


void cl_shoker::deplacer(void)
{
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
		this->effet=(fly->getPos().x-this->pos->x)+ (fly->getPos().y-this->pos->y)+(fly->getPos().z-this->pos->z);

		if(this->effet<=0) this->effet=-this->effet;
	}

	return;
}

void cl_shoker::Update()
{
	// On remet à jour le déplacement
	this->deplacer();


	return;
}


