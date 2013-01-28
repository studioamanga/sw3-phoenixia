/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
************************** S_MAD ****************************
*************************************************************
**                                                         **
****** fonctions.hpp **** auteur : Vincent Tourraine ********
**                                                         **
**                                                         **
*************************************************************/

#define PI 3.1415926535897932

void New(void)
{
  madModel* M=loadMadModel("track.mad");
  Vertex3f V[21]={{-375,100,-500},
		  {-200,100,-500},
		  {0,75,-300},
		  {120,75,50},
		  {575,10,575}, // 4
		  {700,0,500},
		  {700,0,-425},
		  {450,0,-740},
		  {225,0,-740},
		  {125,0,-550}, // 9
		  {125,-20,50},
		  {-250,-120,375},
		  {-375,-120,375},
		  {-750,-150,0},
		  {-500,-150,-325}, // 14
		  {-425,-100,-250},
		  {-425,-50,-150},
		  {-500,0,-75},
		  {-575,50,-150},
		  {-575,100,-250},
		  {-375,100,-500}};
  Vertex3f V2[21]={{1,1,30},
		   {1.5,1.5,-45},
		   {1.5,1.5,-90},
		   {1.5,1.5,-45},
		   {1.5,1.5,0},
		   {3,1,40},//5
		   {3,1,110},
		   {3,1,160},
		   {3,1,200},
		   {1.5,1.5,250},
		   {1.5,1.5,260},//10
		   {1.5,1.5,200},
		   {3,2,160},
		   {3,2,90},
		   {3,2,0},
		   {3,2,-45},//15
		   {3,2,-135},
		   {3,2,-180},
		   {3,2,-225},
		   {3,2,-315},
		   {1,1,30}};
  Vertex3f Mot[4]={{-10,0,0},
		   {-10,8,0.195},
		   {10,8,0.508},
		   {10,0,0.703}};
  madAddTunnel(M, 4, Mot, "data/texture/wall/track.tga", 0.2, 0.75, 21, V, V2);
  Mot[0].x=-10;
  Mot[0].y=-0.5;
  Mot[0].z=0.703;
  Mot[1].x=0;
  Mot[1].y=-9;
  Mot[1].z=1;
  Mot[2].x=10;
  Mot[2].y=-0.5;
  Mot[2].z=0.703;
  madAddTunnel(M, 3, Mot, "data/texture/wall/track.tga", 0.5, 0.75, 21, V, V2);
  saveMadModel(M);
  delMadModel(M);
/*
	printf("Nouveau modèle\n");
	Model* M=new Model;

	printf("Entrez le type d'animation du modèle : ( S-Shoker / autre-no anim )\n");
	scanf("%c",&(M->typeAnim));
	scanf("%c",&(M->typeAnim));


	printf("Entrez le nombre d'objet du modèle :\n");

	scanf("%d",&(M->nbObjets));
	M->Objets=(sObjet *)malloc(sizeof(sObjet)*M->nbObjets);
	for( int y=0 ; y<M->nbObjets ; y++ )
	{
		printf("* Objet n%d *\n",y+1);
		printf("Entrez le nom de la texture :\n");
		char c;
		scanf("%c",&c);
		scanf("%[^'\n']",M->Objets[y]->texture);
		scanf("%c",&c);
		printf("Entrez le type de surface ( Q-QUADS / T-TRIANGLE_STRIP ) :\n");
		M->Objets[y]->surfacetype=getchar();
		printf("Entrez le nombre de vertices :\n");
		scanf("%d",&M->Objets[y]->nb_vertices);
		M->Objets[y]->vertices=new vertex*[M->Objets[y]->nb_vertices];
		for( int t=0 ; t<M->Objets[y]->nb_vertices ; t++)
		{
			M->Objets[y]->vertices[t]=new vertex;
			printf("* Vertex n%d de l'objet n%d *\n",t+1, y+1);
			printf("Coordonnees en X du vertex : ");
			scanf("%f",&(M->Objets[y]->vertices[t]->p.x));
			printf("Coordonnees en Y du vertex : ");
			scanf("%f",&(M->Objets[y]->vertices[t]->p.y));
			printf("Coordonnees en Z du vertex : ");
			scanf("%f",&(M->Objets[y]->vertices[t]->p.z));
			printf("Coordonnees de la texture en X : ");
			scanf("%f",&(M->Objets[y]->vertices[t]->text.x));
			printf("Coordonnees de la texture en Y : ");
			scanf("%f",&(M->Objets[y]->vertices[t]->text.y));

			printf("Confirmez le vertex (%f,%f,%f,%f,%f)? Y/N \n",M->Objets[y]->vertices[t]->p.x,M->Objets[y]->vertices[t]->p.y,M->Objets[y]->vertices[t]->p.z,M->Objets[y]->vertices[t]->text.x,M->Objets[y]->vertices[t]->text.y);

			char cha;
			scanf("%c",&cha);
			scanf("%c",&cha);

			if(cha!='N'&&cha!='n')
			{
			}
			else
			{
				t--;
			}
		}

	}

	// Enregistrement du modèle
	printf("Entrez le nom du modèle :\n");
	char ch, url[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	strcat(url,".mad");

	FILE* fOut=fopen(url,"w");
	unsigned char id= 136;
	fwrite(&id,sizeof(unsigned char),1,fOut);
	int nbtag=0;
	fwrite(&nbtag,sizeof(int),1,fOut);
	fwrite(&(M->typeAnim),sizeof(char),1,fOut);
	fwrite(&(M->nbObjets),sizeof(int),1,fOut);
	for (int o=0 ; o<M->nbObjets ; o++)
	{
		fwrite(M->Objets[o]->texture,sizeof(char),50,fOut);
		fwrite(&(M->Objets[o]->surfacetype),sizeof(char),1,fOut);
		fwrite(&(M->Objets[o]->nb_vertices),sizeof(int),1,fOut);
		for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
		{
			fwrite(&(M->Objets[o]->vertices[p]->p.x),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->p.y),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->p.z),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->text.x),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->text.y),sizeof(float),1,fOut);
		}
	}
	fclose(fOut);
	
	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nbObjets ; i++)
	{
		for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
		delete M->Objets[i]->vertices;
		delete M->Objets[i];
	}

	delete M;
	return;*/
}

