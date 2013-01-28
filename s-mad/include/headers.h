
#define PI 3.1415926535897932

GtkWidget * pWin;

void AlertMsgInfo(char*msg);
void AlertMsgWarning(char*msg);
void OnMapAdd(GtkWidget *pWidget, gpointer pData);
void OnWingAdd(GtkWidget *pWidget, gpointer pData);
void OnOpen_create_file_selection (void);
void OnClose(GtkWidget *pWidget, gpointer pData);
void Open_File(char * url);
void Save_File(void);
void Aff_Tag_Info(void);
void Aff_Tag_Mod(void);
void UpdateFrameD(GtkWidget *pWidget, gpointer pData);
void OnAide(GtkWidget *pWidget, gpointer pData);
void OnSave(GtkWidget *pWidget, gpointer pData);
void OnSaveAs(GtkWidget *pWidget, gpointer pData);
void OnAddSkySphere(GtkWidget *pWidget, gpointer pData);
void OnAddGrounder(GtkWidget *pWidget, gpointer pData);
void OnAddBuilder(GtkWidget *pWidget, gpointer pData);
void OnRemObj(GtkWidget *pWidget, gpointer pData);
void OnAddObj(GtkWidget *pWidget, gpointer pData);
void OnMoveObj(GtkWidget *pWidget, gpointer pData);
void OnFlipObj(GtkWidget *pWidget, gpointer pData);
void OnEquaTex(GtkWidget *pWidget, gpointer pData);
void OnShapeSphere(GtkWidget *pWidget, gpointer pData);
void OnShapeDisc(GtkWidget *pWidget, gpointer pData);
void OnChamps(GtkWidget *pWidget, gpointer pData);
void New_Tag_Drone(void);
void New_Tag_Shoker(void);
void New_Tag_Map(void);
void New_Tag_Wing(void);
void Remove_Tag(void);

GtkTreeModel * Model;
GtkWidget * TreeView;
GtkWidget * FrameD;
GtkWidget * VBoxD;
GtkWidget * entryD[2]={NULL,NULL}; // type / texture
int oD=-1;

#define MAPDIR "../data/model/"
#define SW3DIR "../"
#define CFGDIR "../config/map.cfg"
#define WINGDIR "../data/model/"
#define WINGCFGDIR "../config/wing.cfg"

#define CLIMAT_NORMAL '0'
#define CLIMAT_TEMPETE 'T'
#define CLIMAT_SABLE 'S'
#define CLIMAT_NUIT 'N'
#define CLIMAT_NEIGE 'n'
#define CLIMAT_CRUE 'C'
#define CLIMAT_INONDATION 'I'
#define CLIMAT_SECHERESSE 's'
#define CLIMAT_AUBE 'A'
#define CLIMAT_ESPACE 'E'
#define CLIMAT_CREPUSCULE 'c'
#define CLIMAT_ENFER 'e'

#include "method.h"
#include "madDef.h"
madModel * M=NULL;
#include "cell.h"
#include "map-add.h"
#include "wing-add.h"
#include "on.h"
#include "menu.h"
#include "boxes.h"
#include "tag.h"
#include "file.h"
#include "loadnsave.h"
#include "framed.h"
