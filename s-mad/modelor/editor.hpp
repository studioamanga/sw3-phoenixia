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
bool newLook=false;
#define MAX_SELECT 20
int idSelect[MAX_SELECT+1]={-1};
bool selectSymetrie[3]={false,false,false};

float valAbs(float x)	//**** Retourne la valeur absolue d'un float ****//
{
  if(x<0) x*=-1;
  return x;
}

void selectBySymetrie(float fx, float fy, float fz)
{
  int idSel=0;
  idSelect[0]=-1;
  for(int iv=0 ; iv<M3D->Objets[idObj].nbVertices ; iv++)
    {
      if( ((M3D->Objets[idObj].Vertices[iv].x==fx) &&
	   (M3D->Objets[idObj].Vertices[iv].y==fy) &&
	   (M3D->Objets[idObj].Vertices[iv].z==fz)) ||
	  ((selectSymetrie[0]) &&
	   (M3D->Objets[idObj].Vertices[iv].x==-fx) &&
	   (M3D->Objets[idObj].Vertices[iv].y==fy) &&
	   (M3D->Objets[idObj].Vertices[iv].z==fz)) ||
	  ((selectSymetrie[1]) &&
	   (M3D->Objets[idObj].Vertices[iv].x==fx) &&
	   (M3D->Objets[idObj].Vertices[iv].y==-fy) &&
	   (M3D->Objets[idObj].Vertices[iv].z==fz)) ||
	  ((selectSymetrie[2]) &&
	   (M3D->Objets[idObj].Vertices[iv].x==fx) &&
	   (M3D->Objets[idObj].Vertices[iv].y==fy) &&
	   (M3D->Objets[idObj].Vertices[iv].z==-fz)))
	{
	  idSelect[idSel]=iv;
	  idSel++;
	  idSelect[idSel]=-1;
	  if(idSel>=MAX_SELECT)
	    break;
	}
    }
  printf("%d vertex selectionnes\n", idSel);
  return;
}

// Fonctions de trigonom�trie ( conversion degr�s-radians )
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

// Fonction d'affichage de la sc�ne
void Display(void)
{
  // Nettoyage du tampon ( par la couleur noire )
  glClearColor(0,vert,0,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // R�initialisation de la matrice de vue
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Configuration de la cam�ra ( position, orientation et cadrage )
  gluLookAt(posX-(Cos(angleY)*10)*Cos(valAbs(angleX)), posY-(Sin(angleX)*10), posZ+(Sin(angleY)*10)*Cos(valAbs(angleX)), posX, posY, posZ,0,1,0);

  for(int i=0 ; i<M3D->nbObjets ; i++)
    {
      glBindTexture(GL_TEXTURE_2D,Textures[i]);
      switch(M3D->Objets[i].typeSurf)
	{
	case 'L' :
	  glBegin(GL_TRIANGLES);
	  break;
	default :
	  glBegin(GL_QUADS);
	  break;
	}
      for(int y=0 ; y<M3D->Objets[i].nbVertices ; y++)
	{
	  glTexCoord2f(M3D->Objets[i].Vertices[y].tx,M3D->Objets[i].Vertices[y].ty);
	  glVertex3f(M3D->Objets[i].Vertices[y].x,M3D->Objets[i].Vertices[y].y,M3D->Objets[i].Vertices[y].z);
	}
      glEnd();
    }

  if(hid==false)
    {
      glTranslated(M3D->Objets[idObj].Vertices[idVertex].x, M3D->Objets[idObj].Vertices[idVertex].y, M3D->Objets[idObj].Vertices[idVertex].z);
      glColor3f(0,0,0);
      glutSolidSphere(precis,8,8);
      glutWireSphere(50,8,8);
      glutWireSphere(200,15,15);
      glColor3f(1,1,1);
    }

  // Inversion des buffers ( multi-buffering )
  glutSwapBuffers();
  return;
}

// Fonction de redimensionnement de la fen�tre
void Reshape(int w,int h)
{
  // R�glage du rendu et de la perspective
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,(float) w/h, 1.,500000.);
  return;
}

// Fonction de remise � jour
void Idle(void)
{
  // Actualisation des variables
  vert+=0.01;
  if(vert>=1) vert=0;

  // Forcer le reDisplay
  glutPostRedisplay();
  return;
}