void Mix(void)
{/*
	printf("Mixeur de modèle\n");
	Model* M=new Model;

	printf("Entrez le type d'animation du modèle : ( S-Shoker / autre-no anim )\n");
	scanf("%c",&(M->typeAnim));
	scanf("%c",&(M->typeAnim));


	printf("Entrez le nom du premier model :\n");
	char cha, urli[50];
	scanf("%c",&cha);
	scanf("%[^'\n']",&urli);
	strcat(urli,".mad");
	printf("Entrez le nom du second model :\n");
	char chu, urly[50];
	scanf("%c",&chu);
	scanf("%[^'\n']",&urly);
	strcat(urly,".mad");

	FILE* fIn1=fopen(urli,"r");
	FILE* fIn2=fopen(urly,"r");

	if(fIn1==NULL||fIn2==NULL)
	{
		printf("Erreur : model inexistant !\n");
	}
	else
	{
	unsigned char id1, id2;
	fread(&id1,sizeof(unsigned char),1,fIn1);
	fread(&id2,sizeof(unsigned char),1,fIn2);
	if(id1!=136||id2!=136)
	{
		printf("Erreur : model incorrect !\n");
	}
	{
		fseek(fIn1,sizeof(char)+sizeof(int),SEEK_CUR);
		fseek(fIn2,sizeof(char)+sizeof(int),SEEK_CUR);

		int nbSurf1, nbSurf2;
		fread(&nbSurf1,sizeof(int),1,fIn1);
		fread(&nbSurf2,sizeof(int),1,fIn2);
		M->nbObjets=nbSurf1+nbSurf2;

	M->Objets=(sObjet *)malloc(sizeof(sObjet)*M->nbObjets);
	for(int i1=0 ; i1<nbSurf1 ; i1++)
	{
		fread(&(M->Objets[i1]->texture),sizeof(char),50,fIn1);
		fread(&(M->Objets[i1]->surfacetype),sizeof(char),1,fIn1);
		fread(&(M->Objets[i1]->nb_vertices),sizeof(int),1,fIn1);
		M->Objets[i1]->vertices=new vertex*[M->Objets[i1]->nb_vertices];
	for (int i11=0 ; i11<M->Objets[i1]->nb_vertices ; i11++)
	{
		M->Objets[i1]->vertices[i11]=new vertex;
		fread(&(M->Objets[i1]->vertices[i11]->p.x),sizeof(float),1,fIn1);
		fread(&(M->Objets[i1]->vertices[i11]->p.y),sizeof(float),1,fIn1);
		fread(&(M->Objets[i1]->vertices[i11]->p.z),sizeof(float),1,fIn1);
		fread(&(M->Objets[i1]->vertices[i11]->text.x),sizeof(float),1,fIn1);
		fread(&(M->Objets[i1]->vertices[i11]->text.y),sizeof(float),1,fIn1);
	}
	}
	for(int i2=nbSurf1 ; i2<M->nbObjets ; i2++)
	{
		fread(&(M->Objets[i2]->texture),sizeof(char),50,fIn2);
		fread(&(M->Objets[i2]->surfacetype),sizeof(char),1,fIn2);
		fread(&(M->Objets[i2]->nb_vertices),sizeof(int),1,fIn2);
		M->Objets[i2]->vertices=new vertex*[M->Objets[i2]->nb_vertices];
	for (int i21=0 ; i21<M->Objets[i2]->nb_vertices ; i21++)
	{
		M->Objets[i2]->vertices[i21]=new vertex;
		fread(&(M->Objets[i2]->vertices[i21]->p.x),sizeof(float),1,fIn2);
		fread(&(M->Objets[i2]->vertices[i21]->p.y),sizeof(float),1,fIn2);
		fread(&(M->Objets[i2]->vertices[i21]->p.z),sizeof(float),1,fIn2);
		fread(&(M->Objets[i2]->vertices[i21]->text.x),sizeof(float),1,fIn2);
		fread(&(M->Objets[i2]->vertices[i21]->text.y),sizeof(float),1,fIn2);
	}
	}

			fclose(fIn1);
			fclose(fIn2);
		}
		}



	// Enregistrement du modèle
	printf("Entrez le nom du modèle :\n");
	char ch, url[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	strcat(url,".mad");

	FILE* fOut=fopen(url,"w");
	unsigned char id= 136;
	fwrite(&id,sizeof(unsigned char),1,fOut);
	int nbtag=0;
	fwrite(&nbtag,sizeof(int),1,fOut);
	fwrite(&(M->typeAnim),sizeof(char),1,fOut);
	fwrite(&(M->nbObjets),sizeof(int),1,fOut);
	for (int o=0 ; o<M->nbObjets ; o++)
	{
		fwrite(M->Objets[o]->texture,sizeof(char),50,fOut);
		fwrite(&(M->Objets[o]->surfacetype),sizeof(char),1,fOut);
		fwrite(&(M->Objets[o]->nb_vertices),sizeof(int),1,fOut);
		for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
		{
			fwrite(&(M->Objets[o]->vertices[p]->p.x),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->p.y),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->p.z),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->text.x),sizeof(float),1,fOut);
			fwrite(&(M->Objets[o]->vertices[p]->text.y),sizeof(float),1,fOut);
		}
	}
	fclose(fOut);

	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nbObjets ; i++)
	{
		for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
		delete M->Objets[i]->vertices;
		delete M->Objets[i];
	}

	delete M;
	return;*/
}

