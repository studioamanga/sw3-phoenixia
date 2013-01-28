/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********** jeu.cpp **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

#include "phasem.cpp"
#include "phasej.cpp"

void FinPartie(void)
{
  bool Win=false;
  if(Crystals->nbDrones==0)
    Win=true;

  clAvaMan * AvaMan=clAvaMan::Create();

  if(Win) // Victoire
    {
      setScore();
      Disp=DISP_MENU;
      curMenu=&WIN_MENU;
      cursMenu=1;
      cursMenuMax=curMenu->MENU_SIZE;
      menuCommentTime=0;
      switch(cursMod)
	{
	case MOD_DEFI :
	  if(AvaMan->curAva->IsRight(cursMod) == cursDefiMission && (cursDefiMission+1) < NB_DEFI_MISSION)
	    {
	      AvaMan->curAva->Upgrade(cursMod);
	      menuSetComment("Nouvelle Mission Disponible.",5000);
	    }
	  break;
	}
    }
  else // Défaite
    {
      Disp=DISP_MENU;
      curMenu=&MAIN_MENU;
      cursMenu=1;
      cursMenuMax=curMenu->MENU_SIZE;
      menuCommentTime=0;
    }

  // Destructions
  DelJ();
}