// Fonction pour g�rer l'appui de touche du clavier
void Keyboard(unsigned char key, int x, int y)
{
  // R�glage de la vitesse
  if(key=='9') vit++;
  if(key=='6') { vit--; if(vit<0) vit=0; }

  // R�glage de la pr�cision
  if(key=='+') { precis*=4; printf("Precision : %f\n", precis); }
  if(key=='-') { precis/=4; printf("Precision : %f\n", precis); }


  // Actualisation des variables input pour le d�placement de la cam�ra
  if(key=='z') angleX+=vit;
  if(key=='s') angleX-=vit;
  if(key=='q') angleY+=vit;
  if(key=='d') angleY-=vit;
  if(angleX>360) angleX-=360;
  if(angleY>360) angleY-=360;
  if(angleX<0) angleX+=360;
  if(angleY<0) angleY+=360;

  // Axes de symetrie
  if(key==';' || key==':' || key=='!')
    {
      if(key==';')
	selectSymetrie[0]=!selectSymetrie[0];
      if(key==':')
	selectSymetrie[1]=!selectSymetrie[1];
      if(key=='!')
	selectSymetrie[2]=!selectSymetrie[2];
      // Affichage
      printf("Symetries : ");
      if(selectSymetrie[0])
	printf("X ");
      if(selectSymetrie[1])
	printf("Y ");
      if(selectSymetrie[2])
	printf("Z ");
      printf("\n");
    }
  // D�placement
  if(key=='1')
    {
      // On remet � jour la position
      posY+=vit*Sin(angleX);
      posX+=vit*Cos(angleY)*Cos(valAbs(angleX));
      posZ-=vit*Sin(angleY)*Cos(valAbs(angleX));
    }
  if(key=='2')
    {
      // On remet � jour la position
      posY-=vit*Sin(angleX);
      posX-=vit*Cos(angleY)*Cos(valAbs(angleX));
      posZ+=vit*Sin(angleY)*Cos(valAbs(angleX));
    }

  // Focus sur le vertex
  if(key=='3')
    {
      static int iFoc=0;

      switch(iFoc)
	{
	case 0 :
	  angleY=135;
	  angleX=-45;
	  break;
	case 1 :
	  angleY=0;
	  angleX=-90;
	  break;
	case 2 :
	  angleY=0;
	  angleX=90;
	  break;
	case 3 :
	  angleY=0;
	  angleX=0;
	  break;
	case 4 :
	  angleY=0;
	  angleX=180;
	  break;
	case 5 :
	  angleY=90;
	  angleX=0;
	  break;
	case 6 :
	  angleY=-90;
	  angleX=0;
	default :
	  iFoc=-1;
	}
      iFoc++;
      posX=M3D->Objets[idObj].Vertices[idVertex].x+3*Cos(angleY)*Cos(angleX);
      posY=M3D->Objets[idObj].Vertices[idVertex].y+3*Sin(angleX);
      posZ=M3D->Objets[idObj].Vertices[idVertex].z+3*Sin(-angleY)*Cos(angleX);
    }

  // Changement d'objet
  if(key=='8')
    {
      idObj++;
      if(idObj>=M3D->nbObjets) idObj=M3D->nbObjets-1;
      posX=M3D->Objets[idObj].Vertices[idVertex].x+10;
      posY=M3D->Objets[idObj].Vertices[idVertex].y+10;
      posZ=M3D->Objets[idObj].Vertices[idVertex].z+10;
      angleY=135;
      angleX=-45;
      idVertex=0;
    }
  if(key=='5')
    {
      idObj--;
      if(idObj<=0) idObj=0;
      posX=M3D->Objets[idObj].Vertices[idVertex].x+10;
      posY=M3D->Objets[idObj].Vertices[idVertex].y+10;
      posZ=M3D->Objets[idObj].Vertices[idVertex].z+10;
      angleY=135;
      angleX=-45;
      idVertex=0;
    }

  // Changement de vertex
  if(key=='7')
    {
      idVertex++;
      if(idVertex>=M3D->Objets[idObj].nbVertices)  idVertex=M3D->Objets[idObj].nbVertices-1;
      if(newLook==true)
	{
	  posX=M3D->Objets[idObj].Vertices[idVertex].x+5;
	  posY=M3D->Objets[idObj].Vertices[idVertex].y+5;
	  posZ=M3D->Objets[idObj].Vertices[idVertex].z+5;
	  angleY=135;
	  angleX=-45;
	}
      // Selection des Vertices assimil�s
      selectBySymetrie(M3D->Objets[idObj].Vertices[idVertex].x, M3D->Objets[idObj].Vertices[idVertex].y, M3D->Objets[idObj].Vertices[idVertex].z);
    }
  if(key=='4')
    {
      idVertex--;
      if(idVertex<=0) idVertex=0;
      if(newLook==true)
	{
	  posX=M3D->Objets[idObj].Vertices[idVertex].x+5;
	  posY=M3D->Objets[idObj].Vertices[idVertex].y+5;
	  posZ=M3D->Objets[idObj].Vertices[idVertex].z+5;
	  angleY=135;
	  angleX=-45;
	}
      // Selection des Vertices assimil�s
      selectBySymetrie(M3D->Objets[idObj].Vertices[idVertex].x, M3D->Objets[idObj].Vertices[idVertex].y, M3D->Objets[idObj].Vertices[idVertex].z);
    }

  // Modification des coordonn�es
  if(key=='y')
    {
      for(int iv=0 ; ; iv++)
	{
	  if(idSelect[iv]==-1)
	    break;
	  M3D->Objets[idObj].Vertices[idSelect[iv]].x+=precis;
	}
    }
  if(key=='h')
    {
      for(int iv=0 ; ; iv++)
	{
	  if(idSelect[iv]==-1)
	    break;
	  M3D->Objets[idObj].Vertices[idSelect[iv]].x-=precis;
	}
    }
  if(key=='u')
    {
      for(int iv=0 ; ; iv++)
	{
	  if(idSelect[iv]==-1)
	    break;
	  M3D->Objets[idObj].Vertices[idSelect[iv]].y+=precis;
	}
    }
  if(key=='j')
    {
      for(int iv=0 ; ; iv++)
	{
	  if(idSelect[iv]==-1)
	    break;
	  M3D->Objets[idObj].Vertices[idSelect[iv]].y-=precis;
	}
    }
  if(key=='i')
    {
      for(int iv=0 ; ; iv++)
	{
	  if(idSelect[iv]==-1)
	    break;
	  M3D->Objets[idObj].Vertices[idSelect[iv]].z+=precis;
	}
    }
  if(key=='k')
    {
      for(int iv=0 ; ; iv++)
	{
	  if(idSelect[iv]==-1)
	    break;
	  M3D->Objets[idObj].Vertices[idSelect[iv]].z-=precis;
	}
    }
  // Modification des coordonn�es de texture
  if(key=='o')
    {
      M3D->Objets[idObj].Vertices[idVertex].x+=precis;
    }
  if(key=='l')
    {
      M3D->Objets[idObj].Vertices[idVertex].tx-=precis;
    }
  if(key=='p')
    {
      M3D->Objets[idObj].Vertices[idVertex].ty+=precis;
    }
  if(key=='m')
    {
      M3D->Objets[idObj].Vertices[idVertex].ty-=precis;
    }
  if(key=='b')
    {
      printf("Vertex n%d, Objet n%d, Pos : %f, %f, %f, Dist de l'origine : %f\n",idVertex+1,idObj+1,M3D->Objets[idObj].Vertices[idVertex].x,M3D->Objets[idObj].Vertices[idVertex].y,M3D->Objets[idObj].Vertices[idVertex].z, sqrt(M3D->Objets[idObj].Vertices[idVertex].x*M3D->Objets[idObj].Vertices[idVertex].x+M3D->Objets[idObj].Vertices[idVertex].y*M3D->Objets[idObj].Vertices[idVertex].y+M3D->Objets[idObj].Vertices[idVertex].z*M3D->Objets[idObj].Vertices[idVertex].z));
    }
  if(key=='v')
    {
      newLook=!newLook;
    }

  // Nouvelle face
  if(key=='n')
    {/*
      int nbSurf=M3D->Objets[idObj]->nb_Vertices;
      if(M3D->Objets[idObj]->surfacetype='Q') nbSurf+=4;
      else nbSurf+=3;
      vertex ** vtable;
      vtable=new vertex * [nbSurf];
      for(int i=0 ; i<M3D->Objets[idObj]->nb_Vertices ;i++)
	{
	  vtable[i]=new vertex;
	  vtable[i]->p.x=M3D->Objets[idObj]->Vertices[i]->p.x;
	  vtable[i]->p.y=M3D->Objets[idObj]->Vertices[i]->p.y;
	  vtable[i]->p.z=M3D->Objets[idObj]->Vertices[i]->p.z;
	  vtable[i]->text.x=M3D->Objets[idObj]->Vertices[i]->text.x;
	  vtable[i]->text.y=M3D->Objets[idObj]->Vertices[i]->text.y;
	}
      if(M3D->Objets[idObj]->surfacetype='Q')
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
      for(int u=0;u<M3D->Objets[idObj]->nb_Vertices;u++) delete M3D->Objets[idObj]->Vertices[u];
      delete M3D->Objets[idObj];
      M3D->Objets[idObj]->Vertices= new vertex*[nbSurf];
      for(int u=0;u<nbSurf;u++)
	{
	  M3D->Objets[idObj]->Vertices[u]=new vertex;
	  M3D->Objets[idObj]->Vertices[u]->p.x=vtable[u]->p.x;
	  M3D->Objets[idObj]->Vertices[u]->p.y=vtable[u]->p.y;
	  M3D->Objets[idObj]->Vertices[u]->p.z=vtable[u]->p.z;
	  M3D->Objets[idObj]->Vertices[u]->text.x=vtable[u]->text.x;
	  M3D->Objets[idObj]->Vertices[u]->text.y=vtable[u]->text.y;
	}
	M3D->Objets[idObj]->nb_Vertices=nbSurf;*/
    }

  // Cacher la selection
  if(key=='w')
    {
      hid=!hid;
    }

  // Sauvegarder
  if(key=='x')
    {
      saveMadModel(M3D);
      printf("[!] Model sauvegarde\n");
    }

  return;
}