void Export(void)
{/*
	Model* M=new Model;

	printf("Exportateur de model au format View&Edit Mad\nEntrez le nom du fichier à exporter :\n");

	char ch, url[50], url2[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	strcpy(url2,url);
	strcat(url,".mad");
	strcat(url2,".vem");
	
	FILE* fIn=fopen(url,"r");
	if(fIn==NULL)
	{
		printf("Model inexistant !\n");
		return;
	}
	unsigned char id;
	fread(&id,sizeof(unsigned char),1,fIn);
	if(id!=136)
	{
		printf("Model incorrect !\n");
		return;
	}
	int nbtag=0;
	fread(&nbtag,sizeof(int),1,fIn);
	fread(&(M->typeAnim),sizeof(char),1,fIn);
	fread(&(M->nbObjets),sizeof(int),1,fIn);

	M->Objets=(sObjet *)malloc(sizeof(sObjet)*M->nbObjets);
	for (int o=0 ; o<M->nbObjets ; o++)
	{
	  fread(M->Objets[o]->texture,sizeof(char),50,fIn);
	  fread(&(M->Objets[o]->surfacetype),sizeof(char),1,fIn);
	  fread(&(M->Objets[o]->nb_vertices),sizeof(int),1,fIn);
	  M->Objets[o]->vertices=new vertex*[M->Objets[o]->nb_vertices];
	  for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
	    {
	      M->Objets[o]->vertices[p]=new vertex;
	      fread(&(M->Objets[o]->vertices[p]->p.x),sizeof(float),1,fIn);
	      fread(&(M->Objets[o]->vertices[p]->p.y),sizeof(float),1,fIn);
	      fread(&(M->Objets[o]->vertices[p]->p.z),sizeof(float),1,fIn);
	      fread(&(M->Objets[o]->vertices[p]->text.x),sizeof(float),1,fIn);
	      fread(&(M->Objets[o]->vertices[p]->text.y),sizeof(float),1,fIn);
	    }
	}
	fclose(fIn);

	// Sauvegarde de l'exportation
	ofstream fOut(url2);
	if(!fOut)
	{
		printf("Erreur lors de l'exportation !\n");
		return;
	}
	nbtag=0;
	fOut<<nbtag<<endl;
	fOut<<M->typeAnim<<endl;
	fOut<<M->nbObjets<<endl;
	for (int i=0 ; i<M->nbObjets ; i++)
	{
		fOut<<"_##_Nouvelle_surface\n";
		fOut<<M->Objets[i]->texture<<endl;
		fOut<<M->Objets[i]->surfacetype<<endl;
		fOut<<M->Objets[i]->nb_vertices<<endl;

		for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )
		{
			fOut<<"_#_Nouveau_vertex\n";
			fOut<<M->Objets[i]->vertices[u]->p.x<<endl;
			fOut<<M->Objets[i]->vertices[u]->p.y<<endl;
			fOut<<M->Objets[i]->vertices[u]->p.z<<endl;
			fOut<<M->Objets[i]->vertices[u]->text.x<<endl;
			fOut<<M->Objets[i]->vertices[u]->text.y<<endl;
		}
	}
	fOut.close();


	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nbObjets ; i++)
	{
		for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
		delete M->Objets[i]->vertices;
		delete M->Objets[i];
	}

	delete M;

	return;*/
}

#define sX (maxx-minx)
#define sY (maxy-miny)

