/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** avaman.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Constantes et fonctions liées à la gestion des Avatars. **
**                                                         **
*************************************************************/


class clAvaMan
{
private:
  static clAvaMan *Manager;

  clAvatar * fAva;
  clAvatar * lAva;

  clAvaMan (void);
  ~clAvaMan (void);

public:
  clAvatar * curAva;

  bool AddAva(char * url);
  bool LoadAva(char * url);
  void gotoNext(void);
  bool delCur(void);
  void SaveList(void);
  void OpenList(void);
  int IsCurRight(void);

  static clAvaMan* Create ();
  static void	Kill ();
};


clAvaMan* clAvaMan::Manager = 0;

int clAvaMan::IsCurRight(void)
{
  return curAva->IsRight(cursMod);
}

bool clAvaMan::AddAva(char * url)
{
  // recherche d'un doublon
  clAvatar * aN=fAva;
  do
    {
      if(strcmp(url,aN->Nom)==0)
	return false;
      aN=aN->getNext();
    }
  while(aN!=fAva);

  // création de l'avatar
  aN=new clAvatar(url);
  lAva->NEXT=aN;
  lAva=aN;
  lAva->NEXT=fAva;
  curAva=lAva;

  lAva->Save();
  SaveList();

  return true;
}

bool clAvaMan::LoadAva(char * url)
{
  // création de l'avatar
  clAvatar * aN=new clAvatar(url);
  lAva->NEXT=aN;
  lAva=aN;
  lAva->NEXT=fAva;
  curAva=lAva;

  lAva->Load();

  return true;
}

bool clAvaMan::delCur(void)
{
  clAvatar * cA=curAva;

  if(curAva==fAva)
    return false;

  clAvatar * iA=fAva;

  while(iA->getNext()!=cA)
    iA=iA->getNext();
  if(lAva==cA)
    lAva=iA;
  iA->NEXT=cA->getNext();
  delete cA;

  curAva=fAva;
  SaveList();

  return true;
}

void clAvaMan::gotoNext(void)
{
  curAva=curAva->getNext();
}

void clAvaMan::SaveList(void)
{
  clAvatar * aN=fAva->getNext();
  FILE * fOut=fopen("config/avatar.cfg","w");

  if(!fOut)
    return;

  while(aN!=fAva)
    {
      fwrite(aN->Nom, sizeof(char), 21, fOut);
      aN=aN->getNext();
    }
  fclose(fOut);
}

void clAvaMan::OpenList(void)
{
  FILE * fIn=fopen("config/avatar.cfg","r");

  if(!fIn)
    return;

  while(1)
    {
      char NomIn[21];
      fread(&NomIn, sizeof(char), 21, fIn);
      if(feof(fIn))
	break;
      LoadAva(NomIn);
      //printf("%s\n",NomIn);
    }
  fclose(fIn);

  this->curAva=this->fAva;
}


clAvaMan::clAvaMan(void)
{
  fAva=new clAvatar;
  fAva->NEXT=fAva;
  curAva=fAva;
  lAva=fAva;
}

clAvaMan::~clAvaMan(void)
{
  SaveList();

  if(fAva)
    {
      clAvatar*cA =fAva->getNext();
      while(cA!=fAva)
	{
	  clAvatar*cAdead=cA;
	  cA->Save();
	  cA=cA->getNext();
	  delete cAdead;
	}
      delete fAva;
    }
}

clAvaMan* clAvaMan::Create ()
{
	if (Manager == 0)
		Manager = new clAvaMan;
	return Manager;
}

void clAvaMan::Kill ()
{
	if (Manager != 0)
	{
		delete Manager;
		Manager = 0;
	}
}
