/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* bsp.cpp **** auteur : Vincent Tourraine ***********
**                                                         **
** Fonctions, structures et classes liées aux arbres BSP   **
** et à l'optimisation des collisions                      **
**                                                         **
*************************************************************/


float getSizeX(Cvf F [], int nbF);
float getSizeY(Cvf F [], int nbF);
float getSizeZ(Cvf F [], int nbF);

float getMedianeX(Cvf F [], int nbF);
float getMedianeY(Cvf F [], int nbF);
float getMedianeZ(Cvf F [], int nbF);

float getMinX(Cvf F [], int nbF);
float getMaxX(Cvf F [], int nbF);
float getMinZ(Cvf F [], int nbF);
float getMaxZ(Cvf F [], int nbF);
float getMinY(Cvf F [], int nbF);
float getMaxY(Cvf F [], int nbF);



// Structure des noeuds de l'arbre BSP
class noeud
{
	public :
		int nb_face;
		Cvf * face;

		float med;
		char axe;

		noeud(void);
		~noeud(void);
};


noeud::noeud(void)
{
  this->nb_face=0;
  this->face=NULL;
  med=0;
  axe='0';
}

noeud::~noeud(void)
{
  if(nb_face>0&&face!=NULL)
    {
      //for(int i=0 ; i<nb_face ; i++)
      //{
      //	delete &(this->face[i]);
      //}
      delete this->face;
    }
}

#define MAPLIMITSUP 0
#define MAPLIMITSDOWN 1
#define MAPLIMITSLEFT 2
#define MAPLIMITSRIGHT 3
#define MAPLIMITSTOP 4
#define MAPLIMITSBOTTOM 5

// Classe d'un arbre BSP
class cl_bsp
{
protected :
  // Nombre de noeuds
  int nb_noeud;
  // Tableaux de l'ensemble des noeuds
  noeud ** Noeud;
  
  
public :
  // Climat
  cl_climat* Climat;

  // Positions
  float MapLimits[6];
  float MapLimitsGraph[6];
  float getSizeX(void);
  float getSizeZ(void);
  bool IsTop(float pY);
  bool IsBottom(float pY);
  bool IsUp(float pX);
  bool IsDown(float pX);
  bool IsRight(float pZ);
  bool IsLeft(float pZ);
  // Données relatives au temps
  float TIMEmax, TIMEactu;
  // Crystals
  int TotalCrystals, NbCrystals;
  void TIMEupdate(void);
  bool isFinish(void);
  // Permet de situer un vertex dans l'arbre et de tester les faces
  bool explorer(swVertex p, swVertex pOld, float rayon);
  // Test d'un noeud pour l'exploration
  bool testNoeud(int id, swVertex p, swVertex pOld, float rayon);
  // Test d'un noeud pour l'exploration des balles
  float testNoeudDist(int id, swVertex & vPos, swVertex & vDist);
  // Test de la collision
  bool test(swVertex p, swVertex pOld, float rayon, int target);
  // Test de la collision pour les balles
  float testDist(swVertex & vPos, swVertex & vDest, int target);
  // Segmenter un noeud
  bool segmentNoeud(int id, char Axe, float Min, float Max);
  // Aff Liquid
  void affLiquid(void);
  // Pour les balles
  float bulletDistMur(swVertex & vPos, swVertex & vDest);
  // Constructeur
  cl_bsp(char * name);
  // Destructeur
  ~cl_bsp(void);
  
  friend class cl_wing;
};

float cl_bsp::bulletDistMur(swVertex & vPos, swVertex & vDest)
{
  return this->testNoeudDist(1,vPos,vDest);
}

