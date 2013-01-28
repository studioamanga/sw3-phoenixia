/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** serie.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Structures, classes et fonctions liées aux entitées     **
** drones et à leur Intelligence Artificielle              **
**                                                         **
*************************************************************/



// Ensemble de drones
class cl_Serie
{
private :
  // Skin
  cl_model * model;
public :
  float yOsc;
  // Liste des shokers ( element 1 )
  cl_drone * Drones;
  // Liste des shokers ( dernier element )
  cl_drone * LastDrone;
  // Nombre de drone
  short nbDrones;
  // Model (skin) : texture + 2 matériaux
  GLuint text_shoker;
  int id_shokerPIQ, id_shokerCOR;


  // Detruire un drone
  void Delete(int id);
  // Affiche tous les shokers
  void afficher(void);
  // Constructeur
  cl_Serie(char Type, short nb, type_drone type[], vertex positions[]);
  // Destructeur
  ~cl_Serie();

  friend class cl_shoker;
};

void cl_Serie::Delete(int id)
{
	if(id!=0)
	{
		cl_drone*p=this->Drones;

		for(int i=0 ; i<id-1 ; i++)
		{
			p=p->NEXT;
		}
		//cl_drone*err=p->NEXT;
		p->NEXT=p->NEXT->NEXT;
		//delete err;
	}
	else
	{
		cl_drone*fst=Drones;
		Drones=Drones->NEXT;
		//delete fst;
	}

	this->nbDrones--;

	return;
}


cl_Serie::cl_Serie(char Type, short nb, type_drone type [], vertex positions[])
{
  yOsc=-2;
  this->nbDrones=nb;
  if(Type=='S')
    {
      this->Drones=new cl_shoker(type[0], positions[0].x, positions[0].y, positions[0].z);
    }
  if(Type=='C')
    {
      this->Drones=new cl_crystal(type[0], positions[0].x, positions[0].y, positions[0].z);
    }
  
  
  this->LastDrone=this->Drones;
  
  cl_drone *p=this->Drones;
  
  for(int i=1 ; i<nb ; i++)
    {
      p->NewDrone(type[i],positions[i].x, positions[i].y, positions[i].z);
      
      p=p->NEXT;
      
    }
  
  char *urlSkin=NULL;
  if(Type=='S')
    urlSkin=getStrFromMadMap(MAPURL,'S',1);
  if(Type=='C')
    urlSkin=getStrFromMadMap(MAPURL,'D',1);

  this->model=new cl_model(urlSkin);

  delete urlSkin;
  
  
  printf("  [OK] Elaboration de la serie réussie (%d elements)\n",nb);

}

cl_Serie::~cl_Serie()
{
	delete this->model;
	if(Drones!=NULL)
	{
		delete Drones;
	}
}

void cl_Serie::afficher(void)
{
  yOsc+=0.0007*GETTIMER;
  if(yOsc>2)
    yOsc=-2;

  float yOsci=(yOsc*yOsc)-2;

  glBindTexture(GL_TEXTURE_2D, this->text_shoker);
  
  cl_drone * p=this->Drones;
  for(short i=0 ; i<this->nbDrones ; i++)
    {
      p->afficher(model,yOsci);
      p=p->NEXT;
    }
  return;
}

cl_Serie* Crystals;
cl_Serie* Shokers;