void Generate(void)
{/*
	Model* M=new Model;

	printf("Générateur de modèle.\nEntrez le nom du fichier à générer :\n");

	char ch, url[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	strcat(url,".vem");

	
	// Sauvegarde de l'exportation
	ofstream fOut(url);
	if(!fOut)
	{
		printf("Erreur lors de la création !\n");
		return;
	}
	int nbtag=1;
	fOut<<nbtag<<endl;
	M->typeAnim='0';
	fOut<<M->typeAnim<<endl;
	M->nbObjets=1;
	fOut<<M->nbObjets<<endl;
	M->Objets=(sObjet *)malloc(sizeof(sObjet)*M->nbObjets);
	
	for (int i=0 ; i<M->nbObjets ; i++)
	{
	  fOut<<"_##_Nouvelle_surface\n";
	  cout<<"Entrez le nom de la texture :"<<endl;
	  cin >> M->Objets[i]->texture;
	  fOut<<M->Objets[i]->texture<<endl;
	  M->Objets[i]->surfacetype='Q';
	  fOut<<M->Objets[i]->surfacetype<<endl;
	  cout<<"Entrez les limites min/max en x/y :"<<endl;
	  int minx,maxx,miny,maxy,minz,maxz;
	  cin >> minx >> maxx >> miny >> maxy;
	  cout<<"Entrez l'échelle des hauteurs :"<<endl;
	  int scalz, scalx, scaly;
	  cin >> scalz ;
	  cout<<"Entrez l'échelle de la texture x/y :"<<endl;
	  int tx,ty;
	  cin >> tx >> ty ;
	  cout<<"Entrez le nombre tile en x et y :"<<endl;
	  int L,C;
	  cin >> L >> C;
	  scalx=maxx-minx/(C);
	  scaly=maxy-miny/(L);
	  cout<<"Entrez la grille des hauteurs"<<endl;
	  int tab[100][100];
	  for(int c=0;c<(C+1);c++)
	    {
	      for(int l=0;l<(L+1);l++)
		{
		  cin >> tab[c][l];
		}
	    }
	  M->Objets[i]->nb_vertices=((C)*(L)*4)+16;
	  fOut<<M->Objets[i]->nb_vertices<<endl;

	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+1<<endl;
	  fOut<<tab[0][0]*scalz<<endl;
	  fOut<<miny+1<<endl;
	  fOut<<0<<endl;
	  fOut<<0<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+1<<endl;
	  fOut<<tab[C][0]*scalz<<endl;
	  fOut<<miny+(C*scaly)<<endl;
	  fOut<<0<<endl;
	  fOut<<C*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-10*sX<<endl;
	  fOut<<tab[C][0]*scalz<<endl;
	  fOut<<miny+10*sY<<endl;
	  fOut<<-10*L*tx<<endl;
	  fOut<<C*ty+C*10*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-10*sX<<endl;
	  fOut<<tab[0][0]*scalz<<endl;
	  fOut<<miny-10*sY<<endl;
	  fOut<<-10*L*tx<<endl;
	  fOut<<-C*10*ty<<endl;

	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+1<<endl;
	  fOut<<tab[0][0]*scalz<<endl;
	  fOut<<miny+1<<endl;
	  fOut<<0<<endl;
	  fOut<<0<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-1+(L*scalx)<<endl;
	  fOut<<tab[0][L]*scalz<<endl;
	  fOut<<miny+1<<endl;
	  fOut<<L*tx<<endl;
	  fOut<<0<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+(L*scalx)+10*sX<<endl;
	  fOut<<tab[0][L]*scalz<<endl;
	  fOut<<miny-10*sY<<endl;
	  fOut<<L*tx+10*L*tx<<endl;
	  fOut<<-C*10*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-10*sX<<endl;
	  fOut<<tab[0][0]*scalz<<endl;
	  fOut<<miny-10*sY<<endl;
	  fOut<<-10*L*tx<<endl;
	  fOut<<-C*10*ty<<endl;

	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-1+(L*scalx)<<endl;
	  fOut<<tab[0][L]*scalz<<endl;
	  fOut<<miny+1<<endl;
	  fOut<<L*tx<<endl;
	  fOut<<0<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-1+(L*scalx)<<endl;
	  fOut<<tab[C][L]*scalz<<endl;
	  fOut<<miny-1+(C*scaly)<<endl;
	  fOut<<L*tx<<endl;
	  fOut<<C*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+(L*scalx)+10*sX<<endl;
	  fOut<<tab[C][L]*scalz<<endl;
	  fOut<<miny+10*sY<<endl;
	  fOut<<L*tx+10*L*tx<<endl;
	  fOut<<C*ty+C*10*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+(L*scalx)+10*sX<<endl;
	  fOut<<tab[0][L]*scalz<<endl;
	  fOut<<miny-10*sY<<endl;
	  fOut<<L*tx+10*L*tx<<endl;
	  fOut<<-C*10*ty<<endl;
	  
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+1<<endl;
	  fOut<<tab[C][0]*scalz<<endl;
	  fOut<<miny-1+(C*scaly)<<endl;
	  fOut<<0<<endl;
	  fOut<<C*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-1+(L*scalx)<<endl;
	  fOut<<tab[C][L]*scalz<<endl;
	  fOut<<miny-1+(C*scaly)<<endl;
	  fOut<<L*tx<<endl;
	  fOut<<C*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx+(L*scalx)+10*sX<<endl;
	  fOut<<tab[C][L]*scalz<<endl;
	  fOut<<miny+10*sY<<endl;
	  fOut<<L*tx+10*L*tx<<endl;
	  fOut<<C*ty+C*10*ty<<endl;
	  fOut<<"_#_Nouveau_vertex\n";
	  fOut<<minx-10*sX<<endl;
	  fOut<<tab[C][0]*scalz<<endl;
	  fOut<<miny+10*sY<<endl;
	  fOut<<-10*L*tx<<endl;
	  fOut<<C*ty+C*10*ty<<endl;
		
	  for(int c=0;c<C;c++)
	    {
	      for(int l=0;l<L;l++)
		{
		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<minx+(l*scalx)<<endl;
		  fOut<<tab[c][l]*scalz<<endl;
		  fOut<<miny+(c*scaly)<<endl;
		  fOut<<l*tx<<endl;
		  fOut<<c*ty<<endl;
		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<minx+((l+1)*scalx)<<endl;
		  fOut<<tab[c][l+1]*scalz<<endl;
		  fOut<<miny+((c)*scaly)<<endl;
		  fOut<<(l+1)*tx<<endl;
		  fOut<<c*ty<<endl;
		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<minx+((l+1)*scalx)<<endl;
		  fOut<<tab[c+1][l+1]*scalz<<endl;
		  fOut<<miny+((c+1)*scaly)<<endl;
		  fOut<<(l+1)*tx<<endl;
		  fOut<<(c+1)*ty<<endl;
		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<minx+(l*scalx)<<endl;
		  fOut<<tab[c+1][l]*scalz<<endl;
		  fOut<<miny+((c+1)*scaly)<<endl;
		  fOut<<l*tx<<endl;
		  fOut<<(c+1)*ty<<endl;
		}
	    }
	  
	}
	fOut.close();


	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nbObjets ; i++)
	  {
	    for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
	    delete M->Objets[i]->vertices;
	    delete M->Objets[i];
	  }
	
	delete M;
	
	return;*/
}


