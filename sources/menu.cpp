/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* menu.cpp **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

#include "menu.hpp"

#define INTRO_LONG 3

void affMenuTxt(void)
{
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Fonter.Couleur(0.7+RandFloat(0,0.3),0,0);
  Fonter.setScaleFact(2);
  if(curMenu==NULL)
    {
      static float introMenu=0;
      Fonter.Print (FONT_POSITION_CENTRE, "|studio|AMANgA|");
      introMenu+=GETTIMER;
      if(introMenu>INTRO_LONG*1000)
	{
	  curMenu=&MAIN_MENU;
	  cursMenu=1;
	  cursMenuMax=curMenu->MENU_SIZE;
	  cursMod=0;
	  return;
	}
    }
  else
    {
      Fonter.Print (FONT_POSITION_CENTRE, "|SW3|PHOENIXIA|");

      Fonter.setScaleFact(1);
      Fonter.Couleur(1,1,1);
      for(int idLi=0 ; idLi<curMenu->MENU_SIZE ; idLi++)
	{
	  printMenuLine(idLi);
	}
      if(menuCommentTime>0)
	{
	  menuCommentTime-=GETTIMER;
	  Fonter.Couleur(1,1,1);
	  Fonter.setScaleFact(0.8);
	  Fonter.Print(FONT_POSITION_CENTRE, SCREEN_Y-20, menuComment);
	  Fonter.setScaleFact(1);
	}

      Fonter.Couleur(0,0,1);
      printMenuLine(cursMenu-1);
    }

  glDisable(GL_BLEND);
}

