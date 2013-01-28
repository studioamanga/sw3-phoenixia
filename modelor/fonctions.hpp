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




void New(void)
{
	printf("Nouveau modèle\n");
	model* M=new model;

	printf("Entrez le type d'animation du modèle : ( S-Shoker / autre-no anim )\n");
	scanf("%c",&(M->anim));
	scanf("%c",&(M->anim));

	printf("Entrez le rayon de la zone de collision du modèle :\n");
	scanf("%f",&(M->taille));

	printf("Entrez le facteur de vitesse du modèle :\n");
	scanf("%f",&(M->vit));

	printf("Entrez le facteur de vitesse de direction du modèle :\n");
	scanf("%f",&(M->dir));

	printf("Entrez le facteur d'armure du modèle :\n");
	scanf("%f",&(M->armure));

	printf("Entrez le facteur d'attaque du modèle :\n");
	scanf("%f",&(M->att));


	printf("Entrez le nombre d'objet du modèle :\n");

	scanf("%d",&(M->nb_surface));
	M->mod=new surface*[M->nb_surface];
	for( int y=0 ; y<M->nb_surface ; y++ )
	{
		M->mod[y]=new surface;
		printf("* Objet n%d *\n",y+1);
		printf("Entrez le nom de la texture :\n");
		char c;
		scanf("%c",&c);
		scanf("%[^'\n']",M->mod[y]->texture);
		scanf("%c",&c);
		printf("Entrez le type de surface ( Q-QUADS / T-TRIANGLE_STRIP ) :\n");
		M->mod[y]->surfacetype=getchar();
		printf("Entrez le nombre de vertices :\n");
		scanf("%d",&M->mod[y]->nb_vertices);
		M->mod[y]->vertices=new vertex*[M->mod[y]->nb_vertices];
		for( int t=0 ; t<M->mod[y]->nb_vertices ; t++)
		{
			M->mod[y]->vertices[t]=new vertex;
			printf("* Vertex n%d de l'objet n%d *\n",t+1, y+1);
			printf("Coordonnees en X du vertex : ");
			scanf("%f",&(M->mod[y]->vertices[t]->p.x));
			printf("Coordonnees en Y du vertex : ");
			scanf("%f",&(M->mod[y]->vertices[t]->p.y));
			printf("Coordonnees en Z du vertex : ");
			scanf("%f",&(M->mod[y]->vertices[t]->p.z));
			printf("Coordonnees de la texture en X : ");
			scanf("%f",&(M->mod[y]->vertices[t]->text.x));
			printf("Coordonnees de la texture en Y : ");
			scanf("%f",&(M->mod[y]->vertices[t]->text.y));

			printf("Confirmez le vertex (%f,%f,%f,%f,%f)? Y/N \n",M->mod[y]->vertices[t]->p.x,M->mod[y]->vertices[t]->p.y,M->mod[y]->vertices[t]->p.z,M->mod[y]->vertices[t]->text.x,M->mod[y]->vertices[t]->text.y);

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
	fwrite(&(M->anim),sizeof(char),1,fOut);
	fwrite(&(M->taille),sizeof(float),1,fOut);
	fwrite(&(M->vit),sizeof(float),1,fOut);
	fwrite(&(M->dir),sizeof(float),1,fOut);
	fwrite(&(M->armure),sizeof(float),1,fOut);
	fwrite(&(M->att),sizeof(float),1,fOut);
	fwrite(&(M->nb_surface),sizeof(int),1,fOut);
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		fwrite(M->mod[o]->texture,sizeof(char),50,fOut);
		fwrite(&(M->mod[o]->surfacetype),sizeof(char),1,fOut);
		fwrite(&(M->mod[o]->nb_vertices),sizeof(int),1,fOut);
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
			fwrite(&(M->mod[o]->vertices[p]->p.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.y),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.z),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.y),sizeof(float),1,fOut);
		}
	}
	fclose(fOut);
	
	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nb_surface ; i++)
	{
		for (int u=0 ; u< M->mod[i]->nb_vertices ; u++ )delete M->mod[i]->vertices ;
		delete M->mod[i]->vertices;
		delete M->mod[i];
	}

	delete M;
	return;
}

