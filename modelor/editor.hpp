/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
************************** S_MAD ****************************
*************************************************************
**                                                         **
******** editor.hpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/


float posX=0,posY=0,posZ=0, precis=1;
double angleX=0,angleY=0;
int idObj=0, idVertex=0, vit=2;
float vert=0;
bool hid=false;
bool newLook=true;

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

// Gestion d'initialisation globale
void Init(void)
{
	// Activation du test de profondeur
	glEnable(GL_DEPTH_TEST);
	// Activation des textures
	glEnable(GL_TEXTURE_2D);


	return;
}

// Fonction d'affichage de la scène
void Display(void)
{
	// Nettoyage du tampon ( par la couleur noire )
	glClearColor(0,vert,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Réinitialisation de la matrice de vue
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Configuration de la caméra ( position, orientation et cadrage )
	gluLookAt(posX-(Cos(angleY)*10)*Cos(valAbs(angleX)), posY-(Sin(angleX)*10), posZ+(Sin(angleY)*10)*Cos(valAbs(angleX)), posX, posY, posZ,0,1,0);



	for(int i=0 ; i<M3D->nb_surface ; i++)
	{
		glBindTexture(GL_TEXTURE_2D,*(Textures[i]));
		switch(M3D->mod[i]->surfacetype)
		{
		case 'L' :
			glBegin(GL_TRIANGLES);
			break;
		default :
			glBegin(GL_QUADS);
			break;
		}
		for(int y=0 ; y<M3D->mod[i]->nb_vertices ; y++)
		{
			glTexCoord2f(M3D->mod[i]->vertices[y]->text.x,M3D->mod[i]->vertices[y]->text.y);
			glVertex3f(M3D->mod[i]->vertices[y]->p.x,M3D->mod[i]->vertices[y]->p.y,M3D->mod[i]->vertices[y]->p.z);
		}

		glEnd();
	}

	if(hid==false)
	{
		glTranslated(M3D->mod[idObj]->vertices[idVertex]->p.x, M3D->mod[idObj]->vertices[idVertex]->p.y, M3D->mod[idObj]->vertices[idVertex]->p.z);
		glutSolidSphere(precis,5,5);
		glutWireSphere(50,8,8);
		glutWireSphere(200,15,15);
	}

	// Inversion des buffers ( multi-buffering )
	glutSwapBuffers();
	return;
}

// Fonction de redimensionnement de la fenêtre
void Reshape(int w,int h)
{
	// Réglage du rendu et de la perspective
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float) w/h, 1.,500000.);
	return;
}

// Fonction de remise à jour
void Idle(void)
{
	// Actualisation des variables
	vert+=0.01;
	if(vert>=1) vert=0;

	// Forcer le reDisplay
	glutPostRedisplay();
	return;
}

