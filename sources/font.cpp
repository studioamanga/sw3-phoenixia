/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* font.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Constantes et fonctions li�es � la gestion des fonts  . **
**                                                         **
*************************************************************/



#include <stdarg.h>

//! Identifiants de positions pr�d�finies � l'�cran.
typedef enum
  {
    FONT_POSITION_NULL = 0,
    FONT_POSITION_CENTRE,
    FONT_POSITION_CENTRE_HAUT
  } EFontPosition;

//! Affichage de cha�nes de caract�res.
class CFont
{
private:
  unsigned int m_uiTexture;
  unsigned int m_uiDisplayList;
  float m_fCouleur [3], scaleFact;

public:
  //! Le constructeur.
  CFont ();
  //! Le destructeur.
  ~CFont ();

  //! Indique la couleur d'affichage des caract�res.
  void Couleur (float r, float g, float b);
  void setScaleFact(float s);
  //! Chargement d'une image contenant les caract�res � afficher.
  void ChargerTexture (const char* szTexture);
  //! Affichage d'une cha�ne de caract�res par rapport � une position (X,Y) sur l'�cran.
  void Print (int x, int y, const char *szMsg, ...);
  //! Affichage d'une cha�ne de caract�res par rapport � une position pr�d�fini sur l'�cran.
  void Print (EFontPosition FontPosition, const char *szMsg, ...);
  //! Affichage d'une cha�ne de caract�res par rapport � une position pr�d�fini en X et configurable en Y sur l'�cran.
  void Print (EFontPosition FontPosition, int y, const char *szMsg, ...);
};

class CFont Fonter;

CFont::CFont ()
{
  m_fCouleur [0] = 1;
  m_fCouleur [1] = 1;
  m_fCouleur [2] = 1;
  scaleFact=1;
}

CFont::~CFont ()
{
  glDeleteTextures(1,&m_uiTexture);
}

void CFont::Couleur (float r, float g, float b)
{
  m_fCouleur [0] = r;
  m_fCouleur [1] = g;
  m_fCouleur [2] = b;
}

void CFont::setScaleFact (float s)
{
  scaleFact=s;
}

// La fonction Print s'utilise comme printf sauf que l'on indique la position o� doit s'afficher le texte.
void CFont::Print (EFontPosition FontPosition, const char *szMsg, ...)
{
  char szText[256];
  va_list ap;

  // Pour cela, strlen recherche compte les caract�res jusqu'au caract�re '\0'
  memset (szText, '\0', 256);

  if (szMsg == 0)
    return;

  // Analyse la cha�ne format� et place le r�sultat dans szText
  va_start (ap, szMsg);
  vsprintf (szText, szMsg, ap);
  va_end (ap);

  // D�termine la longueur de cha�ne contenu dans szText
  // Pour cela, strlen recherche compte les caract�res jusqu'au caract�re '\0'
  int iLongeur = strlen (szMsg);

  // On active l'utilisation des textures.
  //glEnable (GL_TEXTURE_2D);
  // On active la transparence.
  //glEnable (GL_BLEND);
  glDisable (GL_DEPTH_TEST);
  // On d�finie le mode de transparence, la transparence est r�alis�e par la couche alpha.
  //glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	
  // Indique la couleur d'affichage des fonts
  glColor3fv (m_fCouleur);
  glPushMatrix ();
  glLoadIdentity ();
  switch (FontPosition)
    {
    default:
    case FONT_POSITION_CENTRE:
      glTranslated (SCREEN_X / 2 - iLongeur * 12 * scaleFact / 2, SCREEN_Y / 2, 0);
      break;
    case FONT_POSITION_CENTRE_HAUT:
      glTranslated (SCREEN_X / 2 - iLongeur * 12 * scaleFact / 2, SCREEN_Y - 16*scaleFact, 0);
      break;
    }
  if(scaleFact!=1)
    glScalef(scaleFact,scaleFact,scaleFact);
  glListBase (m_uiDisplayList);

  // Ex�cute chaque liste d'affichages, chaque charact�re �tant l'identifiant d'une liste d'affichages.
  glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
  glPopMatrix ();
  glColor3d(1,1,1);

  // On deactive la transparence
  //glDisable (GL_BLEND);
  // On deactive l'utilisation des textures.
  //glDisable (GL_TEXTURE_2D);
  glEnable (GL_DEPTH_TEST);
}

