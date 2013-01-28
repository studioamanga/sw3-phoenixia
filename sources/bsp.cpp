/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* bsp.cpp **** auteur : Vincent Tourraine ***********
**                                                         **
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
	delete this->face;
}

// Classe d'un arbre BSP
class cl_bsp
{
	private :
		// Nombre de noeuds
		int nb_noeud;
		// Tableaux de l'ensemble des noeuds
		noeud ** Noeud;
	public :
		// Permet de situer un vertex dans l'arbre et de tester les faces
		bool explorer(vertex p, float rayon);
		// Test d'un noeud pour l'exploration
		bool testNoeud(int id, vertex p, float rayon);
		// Test de la collision
		bool test(vertex p, float rayon, int target);
		// Segmenter un noeud
		bool segmentNoeud(int id, char Axe, float Min, float Max);
		// Constructeur
		cl_bsp(char * name);
		// Destructeur
		~cl_bsp(void);
};

// Test d'un noeud pour l'exploration
bool cl_bsp::testNoeud(int id, vertex p, float rayon)
{
	int target=1;
	if(this->Noeud[id]->axe!='0')
	{
		if(this->Noeud[id]->axe=='x')
		{
			if(p.x<this->Noeud[id]->med)
				target=id*2;
			else
				target=(id*2)+1;
		}
		if(this->Noeud[id]->axe=='y')
		{
			if(p.y<this->Noeud[id]->med)
				target=id*2;
			else
				target=(id*2)+1;
		}
		if(this->Noeud[id]->axe=='z')
		{
			if(p.z<this->Noeud[id]->med)
				target=id*2;
			else
				target=(id*2)+1;
		}
		if(this->testNoeud(target,p,rayon)==true)
			return true;
	}
	else
	{
		if(this->test(p,rayon,id)==true)
			return true;
	}

	return false;
}