#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)	//r�cup�re en int un nombre point� par un char*

// Fonction pour charger une texture � partir d'un fichier *.bmp
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

//R�cup�re les infos du fichier
	DataPos			= CTOI(Header[0x0A]);
	DataSize		= CTOI(Header[0x22]);
//R�cup�re les infos de l'image
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

//Envoie la texture � OpenGL
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

#ifndef _libtarga_h_
#define _libtarga_h_


/* uncomment this line if you're compiling on a big-endian machine */
/* #define WORDS_BIGENDIAN */


/* make sure these types reflect your system's type sizes. */
#define byte    char
#define int32   int
#define int16   short

#define ubyte   unsigned byte
#define uint32  unsigned int32
#define uint16  unsigned int16



/*  
    Truecolor images supported:

    bits            breakdown   components
    --------------------------------------
    32              8-8-8-8     RGBA
    24              8-8-8       RGB
    16              5-6-5       RGB
    15              5-5-5-1     RGB (ignore extra bit)


    Paletted images supported:
    
    index size      palette entry   breakdown   components
    ------------------------------------------------------
    8               <any of above>  <same as above> ..
    16              <any of above>  <same as above> ..
    24              <any of above>  <same as above> ..

*/



/*

   Targa files are read in and converted to
   any of these three for you -- you choose which you want.

   This is the 'format' argument to tga_create/load/write.
   
   For create and load, format is what you want the data
   converted to.

   For write, format is what format the data you're writing
   is in. (NOT the format you want written)

   Only TGA_TRUECOLOR_32 supports an alpha channel.

*/

#define TGA_TRUECOLOR_32      (4)
#define TGA_TRUECOLOR_24      (3)


/*
   Image data will start in the low-left corner
   of the image.
*/


#ifdef __cplusplus
extern "C" {
#endif


/* Error handling routines */
int             tga_get_last_error();
const char *    tga_error_string( int error_code );


/* Creating/Loading images  --  a return of NULL indicates a fatal error */
void * tga_create( int width, int height, unsigned int format );
void * tga_load( const char * file, int * width, int * height, unsigned int format );


/* Writing images to file  --  a return of 1 indicates success, 0 indicates error*/
int tga_write_raw( const char * file, int width, int height, unsigned char * dat, unsigned int format );
int tga_write_rle( const char * file, int width, int height, unsigned char * dat, unsigned int format );



#ifdef __cplusplus
}
#endif


#endif /* _libtarga_h_ */

/*
** libtarga.c -- routines for reading targa files.
*/

#include <stdio.h>
#include <malloc.h>




#define TGA_IMG_NODATA             (0)
#define TGA_IMG_UNC_PALETTED       (1)
#define TGA_IMG_UNC_TRUECOLOR      (2)
#define TGA_IMG_UNC_GRAYSCALE      (3)
#define TGA_IMG_RLE_PALETTED       (9)
#define TGA_IMG_RLE_TRUECOLOR      (10)
#define TGA_IMG_RLE_GRAYSCALE      (11)


#define TGA_LOWER_LEFT             (0)
#define TGA_LOWER_RIGHT            (1)
#define TGA_UPPER_LEFT             (2)
#define TGA_UPPER_RIGHT            (3)


#define HDR_LENGTH               (18)
#define HDR_IDLEN                (0)
#define HDR_CMAP_TYPE            (1)
#define HDR_IMAGE_TYPE           (2)
#define HDR_CMAP_FIRST           (3)
#define HDR_CMAP_LENGTH          (5)
#define HDR_CMAP_ENTRY_SIZE      (7)
#define HDR_IMG_SPEC_XORIGIN     (8)
#define HDR_IMG_SPEC_YORIGIN     (10)
#define HDR_IMG_SPEC_WIDTH       (12)
#define HDR_IMG_SPEC_HEIGHT      (14)
#define HDR_IMG_SPEC_PIX_DEPTH   (16)
#define HDR_IMG_SPEC_IMG_DESC    (17)



#define TGA_ERR_NONE                    (0)
#define TGA_ERR_BAD_HEADER              (1)
#define TGA_ERR_OPEN_FAILS              (2)
#define TGA_ERR_BAD_FORMAT              (3)
#define TGA_ERR_UNEXPECTED_EOF          (4)
#define TGA_ERR_NODATA_IMAGE            (5)
#define TGA_ERR_COLORMAP_FOR_GRAY       (6)
#define TGA_ERR_BAD_COLORMAP_ENTRY_SIZE (7)
#define TGA_ERR_BAD_COLORMAP            (8)
#define TGA_ERR_READ_FAILS              (9)
#define TGA_ERR_BAD_IMAGE_TYPE          (10)
#define TGA_ERR_BAD_DIMENSIONS          (11)



static uint32 TargaError;


static int16 ttohs( int16 val );
/*static int16 htots( int16 val );*/
static int32 ttohl( int32 val );
static int32 htotl( int32 val );


static uint32 tga_get_pixel( FILE * tga, ubyte bytes_per_pix, 
                            ubyte * colormap, ubyte cmap_bytes_entry );
static uint32 tga_convert_color( uint32 pixel, uint32 bpp_in, ubyte alphabits, uint32 format_out );
static void tga_write_pixel_to_mem( ubyte * dat, ubyte img_spec, uint32 number, 
                                   uint32 w, uint32 h, uint32 pixel, uint32 format );



/* returns the last error encountered */
int tga_get_last_error() {
    return( TargaError );
}