// Test d'un noeud pour l'exploration des balles et renvoie la distance du mur le plus proche
float cl_bsp::testNoeudDist(int id, swVertex & vPos, swVertex & vDest)
{
  int target=1;
  if(this->Noeud[id]->axe!='0')
    {
      if(this->Noeud[id]->axe=='x')
	{
	  if(vPos.x<this->Noeud[id]->med && vDest.x<this->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      if(vPos.x>this->Noeud[id]->med && vDest.x>this->Noeud[id]->med)
		target=(id*2)+1;
	      else
		target=-99;
	    }
	}
      if(this->Noeud[id]->axe=='y')
	{
	  if(vPos.y<this->Noeud[id]->med && vDest.y<this->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      if(vPos.y>this->Noeud[id]->med && vDest.y>this->Noeud[id]->med)
		target=(id*2)+1;
	      else
		target=-99;
	    }
	}
      if(this->Noeud[id]->axe=='z')
	{
	  if(vPos.z<this->Noeud[id]->med && vDest.z<this->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      if(vPos.z>this->Noeud[id]->med && vDest.z>this->Noeud[id]->med)
		target=(id*2)+1;
	      else
		target=-99;
	    }
	}
      // Si la destination est simple...
      if(target!=-99)
	{
	  return this->testNoeudDist(target,vPos, vDest);
	}
      // Si la destination est double
      else
	{
	  float minDist;
	  minDist=minFloat(this->testNoeudDist(id*2, vPos, vDest), this->testNoeudDist((id*2)+1, vPos, vDest));
	  return minDist;
	}
    }
  else
    {
      return this->testDist(vPos, vDest, id);
    }

  return (INF_THEO);
}

// Test de la collision pour les balles
float cl_bsp::testDist(swVertex & vPos, swVertex & vDest, int target)
{
  float resultMin=INF_THEO;
  swVertex vLine[2];
  vLine[0].x=vPos.x;
  vLine[0].y=vPos.y;
  vLine[0].z=vPos.z;
  vLine[1].x=vDest.x;
  vLine[1].y=vDest.y;
  vLine[1].z=vDest.z;

  for(int y=0 ; y<Noeud[target]->nb_face ; y++)
    {
      float result;

      result=IntersectedPolygonDist(Noeud[target]->face[y].t, vLine, 3);
      if(result!=(INF_THEO))
	{
	  resultMin=minFloat(resultMin, result);
	}
    }

  return resultMin;
}


float cl_bsp::getSizeX(void)
{
  return valAbs((this->MapLimits[MAPLIMITSUP])-(this->MapLimits[MAPLIMITSDOWN]));
}
float cl_bsp::getSizeZ(void)
{
  return valAbs((this->MapLimits[MAPLIMITSLEFT])-(this->MapLimits[MAPLIMITSRIGHT]));
}

bool cl_bsp::IsTop(float pY)
{
  if(pY > (this->MapLimits[MAPLIMITSTOP]-300))
     return true;
  return false;
}
bool cl_bsp::IsBottom(float pY)
{
  if(pY < (this->MapLimits[MAPLIMITSBOTTOM]+300))
    return true;
  return false;
}

bool cl_bsp::IsUp(float pX)
{
  if(pX > (this->MapLimits[MAPLIMITSUP]-300))
     return true;
  return false;
}
bool cl_bsp::IsDown(float pX)
{
  if(pX < (this->MapLimits[MAPLIMITSDOWN]+300))
    return true;
  return false;
}

bool cl_bsp::IsRight(float pZ)
{
  if(pZ > (this->MapLimits[MAPLIMITSRIGHT]-300))
     return true;
  return false;
}
bool cl_bsp::IsLeft(float pZ)
{
  if(pZ < (this->MapLimits[MAPLIMITSLEFT]+300))
    return true;
  return false;
}


void cl_bsp::TIMEupdate(void)
{
  this->TIMEactu+=(GETTIMER);

  return;
}

bool cl_bsp::isFinish(void)
{
  if(this->TIMEactu > this->TIMEmax)
    return true;

  return false;
}


