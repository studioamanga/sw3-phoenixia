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


void PerspectiveMode(void);
void OrthoMode(int left, int top, int right, int bottom);

float VIEWa1=0,VIEWa2=0,VIEWz=1;

#include "graphm.cpp"
#include "graphj.cpp"

void logOut(char * str)
{
  if(LOG==true)
    printf(str);
  return;
}

// Constructeur
cl_model::cl_model(char * file, char shape, float Rext, float Rint, int resol, char loadtype)
{
  if(shape!=0)
    {
      // Space ( universe )
      if(shape=='U')
	{
	  resol*=NIV_DETAIL;
	  this->nb_objet=1;
	  this->anim='0';
	  this->texture=new cl_texture*[this->nb_objet];
	  this->skin=new int[this->nb_objet];
	  this->skin[0]=glGenLists(1);
	  this->texture[0]=new cl_texture(file, loadtype);
	  glNewList(this->skin[0],GL_COMPILE);
	  glBegin(GL_QUADS);
	  float angy=-(PI/2);
	  for(int re=0 ; re<=(resol/2) ; re++)
	    {
	      float angx=0;
	      float cons=(2*PI)/resol;
	      for(int Re=0 ; Re<resol ; Re++)
		{
		  if( angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		    glTexCoord2f( 0.5*Rint, (angy+PI/2)/PI*Rint);
		  else
		    glTexCoord2f( angx/(2*PI)*Rint, (angy+PI/2)/PI*Rint);
		  if(angy>=(PI/2)-0.01 )
		    glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext+Rint*0.001, sin(angx)*Rext*cos(angy));
		  else
		    glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));

		  angx+=cons;

		  if( angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		    glTexCoord2f( 0.5*Rint, (angy+PI/2)/PI*Rint);
		  else
		    glTexCoord2f( angx/(2*PI)*Rint, (angy+PI/2)/PI*Rint);
		  glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));

		  angy+=cons;

		  if( angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		    glTexCoord2f( 0.5*Rint, (angy+PI/2)/PI*Rint);
		  else
		    glTexCoord2f( angx/(2*PI)*Rint, (angy+PI/2)/PI*Rint);
		  glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));

		  angx-=cons;

		  if( angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		    glTexCoord2f( 0.5*Rint, (angy+PI/2)/PI*Rint);
		  else
		    glTexCoord2f( angx/(2*PI)*Rint, (angy+PI/2)/PI*Rint);
		  if(angy>=(PI/2)-0.01 )
		    glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext-Rint*0.001, sin(angx)*Rext*cos(angy));
		  else
		    glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));

		  angx+=cons;
		  angy-=cons;
		}
	      angy+=cons;
	    }
	  glEnd();
	  glEndList();
	}
      // Shield
      if(shape=='S')
	{
	  resol*=NIV_DETAIL;
	  this->nb_objet=1;
	  this->anim='0';
	  this->texture=new cl_texture*[this->nb_objet];
	  this->skin=new int[this->nb_objet];
	  this->skin[0]=glGenLists(1);
	  this->texture[0]=new cl_texture(file, loadtype);
	  glNewList(this->skin[0],GL_COMPILE);
	  glBegin(GL_QUADS);
	  float ang=0;
	  for(int re=0 ; re<resol ; re++)
	    {
	      glTexCoord2f( 1, 0);
	      glVertex3f( cos(ang)*Rext, 0, sin(ang)*Rext);
	      glTexCoord2f( 1, 1);
	      glVertex3f( cos(ang)*Rint, 0, sin(ang)*Rint);
	      ang+=((2*PI)/resol);
	      glTexCoord2f( 0, 1);
	      glVertex3f( cos(ang)*Rint, 0, sin(ang)*Rint);
	      glTexCoord2f( 0, 0);
	      glVertex3f( cos(ang)*Rext, 0, sin(ang)*Rext);
	    }
	  glEnd();
	  glEndList();
	}
      // Reacteurs
      if(shape=='R')
	{
	  char *urlget=getStrFromMadWing(file, 'R');
	  this->nb_objet=1;
	  this->anim='0';
	  this->texture=new cl_texture*[this->nb_objet];
	  this->skin=new int[this->nb_objet];
	  this->skin[0]=glGenLists(1);
	  this->texture[0]=new cl_texture(urlget);
	  delete urlget;
	  int nbReacteurs=getNbFromMadWing(file, 'R');
	  glNewList(this->skin[0],GL_COMPILE);

	  if(ISARB)
	    {
	      glEnable (GL_POINT_SPRITE_ARB);
	      glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	      glBegin (GL_POINTS);
	    }
	  else
	    glBegin(GL_QUADS);

	  for(int i=0 ; i<nbReacteurs ; i++)
	    {
	      affPoint(getRealFromMadWing(file,'r',i,0),
		       getRealFromMadWing(file,'r',i,1),
		       getRealFromMadWing(file,'r',i,2),
		       getRealFromMadWing(file,'r',i,3));
	    }
	  glEnd();
	  glEndList();
	}
    }
  else
    {
      this->nb_objet=0;

      FILE * fOut=fopen(file,"r");

      unsigned char id;
      fread(&id,sizeof(unsigned char),1,fOut);
      if(id!=136) logOut("Type de model erroné !\n");

      fseek(fOut, sizeof(int), SEEK_CUR);

      fread(&(this->anim),sizeof(char),1,fOut);

      fread(&(this->nb_objet),sizeof(int),1,fOut);
      this->texture=new cl_texture*[this->nb_objet];
      this->skin=new int[this->nb_objet];

      int nbVertices=0;

      for(int i=0 ; i<this->nb_objet ; i++)
	{
	  char text[50];
	  fread(&text, sizeof(char), 50, fOut);
	  char type;
	  fread(&type, sizeof(char), 1, fOut);
	  	  
	  this->skin[i]=glGenLists(1);
	  this->texture[i]=new cl_texture(text);

	  glNewList(this->skin[i],GL_COMPILE);

	  if(type=='M')
	    {
	      fseek(fOut,sizeof(int),SEEK_CUR);
	      int Rext, resol;
	      float fRext, fresol, fTex, nbStars;
	      fread(&fRext,sizeof(float),1,fOut);
	      fread(&fresol,sizeof(float),1,fOut);
	      fread(&fTex,sizeof(float),1,fOut);
	      fread(&nbStars,sizeof(float),1,fOut);
	      fseek(fOut,sizeof(float),SEEK_CUR);

	      Rext=int(fRext);
	      resol=int(fresol);
	      resol*=NIV_DETAIL;

	      if(fTex!=0)
		{
		  glBegin(GL_QUADS);
		  float angy=-(PI/2);
		  for(int re=0 ; re<=(resol/2) ; re++)
		    {
		      float angx=0;
		      for(int Re=0 ; Re<resol ; Re++)
			{
			  glTexCoord2f( angx/(2*PI)*fTex, (angy+PI/2)/PI*fTex);
			  glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));
			  angx+=((2*PI)/resol);
			  glTexCoord2f( angx/(2*PI)*fTex, (angy+PI/2)/PI*fTex);
			  glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));
			  angy+=((2*PI)/resol);
			  glTexCoord2f( angx/(2*PI)*fTex, (angy+PI/2)/PI*fTex);
			  glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));
			  angx-=((2*PI)/resol);
			  glTexCoord2f( angx/(2*PI)*fTex, (angy+PI/2)/PI*fTex);
			  glVertex3f( cos(angx)*Rext*cos(angy), sin(angy)*Rext, sin(angx)*Rext*cos(angy));
			  angx+=((2*PI)/resol);
			  angy-=((2*PI)/resol);
			}
		      angy+=((2*PI)/resol);
		    }
		  glEnd();
		}
	      if(nbStars!=0)
		{
		  glDisable(GL_TEXTURE_2D);
		  glBegin(GL_POINTS);
		  int iColor=int(nbStars/6);
		  Rext-=100;
		  for(int iStar=0 ; iStar<int(nbStars) ; iStar++)
		    {
		      float a1=RandFloat(-M_PI,M_PI), a2=RandFloat(-M_PI,M_PI);
		      if(iColor==0)
			{
			  float cR=(iStar/nbStars/2)+0.5;
			  glColor3f(cR,cR,cR);
			  iColor=int(nbStars/6);
			}
		      glVertex3f(cos(a1)*cos(valAbs(a2))*Rext,
				 sin(a2)*Rext,
				 -sin(a1)*cos(valAbs(a2))*Rext);
		      iColor--;
		    }
		  glEnd();
		  glColor3f(1,1,1);
		  glEnable(GL_TEXTURE_2D);
		}
	      glEndList();
	    }
	  else
	    {
	      switch (type)
		{
		case 'L' :
		  glBegin(GL_TRIANGLES);
		  break;
		case 'T' :
		  glBegin(GL_TRIANGLE_STRIP);
		  break;
		case 'F' :
		  glBegin(GL_TRIANGLE_FAN);
		  break;
		default :
		  glBegin(GL_TRIANGLES);
		}

	      int nb_vert;
	      fread(&nb_vert, sizeof(int), 1, fOut);


	      int quad=0;
	      float x1=0,y1=0,z1=0,tx1=0,ty1=0;
	      float x3=0,y3=0,z3=0,tx3=0,ty3=0;
      
	      for(int y=0 ; y<nb_vert ; y++)
		{
		  float x,y,z,tx,ty;
		  fread(&x, sizeof(float), 1, fOut);
		  fread(&y, sizeof(float), 1, fOut);
		  fread(&z, sizeof(float), 1, fOut);
		  fread(&tx, sizeof(float), 1, fOut);
		  fread(&ty, sizeof(float), 1, fOut);
		  nbVertices++;

		  glTexCoord2f(tx,ty); glVertex3f(x,y,z);

		  quad++;
		  if(quad==1)
		    {
		      x1=x;
		      y1=y;
		      z1=z;
		      tx1=tx;
		      ty1=ty;
		    }
		  if(quad==3)
		    {
		      x3=x;
		      y3=y;
		      z3=z;
		      tx3=tx;
		      ty3=ty;
		    }
		  if(quad==4&&type=='Q')
		    {
		      glTexCoord2f(tx1,ty1); glVertex3f(x1,y1,z1);
		      glTexCoord2f(tx3,ty3); glVertex3f(x3,y3,z3);
		      quad=0;
		    }
		}
	      glEnd();
	      glEndList();
	    }
	}
      //logOut("  [OK] Model chargé (%d objets, %d vertices, file : '%s')\n", this->nb_objet,nbVertices,file);
      fclose (fOut);
    }

}

