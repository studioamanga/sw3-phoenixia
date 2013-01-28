/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********** ent.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Classes des entit�s et de ses d�riv�s : vaisseaux...    **
**                                                         **
*************************************************************/

// Classe d'une entit�
class cl_ent
{

	protected :
		// Position
		vertex *pos;
	public :
		// Fonction d'affichage
		virtual void afficher(void);
		// Conna�tre la position de l'entit�
		vertex getPos(void);
		// Constructeur et destructeur
		cl_ent(void);
		~cl_ent(void);
};

// Retourne sous la forme d'un vertex la position de l'entit�
vertex cl_ent::getPos(void)
{
	return *(this->pos);
}

// Structure pour g�rer les touches maintenues appuy�es
struct cl_input
{
	// Bool�ennes des touches appuy�es
	bool up, down, left, right;
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
		GLuint **texture;
		// Id vers la skin
		int **skin;
	public :
		cl_model(char * file);
		~cl_model(void);
		bool aff(void);
};

cl_model * Map;


// Classe d'un vaisseau, d�riv�e d'une entit�
class cl_wing : public cl_ent
{
	protected :
		// Angle d'orientation sur le plan x/z et angle d'inclinaison dans les virages
  		double dir, dirMod;
		// Angle d'inclinaison ( axe y ) et angle d'inclinaison dans les virages
		double inclin, inclinMod;
		// Facteur de vitesse
		float v;
		// Model (skin)
		cl_model *Model;
	public :
		// Gestion des touches agissants sur le vaisseau
		cl_input *input;
		// Fonction d'affichage du vaisseau
		virtual void afficher(void);
		// Fonction de remise � jour des param�tres de d�placement
		void avancer(void);
		// Accesseur sur le facteur de vitesse
		float getV(void);
		// Mutateur absolu sur le facteur de vitesse
		void setV(float v1);
		// Accesseur sur l'angle d'orientation
		double getDir(void);
		// Accesseur sur l'angle d'inclinaison
		double getInclin(void);
		// Constructeur et destructeur
		cl_wing(void);
		~cl_wing(void);
};

// Constructeur de la classe d'entit�
cl_ent::cl_ent(void)
{
	// Allocation m�moire du vertex dynamique de position
	pos=new vertex;
	// Donner une position � l'origine
	pos->x=0;
	pos->y=0;
	pos->z=500;
}

// Destructeur de la classe d'entit�
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
	if(this->v>6) this->v=6;
	return;
}

// Accesseur sur l'angle de direction du vaisseau
double cl_wing::getDir(void)
{
	return this->dir;
}

// Accesseur sur l'angle d'inclinaison du vaisseau
double cl_wing::getInclin(void)
{
	return this->inclin;
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


// Fonction de remise � jour des positions du vaisseau en fonction des touches press�es
void cl_wing::avancer(void)
{

	if(this->input->up==true)
	{	// Touche 'haut'
		this->inclin-=5*Tfact;	// On ajuste l'angle de braquage
		if(this->inclin<-90) inclin=-90; // On pose la limite
		this->inclinMod-=1*Tfact;	// On ajuste l'angle d'inclinaison
		if(this->inclinMod<-10) inclinMod=-10; // On pose la limite
	}
	// Sinon on r�ajuste l'angle d'inclinaison
	else{  if(this->inclinMod<0) this->inclinMod++;  if(this->inclinMod<0) this->inclinMod++; }

	if(this->input->down==true)
	{	// Touche 'bas'
		this->inclin+=5*Tfact;	// On ajuste l'angle de braquage
		if(this->inclin>90) inclin=90; // On pose la limite
		this->inclinMod+=1*Tfact;	// On ajuste l'angle d'inclinaison
		if(this->inclinMod>10) inclinMod=10; // On pose la limite
	}
	// Sinon on r�ajuste l'angle d'inclinaison
	else { if(this->inclinMod>0) this->inclinMod--; if(this->inclinMod>0) this->inclinMod--; }

	if(this->input->left==true)
	{	// Touche 'gauche'
		this->dir+=5*Tfact;		// On ajuste l'angle de braquage
		if(this->dir>=360) dir-=360; // On pose la limite
		this->dirMod+=1*Tfact;	// On ajuste l'angle d'inclinaison
		if(this->dirMod>=15) dirMod=15; // On pose la limite
	}
	// Sinon on r�ajuste l'angle d'inclinaison
	else { if(this->dirMod>0) this->dirMod--; if(this->dirMod>0) this->dirMod--; }

	if(this->input->right==true)
	{	// Touche 'droite'
		this->dir-=5*Tfact;		// On ajuste l'angle de braquage
		if(this->dir<=0) dir+=360; // On pose la limite
		this->dirMod-=1*Tfact;	// On ajuste l'angle d'inclinaison
		if(this->dirMod<=-15) dirMod=-15; // On pose la limite
	}
	// Sinon on r�ajuste l'angle d'inclinaison
	else { if(this->dirMod<0) this->dirMod++; if(this->dirMod<0) this->dirMod++; }

	vertex may;

	// On remet � jour la position en y par rapport � l'angle d'inclinaison
	may.y=this->v*Sin(inclin)*Tfact+this->pos->y;

	// On remet � jour les positions en x et z par rapport � l'angle de direction
	may.x=this->pos->x+this->v*Cos(dir)*Cos(valAbs(inclin))*Tfact;
	may.z=this->pos->z-this->v*Sin(dir)*Cos(valAbs(inclin))*Tfact;

	if(MapColl->explorer(may,3)){}
	else
	{
		this->pos->x=may.x;
		this->pos->y=may.y;
		this->pos->z=may.z;
	}

	return;
}

// Constructeur de la classe de vaisseau
cl_wing::cl_wing(void)
{
	// Mise � z�ro des angles de direction et d'inclinaison
	this->dir=this->inclin=this->dirMod=this->inclinMod=0;
	// Determine un faible facteur de vitesse
	this->v=0.1;
	// D�claration de la classe qui g�re les touches press�es
	input=new cl_input;
	// Toutes les touches sont suppos�es relach�es
	input->up=false;
	input->down=false;
	input->left=false;
	input->right=false;

	Model=new cl_model("modelor/serv03.mad");

}

// Destructeur de la classe de vaisseau
cl_wing::~cl_wing(void)
{
	delete input;
	delete Model;
}

// D�claration du pointeur vers le vaisseau principal
cl_wing* fly;