void Mix(void)
{
	printf("Mixeur de modèle\n");
	model* M=new model;

	printf("Entrez le type d'animation du modèle : ( S-Shoker / autre-no anim )\n");
	scanf("%c",&(M->anim));
	scanf("%c",&(M->anim));

	printf("Entrez le rayon de la zone de collision du modèle :\n");
	scanf("%f",&(M->taille));

	printf("Entrez le facteur de vitesse du modèle :\n");
	scanf("%f",&(M->vit));

	printf("Entrez le facteur de vitesse de direction du modèle :\n");
	scanf("%f",&(M->dir));

	printf("Entrez le facteur d'armure du modèle :\n");
	scanf("%f",&(M->armure));

	printf("Entrez le facteur d'attaque du modèle :\n");
	scanf("%f",&(M->att));

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
		fseek(fIn1,sizeof(char)+sizeof(float)*5,SEEK_CUR);
		fseek(fIn2,sizeof(char)+sizeof(float)*5,SEEK_CUR);

		int nbSurf1, nbSurf2;
		fread(&nbSurf1,sizeof(int),1,fIn1);
		fread(&nbSurf2,sizeof(int),1,fIn2);
		M->nb_surface=nbSurf1+nbSurf2;

	M->mod=new surface*[M->nb_surface];
	for(int i1=0 ; i1<nbSurf1 ; i1++)
	{
		M->mod[i1]=new surface;
		fread(&(M->mod[i1]->texture),sizeof(char),50,fIn1);
		fread(&(M->mod[i1]->surfacetype),sizeof(char),1,fIn1);
		fread(&(M->mod[i1]->nb_vertices),sizeof(int),1,fIn1);
		M->mod[i1]->vertices=new vertex*[M->mod[i1]->nb_vertices];
	for (int i11=0 ; i11<M->mod[i1]->nb_vertices ; i11++)
	{
		M->mod[i1]->vertices[i11]=new vertex;
		fread(&(M->mod[i1]->vertices[i11]->p.x),sizeof(float),1,fIn1);
		fread(&(M->mod[i1]->vertices[i11]->p.y),sizeof(float),1,fIn1);
		fread(&(M->mod[i1]->vertices[i11]->p.z),sizeof(float),1,fIn1);
		fread(&(M->mod[i1]->vertices[i11]->text.x),sizeof(float),1,fIn1);
		fread(&(M->mod[i1]->vertices[i11]->text.y),sizeof(float),1,fIn1);
	}
	}
	for(int i2=nbSurf1 ; i2<M->nb_surface ; i2++)
	{
		M->mod[i2]=new surface;
		fread(&(M->mod[i2]->texture),sizeof(char),50,fIn2);
		fread(&(M->mod[i2]->surfacetype),sizeof(char),1,fIn2);
		fread(&(M->mod[i2]->nb_vertices),sizeof(int),1,fIn2);
		M->mod[i2]->vertices=new vertex*[M->mod[i2]->nb_vertices];
	for (int i21=0 ; i21<M->mod[i2]->nb_vertices ; i21++)
	{
		M->mod[i2]->vertices[i21]=new vertex;
		fread(&(M->mod[i2]->vertices[i21]->p.x),sizeof(float),1,fIn2);
		fread(&(M->mod[i2]->vertices[i21]->p.y),sizeof(float),1,fIn2);
		fread(&(M->mod[i2]->vertices[i21]->p.z),sizeof(float),1,fIn2);
		fread(&(M->mod[i2]->vertices[i21]->text.x),sizeof(float),1,fIn2);
		fread(&(M->mod[i2]->vertices[i21]->text.y),sizeof(float),1,fIn2);
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
	fwrite(&(M->anim),sizeof(char),1,fOut);
	fwrite(&(M->taille),sizeof(float),1,fOut);
	fwrite(&(M->vit),sizeof(float),1,fOut);
	fwrite(&(M->dir),sizeof(float),1,fOut);
	fwrite(&(M->armure),sizeof(float),1,fOut);
	fwrite(&(M->att),sizeof(float),1,fOut);
	fwrite(&(M->nb_surface),sizeof(int),1,fOut);
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		fwrite(M->mod[o]->texture,sizeof(char),50,fOut);
		fwrite(&(M->mod[o]->surfacetype),sizeof(char),1,fOut);
		fwrite(&(M->mod[o]->nb_vertices),sizeof(int),1,fOut);
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
			fwrite(&(M->mod[o]->vertices[p]->p.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.y),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.z),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.y),sizeof(float),1,fOut);
		}
	}
	fclose(fOut);

	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nb_surface ; i++)
	{
		for (int u=0 ; u< M->mod[i]->nb_vertices ; u++ )delete M->mod[i]->vertices ;
		delete M->mod[i]->vertices;
		delete M->mod[i];
	}

	delete M;
	return;
}