// Destructeur
cl_model::~cl_model(void)
{
	for(int i=0; i<this->nb_objet ; i++)
	{
		delete this->texture[i];
	}

	delete this->texture;
	delete this->skin;
}

// Affichage
bool cl_model::aff(void)
{
  switch(this->anim)
    {
    case 'S' :
      this->texture[0]->setTexture();
      glCallList(this->skin[0]);
      static float angle=0;
      // Rotation autour de y pour le pivot
      glRotated(angle,0,1,0);
      this->texture[1]->setTexture();
      glCallList(this->skin[1]);

      angle +=0.02*GETTIMER;
      if(angle>360)
	angle-=360;
      
      break;
    case 'M' :
      // Sauvegarde de la matrice courante
      glPushMatrix();
      if(fly)
	// Translation vers les positions en x, y et z du vaisseau
	glTranslated(fly->getPos().x,fly->getPos().y,fly->getPos().z);
      this->texture[0]->setTexture();
      glCallList(this->skin[0]);
      glPopMatrix();
      for(int i=1 ; i<this->nb_objet ; i++)
	{
	  this->texture[i]->setTexture();
	  glCallList(this->skin[i]);
	}
      
      break;
    default :
      for(int i=0 ; i<this->nb_objet ; i++)
	{
	  this->texture[i]->setTexture();
	  glCallList(this->skin[i]);
	}
      break;
    }
  return true;
}