// La fonction Print s'utilise comme printf sauf que l'on indique la position o� doit s'afficher le texte.
void CFont::Print (EFontPosition FontPosition, int y, const char *szMsg, ...)
{
  char szText[256];
  va_list ap;

  memset (szText, '\0', 256);

  if (szMsg == 0)
    return;

  // Analyse la cha�ne format� et place le r�sultat dans szText.
  va_start (ap, szMsg);
  vsprintf (szText, szMsg, ap);
  va_end (ap);

  // D�termine la longueur de la cha�ne contenu dans szText.
  // Pour cela, strlen recherche compte les caract�res jusqu'au caract�re '\0'
  int iLongeur = strlen (szMsg);

  // On active l'utilisation des textures.
  //glEnable (GL_TEXTURE_2D);
  // On active la transparence.
  //glEnable (GL_BLEND);
  glDisable (GL_DEPTH_TEST);
  // On d�finie le mode de transparence, la transparence est r�alis�e par la couche alpha.
  //glBlendFunc (GL_SRC_ALPHA, GL_ONE);

  glColor3fv (m_fCouleur);
  glPushMatrix ();
  glLoadIdentity ();
  switch (FontPosition)
    {
    default:
    case FONT_POSITION_CENTRE:
      glTranslated (SCREEN_X / 2 - iLongeur * 12 * scaleFact / 2, y, 0);
      break;
    }
  if(scaleFact!=1)
    glScalef(scaleFact,scaleFact,scaleFact);
  glListBase (m_uiDisplayList);

  // Ex�cute chaque liste d'affichages, chaque charact�re �tant l'identifiant d'une liste d'affichages.
  glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
  glPopMatrix ();
  glColor3d(1,1,1);

  // On deactive la transparence
  //glDisable (GL_BLEND);
  // On deactive l'utilisation des textures.
  //glDisable (GL_TEXTURE_2D);
  glEnable (GL_DEPTH_TEST);
}

// La fonction Print s'utilise comme printf sauf que l'on indique la position o� doit s'afficher le texte.
void CFont::Print (int x, int y, const char *szMsg, ...)
{
  char szText[256];
  va_list ap;

  memset (szText, '\0', 256);

  if (szMsg == 0)
    return;

  // Analyse la cha�ne format� et place le r�sultat dans szText
  va_start (ap, szMsg);
  vsprintf (szText, szMsg, ap);
  va_end (ap);

  // On active l'utilisation des textures.
  //glEnable (GL_TEXTURE_2D);
  // On active la transparence.
  //glEnable (GL_BLEND);
  glDisable (GL_DEPTH_TEST);
  // On d�finie le mode de transparence, la transparence est r�alis�e par la couche alpha.
  //glBlendFunc (GL_SRC_ALPHA, GL_ONE);

  glColor3fv (m_fCouleur);
  glPushMatrix ();
  glLoadIdentity ();
  glTranslated (x, y, 0);
  if(scaleFact!=1)
    glScalef(scaleFact,scaleFact,scaleFact);
  glListBase (m_uiDisplayList);

  // Ex�cute chaque liste d'affichages, chaque charact�re �tant l'identifiant d'une liste d'affichages.
  glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
  glPopMatrix ();
  glColor3d(1,1,1);

  // On deactive la transparence
  //glDisable (GL_BLEND);
  // On deactive l'utilisation des textures.
  //glDisable (GL_TEXTURE_2D);
  glEnable (GL_DEPTH_TEST);
}


void CFont::ChargerTexture (const char* szTexture)
{
  int iLargeur, iHauteur;
  unsigned char* pucData = (unsigned char*) tga_load (szTexture, &iLargeur, &iHauteur, TGA_TRUECOLOR_24);

  // Chargement d'une texture.
  // On cr�� un objet de texture qui est identifi� par m_uiTexture.
  glGenTextures (1, &m_uiTexture);
  // Indique que l'on utilise l'objet de texture identifi� par m_uiTexture.
  glBindTexture (GL_TEXTURE_2D, m_uiTexture);
  // Param�trage de l'objet de texture, on utilise un filtre lin�aire.
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // Param�trage de l'objet de texture, on utilise un filtre lin�aire.
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Chargement des donn�es de la texture. OpenGL copie en m�moire les donn�es.
  glTexImage2D (GL_TEXTURE_2D, 0, 3, iLargeur, iHauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, pucData);

  // On n'a plus besoin de la m�moire allou� pour le chargement de l'image.
  delete [] pucData;

  // On cr�� 256 display lists, une par caract�re.
  m_uiDisplayList = glGenLists (256);
  for (int i = 0; i < 256; i++)
    {
      float fTexCoordX = float (i%16) / 16.0f;
      float fTexCoordY = float (i/16) / 16.0f;

      // Indique le contenu des listes d'affichages
      glNewList (m_uiDisplayList + i, GL_COMPILE);
      // Liste des commandes qui seront ex�cut�s par la liste d'affichage
      // Indique la texture que l'on souhait utiliser
      glBindTexture (GL_TEXTURE_2D, m_uiTexture);
      // Affiche un quadrangle comme fragment de la texture c'est � dire restreint � un caract�re
      glBegin (GL_QUADS);
      // Indique les coordonn�es de la texture pour le vertex bas gauche
      glTexCoord2f (fTexCoordX, 1.0f - fTexCoordY);
      glVertex2f (0, 0);
				
      // Indique les coordonn�es de la texture pour le vertex bas droit
      glTexCoord2f (fTexCoordX + 0.0625f, 1.0f - fTexCoordY);
      glVertex2f (iLargeur / 16.f, 0);
				
      // Indique les coordonn�es de la texture pour le vertex haut droit
      glTexCoord2f (fTexCoordX + 0.0625f, 1.0f - fTexCoordY - 0.0625f); // (0.0625 = 1 / 16)
      glVertex2f (iLargeur / 16.f, iHauteur / 16.f);
				
      // Indique les coordonn�es de la texture pour le vertex haut gauche
      glTexCoord2f (fTexCoordX, 1.0f - fTexCoordY - 0.0625f);
      glVertex2f (0, iHauteur / 16.f);
      glEnd ();
      glTranslated (12.f, 0, 0);
      glEndList ();
    }
}