/* returns a pointer to the string for an error code */
const char * tga_error_string( int error_code ) {

    switch( error_code ) {
    
    case TGA_ERR_NONE:
        return( "no error" );

    case TGA_ERR_BAD_HEADER:
        return( "bad image header" );

    case TGA_ERR_OPEN_FAILS:
        return( "cannot open file" );

    case TGA_ERR_BAD_FORMAT:
        return( "bad format argument" );

    case TGA_ERR_UNEXPECTED_EOF:
        return( "unexpected end-of-file" );

    case TGA_ERR_NODATA_IMAGE:
        return( "image contains no data" );

    case TGA_ERR_COLORMAP_FOR_GRAY:
        return( "found colormap for a grayscale image" );

    case TGA_ERR_BAD_COLORMAP_ENTRY_SIZE:
        return( "unsupported colormap entry size" );

    case TGA_ERR_BAD_COLORMAP:
        return( "bad colormap" );

    case TGA_ERR_READ_FAILS:
        return( "cannot read from file" );

    case TGA_ERR_BAD_IMAGE_TYPE:
        return( "unknown image type" );

    case TGA_ERR_BAD_DIMENSIONS:
        return( "image has size 0 width or height (or both)" );

    default:
        return( "unknown error" );

    }

    // shut up compiler..
    return( NULL );

}



/* creates a targa image of the desired format */
void * tga_create( int width, int height, unsigned int format ) {

    switch( format ) {
        
    case TGA_TRUECOLOR_32:
        return( (void *)malloc( width * height * 4 ) );
        
    case TGA_TRUECOLOR_24:
        return( (void *)malloc( width * height * 3 ) );
        
    default:
        TargaError = TGA_ERR_BAD_FORMAT;
        break;

    }

    return( NULL );

}