// Gestion d'initialisation globale
void Init(void)
{
  char* szExtList = (char*) glGetString (GL_EXTENSIONS);
  if (!strstr (szExtList, "GL_ARB_point_sprite"))
    {
      // L'extension GL_ARB_point_sprite n'est pas supporté 
      ISARB=false;
      logOut(" [!] L'extension OpenGL 'GL_ARB_point_sprite', n'est pas supporté ...\n");
      logOut(" [!] Veuillez installer les derniers pilotes de votre carte graphique.\n");
    }

  
  Particule= new ParticuleManager;
  logOut("  [OK] Moteur à Particule initialisé\n");

  clSoundMan::Create();
  logOut("  [OK] Son initialisé\n");

  // Activation du test de profondeur
  glEnable(GL_DEPTH_TEST);
  // Activation des textures
  glEnable(GL_TEXTURE_2D);

  if(LIGHTON)
    {
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
    }

  clAvaMan::Create();
  logOut("  [OK] Manager d'Avatar initialisé\n");

  switch(Disp)
    {
    case DISP_JEU :
      InitJ();
      break;
    case DISP_MENU :
      InitM();
      break;
    }

  // Chargement de la configuration
  LoadCfg();

  srand(GETTIME);

  return;
}


// Fonction d'affichage de la scène
void Display(void)
{  
  switch(Disp)
    {
    case DISP_JEU :
      DisplayJ();
      break;
    case DISP_MENU :
      DisplayM();
      break;
    }

  return;
}

