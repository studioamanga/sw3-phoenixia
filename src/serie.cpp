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



void cl_Serie::Delete(int id)
{
	if(id!=0)
	{
		cl_drone*p=this->Drones;

		for(int i=0 ; i<id-1 ; i++)
		{
			p=p->NEXT;
		}
		cl_drone*err=p->NEXT;
		p->NEXT=p->NEXT->NEXT;
		delete err;
	}
	else
	{
		cl_drone*fst=Drones;
		Drones=Drones->NEXT;
		delete fst;
	}

	this->nbDrones--;

	return;
}


cl_Serie::cl_Serie(char Type, short nb, swVertex positions[])
{
  char *urlSkin=NULL;
  if(Type=='S')
    urlSkin=getStrFromMadMap(MAPURL,'S',1);
  if(Type=='C')
    urlSkin=getStrFromMadMap(MAPURL,'D',1);

  yOsc=-2;
  this->nbDrones=nb;
  if(Type=='S')
    {
      this->effet=getNbFromMadShoker(urlSkin,'A');
      this->rayon=getRealFromMadShoker(urlSkin,'R');
      this->Drones=new cl_shoker(urlSkin, positions[0].x, positions[0].y, positions[0].z);
    }
  if(Type=='C')
    {
      this->effet=getNbFromMadDrone(urlSkin,'E');
      this->rayon=getRealFromMadDrone(urlSkin,'R');
      this->Drones=new cl_crystal(urlSkin, positions[0].x, positions[0].y, positions[0].z);
    }
  
  
  this->LastDrone=this->Drones;
  
  cl_drone *p=this->Drones;
  
  for(int i=1 ; i<nb ; i++)
    {
      p->NewDrone(urlSkin, positions[i].x, positions[i].y, positions[i].z);
      
      p=p->NEXT;
      
    }

  this->model=new cl_model(urlSkin);

  logOut("  [OK] Elaboration de la serie réussie");// (%d elements)\n",nb);
  delete urlSkin;
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