void Export(void)
{
	model* M=new model;

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
	fread(&(M->anim),sizeof(char),1,fIn);
	fread(&(M->taille),sizeof(float),1,fIn);
	fread(&(M->vit),sizeof(float),1,fIn);
	fread(&(M->dir),sizeof(float),1,fIn);
	fread(&(M->armure),sizeof(float),1,fIn);
	fread(&(M->att),sizeof(float),1,fIn);
	fread(&(M->nb_surface),sizeof(int),1,fIn);
	M->mod=new surface*[M->nb_surface];
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		M->mod[o]=new surface;
		fread(M->mod[o]->texture,sizeof(char),50,fIn);
		fread(&(M->mod[o]->surfacetype),sizeof(char),1,fIn);
		fread(&(M->mod[o]->nb_vertices),sizeof(int),1,fIn);
		M->mod[o]->vertices=new vertex*[M->mod[o]->nb_vertices];
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
			M->mod[o]->vertices[p]=new vertex;
			fread(&(M->mod[o]->vertices[p]->p.x),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->p.y),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->p.z),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->text.x),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->text.y),sizeof(float),1,fIn);
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
	fOut<<"###_Model_.mad_exporté_au_format_.vem\n";
	fOut<<M->anim<<endl;
	fOut<<M->taille<<endl;
	fOut<<M->vit<<endl;
	fOut<<M->dir<<endl;
	fOut<<M->armure<<endl;
	fOut<<M->att<<endl;
	fOut<<M->nb_surface<<endl;
	for (int i=0 ; i<M->nb_surface ; i++)
	{
		fOut<<"_##_Nouvelle_surface\n";
		fOut<<M->mod[i]->texture<<endl;
		fOut<<M->mod[i]->surfacetype<<endl;
		fOut<<M->mod[i]->nb_vertices<<endl;

		for (int u=0 ; u< M->mod[i]->nb_vertices ; u++ )
		{
			fOut<<"_#_Nouveau_vertex\n";
			fOut<<M->mod[i]->vertices[u]->p.x<<endl;
			fOut<<M->mod[i]->vertices[u]->p.y<<endl;
			fOut<<M->mod[i]->vertices[u]->p.z<<endl;
			fOut<<M->mod[i]->vertices[u]->text.x<<endl;
			fOut<<M->mod[i]->vertices[u]->text.y<<endl;
		}
	}
	fOut.close();


	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nb_surface ; i++)
	{
		for (int u=0 ; u< M->mod[i]->nb_vertices ; u++ )delete M->mod[i]->vertices ;
		delete M->mod[i]->vertices;
		delete M->mod[i];
	}

	delete M;

	return;
}