// Test d'un noeud pour l'exploration
bool cl_bsp::testNoeud(int id, swVertex p, swVertex pOld, float rayon)
{
  int target=1;
  if(this->Noeud[id]->axe!='0')
    {
      if(this->Noeud[id]->axe=='x')
	{
	  if(p.x<this->Noeud[id]->med&&pOld.x<this->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      if(p.x>this->Noeud[id]->med&&pOld.x>this->Noeud[id]->med)
		target=(id*2)+1;
	      else
		target=-99;
	    }
	}
      if(this->Noeud[id]->axe=='y')
	{
	  if(p.y<this->Noeud[id]->med&&pOld.y<this->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      if(p.y>this->Noeud[id]->med&&pOld.y>this->Noeud[id]->med)
		target=(id*2)+1;
	      else
		target=-99;
	    }
	}
      if(this->Noeud[id]->axe=='z')
	{
	  if(p.z<this->Noeud[id]->med&&pOld.z<this->Noeud[id]->med)
	    target=id*2;
	  else
	    {
	      if(p.z>this->Noeud[id]->med&&pOld.z>this->Noeud[id]->med)
		target=(id*2)+1;
	      else
		target=-99;
	    }
	}
      // Si la destination est simple...
      if(target!=-99)
	{
	  if(this->testNoeud(target,p,pOld,rayon)==true)
	    return true;
	}
      // Si la destination est double
      else
	{
	  if(this->testNoeud(id*2,p,pOld,rayon)==true)
	    return true;
	  if(this->testNoeud((id*2)+1,p,pOld,rayon)==true)
	    return true;
	}
    }
  else
    {
      if(this->test(p,pOld,rayon,id)==true)
	return true;
    }

  return false;
}

// Permet de situer un vertex dans l'arbre et de tester les faces
bool cl_bsp::explorer(swVertex p, swVertex pOld, float rayon)
{
	return this->testNoeud(1,p,pOld,rayon);
}

