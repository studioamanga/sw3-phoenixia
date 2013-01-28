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

#define INF_THEO 9999999

// Recherche d'un nombre alléatoire flottant
float RandFloat (float fMin, float fMax)
{
	return (rand () / (float)RAND_MAX * (fMax - fMin)) + fMin;
}

// Recherche d'un nombre alléatoire entier
int RandInt (int iMin, int iMax)
{
	return (int)(rand () / (float)RAND_MAX * (iMax - iMin)) + iMin;
}


typedef struct vertexPol
{
  float aDir, aInclin;
  float rayon;
};

typedef struct swVertex
{
public:

    // A default constructor
    swVertex() {}

    // This is our constructor that allows us to initialize our data upon creating an instance
    swVertex(float X, float Y, float Z)
    {
        x = X; y = Y; z = Z;
    }

    // Here we overload the + operator so we can add vectors together
    swVertex operator+(swVertex vVector)
    {
        // Return the added vectors result.
        return swVertex(vVector.x + x, vVector.y + y, vVector.z + z);
    }

    // Here we overload the - operator so we can subtract vectors
    swVertex operator-(swVertex vVector)
    {
        // Return the subtracted vectors result
        return swVertex(x - vVector.x, y - vVector.y, z - vVector.z);
    }

    // Here we overload the - operator so we can subtract vectors
    swVertex operator*(float num)
    {
        // Return the subtracted vectors result
        return swVertex(x * num, y * num, z * num);
    }


	float x,y,z;
};

void operator % ( swVertex v1, swVertex v2 )
{
	v1.x=v2.x;
	v1.y=v2.y;
	v1.z=v2.z;

	return;
}

//  This returns a perpendicular vector from 2 given vectors by taking the cross product.
swVertex Cross(swVertex vVector1, swVertex vVector2);

//  This returns the magnitude of a normal (or any other vector)
float Magnitude(swVertex vNormal);

//  This returns a normalize vector (A vector exactly of length 1)
swVertex Normalize(swVertex vNormal);

//  This returns the normal of a polygon (The direction the polygon is facing)
swVertex Normal(swVertex vPolygon[]);

// This returns the distance between 2 3D points
float Distance(swVertex vPoint1, swVertex vPoint2);

// This returns the point on the line segment vA_vB that is closest to point vPoint
swVertex ClosestPointOnLine(swVertex vA, swVertex vB, swVertex vPoint);

// This returns the distance the plane is from the origin (0, 0, 0)
// It takes the normal to the plane, along with ANY point that lies on the plane (any corner)
float PlaneDistance(swVertex Normal, swVertex Point);

// This takes a triangle (plane) and line and returns true if they intersected
bool IntersectedPlane(swVertex vPoly[], swVertex vLine[], swVertex &vNormal, float &originDistance);

// This returns the dot product between 2 vectors
float Dot(swVertex vVector1, swVertex vVector2);

// This returns the angle between 2 vectors
double AngleBetweenVectors(swVertex Vector1, swVertex Vector2);

// This returns an intersection point of a polygon and a line (assuming intersects the plane)
swVertex IntersectionPoint(swVertex vNormal, swVertex vLine[], double distance);

// This returns true if the intersection point is inside of the polygon
bool InsidePolygon(swVertex vIntersection, swVertex Poly[], long verticeCount);

// Use this function to test collision between a line and polygon
bool IntersectedPolygon(swVertex vPoly[], swVertex vLine[], int verticeCount);

// Use this function to test collision between a line and polygon and get distance
float IntersectedPolygonDist(swVertex vPoly[], swVertex vLine[], int verticeCount);

int ClassifySphere(swVertex &vCenter,
                   swVertex &vNormal, swVertex &vPoint, float radius, float &distance);

// This takes in the sphere center, radius, polygon vertices and swVertex count.
// This function is only called if the intersection point failed.  The sphere
// could still possibly be intersecting the polygon, but on it's edges.
bool EdgeSphereCollision(swVertex &vCenter,
                         swVertex vPolygon[], int vertexCount, float radius);

// This returns true if the sphere is intersecting with the polygon.
// The parameters are the vertices of the polygon, swVertex count, along with the center
// and radius of the sphere.
bool SpherePolygonCollision(swVertex vPolygon[],
                            swVertex &vCenter, int vertexCount, float radius);

swVertex GetCollisionOffset(swVertex &vNormal, float radius, float distance);


float valAbs(float x)	//**** Retourne la valeur absolue d'un float ****//
{
	if(x<0) x*=-1;
	return x;
}

float minFloat(float f1, float f2)
{
  if(f1<f2)
    return f1;
  return f2;
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
		swVertex vector;
	public :
		swVertex getVector(void);
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

swVertex vecteur::getVector(void)
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


// Collision swVertex format
typedef struct Cvf
{
	swVertex t[3];
};
