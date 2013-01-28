/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* score.cpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/

#define SCORE_URL "data/score/"


//
// 'nom_de_la_map'.'nom_du_mod'.psd : Phoenixia Score Data
//
// contient 5 structure de score du type :
// int      : score (time)
// char[21] : nom de l'avatar
//

typedef struct psdScore
{
  int Time;
  char Name[21];
};

void setScore(void)
{
  psdScore Scr;
  psdScore tabScr[5];
  clAvaMan * AvaMan=clAvaMan::Create();

  strcpy(Scr.Name, AvaMan->curAva->Nom);
  float t=MapColl->TIMEactu/1000;
  Scr.Time=int(t);

  char url[70];
  strcpy(url, SCORE_URL);
  char*inf=NULL;
  inf=getStrFromMadMap(MAPURL,'n',1);
  strcat(url, inf);
  strcat(url, ".");
  delete inf;
  strcat(url, MOD_LIST[cursMod]);
  strcat(url, ".psd");

  FILE * fOut=fopen(url,"r");
  if(fOut==NULL)
    {
      // Si le fichier des scores n'existe pas, on le rempli
      tabScr[0]=Scr;
      psdScore Unk;
      strcpy(Unk.Name, "*********");
      Unk.Time=999999;
      for(int iS=1 ; iS<5 ; iS++)
	tabScr[iS]=Unk;
      menuSetComment("Vous accedez au classement des meilleurs pilotes.",5000);
    }
  else
    {
      // sinon on update le contenu
      for(int iS=0 ; iS<5 ; iS++)
	{
	  fread(&(tabScr[iS].Time), sizeof(int), 1, fOut);
	  fread(tabScr[iS].Name, sizeof(char), 21, fOut);
	}
      fclose(fOut);
      // où on insère notre résultat s'il le vaut bien
      for(int iS=0 ; iS<5 ; iS++)
	if(Scr.Time < tabScr[iS].Time)
	  {
	    for(int iS2=5 ; iS2>iS ; iS2--)
	      tabScr[iS2]=tabScr[(iS2-1)];
	    tabScr[iS]=Scr;
	    menuSetComment("Vous accedez au classement des meilleurs pilotes.",5000);
	    break;
	  }
    }

  // puis on sauvegarde le tout
  fOut=fopen(url,"w");
  if(fOut==NULL)
    {
      return;
    }
  for(int iS=0 ; iS<5 ; iS++)
    {
      fwrite(&(tabScr[iS].Time), sizeof(int), 1, fOut);
      fwrite(tabScr[iS].Name, sizeof(char), 21, fOut);
    }
  fclose(fOut);
}

char * getScore(int rank=1)
{
  if(rank>5)
    return NULL;

  char url[70];
  strcpy(url, SCORE_URL);
  char*inf=NULL;
  inf=getStrFromMadMap(MAPURL,'n',1);
  strcat(url, inf);
  strcat(url, ".");
  delete inf;
  strcat(url, MOD_LIST[cursMod]);
  strcat(url, ".psd");

  FILE * fIn=fopen(url,"r");
  if(fIn==NULL)
    return NULL;

  fseek(fIn, (sizeof(int)+(sizeof(char)*21))*(rank-1), SEEK_CUR);
  psdScore Scr;
  fread(&(Scr.Time), sizeof(int), 1, fIn);
  fread(Scr.Name, sizeof(char), 21, fIn);
  fclose(fIn);

  clAvaMan * AvaMan=clAvaMan::Create();
  char * ret=new char[51];
  char linkin='-';
  if(strcmp(AvaMan->curAva->Nom, Scr.Name)==0)
    linkin='>';
  sprintf(ret,"#%d %c %ds %c %s", rank, linkin, Scr.Time, linkin, Scr.Name);
  return ret;
}