// Segmenter un noeud
bool cl_bsp::segmentNoeud(int id, char Axe, float Min, float Max)
{
	float Med=(((Max-Min)/2)+Min);
	if(id>this->nb_noeud)
		return false;

	this->Noeud[id]->med=Med;
	this->Noeud[id]->axe=Axe;

	bool inG=false, inD=false;
	int nbG=0, nbD=0;
	for(int i=0 ; i<this->Noeud[id]->nb_face ; i++)
	{
		inG=false, inD=false;
		if(Axe=='x')
		{
			if(this->Noeud[id]->face[i].t[0].x<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[1].x<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[2].x<Med)
			{
				inG=true;
			}
			else
				inD=true;
		}
		if(Axe=='y')
		{
			if(this->Noeud[id]->face[i].t[0].y<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[1].y<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[2].y<Med)
			{
				inG=true;
			}
			else
				inD=true;
		}
		if(Axe=='z')
		{
			if(this->Noeud[id]->face[i].t[0].z<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[1].z<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[2].z<Med)
			{
				inG=true;
			}
			else
				inD=true;
		}


		if(inG==true)
			nbG++;
		if(inD==true)
			nbD++;
	}

	this->Noeud[id*2]=new noeud;
	this->Noeud[id*2]->nb_face=nbG;
	this->Noeud[id*2]->face=new Cvf[nbG];

	this->Noeud[(id*2)+1]=new noeud;
	this->Noeud[(id*2)+1]->nb_face=nbD;
	this->Noeud[(id*2)+1]->face=new Cvf[nbD];

	nbD=nbG=0;
	for(int i=0 ; i<this->Noeud[id]->nb_face ; i++)
	{
		inG=false, inD=false;
		if(Axe=='x')
		{
			if(this->Noeud[id]->face[i].t[0].x<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[1].x<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[2].x<Med)
			{
				inG=true;
			}
			else
				inD=true;
		}
		if(Axe=='y')
		{
			if(this->Noeud[id]->face[i].t[0].y<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[1].y<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[2].y<Med)
			{
				inG=true;
			}
			else
				inD=true;
		}
		if(Axe=='z')
		{
			if(this->Noeud[id]->face[i].t[0].z<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[1].z<Med)
			{
				inG=true;
			}
			else
				inD=true;
			if(this->Noeud[id]->face[i].t[2].z<Med)
			{
				inG=true;
			}
			else
				inD=true;
		}


		if(inG==true)
		{
			nbG++;
			this->Noeud[id*2]->face[nbG-1].t[0].x=this->Noeud[id]->face[i].t[0].x;
			this->Noeud[id*2]->face[nbG-1].t[0].y=this->Noeud[id]->face[i].t[0].y;
			this->Noeud[id*2]->face[nbG-1].t[0].z=this->Noeud[id]->face[i].t[0].z;

			this->Noeud[id*2]->face[nbG-1].t[1].x=this->Noeud[id]->face[i].t[1].x;
			this->Noeud[id*2]->face[nbG-1].t[1].y=this->Noeud[id]->face[i].t[1].y;
			this->Noeud[id*2]->face[nbG-1].t[1].z=this->Noeud[id]->face[i].t[1].z;

			this->Noeud[id*2]->face[nbG-1].t[2].x=this->Noeud[id]->face[i].t[2].x;
			this->Noeud[id*2]->face[nbG-1].t[2].y=this->Noeud[id]->face[i].t[2].y;
			this->Noeud[id*2]->face[nbG-1].t[2].z=this->Noeud[id]->face[i].t[2].z;
		}
		if(inD==true)
		{
			nbD++;
			this->Noeud[(id*2)+1]->face[nbD-1].t[0].x=this->Noeud[id]->face[i].t[0].x;
			this->Noeud[(id*2)+1]->face[nbD-1].t[0].y=this->Noeud[id]->face[i].t[0].y;
			this->Noeud[(id*2)+1]->face[nbD-1].t[0].z=this->Noeud[id]->face[i].t[0].z;

			this->Noeud[(id*2)+1]->face[nbD-1].t[1].x=this->Noeud[id]->face[i].t[1].x;
			this->Noeud[(id*2)+1]->face[nbD-1].t[1].y=this->Noeud[id]->face[i].t[1].y;
			this->Noeud[(id*2)+1]->face[nbD-1].t[1].z=this->Noeud[id]->face[i].t[1].z;

			this->Noeud[(id*2)+1]->face[nbD-1].t[2].x=this->Noeud[id]->face[i].t[2].x;
			this->Noeud[(id*2)+1]->face[nbD-1].t[2].y=this->Noeud[id]->face[i].t[2].y;
			this->Noeud[(id*2)+1]->face[nbD-1].t[2].z=this->Noeud[id]->face[i].t[2].z;
		}

	}

	this->Noeud[id]->nb_face=0;
	delete this->Noeud[id]->face;

	if(Max-Min>400)
	{
		if(Axe=='x')
		{
			if(segmentNoeud(id*2,'y',Min,Med)==false)
				return false;
			if(segmentNoeud((id*2)+1,'y',Med,Max)==false)
				return false;
		}
		if(Axe=='y')
		{
			if(segmentNoeud(id*2,'z',Min,Med)==false)
				return false;
			if(segmentNoeud((id*2)+1,'z',Med,Max)==false)
				return false;
		}
		if(Axe=='z')
		{
			if(segmentNoeud(id*2,'x',Min,Med)==false)
				return false;
			if(segmentNoeud((id*2)+1,'x',Med,Max)==false)
				return false;
		}
	}

	return true;
}


// Test de la collision
bool cl_bsp::test(swVertex p, swVertex pOld, float rayon, int target)
{
  for(int y=0 ; y<Noeud[target]->nb_face ; y++)
	{
	  if(SpherePolygonCollision(Noeud[target]->face[y].t, p, 3, rayon))
		{
			return true;
		}
		swVertex vLine[2];
		vLine[0].x=p.x;
		vLine[0].y=p.y;
		vLine[0].z=p.z;
		vLine[1].x=pOld.x;
		vLine[1].y=pOld.y;
		vLine[1].z=pOld.z;
	if(IntersectedPolygon(Noeud[target]->face[y].t, vLine, 3))
		{
			return true;
		}
	}

	return false;
}