void Shape(void)
{/*
	Model* M=new Model;

	printf("Shaper de modèle.\nEntrez le nom du fichier à générer :\n");

	char ch, url[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	strcat(url,".vem");

	
	// Sauvegarde de l'exportation
	ofstream fOut(url);
	if(!fOut)
	{
		printf("Erreur lors de la création !\n");
		return;
	}
	int nbtag=1;
	fOut<<nbtag<<endl;
	M->typeAnim='0';
	fOut<<M->typeAnim<<endl;
	M->nbObjets=1;
	fOut<<M->nbObjets<<endl;
	M->Objets=new surface*[M->nbObjets];
	
	for (int i=0 ; i<M->nbObjets ; i++)
	{
	  M->Objets[i]=new surface;
	  fOut<<"_##_Nouvelle_surface\n";
	  cout<<"Entrez le nom de la texture :"<<endl;
	  cin >> M->Objets[i]->texture;
	  fOut<<M->Objets[i]->texture<<endl;
	  M->Objets[i]->surfacetype='Q';
	  fOut<<M->Objets[i]->surfacetype<<endl;
	  float angy=-(PI/2);
	  M->Objets[i]->nb_vertices=0;
	  int resol=0;
	  float Rext=0, fTex=1;
	  cout<<"Résolution, Rayon, Facteur des textures :"<<endl;
	  cin>>resol>>Rext>>fTex;
	  for(int re=0 ; re<=(resol/2) ; re++)
	    {
	      float angx=0;
	      for(int Re=0 ; Re<resol ; Re++)
		{
		  angx+=((2*PI)/resol);
		  M->Objets[i]->nb_vertices+=4;
		}
	      angy+=((2*PI)/resol);
	    }
	  fOut<<M->Objets[i]->nb_vertices<<endl;
	  for(int re=0 ; re<=(resol/2) ; re++)
	    {
	      float angx=0;
	      for(int Re=0 ; Re<resol ; Re++)
		{
		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<cos(angx)*Rext*cos(angy)<<endl;
		  fOut<<sin(angy)*Rext<<endl;
		  fOut<<sin(angx)*Rext*cos(angy)<<endl;
		  fOut<<(angx/(2*PI)*fTex)<<endl;
		  fOut<<(angy+PI/2)/PI*fTex<<endl;
		  angx+=((2*PI)/resol);

		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<cos(angx)*Rext*cos(angy)<<endl;
		  fOut<<sin(angy)*Rext<<endl;
		  fOut<<sin(angx)*Rext*cos(angy)<<endl;
		  fOut<<(angx/(2*PI)*fTex)<<endl;
		  fOut<<(angy+PI/2)/PI*fTex<<endl;
		  angy+=((2*PI)/resol);

		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<cos(angx)*Rext*cos(angy)<<endl;
		  fOut<<sin(angy)*Rext<<endl;
		  fOut<<sin(angx)*Rext*cos(angy)<<endl;
		  fOut<<(angx/(2*PI)*fTex)<<endl;
		  fOut<<(angy+PI/2)/PI*fTex<<endl;
		  angx-=((2*PI)/resol);

		  fOut<<"_#_Nouveau_vertex\n";
		  fOut<<cos(angx)*Rext*cos(angy)<<endl;
		  fOut<<sin(angy)*Rext<<endl;
		  fOut<<sin(angx)*Rext*cos(angy)<<endl;
		  fOut<<(angx/(2*PI)*fTex)<<endl;
		  fOut<<(angy+PI/2)/PI*fTex<<endl;
		  angx+=((2*PI)/resol);
		  angy-=((2*PI)/resol);
		}
	      angy+=((2*PI)/resol);
	    }
	}
	fOut.close();


	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nbObjets ; i++)
	{
		for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
		delete M->Objets[i]->vertices;
		delete M->Objets[i];
	}

	delete M;

	return;*/
}

