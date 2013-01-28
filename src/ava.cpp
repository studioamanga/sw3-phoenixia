/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********** ava.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Constantes et fonctions liées à la gestion des Avatars. **
**                                                         **
*************************************************************/

#define AVA_DIR_URL "data/avatar/"
#define AVA_EXT     ".ava"

class clAvatar
{
private:
  int Right[MOD_NB];

public :
  clAvatar * NEXT;
  char Nom[21];

  clAvatar(void);
  clAvatar(char * url);
  ~clAvatar(void);

  clAvatar * getNext(void);
  void Save(void);
  void Load(void);
  int IsRight(int idMod);
  void Upgrade(int idMod);
};


clAvatar::clAvatar(void)
{
  strcpy(this->Nom,"Invite");

  for(int imod=0 ; imod<MOD_NB ; imod++)
    {
      Right[imod]=0;
    }
  Right[MOD_EXPLORATION]=1;
}

clAvatar::clAvatar(char * url)
{
  strcpy(this->Nom,url);

  for(int imod=0 ; imod<MOD_NB ; imod++)
    {
      Right[imod]=0;
    }
  Right[MOD_EXPLORATION]=1;
  Right[MOD_DEFI]=1;
}

clAvatar::~clAvatar(void)
{
  //
}

clAvatar * clAvatar::getNext(void)
{
  return this->NEXT;
}

void clAvatar::Save(void)
{
  FILE * fOut;
  char url[50];

  strcpy(url,AVA_DIR_URL);
  strcat(url,this->Nom);
  strcat(url,AVA_EXT);

  fOut=fopen(url,"w");
  if(!fOut)
    return;

  for(int imod=0 ; imod<MOD_NB ; imod++)
    {
      fwrite(&(this->Right[imod]),sizeof(int),1,fOut);
    }

  fclose(fOut);
}

void clAvatar::Load(void)
{
  FILE * fIn;
  char url[50];

  strcpy(url,AVA_DIR_URL);
  strcat(url,this->Nom);
  strcat(url,AVA_EXT);

  fIn=fopen(url,"r");
  if(!fIn)
    {
      this->Save();
      return;
    }

  for(int imod=0 ; imod<MOD_NB ; imod++)
    {
      fread(&(this->Right[imod]),sizeof(int),1,fIn);
    }

  fclose(fIn);
}

int clAvatar::IsRight(int idMod)
{
  return this->Right[idMod];
}

void clAvatar::Upgrade(int idMod)
{
  this->Right[idMod]++;
  this->Save();
}
