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
		// Id vers la texture
		GLuint texture;
		// Id vers le model
		int model;
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
	pos->z=0;
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
	// On s�lectionne la texture correspondant � la skin
	glBindTexture(GL_TEXTURE_2D, this->texture);
	// Translation vers les positions en x, y et z du vaisseau
	glTranslated(this->getPos().x,this->getPos().y,this->getPos().z);
	// Rotation autour de y pour la direction
	glRotated(this->dir+this->dirMod,0,1,0);
	// Rotation autour de z pour l'inclinaison
	glRotated(this->inclin+this->inclinMod,0,0,1);
	// Affichage du model du vaisseau
	glCallList(this->model);
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

	// On remet � jour la position en y par rapport � l'angle d'inclinaison
	this->pos->y+=this->v*Sin(inclin)*Tfact;

	// On remet � jour les positions en x et z par rapport � l'angle de direction
	this->pos->x+=this->v*Cos(dir)*Cos(valAbs(inclin))*Tfact;
	this->pos->z-=this->v*Sin(dir)*Cos(valAbs(inclin))*Tfact;

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

	// G�n�ration de l'identificateur pour le model du vaisseau
	this->model=glGenLists(1);
	// G�n�ration et initialisation de la texture de skin du vaisseau
	this->texture = LoadBMP("data/textures/wing/serv03.bmp");

	// Cr�ation du model du vaisseau
	glNewList(this->model,GL_COMPILE);
	glBegin(GL_QUADS);
	// ************* Corps *******************//
	// Fond
	glTexCoord2f(0.625,0.785); glVertex3f(-1.2,-0.65,0.375);
	glTexCoord2f(0.33,0.785); glVertex3f(-1.2,-0.65,-0.375);
	glTexCoord2f(0.33,0.45); glVertex3f(3.,-0.65,-0.375);
	glTexCoord2f(0.625,0.45); glVertex3f(3.,-0.65,0.375);
	// Petit c�t� droit
	glTexCoord2f(0.625,0.785); glVertex3f(-1.2,-0.65,0.375);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.25,-0.5,0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(3.5,-0.5,0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(3.,-0.65,0.375);
	// Petit c�t� gauche
	glTexCoord2f(0.625,0.785); glVertex3f(-1.2,-0.65,-0.375);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.25,-0.5,-0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(3.5,-0.5,-0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(3.,-0.65,-0.375);
	// Petit c�t� avant
	glTexCoord2f(0.52,0.132); glVertex3f(3.,-0.65,0.375);
	glTexCoord2f(0.48,0.132); glVertex3f(3.,-0.65,-0.375);
	glTexCoord2f(0.48,0.1); glVertex3f(3.5,-0.5,-0.4);
	glTexCoord2f(0.52,0.1); glVertex3f(3.5,-0.5,0.4);
	// Petit c�t� arri�re
	glTexCoord2f(0.52,0.132); glVertex3f(-1.2,-0.65,0.375);
	glTexCoord2f(0.48,0.132); glVertex3f(-1.2,-0.65,-0.375);
	glTexCoord2f(0.48,0.1); glVertex3f(-1.25,-0.5,-0.4);
	glTexCoord2f(0.52,0.1); glVertex3f(-1.25,-0.5,0.4);
	// Petit c�t� avant sup�rieur
	glTexCoord2f(0.52,0.05); glVertex3f(3.5,-0.5,0.4);
	glTexCoord2f(0.48,0.05); glVertex3f(3.5,-0.5,-0.4);
	glTexCoord2f(0.48,0.09); glVertex3f(2.75,-0.25,-0.25);
	glTexCoord2f(0.52,0.09); glVertex3f(2.75,-0.25,0.25);
	// Petit c�t� droit sup�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(3.5,-0.5,0.4);
	glTexCoord2f(0.6,0.785); glVertex3f(0.,-0.5,0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(0.,-0.25,0.25);
	glTexCoord2f(0.625,0.45); glVertex3f(2.75,-0.25,0.25);
	// Petit c�t� gauche sup�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(3.5,-0.5,-0.4);
	glTexCoord2f(0.6,0.785); glVertex3f(0.,-0.5,-0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(0.,-0.25,-0.25);
	glTexCoord2f(0.625,0.45); glVertex3f(2.75,-0.25,-0.25);
	// Vitre avant
	glTexCoord2f(0.52,0.135); glVertex3f(2.75,-0.25,0.25);
	glTexCoord2f(0.48,0.135); glVertex3f(2.75,-0.25,-0.25);
	glTexCoord2f(0.48,0.15); glVertex3f(2.5,0.,-0.2);
	glTexCoord2f(0.52,0.15); glVertex3f(2.5,0.,0.2);
	// Vitre avant m�diane
	glTexCoord2f(0.48,0.15); glVertex3f(2.5,0.,0.2);
	glTexCoord2f(0.52,0.15); glVertex3f(2.5,0.,-0.2);
	glTexCoord2f(0.52,0.30); glVertex3f(1.65,0.45,-0.3);
	glTexCoord2f(0.48,0.30); glVertex3f(1.65,0.45,0.3);
	// Vitre avant sup�rieure
	glTexCoord2f(0.48,0.30); glVertex3f(1.65,0.45,0.3);
	glTexCoord2f(0.52,0.30); glVertex3f(1.65,0.45,-0.3);
	glTexCoord2f(0.52,0.35); glVertex3f(1.2,0.45,-0.4);
	glTexCoord2f(0.48,0.35); glVertex3f(1.2,0.45,0.4);
	// Vitre droite avant
	glTexCoord2f(0.52,0.135); glVertex3f(2.75,-0.25,0.25);
	glTexCoord2f(0.48,0.135); glVertex3f(1.65,-0.25,0.3);
	glTexCoord2f(0.48,0.35); glVertex3f(1.65,0.45,0.3);
	glTexCoord2f(0.52,0.35); glVertex3f(2.5,0.,0.2);
	// Vitre gauche avant
	glTexCoord2f(0.52,0.135); glVertex3f(2.75,-0.25,-0.25);
	glTexCoord2f(0.48,0.135); glVertex3f(1.65,-0.25,-0.3);
	glTexCoord2f(0.48,0.35); glVertex3f(1.65,0.45,-0.3);
	glTexCoord2f(0.52,0.35); glVertex3f(2.5,0.,-0.2);
	// Vitre droite arri�re
	glTexCoord2f(0.52,0.135); glVertex3f(1.65,-0.25,0.3);
	glTexCoord2f(0.48,0.135); glVertex3f(1.,-0.25,0.4);
	glTexCoord2f(0.48,0.35); glVertex3f(1.2,0.45,0.4);
	glTexCoord2f(0.52,0.35); glVertex3f(1.65,0.45,0.3);
	// Vitre gauche arri�re
	glTexCoord2f(0.52,0.135); glVertex3f(1.65,-0.25,-0.3);
	glTexCoord2f(0.48,0.135); glVertex3f(1.,-0.25,-0.4);
	glTexCoord2f(0.48,0.35); glVertex3f(1.2,0.45,-0.4);
	glTexCoord2f(0.52,0.35); glVertex3f(1.65,0.45,-0.3);
	// C�t� droit inf�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,-0.5,0.4);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.,-0.5,0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.,-0.25,0.6);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,-0.25,0.6);
	// C�t� gauche inf�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,-0.5,-0.4);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.,-0.5,-0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.,-0.25,-0.6);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,-0.25,-0.6);
	// C�t� droit sup�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,0.15,0.6);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.,0.15,0.6);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.,0.4,0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,0.4,0.4);
	// C�t� gauche sup�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,0.15,-0.6);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.,0.15,-0.6);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.,0.4,-0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,0.4,-0.4);
	// C�t� droit
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,-0.25,0.6);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.,-0.25,0.6);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.,0.15,0.6);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,0.15,0.6);
	// C�t� gauche
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,-0.25,-0.6);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.,-0.25,-0.6);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.,0.15,-0.6);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,0.15,-0.6);
	// C�t� droit int�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,-0.5,0.4);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.25,-0.5,0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.25,0.4,0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,0.4,0.4);
	// C�t� gauche int�rieur
	glTexCoord2f(0.625,0.785); glVertex3f(1.5,-0.5,-0.4);
	glTexCoord2f(0.6,0.785); glVertex3f(-1.25,-0.5,-0.4);
	glTexCoord2f(0.6,0.45); glVertex3f(-1.25,0.4,-0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(1.5,0.4,-0.4);
	// Toit
	glTexCoord2f(0.625,0.785); glVertex3f(-1.25,0.4,0.4);
	glTexCoord2f(0.33,0.785); glVertex3f(-1.25,0.4,-0.4);
	glTexCoord2f(0.33,0.45); glVertex3f(1.2,0.4,-0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(1.2,0.4,0.4);
	// Back
	glTexCoord2f(0.625,0.785); glVertex3f(-1.25,-0.5,0.4);
	glTexCoord2f(0.33,0.785); glVertex3f(-1.25,-0.5,-0.4);
	glTexCoord2f(0.33,0.45); glVertex3f(-1.25,0.4,-0.4);
	glTexCoord2f(0.625,0.45); glVertex3f(-1.25,0.4,0.4);
	// R�acteur
	glTexCoord2f(0.38,0.9); glVertex3f(-1.45,-0.375,0.45);
	glTexCoord2f(0.62,0.9); glVertex3f(-1.45,-0.375,-0.45);
	glTexCoord2f(0.62,0.8); glVertex3f(-1.45,0.25,-0.45);
	glTexCoord2f(0.38,0.8); glVertex3f(-1.45,0.25,0.45);
	// Face sup�rieure du r�acteur
	glTexCoord2f(0.38,0.9); glVertex3f(-1.45,0.25,0.45);
	glTexCoord2f(0.62,0.9); glVertex3f(-1.45,0.25,-0.45);
	glTexCoord2f(0.62,1.); glVertex3f(0.,0.25,-0.45);
	glTexCoord2f(0.38,1.); glVertex3f(0.,0.25,0.45);
	// Face inf�rieure du r�acteur
	glTexCoord2f(0.38,0.9); glVertex3f(-1.45,-0.375,0.45);
	glTexCoord2f(0.62,0.9); glVertex3f(-1.45,-0.375,-0.45);
	glTexCoord2f(0.62,1.); glVertex3f(0.,-0.375,-0.45);
	glTexCoord2f(0.38,1.); glVertex3f(0.,-0.375,0.45);
	// Face droite du r�acteur
	glTexCoord2f(0.38,0.9); glVertex3f(-1.45,-0.375,0.45);
	glTexCoord2f(0.62,0.9); glVertex3f(-1.45,0.25,0.45);
	glTexCoord2f(0.62,1.); glVertex3f(0.,0.25,0.45);
	glTexCoord2f(0.38,1.); glVertex3f(0.,-0.375,0.45);
	// Face gauche du r�acteur
	glTexCoord2f(0.38,0.9); glVertex3f(-1.45,-0.375,-0.45);
	glTexCoord2f(0.62,0.9); glVertex3f(-1.45,0.25,-0.45);
	glTexCoord2f(0.62,1.); glVertex3f(0.,0.25,-0.45);
	glTexCoord2f(0.38,1.); glVertex3f(0.,-0.375,-0.45);

	// ************* Aile sup�rieure ***************//
	// Face droite avant
	glTexCoord2f(0.33,1.); glVertex3f(-1.25,0.4,0.05);
	glTexCoord2f(0.,0.6); glVertex3f(-3.,1.6,0.05);
	glTexCoord2f(0.,0.385); glVertex3f(0.25,1.6,0.05);
	glTexCoord2f(0.33,0.785); glVertex3f(1.,0.4,0.05);
	// Face gauche avant
	glTexCoord2f(0.67,1.); glVertex3f(-1.25,0.4,-0.05);
	glTexCoord2f(1.,0.6); glVertex3f(-3.,1.6,-0.05);
	glTexCoord2f(1.,0.385); glVertex3f(0.25,1.6,-0.05);
	glTexCoord2f(0.67,0.785); glVertex3f(1.,0.4,-0.05);
	// Face sup�rieure avant
	glTexCoord2f(0.49,0.4); glVertex3f(1.,0.4,0.05);
	glTexCoord2f(0.51,0.4); glVertex3f(0.25,1.6,0.05);
	glTexCoord2f(0.51,0.7); glVertex3f(0.25,1.6,-0.05);
	glTexCoord2f(0.49,0.7); glVertex3f(1.,0.4,-0.05);
	// Face sup�rieure
	glTexCoord2f(0.49,0.4); glVertex3f(0.25,1.6,0.05);
	glTexCoord2f(0.51,0.4); glVertex3f(-3.,1.6,0.05);
	glTexCoord2f(0.51,0.7); glVertex3f(-3.,1.6,-0.05);
	glTexCoord2f(0.49,0.7); glVertex3f(0.25,1.6,-0.05);
	// Face droite arri�re
	glTexCoord2f(0.2,0.9); glVertex3f(-1.25,0.4,0.05);
	glTexCoord2f(0.15,1.); glVertex3f(-3.,0.6,0.05);
	glTexCoord2f(0.05,1.); glVertex3f(-3.4,1.3,0.05);
	glTexCoord2f(0.,0.6); glVertex3f(-3.,1.6,0.05);
	// Face gauche arri�re
	glTexCoord2f(0.8,0.9); glVertex3f(-1.25,0.4,-0.05);
	glTexCoord2f(0.85,1.); glVertex3f(-3.,0.6,-0.05);
	glTexCoord2f(0.95,1.); glVertex3f(-3.4,1.3,-0.05);
	glTexCoord2f(1.,0.6); glVertex3f(-3.,1.6,-0.05);
	// Face sup�rieure arri�re
	glTexCoord2f(0.49,0.4); glVertex3f(-3.,1.6,0.05);
	glTexCoord2f(0.51,0.4); glVertex3f(-3.4,1.3,0.05);
	glTexCoord2f(0.51,0.7); glVertex3f(-3.4,1.3,-0.05);
	glTexCoord2f(0.49,0.7); glVertex3f(-3.,1.6,-0.05);
	// Face arri�re
	glTexCoord2f(0.49,0.4); glVertex3f(-3.4,1.3,0.05);
	glTexCoord2f(0.51,0.4); glVertex3f(-3.,0.6,0.05);
	glTexCoord2f(0.51,0.7); glVertex3f(-3.,0.6,-0.05);
	glTexCoord2f(0.49,0.7); glVertex3f(-3.4,1.3,-0.05);
	// Face arri�re ant�rieure
	glTexCoord2f(0.49,0.4); glVertex3f(-3.,0.6,0.05);
	glTexCoord2f(0.51,0.4); glVertex3f(-1.25,0.4,0.05);
	glTexCoord2f(0.51,0.7); glVertex3f(-1.25,0.4,-0.05);
	glTexCoord2f(0.49,0.7); glVertex3f(-3.,0.6,-0.05);

	// *********** Ailes lat�rales ***************//
	// Aile droite : face int�rieure sup�rieure
	glTexCoord2f(0.65,0.785); glVertex3f(-1.25,0.4,0.4);
	glTexCoord2f(0.85,0.4); glVertex3f(-0.75,-0.6,2.);
	glTexCoord2f(0.85,0.3); glVertex3f(1.4,-0.6,2.);
	glTexCoord2f(0.65,0.45); glVertex3f(0.65,0.4,0.4);
	// Aile droite : face ext�rieure sup�rieure
	glTexCoord2f(0.85,0.4); glVertex3f(-0.75,-0.6,2.);
	glTexCoord2f(1.,0.385); glVertex3f(0.,-1.5,2.5);
	glTexCoord2f(1.,0.); glVertex3f(2.,-1.5,2.5);
	glTexCoord2f(0.85,0.3); glVertex3f(1.4,-0.6,2.);
	// Aile droite : face int�rieure inf�rieure
	glTexCoord2f(0.65,0.785); glVertex3f(-1.25,0.3,0.4);
	glTexCoord2f(0.85,0.4); glVertex3f(-0.75,-0.7,2.);
	glTexCoord2f(0.85,0.3); glVertex3f(1.4,-0.6,2.);
	glTexCoord2f(0.65,0.45); glVertex3f(0.65,0.4,0.4);
	// Aile droite : face ext�rieure inf�rieure
	glTexCoord2f(0.85,0.4); glVertex3f(-0.75,-0.7,2.);
	glTexCoord2f(1.,0.385); glVertex3f(0.,-1.6,2.45);
	glTexCoord2f(1.,0.); glVertex3f(2.,-1.5,2.5);
	glTexCoord2f(0.85,0.3); glVertex3f(1.4,-0.6,2.);
	// Aile droite : face int�rieure arri�re
	glTexCoord2f(0.49,0.4); glVertex3f(-1.25,0.3,0.4);
	glTexCoord2f(0.51,0.4); glVertex3f(-0.75,-0.7,2.);
	glTexCoord2f(0.51,0.7); glVertex3f(-0.75,-0.6,2.);
	glTexCoord2f(0.49,0.7); glVertex3f(-1.25,0.4,0.4);
	// Aile droite : face ext�rieure arri�re
	glTexCoord2f(0.49,0.4); glVertex3f(-0.75,-0.7,2.);
	glTexCoord2f(0.51,0.4); glVertex3f(0.05,-1.55,2.5);
	glTexCoord2f(0.51,0.7); glVertex3f(0.05,-1.55,2.55);
	glTexCoord2f(0.49,0.7); glVertex3f(-0.75,-0.6,2.);
	// Aile droite : face int�rieure du pic
	glTexCoord2f(1.,0.05); glVertex3f(0.,-1.5,2.5);
	glTexCoord2f(1.,0.); glVertex3f(0.,-1.6,2.45);
	glTexCoord2f(0.7,0.); glVertex3f(3.5,-1.6,2.45);
	glTexCoord2f(0.7,0.05); glVertex3f(3.4,-1.5,2.5);
	// Aile droite : face ext�tieure du pic
	glTexCoord2f(1.,0.05); glVertex3f(0.05,-1.55,2.55);
	glTexCoord2f(1.,0.); glVertex3f(0.05,-1.65,2.5);
	glTexCoord2f(0.7,0.); glVertex3f(3.55,-1.65,2.5);
	glTexCoord2f(0.7,0.05); glVertex3f(3.45,-1.55,2.55);
	// Aile droite : face sup�rieure du pic
	glTexCoord2f(1.,0.05); glVertex3f(0.,-1.5,2.5);
	glTexCoord2f(1.,0.); glVertex3f(0.05,-1.65,2.5);
	glTexCoord2f(0.7,0.); glVertex3f(3.45,-1.55,2.5);
	glTexCoord2f(0.7,0.05); glVertex3f(3.4,-1.5,2.5);
	// Aile droite : face inf�rieure du pic
	glTexCoord2f(1.,0.05); glVertex3f(0.,-1.6,2.45);
	glTexCoord2f(1.,0.); glVertex3f(0.05,-1.65,2.5);
	glTexCoord2f(0.7,0.); glVertex3f(3.55,-1.65,2.5);
	glTexCoord2f(0.7,0.05); glVertex3f(3.4,-1.5,2.5);
	// Aile droite : face avant du pic
	glTexCoord2f(1.,0.05); glVertex3f(3.45,-1.55,2.55);
	glTexCoord2f(1.,0.); glVertex3f(3.55,-1.65,2.5);
	glTexCoord2f(0.7,0.); glVertex3f(3.5,-1.6,2.45);
	glTexCoord2f(0.7,0.05); glVertex3f(3.4,-1.5,2.5);
	// Aile gauche : face int�rieure sup�rieure
	glTexCoord2f(0.33,0.785); glVertex3f(-1.25,0.4,-0.4);
	glTexCoord2f(0.15,0.4); glVertex3f(-0.75,-0.6,-2.);
	glTexCoord2f(0.15,0.3); glVertex3f(1.4,-0.6,-2.);
	glTexCoord2f(0.33,0.45); glVertex3f(0.65,0.4,-0.4);
	// Aile gauche : face ext�rieure sup�rieure
	glTexCoord2f(0.15,0.4); glVertex3f(-0.75,-0.6,-2.);
	glTexCoord2f(0.,0.385); glVertex3f(0.,-1.5,-2.5);
	glTexCoord2f(0.,0.); glVertex3f(2.,-1.5,-2.5);
	glTexCoord2f(0.15,0.3); glVertex3f(1.4,-0.6,-2.);
	// Aile gauche : face int�rieure inf�rieure
	glTexCoord2f(0.33,0.785); glVertex3f(-1.25,0.3,-0.4);
	glTexCoord2f(0.15,0.4); glVertex3f(-0.75,-0.7,-2.);
	glTexCoord2f(0.15,0.3); glVertex3f(1.4,-0.6,-2.);
	glTexCoord2f(0.33,0.45); glVertex3f(0.65,0.4,-0.4);
	// Aile gauche : face ext�rieure inf�rieure
	glTexCoord2f(0.15,0.4); glVertex3f(-0.75,-0.7,-2.);
	glTexCoord2f(0.,0.385); glVertex3f(0.,-1.6,-2.45);
	glTexCoord2f(0.,0.); glVertex3f(2.,-1.5,-2.5);
	glTexCoord2f(0.15,0.3); glVertex3f(1.4,-0.6,-2.);
	// Aile gauche : face int�rieure arri�re
	glTexCoord2f(0.49,0.4); glVertex3f(-1.25,0.3,-0.4);
	glTexCoord2f(0.51,0.4); glVertex3f(-0.75,-0.7,-2.);
	glTexCoord2f(0.51,0.7); glVertex3f(-0.75,-0.6,-2.);
	glTexCoord2f(0.49,0.7); glVertex3f(-1.25,0.4,-0.4);
	// Aile gauche : face ext�rieure arri�re
	glTexCoord2f(0.49,0.4); glVertex3f(-0.75,-0.7,-2.);
	glTexCoord2f(0.51,0.4); glVertex3f(0.05,-1.65,-2.5);
	glTexCoord2f(0.51,0.7); glVertex3f(0.05,-1.55,-2.55);
	glTexCoord2f(0.49,0.7); glVertex3f(-0.75,-0.6,-2.);
	// Aile gauche : face int�rieure du pic
	glTexCoord2f(0.,0.05); glVertex3f(0.,-1.5,-2.5);
	glTexCoord2f(0.,0.); glVertex3f(0.,-1.6,-2.45);
	glTexCoord2f(0.3,0.); glVertex3f(3.5,-1.6,-2.45);
	glTexCoord2f(0.3,0.05); glVertex3f(3.4,-1.5,-2.5);
	// Aile gauche : face ext�tieure du pic
	glTexCoord2f(0.,0.05); glVertex3f(0.05,-1.55,-2.55);
	glTexCoord2f(0.,0.); glVertex3f(0.05,-1.65,-2.5);
	glTexCoord2f(0.3,0.); glVertex3f(3.55,-1.65,-2.5);
	glTexCoord2f(0.3,0.05); glVertex3f(3.45,-1.55,-2.55);
	// Aile gauche : face sup�rieure du pic
	glTexCoord2f(0.,0.05); glVertex3f(0.,-1.5,-2.5);
	glTexCoord2f(0.,0.); glVertex3f(0.05,-1.65,-2.5);
	glTexCoord2f(0.3,0.); glVertex3f(3.45,-1.55,-2.5);
	glTexCoord2f(0.3,0.05); glVertex3f(3.4,-1.5,-2.5);
	// Aile gauche : face inf�rieure du pic
	glTexCoord2f(0.,0.05); glVertex3f(0.,-1.6,-2.45);
	glTexCoord2f(0.,0.); glVertex3f(0.05,-1.65,-2.5);
	glTexCoord2f(0.3,0.); glVertex3f(3.55,-1.65,-2.5);
	glTexCoord2f(0.3,0.05); glVertex3f(3.4,-1.5,-2.5);
	// Aile gauche : face avant du pic
	glTexCoord2f(0.,0.05); glVertex3f(3.45,-1.55,-2.55);
	glTexCoord2f(0.,0.); glVertex3f(3.55,-1.65,-2.5);
	glTexCoord2f(0.3,0.); glVertex3f(3.5,-1.6,-2.45);
	glTexCoord2f(0.3,0.05); glVertex3f(3.4,-1.5,-2.5);

	glEnd();
	glEndList();

}

// Destructeur de la classe de vaisseau
cl_wing::~cl_wing(void)
{
	delete input;
}

// D�claration du pointeur vers le vaisseau principal
cl_wing* fly;