void menuOK(void)
{
  clAvaMan * AvaMan=clAvaMan::Create();
  clSoundMan * Sound=clSoundMan::Create();
  char*inf;

  if(curMenu==NULL)
    return;

  if( curMenu->MENU_LINK[cursMenu-1]>= MENU_LINK_INPUP && curMenu->MENU_LINK[cursMenu-1]<= MENU_LINK_INPBACKWEAP )
    {
      menuSetComment("Appuyez sur la touche voulue",30000);
      idInputStr=-1;
      return;
    }
  switch(curMenu->MENU_LINK[cursMenu-1])
    {
    case MENU_LINK_QUIT :
      eXit();
      break;

    case MENU_LINK_TOMAIN :
      curMenu=&MAIN_MENU;
      cursMenu=1;
      cursMenuMax=curMenu->MENU_SIZE;
      cursMod=0;
      break;

    case MENU_LINK_TOAVA :
      curMenu=&AVA_MENU;
      cursMenu=2;
      cursMenuMax=curMenu->MENU_SIZE;
      break;

    case MENU_LINK_TOOPT :
      curMenu=&OPT_MENU;
      cursMenu=3;
      cursMenuMax=curMenu->MENU_SIZE;
      break;

    case MENU_LINK_TOINPUT1 :
      curMenu=&INP1_MENU;
      cursMenu=2;
      cursMenuMax=curMenu->MENU_SIZE;
      break;

    case MENU_LINK_TOINPUT2 :
      curMenu=&INP2_MENU;
      cursMenu=1;
      cursMenuMax=curMenu->MENU_SIZE;
      break;

    case MENU_LINK_TONEW :
      switch(cursMod)
	{
	case MOD_DEFI :
	  curMenu=&DEFI_MENU;
	  cursMenu=2;
	  cursMenuMax=curMenu->MENU_SIZE;
	  cursDefiMission=AvaMan->IsCurRight();
	  strcpy(MAPURL,MOD_DEFI_MISSIONS[cursDefiMission-1].Map);
	  strcpy(WINGURL,MOD_DEFI_MISSIONS[cursDefiMission-1].Wing);
	  MAPCLIMAT=MOD_DEFI_MISSIONS[cursDefiMission-1].Clim;
	  menuSetComment(MOD_DEFI_MISSIONS[cursDefiMission-1].Comment,5000);
	  break;
	case MOD_EXPLORATION :
	default :
	  curMenu=&NEW_MENU;
	  cursMenu=2;
	  cursMenuMax=curMenu->MENU_SIZE;
	  strcpy(MAPURL,"data/model/");
	  strcat(MAPURL,mapDetail[curMap].nom);
	  strcat(MAPURL,".mad");
	  inf=getStrFromMadMap(MAPURL,'F',1);
	  menuSetComment(inf,5000);
	  delete inf;
	  curClim=0;
	  MAPCLIMAT=mapDetail[curMap].tabClimat[curClim];
	}
      break;
  
    case MENU_LINK_NEXTAVA :
      AvaMan->gotoNext();
      cursMod=0;
      break;

    case MENU_LINK_NEXTMOD :
      do
	{
	  cursMod++;
	  if(cursMod>=MOD_NB)
	    cursMod=0;
	}
      while(!AvaMan->IsCurRight());
      break;

    case MENU_LINK_NEXTMAP :
      curMap++;
      if(curMap==nbMaps)
	curMap=0;
      strcpy(MAPURL,"data/model/");
      strcat(MAPURL,mapDetail[curMap].nom);
      strcat(MAPURL,".mad");
      inf=getStrFromMadMap(MAPURL,'F',1);
      menuSetComment(inf,5000);
      delete inf;
      curClim=0;
      MAPCLIMAT=mapDetail[curMap].tabClimat[curClim];
      break;

    case MENU_LINK_NEXTWING :
      curWing++;
      if(curWing==nbWings)
	curWing=0;
      strcpy(WINGURL,"data/model/");
      strcat(WINGURL,wingDetail[curWing].nom);
      strcat(WINGURL,".mad");
      inf=getStrFromMadWing(WINGURL,'F');
      menuSetComment(inf,5000);
      delete inf;
      break;

    case MENU_LINK_NEXTCLIM :
      curClim++;
      if(curClim==mapDetail[curMap].nbClimat)
	curClim=0;
      MAPCLIMAT=mapDetail[curMap].tabClimat[curClim];
      break;

    case MENU_LINK_NEXTDETL :
      NIV_DETAIL++;
      if(NIV_DETAIL>4)
	NIV_DETAIL=1;
      break;

    case MENU_LINK_MUSIC :
      Sound->SwapMuteMusic();
      break;

    case MENU_LINK_NOISE :
      Sound->SwapMuteNoise();
      break;

    case MENU_LINK_NEXTRESOL :
      switch(SCREEN_X)
	{
	case 640:
	  SCREEN_X=800;
	  SCREEN_Y=600;
	  break;
	case 800:
	  SCREEN_X=1024;
	  SCREEN_Y=768;
	  break;
	default :
	  SCREEN_X=640;
	  SCREEN_Y=480;
	}
      glutReshapeWindow(SCREEN_X,SCREEN_Y);
      break;

    case MENU_LINK_NEXTDEFI :
      cursDefiMission++;
      if(cursDefiMission>(AvaMan->IsCurRight()+1))
	cursDefiMission=1;
      strcpy(MAPURL,MOD_DEFI_MISSIONS[cursDefiMission-1].Map);
      strcpy(WINGURL,MOD_DEFI_MISSIONS[cursDefiMission-1].Wing);
      MAPCLIMAT=MOD_DEFI_MISSIONS[cursDefiMission-1].Clim;
      menuSetComment(MOD_DEFI_MISSIONS[cursDefiMission-1].Comment,5000);
      break;

    case MENU_LINK_NEWAVA :
      if(idInputStr>0)
	{
	  if(AvaMan->AddAva(inputStr))
	    menuSetComment("Nouvel Avatar cree",3000);
	  else
	    menuSetComment("Impossible de creer cet Avatar",3000);
	  idInputStr=0;
	  inputStr[0]='\0';
	  cursMenu=1;
	}
      break;

    case MENU_LINK_DELAVA :
      if(AvaMan->delCur())
	{
	  cursMenu=1;
	  menuSetComment("Avatar supprime",3000);
	}
      else
	menuSetComment("Impossible de supprimer cet Avatar",3000);
      break;

    case MENU_LINK_START :
      Disp=DISP_JEU;
      InitJ();
      break;

    case MENU_LINK_NONE :
    default :
      break;
    }

  return;
}