void Import(void)
{/*
  Model* M=new Model;

  printf("Importateur de model au format View&Edit Mad\nEntrez le nom du fichier à importer :\n");

  char ch, url[50], url2[50],tag;
  scanf("%c",&ch);
  scanf("%[^'\n']",&url);
  scanf("%[^'\n']",&url);
  strcpy(url2,url);
  strcat(url,".mad");
  strcat(url2,".vem");

  ifstream fIn(url2);
  if(!fIn)
    {
      printf("Model inexistant !\n");
      return;
    }
  int nbtag=0;
  fIn>>nbtag;

  fIn>>M->typeAnim;
  fIn>>M->nbObjets;
  M->Objets=new surface*[M->nbObjets];
  for (int o=0 ; o<M->nbObjets ; o++)
    {
      M->Objets[o]=new surface;
      char ets[40];
      fIn>>ets;
      fIn>>M->Objets[o]->texture;
      fIn>>M->Objets[o]->surfacetype;
      fIn>>M->Objets[o]->nb_vertices;
      M->Objets[o]->vertices=new vertex*[M->Objets[o]->nb_vertices];
      for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
	{
	  M->Objets[o]->vertices[p]=new vertex;
	  char etv[40];
	  fIn>>etv;
	  fIn>>M->Objets[o]->vertices[p]->p.x;
	  fIn>>M->Objets[o]->vertices[p]->p.y;
	  fIn>>M->Objets[o]->vertices[p]->p.z;
	  fIn>>M->Objets[o]->vertices[p]->text.x;
	  fIn>>M->Objets[o]->vertices[p]->text.y;
	}
    }
  for(int i=0 ; i<nbtag ; i++)
    {
      char type;
      fIn>>type;
      switch(type)
	{
	case 'W' :
	  M->tagW='W';
	  tag='W';
	  fIn>>M->taille;
	  fIn>>M->vit;
	  fIn>>M->dir;
	  fIn>>M->armure;
	  fIn>>M->att;
	  fIn>>M->nbColl;
	  M->Coll=new Cvf[M->nbColl];
	  for(int y=0 ; y<M->nbColl ; y++)
	    {
	      fIn>>M->Coll[y].t[0].x;
	      fIn>>M->Coll[y].t[0].y;
	      fIn>>M->Coll[y].t[0].z;
	      
	      fIn>>M->Coll[y].t[1].x;
	      fIn>>M->Coll[y].t[1].y;
	      fIn>>M->Coll[y].t[1].z;
	      
	      fIn>>M->Coll[y].t[2].x;
	      fIn>>M->Coll[y].t[2].y;
	      fIn>>M->Coll[y].t[2].z;
	    }
	  fIn>>M->Tir1.x;
	  fIn>>M->Tir1.y;
	  fIn>>M->Tir1.z;
	  
	  fIn>>M->Tir2.x;
	  fIn>>M->Tir2.y;
	  fIn>>M->Tir2.z;
	  
	  fIn>>M->descript;
	  break;
	  
	case 'M' :
	  M->tagM='M';
	  tag='M';
	  fIn>>M->name;
	  fIn>>M->nbClimat;
	  M->Climat=new sClimat[M->nbClimat];
	  for(int y=0 ; y<M->nbClimat ; y++)
	    {
	      fIn>>M->Climat[y].type;
	    }

	  fIn>>M->urlDrone;
	  fIn>>M->nbDrone;
	  M->Drone=new coord[M->nbDrone];
	  for(int y=0 ; y<M->nbDrone ; y++)
	    {
	      fIn>>M->Drone[y].x;
	      fIn>>M->Drone[y].y;
	      fIn>>M->Drone[y].z;
	    }

	  fIn>>M->urlShoker;
	  fIn>>M->nbShoker;
	  M->Shoker=new coord[M->nbShoker];
	  for(int y=0 ; y<M->nbShoker ; y++)
	    {
	      fIn>>M->Shoker[y].x;
	      fIn>>M->Shoker[y].y;
	      fIn>>M->Shoker[y].z;
	    }
	  fIn>>M->depart.x;
	  fIn>>M->depart.y;
	  fIn>>M->depart.z;

	  fIn>>M->yLiq;
	  fIn>>M->yLiqMin;
	  fIn>>M->yLiqMax;
	  fIn>>M->urlLiq;
	  fIn>>M->colorLiq[0];
	  fIn>>M->colorLiq[1];
	  fIn>>M->colorLiq[2];
	  fIn>>M->colorLiq[3];

	  fIn>>M->Limits[0];
	  fIn>>M->Limits[1];
	  fIn>>M->Limits[2];
	  fIn>>M->Limits[3];
	  fIn>>M->Limits[4];
	  fIn>>M->Limits[5];

	  fIn>>M->descript;
	  break;

	case 'D' :
	  M->tagD='D';
	  tag='D';
	  fIn>>M->nbDrone;
	  fIn>>M->type;
	  fIn>>M->taille;
	  break;

	case 'S' :
	  M->tagS='S';
	  tag='S';
	  fIn>>M->att;
	  fIn>>M->vit;
	  fIn>>M->armure;
	  fIn>>M->taille;
	  fIn>>M->type;
	  break;
	}
    }
  fIn.close();
  
  // Sauvegarde de l'importation
  FILE* fOut=fopen(url,"w");
  unsigned char id= 136;
  fwrite(&id,sizeof(unsigned char),1,fOut);
  fwrite(&nbtag,sizeof(int),1,fOut);

  fwrite(&(M->typeAnim),sizeof(char),1,fOut);	
  fwrite(&(M->nbObjets),sizeof(int),1,fOut);
  for (int o=0 ; o<M->nbObjets ; o++)
    {
      cout<<"Egaliser les textures ? (y/n)"<<endl;
      char rep;
      rep=0;
      cin>>rep;
      float facte=1;
      if(rep=='y')
	{
	  cout<<"Facteur de la texture :"<<endl;
	  cin>>facte;
	}

      fwrite(M->Objets[o]->texture,sizeof(char),50,fOut);
      fwrite(&(M->Objets[o]->surfacetype),sizeof(char),1,fOut);
      fwrite(&(M->Objets[o]->nb_vertices),sizeof(int),1,fOut);
      for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
	{
	  fwrite(&(M->Objets[o]->vertices[p]->p.x),sizeof(float),1,fOut);
	  fwrite(&(M->Objets[o]->vertices[p]->p.y),sizeof(float),1,fOut);
	  fwrite(&(M->Objets[o]->vertices[p]->p.z),sizeof(float),1,fOut);
	  if(rep=='y')
	    {
	      M->Objets[o]->vertices[p]->text.x=M->Objets[o]->vertices[p]->p.x*facte;
	      M->Objets[o]->vertices[p]->text.y=M->Objets[o]->vertices[p]->p.z*facte;
	    }
	  fwrite(&(M->Objets[o]->vertices[p]->text.x),sizeof(float),1,fOut);
	  fwrite(&(M->Objets[o]->vertices[p]->text.y),sizeof(float),1,fOut);
	}
    }
  fwrite(&tag,sizeof(char),1,fOut);
  if(M->tagW=='W')
    {
      fwrite(&(M->taille),sizeof(float),1,fOut);
      fwrite(&(M->vit),sizeof(float),1,fOut);
      fwrite(&(M->dir),sizeof(float),1,fOut);
      fwrite(&(M->armure),sizeof(float),1,fOut);
      fwrite(&(M->att),sizeof(float),1,fOut);
      fwrite(&(M->nbColl),sizeof(int),1,fOut);
      for(int y=0 ; y<M->nbColl ; y++)
	{
	  fwrite(&(M->Coll[y].t[0].x),sizeof(float),1,fOut);
	  fwrite(&(M->Coll[y].t[0].y),sizeof(float),1,fOut);
	  fwrite(&(M->Coll[y].t[0].z),sizeof(float),1,fOut);

	  fwrite(&(M->Coll[y].t[1].x),sizeof(float),1,fOut);
	  fwrite(&(M->Coll[y].t[1].y),sizeof(float),1,fOut);
	  fwrite(&(M->Coll[y].t[1].z),sizeof(float),1,fOut);

	  fwrite(&(M->Coll[y].t[2].x),sizeof(float),1,fOut);
	  fwrite(&(M->Coll[y].t[2].y),sizeof(float),1,fOut);
	  fwrite(&(M->Coll[y].t[2].z),sizeof(float),1,fOut);
	}
      fwrite(&(M->Tir1.x),sizeof(float),1,fOut);
      fwrite(&(M->Tir1.y),sizeof(float),1,fOut);
      fwrite(&(M->Tir1.z),sizeof(float),1,fOut);

      fwrite(&(M->Tir2.x),sizeof(float),1,fOut);
      fwrite(&(M->Tir2.y),sizeof(float),1,fOut);
      fwrite(&(M->Tir2.z),sizeof(float),1,fOut);

      fwrite(&(M->descript),sizeof(char),100,fOut);
    }
  if(M->tagM=='M')
    {
      fwrite(&(M->name),sizeof(char),20,fOut);
      fwrite(&(M->nbClimat),sizeof(int),1,fOut);
      for(int y=0 ; y<M->nbClimat ; y++)
	{
	  fwrite(&(M->Climat[y].type),sizeof(char),1,fOut);
	}
      fwrite(&(M->urlDrone),sizeof(char),50,fOut);
      fwrite(&(M->nbDrone),sizeof(int),1,fOut);
      for(int y=0 ; y<M->nbDrone ; y++)
	{
	  fwrite(&(M->Drone[y].x),sizeof(float),1,fOut);
	  fwrite(&(M->Drone[y].y),sizeof(float),1,fOut);
	  fwrite(&(M->Drone[y].z),sizeof(float),1,fOut);
	}
      fwrite(&(M->urlShoker),sizeof(char),50,fOut);
      fwrite(&(M->nbShoker),sizeof(int),1,fOut);
      for(int y=0 ; y<M->nbShoker ; y++)
	{
	  fwrite(&(M->Shoker[y].x),sizeof(float),1,fOut);
	  fwrite(&(M->Shoker[y].y),sizeof(float),1,fOut);
	  fwrite(&(M->Shoker[y].z),sizeof(float),1,fOut);
	}
      fwrite(&(M->depart.x),sizeof(float),1,fOut);
      fwrite(&(M->depart.y),sizeof(float),1,fOut);
      fwrite(&(M->depart.z),sizeof(float),1,fOut);

      fwrite(&(M->yLiq),sizeof(float),1,fOut);
      fwrite(&(M->yLiqMin),sizeof(float),1,fOut);
      fwrite(&(M->yLiqMax),sizeof(float),1,fOut);
      fwrite(&(M->urlLiq),sizeof(char),50,fOut);
      fwrite(&(M->colorLiq[0]),sizeof(float),1,fOut);
      fwrite(&(M->colorLiq[1]),sizeof(float),1,fOut);
      fwrite(&(M->colorLiq[2]),sizeof(float),1,fOut);
      fwrite(&(M->colorLiq[3]),sizeof(float),1,fOut);

      fwrite(&(M->Limits[0]),sizeof(float),1,fOut);
      fwrite(&(M->Limits[1]),sizeof(float),1,fOut);
      fwrite(&(M->Limits[2]),sizeof(float),1,fOut);
      fwrite(&(M->Limits[3]),sizeof(float),1,fOut);
      fwrite(&(M->Limits[4]),sizeof(float),1,fOut);
      fwrite(&(M->Limits[5]),sizeof(float),1,fOut);

      for(int q=0; M->descript[q]!='\0' ;q++)
	{
	  if(M->descript[q]=='_')
	    M->descript[q]=' ';
	}
      fwrite(&(M->descript),sizeof(char),100,fOut);
    }

  if(M->tagD=='D')
    {
      fwrite(&(M->nbDrone),sizeof(int),1,fOut);
      fwrite(&(M->type),sizeof(char),1,fOut);
      fwrite(&(M->taille),sizeof(float),1,fOut);
    }
  
  if(M->tagS=='S')
    {
      fwrite(&(M->att),sizeof(float),1,fOut);
      fwrite(&(M->vit),sizeof(float),1,fOut);
      fwrite(&(M->armure),sizeof(float),1,fOut);
      fwrite(&(M->taille),sizeof(float),1,fOut);
      fwrite(&(M->type),sizeof(char),1,fOut);
    }

  fclose(fOut);
  

  // Destruction de l'objet en mémoire
  for (int i=0 ; i<M->nbObjets ; i++)
    {
      for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
      delete M->Objets[i]->vertices;
      delete M->Objets[i];
    }
  delete M->Coll;
  
  delete M;

  return;*/
}