void Import(void)
{
	model* M=new model;

	printf("Importateur de model au format View&Edit Mad\nEntrez le nom du fichier à importer :\n");

	char ch, url[50], url2[50];
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
	char et[40];
	fIn>>et;
	fIn>>M->anim;
	fIn>>M->taille;
	fIn>>M->vit;
	fIn>>M->dir;
	fIn>>M->armure;
	fIn>>M->att;
	fIn>>M->nb_surface;
	M->mod=new surface*[M->nb_surface];
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		M->mod[o]=new surface;
		char ets[40];
		fIn>>ets;
		fIn>>M->mod[o]->texture;
		fIn>>M->mod[o]->surfacetype;
		fIn>>M->mod[o]->nb_vertices;
		M->mod[o]->vertices=new vertex*[M->mod[o]->nb_vertices];
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
   			M->mod[o]->vertices[p]=new vertex;
			char etv[40];
			fIn>>etv;
			fIn>>M->mod[o]->vertices[p]->p.x;
			fIn>>M->mod[o]->vertices[p]->p.y;
			fIn>>M->mod[o]->vertices[p]->p.z;
			fIn>>M->mod[o]->vertices[p]->text.x;
			fIn>>M->mod[o]->vertices[p]->text.y;
		}
	}
	fIn.close();

	// Sauvegarde de l'importation
	FILE* fOut=fopen(url,"w");
	unsigned char id= 136;
	fwrite(&id,sizeof(unsigned char),1,fOut);
	fwrite(&(M->anim),sizeof(char),1,fOut);
	fwrite(&(M->taille),sizeof(float),1,fOut);
	fwrite(&(M->vit),sizeof(float),1,fOut);
	fwrite(&(M->dir),sizeof(float),1,fOut);
	fwrite(&(M->armure),sizeof(float),1,fOut);
	fwrite(&(M->att),sizeof(float),1,fOut);
	fwrite(&(M->nb_surface),sizeof(int),1,fOut);
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		fwrite(M->mod[o]->texture,sizeof(char),50,fOut);
		fwrite(&(M->mod[o]->surfacetype),sizeof(char),1,fOut);
		fwrite(&(M->mod[o]->nb_vertices),sizeof(int),1,fOut);
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
			fwrite(&(M->mod[o]->vertices[p]->p.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.y),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.z),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.y),sizeof(float),1,fOut);
		}
	}
	fclose(fOut);


	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nb_surface ; i++)
	{
		for (int u=0 ; u< M->mod[i]->nb_vertices ; u++ )delete M->mod[i]->vertices ;
		delete M->mod[i]->vertices;
		delete M->mod[i];
	}

	delete M;

	return;
}

// Prototypes des fonctions principales
void Init(void);
void Display(void);
void Reshape(int,int);
void Idle(void);
void Keyboard(unsigned char key, int x, int y);
int LoadBMP(char *File);

GLuint **Textures;
char Url[50];