// Constructeur qui prend comme argument le nom du fichier
cl_bsp::cl_bsp(char * name)
{
  this->TIMEactu=0;

  switch(cursMod)
    {
    case MOD_DEFI :
      this->TIMEmax=MOD_DEFI_MISSIONS[cursDefiMission-1].duree*1000;
      break;
    case MOD_EXPLORATION :
    default :
      this->TIMEmax=5000*1000;
    }

  // Initialisation nulle de l'arbre
  nb_noeud=0;
  Noeud=NULL;

  this->TotalCrystals=this->NbCrystals=getNbFromMadMap(MAPURL,'D');
  
  FILE* fIn=fopen(name,"r");
  if(fIn==NULL)
    {
      logOut("Echec lors de la création du BSP :\nModel inexistant\n");
    }
  else
    {
      // Controle de format
      unsigned char id;
      fread(&id,sizeof(unsigned char),1,fIn);
      if(id!=136)
	{
	  logOut("Echec lors de la création du BSP :\nModel incorrect\n");
	  return;
	}
      fseek(fIn,sizeof(int)+sizeof(char),SEEK_CUR);
      // Nombre d'objet
      int nb_surface;
      fread(&nb_surface,sizeof(int),1,fIn);
      int nbV=0;
      // Pour chaque objet...
      char type;
      float missMin=0,missMax=0, missX=0;
      for(int i=0;i<nb_surface;i++)
	{
	fseek(fIn, sizeof(char)*50, SEEK_CUR);
	// Saisie dyu type de surface
	fread(&type,sizeof(char),1,fIn);
	// Saisie du nombre de vertices
	int nb_vertices;
	fread(&nb_vertices,sizeof(int),1,fIn);
	for(int f=0 ; f<nb_vertices ; f++)
	  {
	    fread(&missX,sizeof(float),1,fIn);
	    if(type!='M')//Si ce n'est pas une map box
	    {
	      if(missX<missMin) missMin=missX;
	      if(missX>missMax) missMax=missX;
	    }
	    fseek(fIn, sizeof(float)*4, SEEK_CUR);
	  }
	if(type=='M') nb_vertices=0;
	if(type=='Q') nb_vertices=int((nb_vertices)*1.5);
	if(type=='T') nb_vertices=(nb_vertices-2)*3;
	nbV+=nb_vertices;
	}
      
      nbV/=3;
      
      nb_noeud=int(((missMax-missMin)/200));
      if(nb_noeud>20)
	nb_noeud=20;
      nb_noeud=(nb_noeud*nb_noeud*nb_noeud);
 
      Noeud=new noeud*[nb_noeud];
      for(int i=0 ; i<nb_noeud ; i++)
	Noeud[i]=NULL;

      Noeud[1]=new noeud;
      Noeud[1]->nb_face=nbV;
      Noeud[1]->face=new Cvf[nbV];
      
      fseek(fIn, sizeof(char)*2+sizeof(int)*2, SEEK_SET);
      int p=0;
      for(int i=0; i<nb_surface;i++)
	{
	  fseek(fIn, sizeof(char)*50, SEEK_CUR);
	  // Saisie dyu type de surface
	  char type;
	  fread(&type,sizeof(char),1,fIn);
	  // Saisie du nombre de vertices
	  int nb_vertices;
	  fread(&nb_vertices,sizeof(int),1,fIn);
	  
	  int t=0;
	  for(int y=0 ; y<nb_vertices ; y++,p++)
	    {
	      if(type!='M')
		{
		  if(type=='T')
		    {
		      if(t==1)
			{
			  fread(&(Noeud[1]->face[p].t[2].x),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[2].y),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[2].z),sizeof(float),1,fIn);
			  fseek(fIn,sizeof(float)*2,SEEK_CUR);
			  Noeud[1]->face[p].t[0].x=Noeud[1]->face[p-1].t[1].x;
			  Noeud[1]->face[p].t[0].y=Noeud[1]->face[p-1].t[1].y;
			  Noeud[1]->face[p].t[0].z=Noeud[1]->face[p-1].t[1].z;
			  Noeud[1]->face[p].t[1].x=Noeud[1]->face[p-1].t[2].x;
			  Noeud[1]->face[p].t[1].y=Noeud[1]->face[p-1].t[2].y;
			  Noeud[1]->face[p].t[1].z=Noeud[1]->face[p-1].t[2].z;
			}
		      if(t==0)
			{
			  fread(&(Noeud[1]->face[p].t[0].x),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[0].y),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[0].z),sizeof(float),1,fIn);
			  fseek(fIn,sizeof(float)*2,SEEK_CUR);
			  y++;
			  fread(&(Noeud[1]->face[p].t[1].x),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[1].y),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[1].z),sizeof(float),1,fIn);
			  fseek(fIn,sizeof(float)*2,SEEK_CUR);
			  y++;
			  fread(&(Noeud[1]->face[p].t[2].x),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[2].y),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[2].z),sizeof(float),1,fIn);
			  fseek(fIn,sizeof(float)*2,SEEK_CUR);
			  t=1;
			  logOut("Attention : incompatibilité de format lors de la création de l'arbre BSP !\n");
			}
		    }
		  else
		    {
		      fread(&(Noeud[1]->face[p].t[0].x),sizeof(float),1,fIn);
		      fread(&(Noeud[1]->face[p].t[0].y),sizeof(float),1,fIn);
		      fread(&(Noeud[1]->face[p].t[0].z),sizeof(float),1,fIn);
		      fseek(fIn,sizeof(float)*2,SEEK_CUR);
		      y++;
		      fread(&(Noeud[1]->face[p].t[1].x),sizeof(float),1,fIn);
		      fread(&(Noeud[1]->face[p].t[1].y),sizeof(float),1,fIn);
		      fread(&(Noeud[1]->face[p].t[1].z),sizeof(float),1,fIn);
		      fseek(fIn,sizeof(float)*2,SEEK_CUR);
		      y++;
		      fread(&(Noeud[1]->face[p].t[2].x),sizeof(float),1,fIn);
		      fread(&(Noeud[1]->face[p].t[2].y),sizeof(float),1,fIn);
		      fread(&(Noeud[1]->face[p].t[2].z),sizeof(float),1,fIn);
		      fseek(fIn,sizeof(float)*2,SEEK_CUR);
		      
		      if(type=='Q')
			{
			  p++;
			  y++;
			  fread(&(Noeud[1]->face[p].t[0].x),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[0].y),sizeof(float),1,fIn);
			  fread(&(Noeud[1]->face[p].t[0].z),sizeof(float),1,fIn);
			  fseek(fIn,sizeof(float)*2,SEEK_CUR);
			  Noeud[1]->face[p].t[1].x=Noeud[1]->face[p-1].t[0].x;
			  Noeud[1]->face[p].t[1].y=Noeud[1]->face[p-1].t[0].y;
			  Noeud[1]->face[p].t[1].z=Noeud[1]->face[p-1].t[0].z;
			  Noeud[1]->face[p].t[2].x=Noeud[1]->face[p-1].t[2].x;
			  Noeud[1]->face[p].t[2].y=Noeud[1]->face[p-1].t[2].y;
			  Noeud[1]->face[p].t[2].z=Noeud[1]->face[p-1].t[2].z;
			}
		    }
		}
	      else
		{
		  fseek(fIn,sizeof(float)*5,SEEK_CUR);
		  break;
		}
	    }
	}
      fclose(fIn);
    
      // Définition des Limites
      
      this->MapLimits[MAPLIMITSUP]=getRealFromMadMap(MAPURL,'B',2);
      this->MapLimits[MAPLIMITSDOWN]=getRealFromMadMap(MAPURL,'B',1);
      this->MapLimits[MAPLIMITSTOP]=getRealFromMadMap(MAPURL,'B',4);
      this->MapLimits[MAPLIMITSBOTTOM]=getRealFromMadMap(MAPURL,'B',3);
      this->MapLimits[MAPLIMITSRIGHT]=getRealFromMadMap(MAPURL,'B',6);
      this->MapLimits[MAPLIMITSLEFT]=getRealFromMadMap(MAPURL,'B',5);

      this->MapLimitsGraph[MAPLIMITSUP]=getMaxX(Noeud[1]->face,Noeud[1]->nb_face);
      this->MapLimitsGraph[MAPLIMITSDOWN]=getMinX(Noeud[1]->face,Noeud[1]->nb_face);
      this->MapLimitsGraph[MAPLIMITSTOP]=getMaxY(Noeud[1]->face,Noeud[1]->nb_face);
      this->MapLimitsGraph[MAPLIMITSBOTTOM]=getMinY(Noeud[1]->face,Noeud[1]->nb_face);
      this->MapLimitsGraph[MAPLIMITSRIGHT]=getMaxZ(Noeud[1]->face,Noeud[1]->nb_face);
      this->MapLimitsGraph[MAPLIMITSLEFT]=getMinZ(Noeud[1]->face,Noeud[1]->nb_face);
      
      
      segmentNoeud(1,'x',getMinX(Noeud[1]->face,Noeud[1]->nb_face), getMaxX(Noeud[1]->face,Noeud[1]->nb_face));
      
      float liq=getRealFromMadMap(MAPURL, 'L',1);
      float liqmin=getRealFromMadMap(MAPURL, 'L',2);
      float liqmax=getRealFromMadMap(MAPURL, 'L',3);

      this->Climat=new cl_climat(liq,liqmin,liqmax,MAPCLIMAT);

      logOut("  [OK] Construction de l'arbre BSP réussie (x noeuds)\n");//,nb_noeud);
    }
}