// Fonction pour gérer l'appui de touche du clavier
void Keyboard(unsigned char key, int x, int y)
{
	// Réglage de la vitesse
	if(key=='9') vit++;
	if(key=='6') { vit--; if(vit<0) vit=0; }

	// Réglage de la précision
	if(key=='+') precis*=10;
	if(key=='-') { precis/=10; if(precis<0) precis=0; }


	// Actualisation des variables input pour le déplacement de la caméra
	if(key=='z') angleX+=vit;
	if(key=='s') angleX-=vit;
	if(key=='q') angleY+=vit;
	if(key=='d') angleY-=vit;
	if(angleX>360) angleX-=360;
	if(angleY>360) angleY-=360;
	if(angleX<0) angleX+=360;
	if(angleY<0) angleY+=360;

	// Déplacement
	if(key=='1')
	{
		// On remet à jour la position
		posY+=vit*Sin(angleX);
		posX+=vit*Cos(angleY)*Cos(valAbs(angleX));
		posZ-=vit*Sin(angleY)*Cos(valAbs(angleX));
	}
	if(key=='2')
	{
		// On remet à jour la position
		posY-=vit*Sin(angleX);
		posX-=vit*Cos(angleY)*Cos(valAbs(angleX));
		posZ+=vit*Sin(angleY)*Cos(valAbs(angleX));
	}

	// Focus sur le vertex
	if(key=='3')
	{
		posX=M3D->mod[idObj]->vertices[idVertex]->p.x+10;
		posY=M3D->mod[idObj]->vertices[idVertex]->p.y+10;
		posZ=M3D->mod[idObj]->vertices[idVertex]->p.z+10;
		angleY=135;
		angleX=-45;
	}

	// Changement d'objet
	if(key=='8')
	{
		idObj++;
		if(idObj>=M3D->nb_surface) idObj=M3D->nb_surface-1;
		posX=M3D->mod[idObj]->vertices[idVertex]->p.x+10;
		posY=M3D->mod[idObj]->vertices[idVertex]->p.y+10;
		posZ=M3D->mod[idObj]->vertices[idVertex]->p.z+10;
		angleY=135;
		angleX=-45;
		idVertex=0;
	}
	if(key=='5')
	{
		idObj--;
		if(idObj<=0) idObj=0;
		posX=M3D->mod[idObj]->vertices[idVertex]->p.x+10;
		posY=M3D->mod[idObj]->vertices[idVertex]->p.y+10;
		posZ=M3D->mod[idObj]->vertices[idVertex]->p.z+10;
		angleY=135;
		angleX=-45;
		idVertex=0;
	}

	// Changement de vertex
	if(key=='7')
	{
		idVertex++;
		if(idVertex>=M3D->mod[idObj]->nb_vertices)  idVertex=M3D->mod[idObj]->nb_vertices-1;
		if(newLook==true)
		  {
		    posX=M3D->mod[idObj]->vertices[idVertex]->p.x+50;
		    posY=M3D->mod[idObj]->vertices[idVertex]->p.y+50;
		    posZ=M3D->mod[idObj]->vertices[idVertex]->p.z+50;
		    angleY=135;
		    angleX=-45;
		  }
	}
	if(key=='4')
	{
		idVertex--;
		if(idVertex<=0) idVertex=0;
		if(newLook==true)
		  {
		    posX=M3D->mod[idObj]->vertices[idVertex]->p.x+50;
		    posY=M3D->mod[idObj]->vertices[idVertex]->p.y+50;
		    posZ=M3D->mod[idObj]->vertices[idVertex]->p.z+50;
		    angleY=135;
		    angleX=-45;
		  }
	}

	// Modification des coordonnées
	if(key=='y')
	{
		M3D->mod[idObj]->vertices[idVertex]->p.x+=precis;
	}
	if(key=='h')
	{
		M3D->mod[idObj]->vertices[idVertex]->p.x-=precis;
	}
	if(key=='u')
	{
		M3D->mod[idObj]->vertices[idVertex]->p.y+=precis;
	}
	if(key=='j')
	{
		M3D->mod[idObj]->vertices[idVertex]->p.y-=precis;
	}
	if(key=='i')
	{
		M3D->mod[idObj]->vertices[idVertex]->p.z+=precis;
	}
	if(key=='k')
	{
		M3D->mod[idObj]->vertices[idVertex]->p.z-=precis;
	}
	// Modification des coordonnées de texture
	if(key=='o')
	{
		M3D->mod[idObj]->vertices[idVertex]->text.x+=precis;
	}
	if(key=='l')
	{
		M3D->mod[idObj]->vertices[idVertex]->text.x-=precis;
	}
	if(key=='p')
	{
		M3D->mod[idObj]->vertices[idVertex]->text.y+=precis;
	}
	if(key=='m')
	{
		M3D->mod[idObj]->vertices[idVertex]->text.y-=precis;
	}
	if(key=='b')
	  {
	    printf("Vertex n%d, Objet n%d, Pos : %f, %f, %f\n",idVertex+1,idObj+1,M3D->mod[idObj]->vertices[idVertex]->p.x,M3D->mod[idObj]->vertices[idVertex]->p.y,M3D->mod[idObj]->vertices[idVertex]->p.z);
	  }
	if(key=='v')
	  {
	    newLook=!newLook;
	  }
	
	// Nouvelle face
	if(key=='n')
	{
		int nbSurf=M3D->mod[idObj]->nb_vertices;
		if(M3D->mod[idObj]->surfacetype='Q') nbSurf+=4;
		else nbSurf+=3;
		vertex ** vtable;
		vtable=new vertex * [nbSurf];
		for(int i=0 ; i<M3D->mod[idObj]->nb_vertices ;i++)
		{
			vtable[i]=new vertex;
			vtable[i]->p.x=M3D->mod[idObj]->vertices[i]->p.x;
			vtable[i]->p.y=M3D->mod[idObj]->vertices[i]->p.y;
			vtable[i]->p.z=M3D->mod[idObj]->vertices[i]->p.z;
			vtable[i]->text.x=M3D->mod[idObj]->vertices[i]->text.x;
			vtable[i]->text.y=M3D->mod[idObj]->vertices[i]->text.y;
		}
		if(M3D->mod[idObj]->surfacetype='Q')
		{
			vtable[nbSurf-4]=new vertex;
			vtable[nbSurf-4]->p.x=-10;
			vtable[nbSurf-4]->p.y=0;
			vtable[nbSurf-4]->p.z=-10;
			vtable[nbSurf-4]->text.x=1;
			vtable[nbSurf-4]->text.y=0;
			vtable[nbSurf-3]=new vertex;
			vtable[nbSurf-3]->p.x=10;
			vtable[nbSurf-3]->p.y=0;
			vtable[nbSurf-3]->p.z=-10;
			vtable[nbSurf-3]->text.x=1;
			vtable[nbSurf-3]->text.y=1;
			vtable[nbSurf-2]=new vertex;
			vtable[nbSurf-2]->p.x=10;
			vtable[nbSurf-2]->p.y=0;
			vtable[nbSurf-2]->p.z=10;
			vtable[nbSurf-2]->text.x=0;
			vtable[nbSurf-2]->text.y=1;
			vtable[nbSurf-1]=new vertex;
			vtable[nbSurf-1]->p.x=-10;
			vtable[nbSurf-1]->p.y=0;
			vtable[nbSurf-1]->p.z=10;
			vtable[nbSurf-1]->text.x=0;
			vtable[nbSurf-1]->text.y=0;
			printf("Ajout d'une face\n");
		}
		else
		{
			vtable[nbSurf-3]=new vertex;
			vtable[nbSurf-3]->p.x=10;
			vtable[nbSurf-3]->p.y=0;
			vtable[nbSurf-3]->p.z=-10;
			vtable[nbSurf-3]->text.x=1;
			vtable[nbSurf-3]->text.y=1;
			vtable[nbSurf-2]=new vertex;
			vtable[nbSurf-2]->p.x=10;
			vtable[nbSurf-2]->p.y=0;
			vtable[nbSurf-2]->p.z=10;
			vtable[nbSurf-2]->text.x=0;
			vtable[nbSurf-2]->text.y=1;
			vtable[nbSurf-1]=new vertex;
			vtable[nbSurf-1]->p.x=-10;
			vtable[nbSurf-1]->p.y=0;
			vtable[nbSurf-1]->p.z=10;
			vtable[nbSurf-1]->text.x=0;
			vtable[nbSurf-1]->text.y=0;
		}
		for(int u=0;u<M3D->mod[idObj]->nb_vertices;u++) delete M3D->mod[idObj]->vertices[u];
		delete M3D->mod[idObj];
		M3D->mod[idObj]->vertices= new vertex*[nbSurf];
		for(int u=0;u<nbSurf;u++)
		{
			M3D->mod[idObj]->vertices[u]=new vertex;
			M3D->mod[idObj]->vertices[u]->p.x=vtable[u]->p.x;
			M3D->mod[idObj]->vertices[u]->p.y=vtable[u]->p.y;
			M3D->mod[idObj]->vertices[u]->p.z=vtable[u]->p.z;
			M3D->mod[idObj]->vertices[u]->text.x=vtable[u]->text.x;
			M3D->mod[idObj]->vertices[u]->text.y=vtable[u]->text.y;
		}
		M3D->mod[idObj]->nb_vertices=nbSurf;
		
	}

	// Cacher la selection
	if(key=='w')
	{
		hid=!hid;
	}

	// Sauvegarder
	if(key=='x')
	{
		// Sauvegarde de l'importation
		FILE* fOut=fopen(Url,"w");
		unsigned char id= 136;
		fwrite(&id,sizeof(unsigned char),1,fOut);
		int nBtag=0;
		fwrite(&nBtag,sizeof(int),1,fOut);
		fwrite(&(M3D->anim),sizeof(char),1,fOut);
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

	return;
}

#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)	//récupère en int un nombre pointé par un char*

// Fonction pour charger une texture à partir d'un fichier *.bmp
int LoadBMP(char *File)
{
	unsigned char	*Data;
	FILE			*fichier;
	unsigned char	Header[0x36];
	GLuint			DataPos,DataSize;
	GLint			Components;
	GLsizei			Width,Height;
	GLenum			Format,Type;
	GLuint			Name[1];

//Lit le fichier et son header
	fichier = fopen(File,"rb");if (!fichier) return -1;
	if (fread(Header,1,0x36,fichier)!=0x36) EXIT;
	if (Header[0]!='B' || Header[1]!='M')	EXIT;
	if (CTOI(Header[0x1E])!=0)				EXIT;
	if (CTOI(Header[0x1C])!=24)				EXIT;

//Récupère les infos du fichier
	DataPos			= CTOI(Header[0x0A]);
	DataSize		= CTOI(Header[0x22]);
//Récupère les infos de l'image
	Width			= CTOI(Header[0x12]);
	Height			= CTOI(Header[0x16]);
	Type = GL_UNSIGNED_BYTE;
	Format = GL_RGB;
	Components = 3;

	//!!!!
	if (DataSize==0) DataSize=Width*Height*Components;
	if (DataPos==0)  DataPos=0x36;

//Charge l'image
	fseek(fichier,DataPos,0);
	Data = new unsigned char[DataSize];
	if (!Data) EXIT;

	if (fread(Data,1,DataSize,fichier)!=DataSize)
	{
		delete Data;
		fclose(fichier);
		return -1;
	}

	fclose(fichier);

//Inverse R et B
	unsigned char t;
	for (int x=0;x<Width*Height;x++)
	{
		t=Data[x*3];
		Data[x*3]=Data[x*3+2];
		Data[x*3+2]=t;
	}

//Envoie la texture à OpenGL
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, Name);
	glBindTexture(GL_TEXTURE_2D, Name[0]);


	glTexImage2D
	(
		GL_TEXTURE_2D, 	//target
		0,				//mipmap level
		Components,		//nb couleurs
		Width,			//largeur
		Height,			//hauteur
		0,			 	//largeur du bord
		Format,			//type des couleurs
		Type,			//codage de chaque composante
		Data			//Image
	);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	return Name[0];
}

