/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* vector.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Classes, fonctions et méthodes permettant de gérer les  **
** vertices, les vecteurs et les fonctions mathématiques   **
** ou trigonométriques.                                    **
**                                                         **
*************************************************************/

typedef struct vertex
{
	float x,y,z;
};

float valAbs(float x)	//**** Retourne la valeur absolue d'un float ****//
{
	if(x<0) x*=-1;
	return x;
}

// Fonctions de trigonométrie ( conversion degrés-radians )
double Cos(double a)
{
	a=cos(a*0.017453);
	return a;
}
double Sin(double a)
{
	a=sin(a*0.017453);
	return a;
}
double Tan(double a)
{
	a=tan(a*0.017453);
	return a;
}
double aCos(double a)
{
	a=acos(a)*57.29578;
	return a;
}
double aSin(double a)
{
	a=asin(a)*57.29578;
	return a;
}
double aTan(double a)
{
	a=atan(a)*57.29578;
	return a;
}

class vecteur
{
	protected :
		vertex vector;
	public :
		vertex getVector(void);
		float getL2d(float x, float y);
		float getA2d(float x, float y);
		void addVector(float x, float y, float z);
		void setVector(float x, float y, float z);
		vecteur(float x, float y, float z);
		~vecteur(void);
};

void vecteur::addVector(float x, float y, float z)
{
	this->vector.x+=x;
	this->vector.y+=y;
	this->vector.z+=z;

	return;
}

void vecteur::setVector(float x, float y, float z)
{
	this->vector.x=x;
	this->vector.y=y;
	this->vector.z=z;

	return;
}


float vecteur::getL2d(float x, float y)
{
	x=valAbs(x);
	y=valAbs(y);
	float z=x+y;
	return z;
}

float vecteur::getA2d(float x, float y)
{
	x=valAbs(x);
	y=valAbs(y);
	float a=y/x;
	a=aTan(a);
	return a;
}

float getAngle2d(float x, float y)
{
	float x1=valAbs(x);
	float y1=valAbs(y);
	float a=0;
	if (x<0&&y>0||x>0&&y<0) a=y1/x1;
	if (x<0&&y<0||x>0&&y>0) a=x1/y1;

	a=aTan(a);

	if(x>0&&y>0) a+=270;
	if(x<0&&y>0) a+=180;
	if(x<0&&y<0) a+=90;
	if(x>0&&y<0) a+=0;

	return a;
}

vertex vecteur::getVector(void)
{
	return this->vector;
}

vecteur::vecteur(float x, float y, float z)
{
	this->vector.x=x;
	this->vector.y=y;
	this->vector.z=z;
}

vecteur::~vecteur(void)
{
}
