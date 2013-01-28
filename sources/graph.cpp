/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** graph.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives à l'affichage en général, à la      **
** gestion du clavier, ou à l'initialisation des données   **
** globales.                                               **
**                                                         **
*************************************************************/

// Fonction d'affichage de la map
void Aff_map(char id) // Identifiant permettant de spécifier la map
{
	// Sauvegarde de la matrice courante
	glPushMatrix();
	if(id=='c')
	// Correspond à la map 'CyberIndus'
	{
		// Cube d'environnement ( texture + model )
		glBindTexture(GL_TEXTURE_2D, text_ciel);
		glCallList(id_ciel);

		// Sol ( texture + model )
		glBindTexture(GL_TEXTURE_2D, text_sol);
		glCallList(id_sol);

		// Plateformes et piliers du spatioport ( texture + model )
		glBindTexture(GL_TEXTURE_2D, text_spatioport);
		glCallList(id_spatioport);

		// Tours et bâtiments ( texture + model )
		glBindTexture(GL_TEXTURE_2D, text_hlm);
		glCallList(id_hlm);

		// Tours et bâtiments ( texture + model )
		glBindTexture(GL_TEXTURE_2D, text_tunnel);
		glCallList(id_tunnel);
	}
	// Reprise de la matrice d'origine
	glPopMatrix();

	return;
}

// Gestion d'initialisation globale
void Init(void)
{
	// Activation du test de profondeur
	glEnable(GL_DEPTH_TEST);
	// Activation des textures
	glEnable(GL_TEXTURE_2D);

	// Chargement des textures à partir des fichiers
	text_shoker = LoadBMP("data/textures/ent/shoker.bmp");
	text_ciel = LoadBMP("data/textures/env/ciel.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);		text_sol = LoadBMP("data/textures/env/pierrebl.bmp");
	text_spatioport = LoadBMP("data/textures/wall/spatioport.bmp");
	text_hlm = LoadBMP("data/textures/wall/hlm.bmp");
	text_tunnel = LoadBMP("data/textures/wall/tunnel.bmp");

	// Allocation mémoire de la classe 'wing' du vaisseau principal
	fly=new cl_wing;

	// Initialisation des models
	Init_Models();

	// Paramètrage du brouillard
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, FogColor);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 100.0f);
	glFogf(GL_FOG_END, 1000.0);
	// Activation du brouillard
	glEnable(GL_FOG);

	return;
}

// Fonction d'affichage de la scène
void Display(void)
{
	// Nettoyage du tampon ( par la couleur noire )
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Réinitialisation de la matrice de vue
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Configuration de la caméra ( position, orientation et cadrage )
	gluLookAt(fly->getPos().x-(Cos(fly->getDir())*10)*Cos(valAbs(fly->getInclin())), fly->getPos().y-(Sin(fly->getInclin())*10), fly->getPos().z+(Sin(fly->getDir())*10)*Cos(valAbs(fly->getInclin())),  fly->getPos().x, fly->getPos().y, fly->getPos().z, 0, 1, 0);

	// Affichage d'un shoker
	/*glPushMatrix();
	glTranslated(fly->getPos().x,fly->getPos().y,fly->getPos().z);
	glRotated(-angle,0,1,0);
	glCallList(id_shokerCOR);
	glPopMatrix();

	glPushMatrix();
	glTranslated(fly->getPos().x,fly->getPos().y,fly->getPos().z);
	glRotated(angle,0,1,0);
	glCallList(id_shokerPIQ);
	glPopMatrix();*/

	// Affichage de la map 'CyberIndus'
	Aff_map('c');

	// Affichage du vaisseau
	fly->afficher();

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
	gluPerspective(45.0,(float) w/h, 1.,1500.);
	return;
}

// Fonction de remise à jour
void Idle(void)
{
	// Actualisation des variables
	angle+=5;
	if(angle>360) angle=0;

	// Gérer l'avancement du vaisseau
	fly->avancer();

	// Forcer le reDisplay
	glutPostRedisplay();
	return;
}

// Fonction pour gérer l'appui de touche du clavier
void Keyboard(unsigned char key, int x, int y)
{
	// Actualisation des variables input pour le déplacement du vaisseau
	if(key=='z') fly->input->up=true;
	if(key=='s') fly->input->down=true;
	if(key=='q') fly->input->left=true;
	if(key=='d') fly->input->right=true;

	// Actualisation des variables input pour la vitesse du vaisseau
	if(key=='1') fly->setV(fly->getV()+0.1);
	if(key=='2') fly->setV(fly->getV()-0.1);

	return;
}

// Fonction pour gérer le relachement des touches du clavier
void KeyboardUp(unsigned char key, int x, int y)
{
	// Actualisation des variables input pour le déplacement du vaisseau
	if(key=='z') fly->input->up=false;
	if(key=='s') fly->input->down=false;
	if(key=='q') fly->input->left=false;
	if(key=='d') fly->input->right=false;

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