void _3D(int argc, char**argv)
{
	M3D=new model;

	printf("Editeur 3D de model .mad\nEntrez le nom du fichier à éditer :\n");

	char ch, url[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	strcat(url,".mad");
	strcpy(Url,url);

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
	fread(&(M3D->anim),sizeof(char),1,fIn);
	fread(&(M3D->taille),sizeof(float),1,fIn);
	fread(&(M3D->vit),sizeof(float),1,fIn);
	fread(&(M3D->dir),sizeof(float),1,fIn);
	fread(&(M3D->armure),sizeof(float),1,fIn);
	fread(&(M3D->att),sizeof(float),1,fIn);
	fread(&(M3D->nb_surface),sizeof(int),1,fIn);
	M3D->mod=new surface*[M3D->nb_surface];
	Textures=new GLuint*[M3D->nb_surface];
	for (int o=0 ; o<M3D->nb_surface ; o++)
	{
		M3D->mod[o]=new surface;
		Textures[o]=new GLuint;
		fread(M3D->mod[o]->texture,sizeof(char),50,fIn);

		fread(&(M3D->mod[o]->surfacetype),sizeof(char),1,fIn);
		fread(&(M3D->mod[o]->nb_vertices),sizeof(int),1,fIn);
		M3D->mod[o]->vertices=new vertex*[M3D->mod[o]->nb_vertices];
		for(int p=0 ; p<M3D->mod[o]->nb_vertices ; p++)
		{
			M3D->mod[o]->vertices[p]=new vertex;
			fread(&(M3D->mod[o]->vertices[p]->p.x),sizeof(float),1,fIn);
			fread(&(M3D->mod[o]->vertices[p]->p.y),sizeof(float),1,fIn);
			fread(&(M3D->mod[o]->vertices[p]->p.z),sizeof(float),1,fIn);
			fread(&(M3D->mod[o]->vertices[p]->text.x),sizeof(float),1,fIn);
			fread(&(M3D->mod[o]->vertices[p]->text.y),sizeof(float),1,fIn);
		}
	}
	fclose(fIn);
	// Initialisation d'OpenGL et création de la fenêtre
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640,480);
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

	for(int t=0;t<M3D->nb_surface;t++)
	{
		char tampon[50];
		strcpy(tampon,"../");
		strcat(tampon,M3D->mod[t]->texture);

		*(Textures[t])=LoadBMP(tampon);
	}

	// Entrée dans la boucle principale
	glutMainLoop();

	printf("Voulez vous sauvegarder les modifications du model ? (Y/N)\n");
	char cq=getchar();
	if(cq=='Y'||cq=='y')
	{
		// Sauvegarde de l'importation
		FILE* fOut=fopen(url,"w");
		unsigned char id= 136;
		fwrite(&id,sizeof(unsigned char),1,fOut);
		fwrite(&(M3D->anim),sizeof(char),1,fOut);
		fwrite(&(M3D->taille),sizeof(float),1,fOut);
		fwrite(&(M3D->vit),sizeof(float),1,fOut);
		fwrite(&(M3D->dir),sizeof(float),1,fOut);
		fwrite(&(M3D->armure),sizeof(float),1,fOut);
		fwrite(&(M3D->att),sizeof(float),1,fOut);
		fwrite(&(M3D->nb_surface),sizeof(int),1,fOut);
		for (int o=0 ; o<M3D->nb_surface ; o++)
		{
			fwrite(M3D->mod[o]->texture,sizeof(char),50,fOut);
			fwrite(&(M3D->mod[o]->surfacetype),sizeof(char),1,fOut);
			fwrite(&(M3D->mod[o]->nb_vertices),sizeof(int),1,fOut);
			for(int p=0 ; p<M3D->mod[o]->nb_vertices ; p++)
			{
					fwrite(&(M3D->mod[o]->vertices[p]->p.x),sizeof(float),1,fOut);
				fwrite(&(M3D->mod[o]->vertices[p]->p.y),sizeof(float),1,fOut);
				fwrite(&(M3D->mod[o]->vertices[p]->p.z),sizeof(float),1,fOut);
				fwrite(&(M3D->mod[o]->vertices[p]->text.x),sizeof(float),1,fOut);
				fwrite(&(M3D->mod[o]->vertices[p]->text.y),sizeof(float),1,fOut);
			}
		}
		fclose(fOut);
	}

	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M3D->nb_surface ; i++)
	{
		for (int u=0 ; u< M3D->mod[i]->nb_vertices ; u++ )delete M3D->mod[i]->vertices ;
		delete M3D->mod[i]->vertices;
		delete M3D->mod[i];
		delete Textures[i];
	}
	delete Textures;
	delete M3D;

	return;
}

