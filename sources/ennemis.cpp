/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* ennemis.cpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/

typedef struct type_shoker
{
	char * skin;
};

const type_shoker SHOKER01={"modelor/drone.mad"};

class cl_shoker
{
	private :
		// Model (skin)
		cl_model *Model;
		// Position & destination
		vertex pos, dest;
		// Etat ( 'M' : en mouvement ; 'A' : en attente )
		char etat;

		// Affichage du Shoker à sa position, en fonction de son état
		void afficher(char tag='0');
		// Deplacement du Shoker
		void deplacer(void);

	public :
		cl_shoker(type_shoker type);
		~cl_shoker(void);

		void Update(void);
};

cl_shoker * Shokers;

cl_shoker::cl_shoker(type_shoker type)
{
	// Chargement du model en mémoire
	this->Model=new cl_model(type.skin);

	// Etat en attente
	this->etat='A';

	// Position et destination dans l'espace
	this->pos.x=this->dest.x=0;
	this->pos.y=this->dest.y=0;
	this->pos.z=this->dest.z=0;
}

cl_shoker::~cl_shoker(void)
{
	// Destruction mémoire du model
	delete this->Model;
}

void cl_shoker::afficher(char tag)
{
	// Sauvegarde de la matrice courante
	glPushMatrix();
	// Translation vers les positions en x, y et z du shoker
	glTranslated(this->pos.x,this->pos.y,this->pos.z);
	// Affichage du model du vaisseau
	this->Model->aff();
	// Reprise de la matrice d'origine
	glPopMatrix();

	return;
}

void cl_shoker::deplacer(void)
{
	// On ne fait rien s'il n'est pas en déplacement
	if(this->etat!='M')
		return;

	// On se dirige vers la destination
	if(this->pos.x!=this->dest.x)
	{
		pos.x+=15;
	}
	if(this->pos.y!=this->dest.y)
	{
		pos.y+=15;
	}
	if(this->pos.z!=this->dest.z)
	{
		pos.z+=15;
	}

	return;
}

void cl_shoker::Update(void)
{
	// On remet à jour le déplacement
	this->deplacer();

	// On affiche
	this->afficher('0');

	return;
}

