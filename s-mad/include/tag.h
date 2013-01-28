
void Aff_Tag_Info_Map(void);
void Aff_Tag_Mod_Map(void);

void Aff_Tag_Info_Wing(void);
void Aff_Tag_Mod_Wing(void);

void Aff_Tag_Info_Drone(void);
void Aff_Tag_Mod_Drone(void);

void Aff_Tag_Info_Shoker(void);
void Aff_Tag_Mod_Shoker(void);

void Aff_Tag_Info_Climats(void);
void Aff_Tag_Info_Drones(void);
void Aff_Tag_Info_Shokers(void);

void Aff_Tag_Mod_Climats(GtkWidget *pWidget, gpointer pData);
void Aff_Tag_Mod_Drones(GtkWidget *pWidget, gpointer pData);
void Aff_Tag_Mod_Shokers(GtkWidget *pWidget, gpointer pData);

void Add_Climat(GtkWidget *pWidget, gpointer pData);
void Add_Drone(GtkWidget *pWidget, gpointer pData);
void Add_Shoker(GtkWidget *pWidget, gpointer pData);

#include "tagmap.h"
#include "tagwing.h"
#include "tagdrone.h"
#include "tagshoker.h"

void Remove_Tag(void)
{
  if(M==NULL)
    {
      AlertMsgWarning("Aucun fichier chargé !");
      return;
    }
  if(M->nbTag<1)
    {
      AlertMsgWarning("Aucun tag associé !");
      return;
    }
  M->nbTag=0;
}

void Aff_Tag_Info(void)
{
  if(M==NULL)
    {
      AlertMsgWarning("Aucun fichier chargé !");
      return;
    }
  if(M->nbTag<1)
    {
      AlertMsgWarning("Aucun tag associé !");
      return;
    }

  switch(M->Tag)
    {
    case 'M' :
      Aff_Tag_Info_Map();
      break;
    case 'W' :
      Aff_Tag_Info_Wing();
      break;
    case 'D' :
      Aff_Tag_Info_Drone();
      break;
    case 'S' :
      Aff_Tag_Info_Shoker();
      break;
    default :
      AlertMsgWarning("Tag non reconnu !");
    }
}

void Aff_Tag_Mod(void)
{
  if(M==NULL)
    {
      AlertMsgWarning("Aucun fichier chargé !");
      return;
    }
  if(M->nbTag<1)
    {
      AlertMsgWarning("Aucun tag associé !");
      return;
    }

  switch(M->Tag)
    {
    case 'M' :
      Aff_Tag_Mod_Map();
      break;
    case 'W' :
      Aff_Tag_Mod_Wing();
      break;
    case 'D' :
      Aff_Tag_Mod_Drone();
      break;
    case 'S' :
      Aff_Tag_Mod_Shoker();
      break;
    default :
      AlertMsgWarning("Tag non reconnu !");
    }
}