/* loads and converts a targa from disk */
void * tga_load( const char * filename, 
                int * width, int * height, unsigned int format ) {
    
    ubyte  idlen;               // length of the image_id string below.
    ubyte  cmap_type;           // paletted image <=> cmap_type
    ubyte  image_type;          // can be any of the IMG_TYPE constants above.
    uint16 cmap_first;          // 
    uint16 cmap_length;         // how long the colormap is
    ubyte  cmap_entry_size;     // how big a palette entry is.
    uint16 img_spec_xorig;      // the x origin of the image in the image data.
    uint16 img_spec_yorig;      // the y origin of the image in the image data.
    uint16 img_spec_width;      // the width of the image.
    uint16 img_spec_height;     // the height of the image.
    ubyte  img_spec_pix_depth;  // the depth of a pixel in the image.
    ubyte  img_spec_img_desc;   // the image descriptor.

    FILE * targafile;

    ubyte * tga_hdr = NULL;

    ubyte * colormap = NULL;

    ubyte cmap_bytes_entry = 0;
    uint32 cmap_bytes;
    
    uint32 tmp_col;
    uint32 tmp_int32;
    ubyte  tmp_byte;

    ubyte alphabits = 0;

    uint32 num_pixels;
    
    uint32 i;
    uint32 j;

    ubyte * image_data;
    uint32 img_dat_len;

    ubyte bytes_per_pix;

    ubyte true_bits_per_pixel;

    uint32 bytes_total = 0;

    ubyte packet_header;
    ubyte repcount;
    

    switch( format ) {

    case TGA_TRUECOLOR_24:
    case TGA_TRUECOLOR_32:
        break;

    default:
        TargaError = TGA_ERR_BAD_FORMAT;
        return( NULL );

    }

    
    /* open binary image file */
    targafile = fopen( filename, "rb" );
    if( targafile == NULL ) {
        TargaError = TGA_ERR_OPEN_FAILS;
        return( NULL );
    }


    /* allocate memory for the header */
    tga_hdr = (ubyte *)malloc( HDR_LENGTH );

    /* read the header in. */
    if( fread( (void *)tga_hdr, 1, HDR_LENGTH, targafile ) != HDR_LENGTH ) {
        free( tga_hdr );
        TargaError = TGA_ERR_BAD_HEADER;
        return( NULL );
    }

    
    /* byte order is important here. */
    idlen              = (ubyte)tga_hdr[HDR_IDLEN];
    
    image_type         = (ubyte)tga_hdr[HDR_IMAGE_TYPE];
    
    cmap_type          = (ubyte)tga_hdr[HDR_CMAP_TYPE];
    cmap_first         = ttohs( *(uint16 *)(&tga_hdr[HDR_CMAP_FIRST]) );
    cmap_length        = ttohs( *(uint16 *)(&tga_hdr[HDR_CMAP_LENGTH]) );
    cmap_entry_size    = (ubyte)tga_hdr[HDR_CMAP_ENTRY_SIZE];

    img_spec_xorig     = ttohs( *(uint16 *)(&tga_hdr[HDR_IMG_SPEC_XORIGIN]) );
    img_spec_yorig     = ttohs( *(uint16 *)(&tga_hdr[HDR_IMG_SPEC_YORIGIN]) );
    img_spec_width     = ttohs( *(uint16 *)(&tga_hdr[HDR_IMG_SPEC_WIDTH]) );
    img_spec_height    = ttohs( *(uint16 *)(&tga_hdr[HDR_IMG_SPEC_HEIGHT]) );
    img_spec_pix_depth = (ubyte)tga_hdr[HDR_IMG_SPEC_PIX_DEPTH];
    img_spec_img_desc  = (ubyte)tga_hdr[HDR_IMG_SPEC_IMG_DESC];

    free( tga_hdr );


    num_pixels = img_spec_width * img_spec_height;

    if( num_pixels == 0 ) {
        TargaError = TGA_ERR_BAD_DIMENSIONS;
        return( NULL );
    }

    
    alphabits = img_spec_img_desc & 0x0F;

    
    /* seek past the image id, if there is one */
    if( idlen ) {
        if( fseek( targafile, idlen, SEEK_CUR ) ) {
            TargaError = TGA_ERR_UNEXPECTED_EOF;
            return( NULL );
        }
    }


    /* if this is a 'nodata' image, just jump out. */
    if( image_type == TGA_IMG_NODATA ) {
        TargaError = TGA_ERR_NODATA_IMAGE;
        return( NULL );
    }


    /* now we're starting to get into the meat of the matter. */
    
    
    /* deal with the colormap, if there is one. */
    if( cmap_type ) {

        switch( image_type ) {
            
        case TGA_IMG_UNC_PALETTED:
        case TGA_IMG_RLE_PALETTED:
            break;
            
        case TGA_IMG_UNC_TRUECOLOR:
        case TGA_IMG_RLE_TRUECOLOR:
            // this should really be an error, but some really old
            // crusty targas might actually be like this (created by TrueVision, no less!)
            // so, we'll hack our way through it.
            break;
            
        case TGA_IMG_UNC_GRAYSCALE:
        case TGA_IMG_RLE_GRAYSCALE:
            TargaError = TGA_ERR_COLORMAP_FOR_GRAY;
            return( NULL );
        }
        
        /* ensure colormap entry size is something we support */
        if( !(cmap_entry_size == 15 || 
            cmap_entry_size == 16 ||
            cmap_entry_size == 24 ||
            cmap_entry_size == 32) ) {
            TargaError = TGA_ERR_BAD_COLORMAP_ENTRY_SIZE;
            return( NULL );
        }
        
        
        /* allocate memory for a colormap */
        if( cmap_entry_size & 0x07 ) {
            cmap_bytes_entry = (((8 - (cmap_entry_size & 0x07)) + cmap_entry_size) >> 3);
        } else {
            cmap_bytes_entry = (cmap_entry_size >> 3);
        }
        
        cmap_bytes = cmap_bytes_entry * cmap_length;
        colormap = (ubyte *)malloc( cmap_bytes );
        
        
        for( i = 0; i < cmap_length; i++ ) {
            
            /* seek ahead to first entry used */
            if( cmap_first != 0 ) {
                fseek( targafile, cmap_first * cmap_bytes_entry, SEEK_CUR );
            }
            
            tmp_int32 = 0;
            for( j = 0; j < cmap_bytes_entry; j++ ) {
                if( !fread( &tmp_byte, 1, 1, targafile ) ) {
                    free( colormap );
                    TargaError = TGA_ERR_BAD_COLORMAP;
                    return( NULL );
                }
                tmp_int32 += tmp_byte << (j * 8);
            }

            // byte order correct.
            tmp_int32 = ttohl( tmp_int32 );

            for( j = 0; j < cmap_bytes_entry; j++ ) {
                colormap[i * cmap_bytes_entry + j] = (tmp_int32 >> (8 * j)) & 0xFF;
            }
            
        }

    }


    // compute number of bytes in an image data unit (either index or BGR triple)
    if( img_spec_pix_depth & 0x07 ) {
        bytes_per_pix = (((8 - (img_spec_pix_depth & 0x07)) + img_spec_pix_depth) >> 3);
    } else {
        bytes_per_pix = (img_spec_pix_depth >> 3);
    }


    /* assume that there's one byte per pixel */
    if( bytes_per_pix == 0 ) {
        bytes_per_pix = 1;
    }


    /* compute how many bytes of storage we need for the image */
    bytes_total = img_spec_width * img_spec_height * format;

    image_data = (ubyte *)malloc( bytes_total );

    img_dat_len = img_spec_width * img_spec_height * bytes_per_pix;

    // compute the true number of bits per pixel
    true_bits_per_pixel = cmap_type ? cmap_entry_size : img_spec_pix_depth;

    switch( image_type ) {

    case TGA_IMG_UNC_TRUECOLOR:
    case TGA_IMG_UNC_GRAYSCALE:
    case TGA_IMG_UNC_PALETTED:

        /* FIXME: support grayscale */

        for( i = 0; i < num_pixels; i++ ) {

            // get the color value.
            tmp_col = tga_get_pixel( targafile, bytes_per_pix, colormap, cmap_bytes_entry );
            tmp_col = tga_convert_color( tmp_col, true_bits_per_pixel, alphabits, format );
            
            // now write the data out.
            tga_write_pixel_to_mem( image_data, img_spec_img_desc, 
                i, img_spec_width, img_spec_height, tmp_col, format );

        }
    
        break;


    case TGA_IMG_RLE_TRUECOLOR:
    case TGA_IMG_RLE_GRAYSCALE:
    case TGA_IMG_RLE_PALETTED:

        // FIXME: handle grayscale..

        for( i = 0; i < num_pixels; ) {

            /* a bit of work to do to read the data.. */
            if( fread( &packet_header, 1, 1, targafile ) < 1 ) {
                // well, just let them fill the rest with null pixels then...
                packet_header = 1;
            }

            if( packet_header & 0x80 ) {
                /* run length packet */

                tmp_col = tga_get_pixel( targafile, bytes_per_pix, colormap, cmap_bytes_entry );
                tmp_col = tga_convert_color( tmp_col, true_bits_per_pixel, alphabits, format );
                
                repcount = (packet_header & 0x7F) + 1;
                
                /* write all the data out */
                for( j = 0; j < repcount; j++ ) {
                    tga_write_pixel_to_mem( image_data, img_spec_img_desc, 
                        i + j, img_spec_width, img_spec_height, tmp_col, format );
                }

                i += repcount;

            } else {
                /* raw packet */
                /* get pixel from file */
                
                repcount = (packet_header & 0x7F) + 1;
                
                for( j = 0; j < repcount; j++ ) {
                    
                    tmp_col = tga_get_pixel( targafile, bytes_per_pix, colormap, cmap_bytes_entry );
                    tmp_col = tga_convert_color( tmp_col, true_bits_per_pixel, alphabits, format );
                    
                    tga_write_pixel_to_mem( image_data, img_spec_img_desc, 
                        i + j, img_spec_width, img_spec_height, tmp_col, format );

                }

                i += repcount;

            }

        }

        break;
    

    default:

        TargaError = TGA_ERR_BAD_IMAGE_TYPE;
        return( NULL );

    }

    fclose( targafile );

    *width  = img_spec_width;
    *height = img_spec_height;

    return( (void *)image_data );

}