cl_bsp* MapColl;

// Destructeur
cl_bsp::~cl_bsp(void)
{
  // Si l'arbre existe
  if(this->Noeud!=NULL&&nb_noeud>0)
    {
      // On détruit tous les noeuds
      for(int i=1 ; i<this->nb_noeud ; i++)
	{
	  if(this->Noeud[i]!=NULL)
	    delete this->Noeud[i];
	}
      // On détruit l'arbre
      delete this->Noeud;
    }
  delete this->Climat;
}

float getMinX(Cvf F [], int nbF)
{
	float min=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].x<min) min=F[i].t[0].x;
		if(F[i].t[1].x<min) min=F[i].t[1].x;
		if(F[i].t[2].x<min) min=F[i].t[2].x;
	}
	return min;
}
float getMaxX(Cvf F [], int nbF)
{
	float max=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].x>max) max=F[i].t[0].x;
		if(F[i].t[1].x>max) max=F[i].t[1].x;
		if(F[i].t[2].x>max) max=F[i].t[2].x;
	}
	return max;
}

float getMinY(Cvf F [], int nbF)
{
	float min=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].y<min) min=F[i].t[0].y;
		if(F[i].t[1].y<min) min=F[i].t[1].y;
		if(F[i].t[2].y<min) min=F[i].t[2].y;
	}
	return min;
}
float getMaxY(Cvf F [], int nbF)
{
	float max=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].y>max) max=F[i].t[0].y;
		if(F[i].t[1].y>max) max=F[i].t[1].y;
		if(F[i].t[2].y>max) max=F[i].t[2].y;
	}
	return max;
}