void printMenuLine(int id)
{
  clAvaMan * AvaMan=clAvaMan::Create();
  clSoundMan * Sound=clSoundMan::Create();
  char txt[25];
  strcpy(txt,curMenu->MENU_TAB[id]);

  if(strcmp(txt,"[AVA]")==0)
    {
      strcpy(txt,AvaMan->curAva->Nom);
      strcat(txt," >>");
    }

  if(strcmp(txt,"[MOD]")==0)
    {
      strcpy(txt,"Mod:");
      strcat(txt,MOD_LIST[cursMod]);
      strcat(txt," >>");
    }

  if(strcmp(txt,"[INPUT]")==0)
    {
      strcpy(txt,":");
      strcat(txt,inputStr);
    }

  if(strcmp(txt,"[MAP]")==0)
    {
      strcpy(txt,mapDetail[curMap].name);
      strcat(txt," >>");
    }

  if(strcmp(txt,"[WING]")==0)
    {
      strcpy(txt,wingDetail[curWing].name);
      strcat(txt," >>");
    }

  if(strcmp(txt,"[CLIM]")==0)
    {
      char*inf=getClimatName(MAPCLIMAT);
      strcpy(txt,inf);
      delete inf;
      strcat(txt," >>");
    }

  if(strcmp(txt,"[DEFI]")==0)
    {
      strcpy(txt,MOD_DEFI_MISSIONS[cursDefiMission-1].Nom);
      strcat(txt," >>");
    }

  if(strcmp(txt,"[RESOL]")==0)
    {
      char sResol[10];
      sprintf(sResol,"Resolution : %dx%d >>", SCREEN_X, SCREEN_Y);
      strcpy(txt,sResol);
    }

  if(strcmp(txt,"[SONMUS]")==0)
    {
      if(Sound->IsActiveMusic())
	strcpy(txt,"Musiques Activees >>");
      else
	strcpy(txt,"Musiques Desactivees >>");
    }

  if(strcmp(txt,"[SONNOI]")==0)
    {
      if(Sound->IsActiveNoise())
	strcpy(txt,"Bruitages Actives >>");
      else
	strcpy(txt,"Bruitages Desactives >>");
    }

  if(strcmp(txt,"[KEYINP]")==0)
    {
      char*s=getInputAction(curMenu->MENU_LINK[id]);
      strcpy(txt,s);
      strcat(txt," : ");
      delete s;
      s=getInputKey(myInput[curMenu->MENU_LINK[id]-MENU_LINK_INPUT_DECALAGE]);
      strcat(txt,s);
      strcat(txt," >>");
      delete s;
    }

  if(strcmp(txt,"[SCORES]")==0)
    {
      strcpy(txt, ">> Classement de ");
      switch(cursMod)
	{
	case MOD_DEFI :
	  strcat(txt,MOD_DEFI_MISSIONS[cursDefiMission-1].Nom);
	  break;
	case MOD_EXPLORATION :
	default :
	  strcat(txt,mapDetail[curMap].name);
	}
      strcat(txt, " :");
    }

  if(strcmp(txt,"[SCORE1]")==0)
    {
      char*inf=getScore(1);
      strcpy(txt,inf);
      delete inf;
    }

  if(strcmp(txt,"[SCORE2]")==0)
    {
      char*inf=getScore(2);
      strcpy(txt,inf);
      delete inf;
    }

  if(strcmp(txt,"[SCORE3]")==0)
    {
      char*inf=getScore(3);
      strcpy(txt,inf);
      delete inf;
    }

  if(strcmp(txt,"[SCORE4]")==0)
    {
      char*inf=getScore(4);
      strcpy(txt,inf);
      delete inf;
    }

  if(strcmp(txt,"[SCORE5]")==0)
    {
      char*inf=getScore(5);
      strcpy(txt,inf);
      delete inf;
    }

  if(strcmp(txt,"[DETLEVEL]")==0)
    {
      strcpy(txt,"Niveau de Details : ");
      switch(NIV_DETAIL)
	{
	case 1 :
	  strcat(txt,"Faible");
	  break;
	case 2 :
	  strcat(txt,"Normal");
	  break;
	case 3 :
	  strcat(txt,"Eleve");
	  break;
	default :
	  strcat(txt,"Tres Eleve");
	}
      strcat(txt," >>");
    }

  Fonter.Print (5,
		SCREEN_Y/2 + curMenu->MENU_Y[id],
		txt);
  return;
}

void menuSetComment(char*str,int timeLong)
{
  menuCommentTime=timeLong;
  strcpy(menuComment,str);
}