int tga_write_raw( const char * file, int width, int height, unsigned char * dat, unsigned int format ) {

    FILE * tga;

    uint32 i, j;

    uint32 size = width * height;

    float red, green, blue, alpha;

    char id[] = "written with libtarga";
    ubyte idlen = 21;
    ubyte zeroes[5] = { 0, 0, 0, 0, 0 };
    uint32 pixbuf;
/*    ubyte one = 1;*/
    ubyte cmap_type = 0;
    ubyte img_type  = 2;  // 2 - uncompressed truecolor  10 - RLE truecolor
    uint16 xorigin  = 0;
    uint16 yorigin  = 0;
    ubyte  pixdepth = format * 8;  // bpp
    ubyte img_desc;
    
    
    switch( format ) {

    case TGA_TRUECOLOR_24:
        img_desc = 0;
        break;

    case TGA_TRUECOLOR_32:
        img_desc = 8;
        break;

    default:
        TargaError = TGA_ERR_BAD_FORMAT;
        return( 0 );
        break;

    }

    tga = fopen( file, "wb" );

    if( tga == NULL ) {
        TargaError = TGA_ERR_OPEN_FAILS;
        return( 0 );
    }

    // write id length
    fwrite( &idlen, 1, 1, tga );

    // write colormap type
    fwrite( &cmap_type, 1, 1, tga );

    // write image type
    fwrite( &img_type, 1, 1, tga );

    // write cmap spec.
    fwrite( &zeroes, 5, 1, tga );

    // write image spec.
    fwrite( &xorigin, 2, 1, tga );
    fwrite( &yorigin, 2, 1, tga );
    fwrite( &width, 2, 1, tga );
    fwrite( &height, 2, 1, tga );
    fwrite( &pixdepth, 1, 1, tga );
    fwrite( &img_desc, 1, 1, tga );


    // write image id.
    fwrite( &id, idlen, 1, tga );

    // color correction -- data is in RGB, need BGR.
    for( i = 0; i < size; i++ ) {

        pixbuf = 0;
        for( j = 0; j < format; j++ ) {
            pixbuf += dat[i*format+j] << (8 * j);
        }

        switch( format ) {

        case TGA_TRUECOLOR_24:

            pixbuf = ((pixbuf & 0xFF) << 16) + 
                     (pixbuf & 0xFF00) + 
                     ((pixbuf & 0xFF0000) >> 16);

            pixbuf = htotl( pixbuf );
            
            fwrite( &pixbuf, 3, 1, tga );

            break;

        case TGA_TRUECOLOR_32:

            /* need to un-premultiply alpha.. */

            red     = (pixbuf & 0xFF) / 255.0f;
            green   = ((pixbuf & 0xFF00) >> 8) / 255.0f;
            blue    = ((pixbuf & 0xFF0000) >> 16) / 255.0f;
            alpha   = ((pixbuf & 0xFF000000) >> 24) / 255.0f;

            if( alpha > 0.0001 ) {
                red /= alpha;
                green /= alpha;
                blue /= alpha;
            }

            /* clamp to 1.0f */

            red = red > 1.0f ? 255.0f : red * 255.0f;
            green = green > 1.0f ? 255.0f : green * 255.0f;
            blue = blue > 1.0f ? 255.0f : blue * 255.0f;
            alpha = alpha > 1.0f ? 255.0f : alpha * 255.0f;

            pixbuf = (ubyte)blue + (((ubyte)green) << 8) + 
                (((ubyte)red) << 16) + (((ubyte)alpha) << 24);
                
            pixbuf = htotl( pixbuf );
           
            fwrite( &pixbuf, 4, 1, tga );

            break;

        }

    }

    fclose( tga );

    return( 1 );

}