// Prototypes des fonctions principales
void Init(void);
void Display(void);
void Reshape(int,int);
void Idle(void);
void Keyboard(unsigned char key, int x, int y);
int LoadBMP(char *File);
#define LOADTYPE_BMP 'b'
#define LOADTYPE_TGA32 'T'
#define LOADTYPE_TGA24 't'
unsigned int ChargerImage32Bits (const char* szFilename);
unsigned int ChargerImage24Bits (const char* szFilename);

GLuint *Textures;
char Url[50];

void _3D(int argc, char**argv)
{
  printf("Editeur 3D de model .mad\nEntrez le nom du fichier à éditer :\n");

  char ch, url[50];
  scanf("%c",&ch);
  scanf("%[^'\n']",&url);
  strcat(url,".mad");
  strcpy(Url,url);
  M3D=loadMadModel(url);
  if(M3D==NULL)
    {
      printf("Model inexistant !\n");
      return;
    }

  // Initialisation d'OpenGL et création de la fenêtre
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(300,200);
  glutInitWindowPosition(0,0);
  glutCreateWindow("S_Mad 3D Editeur");

  // Activation de la gestion du clavier
  glutKeyboardFunc(Keyboard);
  // Activation de la fonction de rendu
  glutDisplayFunc(Display);
  // Activation des fonctions de remise à jour
  glutReshapeFunc(Reshape);
  glutIdleFunc(Idle);

  // Activation du test de profondeur
  glEnable(GL_DEPTH_TEST);
  // Activation des textures
  glEnable(GL_TEXTURE_2D);

  Textures=new GLuint[M3D->nbObjets];

  for(int t=0 ; t<M3D->nbObjets ; t++)
    {
      char tampon[100];
      char type=LOADTYPE_BMP;
      strcpy(tampon,"../../");
      strcat(tampon,M3D->Objets[t].texture);
      printf("%s\n", tampon);

      if(type==LOADTYPE_BMP)
	{
	  int len=strlen(tampon);
	  if(tampon[len-1]=='a')
	    type=LOADTYPE_TGA32;
	}
      if(type==LOADTYPE_TGA32)
	Textures[t]=ChargerImage32Bits(tampon);
      else
	if(type==LOADTYPE_TGA24)
	  Textures[t]=ChargerImage24Bits(tampon);
	else
	  Textures[t]=LoadBMP(tampon);
    }

  // Entrée dans la boucle principale
  glutMainLoop();


  // Destruction de l'objet en mémoire
  delete Textures;
  delMadModel(M3D);

  return;
}