// Fonction de redimensionnement de la fenêtre
void Reshape(int w,int h)
{
  // Réglage du rendu et de la perspective
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,(float) w/h, 1.,10000);
  return;
}

// Fonction de remise à jour
void Idle(void)
{
  switch(Disp)
    {
    case DISP_JEU :
      IdleJ();
      break;
    case DISP_MENU :
      IdleM();
      break;
    }

  return;
}

void PerspectiveMode(void)
{
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void OrthoMode(int left, int top, int right, int bottom)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(left,right,bottom,top,0,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //SCREEN_X=right-left;
  //SCREEN_Y=bottom-top;

  return;
}

int wideScr(bool upd, bool chg)
{
  static float wide=0;
  static bool sens=false;

  if( menuCommentTime>0 && wide==0)
    sens=true;
  if( menuCommentTime<=0 && wide>0)
    sens=false;

  if(chg)
    sens=!sens;

  if(upd)
    {
      if(!sens && wide>0)
	wide-=GETTIMER*0.025;
      if(sens && wide<100)
	wide+=GETTIMER*0.025;

      if(wide<0)
	wide=0;
      if(wide>100)
	wide=100;
    }

  return int(wide);
}

void affPoint(float x, float y, float z, float rayon)
{
  if(ISARB)
    {
      glVertex3f (x, y, z);
      return;
    }
  glTexCoord2f(0.0,0.0 );
  glVertex3f(x-rayon, y-rayon, z);
  glTexCoord2f(0.0,1.0 );
  glVertex3f(x-rayon, y+rayon, z);
  glTexCoord2f(1.0,1.0 );
  glVertex3f(x+rayon, y+rayon, z);
  glTexCoord2f(1.0,0.0 );
  glVertex3f(x+rayon, y-rayon, z);

  glVertex3f(x-rayon, y, z-rayon);
  glTexCoord2f(1.0,1.0 );
  glVertex3f(x-rayon, y, z+rayon);
  glTexCoord2f(0.0,1.0 );
  glVertex3f(x+rayon, y, z+rayon);
  glTexCoord2f(0.0,0.0 );
  glVertex3f(x+rayon, y, z-rayon);

  glVertex3f(x, y-rayon, z-rayon);
  glTexCoord2f(0.0,1.0 );
  glVertex3f(x, y+rayon, z-rayon);
  glTexCoord2f(1.0,1.0 );
  glVertex3f(x, y+rayon, z+rayon);
  glTexCoord2f(1.0,0.0 );
  glVertex3f(x, y-rayon, z+rayon);

  return;
}
