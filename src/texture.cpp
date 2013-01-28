/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
****** texture.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Classe des textures.                                    **
**                                                         **
*************************************************************/

#include "load.cpp"

#define LOADTYPE_BMP 'b'
#define LOADTYPE_TGA32 'T'
#define LOADTYPE_TGA24 't'

unsigned int ChargerImage32Bits (const char* szFilename);
unsigned int ChargerImage24Bits (const char* szFilename);

// Classe des Textures 
class cl_texture
{
        private :
                GLuint id;
        public :
                cl_texture(char * url, char type=LOADTYPE_BMP);
                ~cl_texture(void);

                void setTexture(void);  
  
};

cl_texture* tLiquid;
cl_texture* tmask;
cl_texture* tcache;

cl_texture::cl_texture(char * url, char type)
{
  if(type==LOADTYPE_BMP)
    {
      int len=strlen(url);
      if(url[len-1]=='a')
	type=LOADTYPE_TGA32;
    }
  if(type==LOADTYPE_TGA32)
    this->id=ChargerImage32Bits(url);
  else
    if(type==LOADTYPE_TGA24)
      this->id=ChargerImage24Bits(url);
    else
      this->id=LoadBMP(url);
}

cl_texture::~cl_texture(void)
{
  glDeleteTextures(1,&(this->id));
}

void cl_texture::setTexture(void)
{
  glBindTexture(GL_TEXTURE_2D, this->id);

  return;
}