void Mute(void)
{/*
   Model* M=new Model;
   char mut='0';

   printf("Mutateur de model\nEntrez le nom du fichier à muter :\n");

   char ch, url[50], url2[50];
   scanf("%c",&ch);
   scanf("%[^'\n']",&url);
   scanf("%c",&ch);
   strcpy(url2,url);
   strcat(url,".mad");
   strcat(url2,".mut.mad");

   printf("Entrez la mutation souhaitée :\nS : Symétrie\nH : Homothétie\nT : Translation\n");
   char input=getchar();
   printf("Entrez l'axe de mutation ( X/Y/Z )\n");
   char inAxe;
   cin>>inAxe;
   float homothe=1;
   if(input=='H')
   {
   printf("Entrez le facteur d'homothétie :\n");
   cin>>homothe;
   }
   if(input=='T')
   {
   printf("Entrez la norme du vecteur de Translation :\n");
   cin>>homothe;
   }

   FILE* fIn=fopen(url,"r");
   if(fIn==NULL)
   {
   printf("Model inexistant !\n");
   return;
   }
   unsigned char id;
   fread(&id,sizeof(unsigned char),1,fIn);
   if(id!=136)
   {
   printf("Model incorrect !\n");
   return;
   }
   int nbtag=0;
   fread(&nbtag,sizeof(int),1,fIn);
   fread(&(M->typeAnim),sizeof(char),1,fIn);
   fread(&(M->nbObjets),sizeof(int),1,fIn);
   M->Objets=new surface*[M->nbObjets];
   for (int o=0 ; o<M->nbObjets ; o++)
   {
   M->Objets[o]=new surface;
   fread(M->Objets[o]->texture,sizeof(char),50,fIn);
   fread(&(M->Objets[o]->surfacetype),sizeof(char),1,fIn);
   fread(&(M->Objets[o]->nb_vertices),sizeof(int),1,fIn);
   M->Objets[o]->vertices=new vertex*[M->Objets[o]->nb_vertices];
   for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
   {
   M->Objets[o]->vertices[p]=new vertex;
   fread(&(M->Objets[o]->vertices[p]->p.x),sizeof(float),1,fIn);
   fread(&(M->Objets[o]->vertices[p]->p.y),sizeof(float),1,fIn);
   fread(&(M->Objets[o]->vertices[p]->p.z),sizeof(float),1,fIn);
   fread(&(M->Objets[o]->vertices[p]->text.x),sizeof(float),1,fIn);
   fread(&(M->Objets[o]->vertices[p]->text.y),sizeof(float),1,fIn);
   }
   }
   fclose(fIn);

   // Sauvegarde de l'importation
   FILE* fOut=fopen(url2,"w");
   id= 136;
   fwrite(&id,sizeof(unsigned char),1,fOut);
   int nbtaG=0;
   fwrite(&nbtaG,sizeof(int),1,fOut);

   fwrite(&(M->typeAnim),sizeof(char),1,fOut);	
   fwrite(&(M->nbObjets),sizeof(int),1,fOut);
   for (int o=0 ; o<M->nbObjets ; o++)
   {
   fwrite(M->Objets[o]->texture,sizeof(char),50,fOut);
   fwrite(&(M->Objets[o]->surfacetype),sizeof(char),1,fOut);
   fwrite(&(M->Objets[o]->nb_vertices),sizeof(int),1,fOut);
   for(int p=0 ; p<M->Objets[o]->nb_vertices ; p++)
   {
   if(input=='S')
   {
   if(inAxe=='X')
   M->Objets[o]->vertices[p]->p.x=-M->Objets[o]->vertices[p]->p.x;
   if(inAxe=='Y')
   M->Objets[o]->vertices[p]->p.y=-M->Objets[o]->vertices[p]->p.y;
   if(inAxe=='Z')
   M->Objets[o]->vertices[p]->p.z=-M->Objets[o]->vertices[p]->p.z;
   }
   if(input=='H')
   {
   if(inAxe=='X')
   M->Objets[o]->vertices[p]->p.x=M->Objets[o]->vertices[p]->p.x*homothe;
   if(inAxe=='Y')
   M->Objets[o]->vertices[p]->p.y=M->Objets[o]->vertices[p]->p.y*homothe;
   if(inAxe=='Z')
   M->Objets[o]->vertices[p]->p.z=M->Objets[o]->vertices[p]->p.z*homothe;
   }
   if(input=='T')
   {
   if(inAxe=='X')
   M->Objets[o]->vertices[p]->p.x=M->Objets[o]->vertices[p]->p.x+homothe;
   if(inAxe=='Y')
   M->Objets[o]->vertices[p]->p.y=M->Objets[o]->vertices[p]->p.y+homothe;
   if(inAxe=='Z')
   M->Objets[o]->vertices[p]->p.z=M->Objets[o]->vertices[p]->p.z+homothe;
   }
   fwrite(&(M->Objets[o]->vertices[p]->p.x),sizeof(float),1,fOut);
   fwrite(&(M->Objets[o]->vertices[p]->p.y),sizeof(float),1,fOut);
   fwrite(&(M->Objets[o]->vertices[p]->p.z),sizeof(float),1,fOut);
   fwrite(&(M->Objets[o]->vertices[p]->text.x),sizeof(float),1,fOut);
   fwrite(&(M->Objets[o]->vertices[p]->text.y),sizeof(float),1,fOut);
   }
   }
   fclose(fOut);


   // Destruction de l'objet en mémoire
   for (int i=0 ; i<M->nbObjets ; i++)
   {
   for (int u=0 ; u< M->Objets[i]->nb_vertices ; u++ )delete M->Objets[i]->vertices ;
   delete M->Objets[i]->vertices;
   delete M->Objets[i];
   }

   delete M;

   return;*/
}