float getMinZ(Cvf F [], int nbF)
{
	float min=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].z<min) min=F[i].t[0].z;
		if(F[i].t[1].z<min) min=F[i].t[1].z;
		if(F[i].t[2].z<min) min=F[i].t[2].z;
	}
	return min;
}
float getMaxZ(Cvf F [], int nbF)
{
	float max=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].z>max) max=F[i].t[0].z;
		if(F[i].t[1].z>max) max=F[i].t[1].z;
		if(F[i].t[2].z>max) max=F[i].t[2].z;
	}
	return max;
}

float getSizeX(Cvf F [], int nbF)
{
	return valAbs(getMaxX(F,nbF)-getMinX(F,nbF));
}
float getSizeY(Cvf F [], int nbF)
{
	return valAbs(getMaxY(F,nbF)-getMinY(F,nbF));
}
float getSizeZ(Cvf F [], int nbF)
{
	return valAbs(getMaxZ(F,nbF)-getMinZ(F,nbF));
}

float getMedianeX(Cvf F [], int nbF)
{
	return getMinX(F,nbF)+(getSizeX(F,nbF)/2);
}
float getMedianeY(Cvf F [], int nbF)
{
	return getMinZ(F,nbF)+(getSizeZ(F,nbF)/2);
}
float getMedianeZ(Cvf F [], int nbF)
{
	return getMinZ(F,nbF)+(getSizeZ(F,nbF)/2);
}