void Mute(void)
{
	model* M=new model;
	char mut='0';

	printf("Mutateur de model\nEntrez le nom du fichier à muter :\n");

	char ch, url[50], url2[50];
	scanf("%c",&ch);
	scanf("%[^'\n']",&url);
	scanf("%c",&ch);
	strcpy(url2,url);
	strcat(url,".mad");
	strcat(url2,".mut.mad");

	printf("Entrez la mutation souhaitée :\nX : Symétrie par X\nY : Symétrie par Z\nZ : Symétrie par Z\nH : Homothétie\n");
	char input=getchar();
	float homothe=1;
	if(input=='H')
	{
		printf("Entrez le facteur d'homothétie :\n");
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
	fread(&(M->anim),sizeof(char),1,fIn);
	fread(&(M->taille),sizeof(float),1,fIn);
	fread(&(M->vit),sizeof(float),1,fIn);
	fread(&(M->dir),sizeof(float),1,fIn);
	fread(&(M->armure),sizeof(float),1,fIn);
	fread(&(M->att),sizeof(float),1,fIn);
	fread(&(M->nb_surface),sizeof(int),1,fIn);
	M->mod=new surface*[M->nb_surface];
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		M->mod[o]=new surface;
		fread(M->mod[o]->texture,sizeof(char),50,fIn);
		fread(&(M->mod[o]->surfacetype),sizeof(char),1,fIn);
		fread(&(M->mod[o]->nb_vertices),sizeof(int),1,fIn);
		M->mod[o]->vertices=new vertex*[M->mod[o]->nb_vertices];
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
			M->mod[o]->vertices[p]=new vertex;
			fread(&(M->mod[o]->vertices[p]->p.x),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->p.y),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->p.z),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->text.x),sizeof(float),1,fIn);
			fread(&(M->mod[o]->vertices[p]->text.y),sizeof(float),1,fIn);

			if(input=='X') M->mod[o]->vertices[p]->p.x*=-1;
			if(input=='Y') M->mod[o]->vertices[p]->p.y*=-1;
			if(input=='Z') M->mod[o]->vertices[p]->p.z*=-1;
			if(input=='H')
			{
				M->mod[o]->vertices[p]->p.x*=homothe;
				M->mod[o]->vertices[p]->p.y*=homothe;
				M->mod[o]->vertices[p]->p.z*=homothe;
			}
		}
	}
	fclose(fIn);

	// Sauvegarde de l'importation
	FILE* fOut=fopen(url2,"w");
	unsigned char id2= 136;
	fwrite(&id2,sizeof(unsigned char),1,fOut);
	fwrite(&(M->anim),sizeof(char),1,fOut);
	fwrite(&(M->taille),sizeof(float),1,fOut);
	fwrite(&(M->vit),sizeof(float),1,fOut);
	fwrite(&(M->dir),sizeof(float),1,fOut);
	fwrite(&(M->armure),sizeof(float),1,fOut);
	fwrite(&(M->att),sizeof(float),1,fOut);
	fwrite(&(M->nb_surface),sizeof(int),1,fOut);
	for (int o=0 ; o<M->nb_surface ; o++)
	{
		fwrite(M->mod[o]->texture,sizeof(char),50,fOut);
		fwrite(&(M->mod[o]->surfacetype),sizeof(char),1,fOut);
		fwrite(&(M->mod[o]->nb_vertices),sizeof(int),1,fOut);
		for(int p=0 ; p<M->mod[o]->nb_vertices ; p++)
		{
			fwrite(&(M->mod[o]->vertices[p]->p.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.y),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->p.z),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.x),sizeof(float),1,fOut);
			fwrite(&(M->mod[o]->vertices[p]->text.y),sizeof(float),1,fOut);
		}
	}
	fclose(fOut);


	// Destruction de l'objet en mémoire
	for (int i=0 ; i<M->nb_surface ; i++)
	{
		for (int u=0 ; u< M->mod[i]->nb_vertices ; u++ )delete M->mod[i]->vertices ;
		delete M->mod[i]->vertices;
		delete M->mod[i];
	}

	delete M;

	return;
}