// Permet de situer un vertex dans l'arbre et de tester les faces
bool cl_bsp::explorer(vertex p, float rayon)
{
	return this->testNoeud(1,p,rayon);
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
			if(this->Noeud[id]->face[i].t[4].x<Med)
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
			if(this->Noeud[id]->face[i].t[4].y<Med)
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
			if(this->Noeud[id]->face[i].t[4].z<Med)
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
			if(this->Noeud[id]->face[i].t[4].x<Med)
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
			if(this->Noeud[id]->face[i].t[4].y<Med)
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
			if(this->Noeud[id]->face[i].t[4].z<Med)
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

			this->Noeud[id*2]->face[nbG-1].t[3].x=this->Noeud[id]->face[i].t[3].x;
			this->Noeud[id*2]->face[nbG-1].t[3].y=this->Noeud[id]->face[i].t[3].y;
			this->Noeud[id*2]->face[nbG-1].t[3].z=this->Noeud[id]->face[i].t[3].z;
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

			this->Noeud[(id*2)+1]->face[nbD-1].t[3].x=this->Noeud[id]->face[i].t[3].x;
			this->Noeud[(id*2)+1]->face[nbD-1].t[3].y=this->Noeud[id]->face[i].t[3].y;
			this->Noeud[(id*2)+1]->face[nbD-1].t[3].z=this->Noeud[id]->face[i].t[3].z;
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
bool cl_bsp::test(vertex p, float rayon, int target)
{
	for(int y=0 ; y<Noeud[target]->nb_face ; y++)
	{
	if(SpherePolygonCollision(Noeud[target]->face[y].t, p, 4, rayon))
		{
			return true;
		}
	}

	return false;
}

// Constructeur qui prend comme argument le nom du fichier
cl_bsp::cl_bsp(char * name)
{
	// Initialisation nulle de l'arbre
	nb_noeud=0;
	Noeud=NULL;

	FILE* fIn=fopen(name,"r");
	if(fIn==NULL)
	{
		printf("Echec lors de la création du BSP :\nModel inexistant\n");
	}
	{
		// Controle de format
		unsigned char id;
		fread(&id,sizeof(unsigned char),1,fIn);
		if(id!=136)
		{
			printf("Echec lors de la création du BSP :\nModel incorrect\n");
			return;
		}
		fseek(fIn,sizeof(char)+sizeof(float)*5,SEEK_CUR);
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
				if(missX<missMin) missMin=missX;
				if(missX>missMax) missMax=missX;
				fseek(fIn, sizeof(float)*4, SEEK_CUR);
			}
			if(type=='L') nb_vertices=(nb_vertices)+(nb_vertices/3);
			if(type=='T') nb_vertices=(nb_vertices-2)*4;
			nbV+=nb_vertices;
		}

		nbV/=4;

		nb_noeud=((missMax-missMin)/200);
		nb_noeud=(nb_noeud*nb_noeud*nb_noeud);
		Noeud=new noeud*[nb_noeud];
		Noeud[0]=NULL;
		Noeud[1]=new noeud;
		Noeud[1]->nb_face=nbV;
		Noeud[1]->face=new Cvf[nbV];

		fseek(fIn, sizeof(char)*2+sizeof(float)*5+sizeof(int), SEEK_SET);
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
			if(type=='T')
			{
				if(t==1)
				{
			fread(&(Noeud[1]->face[p].t[3].x),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[3].y),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[3].z),sizeof(float),1,fIn);
			fseek(fIn,sizeof(float)*2,SEEK_CUR);
			Noeud[1]->face[p].t[1].x=Noeud[1]->face[p-1].t[2].x;
			Noeud[1]->face[p].t[1].y=Noeud[1]->face[p-1].t[2].y;
			Noeud[1]->face[p].t[1].z=Noeud[1]->face[p-1].t[2].z;
			Noeud[1]->face[p].t[2].x=Noeud[1]->face[p-1].t[3].x;
			Noeud[1]->face[p].t[2].y=Noeud[1]->face[p-1].t[3].y;
			Noeud[1]->face[p].t[2].z=Noeud[1]->face[p-1].t[3].z;
			Noeud[1]->face[p].t[0].x=Noeud[1]->face[p].t[1].x;
			Noeud[1]->face[p].t[0].y=Noeud[1]->face[p].t[1].y;
			Noeud[1]->face[p].t[0].z=Noeud[1]->face[p].t[1].z;
				}
				if(t==0)
				{
			fread(&(Noeud[1]->face[p].t[1].x),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[1].y),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[1].z),sizeof(float),1,fIn);
			fseek(fIn,sizeof(float)*2,SEEK_CUR);
			y++;
			fread(&(Noeud[1]->face[p].t[2].x),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[2].y),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[2].z),sizeof(float),1,fIn);
			fseek(fIn,sizeof(float)*2,SEEK_CUR);
			y++;
			fread(&(Noeud[1]->face[p].t[3].x),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[3].y),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[3].z),sizeof(float),1,fIn);
			fseek(fIn,sizeof(float)*2,SEEK_CUR);
			Noeud[1]->face[p].t[0].x=Noeud[1]->face[p].t[1].x;
			Noeud[1]->face[p].t[0].y=Noeud[1]->face[p].t[1].y;
			Noeud[1]->face[p].t[0].z=Noeud[1]->face[p].t[1].z;
			t=1;
			printf("Attention : incompatibilité de format lors de la création de l'arbre BSP !\n");
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
			y++;
			fread(&(Noeud[1]->face[p].t[3].x),sizeof(float),1,fIn);
			fread(&(Noeud[1]->face[p].t[3].y),sizeof(float),1,fIn);				fread(&(Noeud[1]->face[p].t[3].z),sizeof(float),1,fIn);
			fseek(fIn,sizeof(float)*2,SEEK_CUR);
			}
			if(type=='L')
			{
			Noeud[1]->face[p].t[3].x=Noeud[1]->face[p].t[2].x;
			Noeud[1]->face[p].t[3].y=Noeud[1]->face[p].t[2].y;
			Noeud[1]->face[p].t[3].z=Noeud[1]->face[p].t[2].z;
			}

			}
			}
		}
		fclose(fIn);


		segmentNoeud(1,'x',getMinX(Noeud[1]->face,Noeud[1]->nb_face), getMaxX(Noeud[1]->face,Noeud[1]->nb_face));


		printf("  [OK] Construction de l'arbre BSP réussie (%d noeuds)\n",nb_noeud);
	}
}

cl_bsp* MapColl;

// Destructeur
cl_bsp::~cl_bsp(void)
{
	// Si l'arbre existe
	if(this->Noeud!=NULL)
	{
		// On détruit tous les noeuds
		for(int i=0 ; i<this->nb_noeud ; i++)
		{
			delete this->Noeud[i];
		}
		// On détruit l'arbre
		delete this->Noeud;
	}
}

float getMinX(Cvf F [], int nbF)
{
	float min=0;
	for(int i=0 ; i<nbF ; i++)
	{
		if(F[i].t[0].x<min) min=F[i].t[0].x;
		if(F[i].t[1].x<min) min=F[i].t[1].x;
		if(F[i].t[2].x<min) min=F[i].t[2].x;
		if(F[i].t[3].x<min) min=F[i].t[3].x;
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
		if(F[i].t[3].x>max) max=F[i].t[3].x;
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
		if(F[i].t[3].y<min) min=F[i].t[3].y;
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
		if(F[i].t[3].y>max) max=F[i].t[3].y;
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
		if(F[i].t[3].z<min) min=F[i].t[3].z;
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
		if(F[i].t[3].z>max) max=F[i].t[3].z;
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
