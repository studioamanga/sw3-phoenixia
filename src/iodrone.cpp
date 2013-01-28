/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* iodrone.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Fonctions liées aux traitements d'entrée/sortie (in/out)**
**                                                         **
*************************************************************/

int getNbFromMadDrone(char * url, char what='C') throw (ErrFile)
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
  if(tag!='D')
    {
      fclose(fOut);
      throw ErrFile(url);
    }

  fread(&nb, sizeof(int), 1, fOut);
  fclose(fOut);

  return nb;
}

float getRealFromMadDrone(char * url, char what='T') throw (ErrFile)
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
  if(tag!='D')
    {
      fclose(fOut);
      throw ErrFile(url);
    }

  fseek(fOut, sizeof(int)+sizeof(char), SEEK_CUR);
  fread(&nb, sizeof(float), 1, fOut);
  fclose(fOut);

  return nb;
}

int getNbFromMadShoker(char * url, char what='A') throw (ErrFile)
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
  if(tag!='S')
    {
      fclose(fOut);
      throw ErrFile(url);
    }

  if(what=='D') // défense, sinon attaque
    fseek(fOut, sizeof(int)+sizeof(float), SEEK_CUR);
  fread(&nb, sizeof(int), 1, fOut);
  fclose(fOut);

  return nb;
}

float getRealFromMadShoker(char * url, char what='T') throw (ErrFile)
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
  if(tag!='S')
    {
      fclose(fOut);
      throw ErrFile(url);
    }

  fseek(fOut, sizeof(int), SEEK_CUR);
  if(what=='T') // taille, sinon vitesse
    fseek(fOut, sizeof(float)+sizeof(int), SEEK_CUR);
  fread(&nb, sizeof(float), 1, fOut);
  fclose(fOut);

  return nb;
}
