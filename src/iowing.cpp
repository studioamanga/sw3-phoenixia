/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** iowing.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Fonctions liées aux traitements d'entrée/sortie (in/out)**
**                                                         **
*************************************************************/

int getNbFromMadWing(char * url, char what='W', int which=0) throw (ErrFile)
{
  int nb=0, nbtag=0;

  FILE * fOut=fopen(url,"r");
  if(fOut==NULL)
    throw ErrFile(url);

  unsigned char control;
  fread(&control,sizeof(unsigned char),1,fOut);
  if(control!=136)
    throw ErrFile(url);

  fread(&nbtag,sizeof(int),1,fOut);
  if(nbtag==0)
    return 0;

  fseek(fOut, sizeof(char), SEEK_CUR);
  int nbsurf=0;
  fread(&nbsurf,sizeof(int),1,fOut);
  for(int i=0 ; i<nbsurf ; i++)
    {
      fseek(fOut, sizeof(char)*51, SEEK_CUR);
      int nbvertices=0;
      fread(&nbvertices,sizeof(int),1,fOut);
      fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
    }

  char tag;
  fread(&tag, sizeof(char),1,fOut);
  if(tag!='W')
    {
      fclose(fOut);
      throw ErrFile(url);
    }

  if(what=='W')
    {
      fseek(fOut, (sizeof(float)*5)+(sizeof(char)*20)+(sizeof(int)*which), SEEK_CUR);
      fread(&nb, sizeof(int), 1, fOut);
      fclose(fOut);
      return nb;
    }

  fseek(fOut, (sizeof(float)*5)+(sizeof(char)*120)+(sizeof(int)*10), SEEK_CUR);
  if(what=='R')
    {
      fread(&nb, sizeof(int), 1, fOut);
      fclose(fOut);
      return nb;
    }

  fclose(fOut);
  return nb;
}

float getRealFromMadWing(char * url, char what='R', int which=0, int whichin=0) throw (ErrFile)
{
  float nb=0;
  int nbtag=0;

  FILE * fOut=fopen(url,"r");
  if(fOut==NULL)
    throw ErrFile(url);

  unsigned char control;
  fread(&control,sizeof(unsigned char),1,fOut);
  if(control!=136)
    throw ErrFile(url);

  fread(&nbtag,sizeof(int),1,fOut);
  if(nbtag==0)
    return 0;

  fseek(fOut, sizeof(char), SEEK_CUR);
  int nbsurf=0;
  fread(&nbsurf,sizeof(int),1,fOut);
  for(int i=0 ; i<nbsurf ; i++)
    {
      fseek(fOut, sizeof(char)*51, SEEK_CUR);
      int nbvertices=0;
      fread(&nbvertices,sizeof(int),1,fOut);
      fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
    }

  char tag;
  fread(&tag, sizeof(char),1,fOut);
  if(tag!='W')
    {
      fclose(fOut);
      throw ErrFile(url);
    }

  fseek(fOut, sizeof(char)*20, SEEK_CUR);

  if(what=='R')
    {// Rayon
      fread(&nb, sizeof(float), 1, fOut);
      fclose(fOut);
      return nb;
    }
  fseek(fOut, sizeof(float), SEEK_CUR);
  if(what=='V')
    {// Vitesse
      fread(&nb, sizeof(float), 1, fOut);
      fclose(fOut);
      return nb;
    }
  fseek(fOut, sizeof(float), SEEK_CUR);
  if(what=='D')
    {// Dir
      fread(&nb, sizeof(float), 1, fOut);
      fclose(fOut);
      return nb;
    }
  fseek(fOut, sizeof(float), SEEK_CUR);
  if(what=='A')
    {// Armure
      fread(&nb, sizeof(float), 1, fOut);
      fclose(fOut);
      return nb;
    }
  fseek(fOut, sizeof(float), SEEK_CUR);
  if(what=='S')
    {// Shield
      fread(&nb, sizeof(float), 1, fOut);
      fclose(fOut);
      return nb;
    }

  fseek(fOut, sizeof(float)+sizeof(char)*150+sizeof(int)*11, SEEK_CUR);
  if(what=='r')
    {// Reacteurs
      fseek(fOut, sizeof(float)*4*which+sizeof(float)*whichin, SEEK_CUR);
      fread(&nb, sizeof(float), 1, fOut);
      fclose(fOut);
      return nb;
    }

  fclose(fOut);
  return 0;
}

char * getStrFromMadWing(char * url, char what='n') throw (ErrFile)
{
  int nbtag=0;
	
  FILE * fOut=fopen(url,"r");
  if(fOut==NULL)
    throw ErrFile(url);

  unsigned char control;
  fread(&control,sizeof(unsigned char),1,fOut);
  if(control!=136)
    throw ErrFile(url);

  fread(&nbtag,sizeof(int),1,fOut);
  if(nbtag==0)
    return NULL;

  fseek(fOut, sizeof(char), SEEK_CUR);
  int nbsurf=0;
  fread(&nbsurf,sizeof(int),1,fOut);
  for(int i=0 ; i<nbsurf ; i++)
    {
      fseek(fOut, sizeof(char)*51, SEEK_CUR);
      int nbvertices=0;
      fread(&nbvertices,sizeof(int),1,fOut);
      fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
    }

  char tag;
  fread(&tag, sizeof(char),1,fOut);
  if(tag!='W')
    {
      fclose(fOut);
      return NULL;
    }

  if(what=='n')
    {// Nom
      char *na=new char[21];
      fread(na,sizeof(char),20,fOut);
      fclose(fOut);
      return na;
    }

  fseek(fOut, (sizeof(float)*5)+(sizeof(int)*10)+(sizeof(char)*20), SEEK_CUR);

  if(what=='F')
    {// Description
      char * desc=new char[100];
      fread(desc,sizeof(char),100,fOut);
      fclose(fOut);
      return desc;
    }

  fseek(fOut, sizeof(char)*100+sizeof(int), SEEK_CUR);

  if(what=='R')
    {// Reacteur (texture)
      char * desc=new char[50];
      fread(desc,sizeof(char),50,fOut);
      fclose(fOut);
      return desc;
    }

  fclose(fOut);

  return NULL;
}