int tga_write_rle( const char * file, int width, int height, unsigned char * dat, unsigned int format ) {

    FILE * tga;

    uint32 i, j;
    uint32 oc, nc;

    enum RLE_STATE { INIT, NONE, RLP, RAWP };

    int state = INIT;

    uint32 size = width * height;

    uint16 shortwidth = (uint16)width;
    uint16 shortheight = (uint16)height;

    ubyte repcount;

    float red, green, blue, alpha;

    int idx, row, column;

    // have to buffer a whole line for raw packets.
    unsigned char * rawbuf = (unsigned char *)malloc( width * format );  

    char id[] = "written with libtarga";
    ubyte idlen = 21;
    ubyte zeroes[5] = { 0, 0, 0, 0, 0 };
    uint32 pixbuf;
    ubyte one = 1;
    ubyte cmap_type = 0;
    ubyte img_type  = 10;  // 2 - uncompressed truecolor  10 - RLE truecolor
    uint16 xorigin  = 0;
    uint16 yorigin  = 0;
    ubyte  pixdepth = format * 8;  // bpp
    ubyte img_desc  = format == TGA_TRUECOLOR_32 ? 8 : 0;
  

    switch( format ) {
    case TGA_TRUECOLOR_24:
    case TGA_TRUECOLOR_32:
        break;

    default:
        TargaError = TGA_ERR_BAD_FORMAT;
        return( 0 );
    }


    tga = fopen( file, "wb" );

    if( tga == NULL ) {
        TargaError = TGA_ERR_OPEN_FAILS;
        return( 0 );
    }

    // write id length
    fwrite( &idlen, 1, 1, tga );

    // write colormap type
    fwrite( &cmap_type, 1, 1, tga );

    // write image type
    fwrite( &img_type, 1, 1, tga );

    // write cmap spec.
    fwrite( &zeroes, 5, 1, tga );

    // write image spec.
    fwrite( &xorigin, 2, 1, tga );
    fwrite( &yorigin, 2, 1, tga );
    fwrite( &shortwidth, 2, 1, tga );
    fwrite( &shortheight, 2, 1, tga );
    fwrite( &pixdepth, 1, 1, tga );
    fwrite( &img_desc, 1, 1, tga );


    // write image id.
    fwrite( &id, idlen, 1, tga );

    // initial color values -- just to shut up the compiler.
    nc = 0;

    // color correction -- data is in RGB, need BGR.
    // also run-length-encoding.
    for( i = 0; i < size; i++ ) {

        idx = i * format;

        row = i / width;
        column = i % width;

        //printf( "row: %d, col: %d\n", row, column );
        pixbuf = 0;
        for( j = 0; j < format; j++ ) {
            pixbuf += dat[idx+j] << (8 * j);
        }

        switch( format ) {

        case TGA_TRUECOLOR_24:

            pixbuf = ((pixbuf & 0xFF) << 16) + 
                     (pixbuf & 0xFF00) + 
                     ((pixbuf & 0xFF0000) >> 16);

            pixbuf = htotl( pixbuf );
            break;

        case TGA_TRUECOLOR_32:

            /* need to un-premultiply alpha.. */

            red     = (pixbuf & 0xFF) / 255.0f;
            green   = ((pixbuf & 0xFF00) >> 8) / 255.0f;
            blue    = ((pixbuf & 0xFF0000) >> 16) / 255.0f;
            alpha   = ((pixbuf & 0xFF000000) >> 24) / 255.0f;

            if( alpha > 0.0001 ) {
                red /= alpha;
                green /= alpha;
                blue /= alpha;
            }

            /* clamp to 1.0f */

            red = red > 1.0f ? 255.0f : red * 255.0f;
            green = green > 1.0f ? 255.0f : green * 255.0f;
            blue = blue > 1.0f ? 255.0f : blue * 255.0f;
            alpha = alpha > 1.0f ? 255.0f : alpha * 255.0f;

            pixbuf = (ubyte)blue + (((ubyte)green) << 8) + 
                (((ubyte)red) << 16) + (((ubyte)alpha) << 24);
                
            pixbuf = htotl( pixbuf );
            break;

        }


        oc = nc;

        nc = pixbuf;


        switch( state ) {

        case INIT:
            // this is just used to make sure we have 2 pixel values to consider.
            state = NONE;
            break;


        case NONE:

            if( column == 0 ) {
                // write a 1 pixel raw packet for the old pixel, then go thru again.
                repcount = 0;
                fwrite( &repcount, 1, 1, tga );
#ifdef WORDS_BIGENDIAN
                fwrite( (&oc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &oc, format, 1, tga );
#endif
                state = NONE;
                break;
            }

            if( nc == oc ) {
                repcount = 0;
                state = RLP;
            } else {
                repcount = 0;
                state = RAWP;
                for( j = 0; j < format; j++ ) {
#ifdef WORDS_BIGENDIAN
                    rawbuf[(repcount * format) + j] = (ubyte)(*((&oc)+format-j-1));
#else
                    rawbuf[(repcount * format) + j] = *(((ubyte *)(&oc)) + j);
#endif
                }
            }
            break;


        case RLP:
            repcount++;

            if( column == 0 ) {
                // finish off rlp.
                repcount |= 0x80;
                fwrite( &repcount, 1, 1, tga );
#ifdef WORDS_BIGENDIAN
                fwrite( (&oc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &oc, format, 1, tga );
#endif
                state = NONE;
                break;
            }

            if( repcount == 127 ) {
                // finish off rlp.
                repcount |= 0x80;
                fwrite( &repcount, 1, 1, tga );
#ifdef WORDS_BIGENDIAN
                fwrite( (&oc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &oc, format, 1, tga );
#endif
                state = NONE;
                break;
            }

            if( nc != oc ) {
                // finish off rlp
                repcount |= 0x80;
                fwrite( &repcount, 1, 1, tga );
#ifdef WORDS_BIGENDIAN
                fwrite( (&oc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &oc, format, 1, tga );
#endif
                state = NONE;
            }
            break;


        case RAWP:
            repcount++;

            if( column == 0 ) {
                // finish off rawp.
                for( j = 0; j < format; j++ ) {
#ifdef WORDS_BIGENDIAN
                    rawbuf[(repcount * format) + j] = (ubyte)(*((&oc)+format-j-1));
#else
                    rawbuf[(repcount * format) + j] = *(((ubyte *)(&oc)) + j);
#endif
                }
                fwrite( &repcount, 1, 1, tga );
                fwrite( rawbuf, (repcount + 1) * format, 1, tga );
                state = NONE;
                break;
            }

            if( repcount == 127 ) {
                // finish off rawp.
                for( j = 0; j < format; j++ ) {
#ifdef WORDS_BIGENDIAN
                    rawbuf[(repcount * format) + j] = (ubyte)(*((&oc)+format-j-1));
#else
                    rawbuf[(repcount * format) + j] = *(((ubyte *)(&oc)) + j);
#endif
                }
                fwrite( &repcount, 1, 1, tga );
                fwrite( rawbuf, (repcount + 1) * format, 1, tga );
                state = NONE;
                break;
            }

            if( nc == oc ) {
                // finish off rawp
                repcount--;
                fwrite( &repcount, 1, 1, tga );
                fwrite( rawbuf, (repcount + 1) * format, 1, tga );
                
                // start new rlp
                repcount = 0;
                state = RLP;
                break;
            }

            // continue making rawp
            for( j = 0; j < format; j++ ) {
#ifdef WORDS_BIGENDIAN
                rawbuf[(repcount * format) + j] = (ubyte)(*((&oc)+format-j-1));
#else
                rawbuf[(repcount * format) + j] = *(((ubyte *)(&oc)) + j);
#endif
            }

            break;

        }
       

    }


    // clean up state.

    switch( state ) {

    case INIT:
        break;

    case NONE:
        // write the last 2 pixels in a raw packet.
        fwrite( &one, 1, 1, tga );
#ifdef WORDS_BIGENDIAN
                fwrite( (&oc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &oc, format, 1, tga );
#endif
#ifdef WORDS_BIGENDIAN
                fwrite( (&nc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &nc, format, 1, tga );
#endif
        break;

    case RLP:
        repcount++;
        repcount |= 0x80;
        fwrite( &repcount, 1, 1, tga );
#ifdef WORDS_BIGENDIAN
                fwrite( (&oc)+4, format, 1, tga );  // byte order..
#else
                fwrite( &oc, format, 1, tga );
#endif
        break;

    case RAWP:
        repcount++;
        for( j = 0; j < format; j++ ) {
#ifdef WORDS_BIGENDIAN
            rawbuf[(repcount * format) + j] = (ubyte)(*((&oc)+format-j-1));
#else
            rawbuf[(repcount * format) + j] = *(((ubyte *)(&oc)) + j);
#endif
        }
        fwrite( &repcount, 1, 1, tga );
        fwrite( rawbuf, (repcount + 1) * 3, 1, tga );
        break;

    }


    // close the file.
    fclose( tga );

    free( rawbuf );

    return( 1 );

}






//**************************************************************************\*********************/







static void tga_write_pixel_to_mem( ubyte * dat, ubyte img_spec, uint32 number, 
                                   uint32 w, uint32 h, uint32 pixel, uint32 format ) {

    // write the pixel to the data regarding how the
    // header says the data is ordered.

    uint32 j;
    uint32 x, y;
    uint32 addy;

    switch( (img_spec & 0x30) >> 4 ) {

    case TGA_LOWER_RIGHT:
        x = w - 1 - (number % w);
        y = number / h;
        break;

    case TGA_UPPER_LEFT:
        x = number % w;
        y = h - 1 - (number / w);
        break;

    case TGA_UPPER_RIGHT:
        x = w - 1 - (number % w);
        y = h - 1 - (number / w);
        break;

    case TGA_LOWER_LEFT:
    default:
        x = number % w;
        y = number / w;
        break;

    }

    addy = (y * w + x) * format;
    for( j = 0; j < format; j++ ) {
        dat[addy + j] = (ubyte)((pixel >> (j * 8)) & 0xFF);
    }
    
}





static uint32 tga_get_pixel( FILE * tga, ubyte bytes_per_pix, 
                            ubyte * colormap, ubyte cmap_bytes_entry ) {
    
    /* get the image data value out */

    uint32 tmp_col;
    uint32 tmp_int32;
    ubyte tmp_byte;

    uint32 j;

    tmp_int32 = 0;
    for( j = 0; j < bytes_per_pix; j++ ) {
        if( fread( &tmp_byte, 1, 1, tga ) < 1 ) {
            tmp_int32 = 0;
        } else {
            tmp_int32 += tmp_byte << (j * 8);
        }
    }
    
    /* byte-order correct the thing */
    switch( bytes_per_pix ) {
        
    case 2:
        tmp_int32 = ttohs( (uint16)tmp_int32 );
        break;
        
    case 3: /* intentional fall-thru */
    case 4:
        tmp_int32 = ttohl( tmp_int32 );
        break;
        
    }
    
    if( colormap != NULL ) {
        /* need to look up value to get real color */
        tmp_col = 0;
        for( j = 0; j < cmap_bytes_entry; j++ ) {
            tmp_col += colormap[cmap_bytes_entry * tmp_int32 + j] << (8 * j);
        }
    } else {
        tmp_col = tmp_int32;
    }
    
    return( tmp_col );
    
}





static uint32 tga_convert_color( uint32 pixel, uint32 bpp_in, ubyte alphabits, uint32 format_out ) {
    
    // this is not only responsible for converting from different depths
    // to other depths, it also switches BGR to RGB.

    // this thing will also premultiply alpha, on a pixel by pixel basis.

    ubyte r, g, b, a;

    switch( bpp_in ) {
        
    case 32:
        if( alphabits == 0 ) {
            goto is_24_bit_in_disguise;
        }
        // 32-bit to 32-bit -- nop.
        break;
        
    case 24:
is_24_bit_in_disguise:
        // 24-bit to 32-bit; (only force alpha to full)
        pixel |= 0xFF000000;
        break;

    case 15:
is_15_bit_in_disguise:
        r = (ubyte)(((float)((pixel & 0x7C00) >> 10)) * 8.2258f);
        g = (ubyte)(((float)((pixel & 0x03E0) >> 5 )) * 8.2258f);
        b = (ubyte)(((float)(pixel & 0x001F)) * 8.2258f);
        // 15-bit to 32-bit; (force alpha to full)
        pixel = 0xFF000000 + (r << 16) + (g << 8) + b;
        break;
        
    case 16:
        if( alphabits == 1 ) {
            goto is_15_bit_in_disguise;
        }
        // 16-bit to 32-bit; (force alpha to full)
        r = (ubyte)(((float)((pixel & 0xF800) >> 11)) * 8.2258f);
        g = (ubyte)(((float)((pixel & 0x07E0) >> 5 )) * 4.0476f);
        b = (ubyte)(((float)(pixel & 0x001F)) * 8.2258f);
        pixel = 0xFF000000 + (r << 16) + (g << 8) + b;
        break;
       
    }
    
    // convert the 32-bit pixel from BGR to RGB.
    pixel = (pixel & 0xFF00FF00) + ((pixel & 0xFF) << 16) + ((pixel & 0xFF0000) >> 16);

    r = pixel & 0x000000FF;
    g = (pixel & 0x0000FF00) >> 8;
    b = (pixel & 0x00FF0000) >> 16;
    a = (pixel & 0xFF000000) >> 24;
    
    // not premultiplied alpha -- multiply.
    r = (ubyte)(((float)r / 255.0f) * ((float)a / 255.0f) * 255.0f);
    g = (ubyte)(((float)g / 255.0f) * ((float)a / 255.0f) * 255.0f);
    b = (ubyte)(((float)b / 255.0f) * ((float)a / 255.0f) * 255.0f);

    pixel = r + (g << 8) + (b << 16) + (a << 24);

    /* now convert from 32-bit to whatever they want. */
    
    switch( format_out ) {
        
    case TGA_TRUECOLOR_32:
        // 32 to 32 -- nop.
        break;
        
    case TGA_TRUECOLOR_24:
        // 32 to 24 -- discard alpha.
        pixel &= 0x00FFFFFF;
        break;
        
    }

    return( pixel );

}




static int16 ttohs( int16 val ) {

#ifdef WORDS_BIGENDIAN
    return( ((val & 0xFF) << 8) + (val >> 8) );
#else
    return( val );
#endif 

}

/*
static int16 htots( int16 val ) {

#ifdef WORDS_BIGENDIAN
    return( ((val & 0xFF) << 8) + (val >> 8) );
#else
    return( val );
#endif

}
*/

static int32 ttohl( int32 val ) {

#ifdef WORDS_BIGENDIAN
    return( ((val & 0x000000FF) << 24) +
            ((val & 0x0000FF00) << 8)  +
            ((val & 0x00FF0000) >> 8)  +
            ((val & 0xFF000000) >> 24) );
#else
    return( val );
#endif 

}


static int32 htotl( int32 val ) {

#ifdef WORDS_BIGENDIAN
    return( ((val & 0x000000FF) << 24) +
            ((val & 0x0000FF00) << 8)  +
            ((val & 0x00FF0000) >> 8)  +
            ((val & 0xFF000000) >> 24) );
#else
    return( val );
#endif 

}

// Chargement d'une image TGA RGB 24 bits
unsigned int ChargerImage24Bits (const char* szFilename)
{
	int iLargeur, iHauteur;
	unsigned int uiTexture;
	unsigned char* pucData = static_cast<unsigned char*> (tga_load (szFilename, &iLargeur, &iHauteur, TGA_TRUECOLOR_24));

	// Chargement d'une texture.
	// On cr�� un objet de texture qui est identifi� par m_uiTexture.
	glGenTextures (1, &uiTexture);
	// Indique que l'on utilise l'objet de texture identifi� par m_uiTexture.
	glBindTexture (GL_TEXTURE_2D, uiTexture);
	// Param�trage de l'objet de texture, on utilise un filtre lin�aire.
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Param�trage de l'objet de texture, on utilise un filtre lin�aire.
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Chargement des donn�es de la texture. OpenGL copie en m�moire les donn�es.
	glTexImage2D (GL_TEXTURE_2D, 0, 3, iLargeur, iHauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, pucData);

	delete [] pucData;
	return uiTexture;
}

// Chargement d'une image TGA RGB 32 bits
unsigned int ChargerImage32Bits (const char* szFilename)
{
	int iLargeur, iHauteur;
	unsigned int uiTexture;
	unsigned char* pucData = static_cast<unsigned char*> (tga_load (szFilename, &iLargeur, &iHauteur, TGA_TRUECOLOR_32));

	// Chargement d'une texture.
	// On cr�� un objet de texture qui est identifi� par m_uiTexture.
	glGenTextures (1, &uiTexture);
	// Indique que l'on utilise l'objet de texture identifi� par m_uiTexture.
	glBindTexture (GL_TEXTURE_2D, uiTexture);
	// Param�trage de l'objet de texture, on utilise un filtre lin�aire.
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Param�trage de l'objet de texture, on utilise un filtre lin�aire.
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Chargement des donn�es de la texture. OpenGL copie en m�moire les donn�es.
	glTexImage2D (GL_TEXTURE_2D, 0, 4, iLargeur, iHauteur, 0, GL_RGBA, GL_UNSIGNED_BYTE, pucData);
	
	delete [] pucData;
	return uiTexture;
}

