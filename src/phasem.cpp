/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** phasem.cpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/

void InitJ(void);

// Gestion d'initialisation globale
void InitM(void)
{
	// Liste des Maps
	mapDetail=(mapDet *) malloc(sizeof(mapDet));
	FILE * fIn=fopen("./config/map.cfg","r");
	if(!fIn)
		logOut("Problème lors de l'ouverture de [config/map.cfg]");
	else
	{
		while(!feof(fIn))
		{
			char cTest[30];
			fread(&cTest,sizeof(char),30,fIn);
			if(!feof(fIn))
			{
				nbMaps++;
				mapDetail=(mapDet *) realloc(mapDetail, sizeof(mapDet)*nbMaps);
				strcpy(mapDetail[nbMaps-1].nom,cTest);      
				char mapUrl[50];
				strcpy(mapUrl,"./data/model/");
				strcat(mapUrl,cTest);
				strcat(mapUrl,".mad");
				char*inf=NULL;
				inf=getStrFromMadMap(mapUrl,'n',1);
				strcpy(mapDetail[nbMaps-1].name,inf);
				delete inf;
				mapDetail[nbMaps-1].nbClimat=getNbFromMadMap(mapUrl,'C');
				mapDetail[nbMaps-1].tabClimat=new char [mapDetail[nbMaps-1].nbClimat];
				for(int ic=0 ; ic<mapDetail[nbMaps-1].nbClimat ; ic++)
				{
					char*cCT=getStrFromMadMap(mapUrl,'C',ic+1);
					mapDetail[nbMaps-1].tabClimat[ic]=*cCT;
					delete cCT;
				}
			}
		}
		fclose(fIn);
	}
	
	strcpy(MAPURL,"data/model/");
	strcat(MAPURL,mapDetail[curMap].nom);
	strcat(MAPURL,".mad");
	
	// Liste des Vaisseaux
	wingDetail=(wingDet *) malloc(sizeof(wingDet));
	fIn=fopen("./config/wing.cfg","r");
	if(!fIn)
		logOut("Problème lors de l'ouverture de [config/wing.cfg]");
	else
	{
		while(!feof(fIn))
		{
			char cTest[30];
			fread(&cTest,sizeof(char),30,fIn);
			if(!feof(fIn))
			{
				nbWings++;
				wingDetail=(wingDet *) realloc(wingDetail, sizeof(wingDet)*nbWings);
				strcpy(wingDetail[nbWings-1].nom,cTest);      
				char wingUrl[50];
				strcpy(wingUrl,"./data/model/");
				strcat(wingUrl,cTest);
				strcat(wingUrl,".mad");
				char*inf=NULL;
				inf=getStrFromMadWing(wingUrl,'n');
				strcpy(wingDetail[nbWings-1].name,inf);
				delete inf;
			}
		}
		fclose(fIn);
	}
	strcpy(WINGURL,"data/model/");
	strcat(WINGURL,wingDetail[curWing].nom);
	strcat(WINGURL,".mad");
	
	clAvaMan * AvaMan=clAvaMan::Create();
	AvaMan->OpenList();
	
	// Charger la texture de la police
	Fonter.ChargerTexture (FILE_TEXTURE_FONT);
	
	SkinMenu=new cl_model("data/model/menu_star.mad");
	
	clSoundMan * Sound=clSoundMan::Create();
	Sound->CtrlNoiseActive(true);
	Sound->JouerStream (MUSIC_MENU, CANAL_MUSIQUE, false);
	
	TIMElast=TIMEcur=GETTIME;
	
	menuSetComment("[http://studioamanga.free.fr]",5000);
	
	return;
}



// Fonction de remise ‡ jour
void IdleM(void)
{
	TIMElast=TIMEcur;
	TIMEcur=GETTIME;
	
	// Forcer le reDisplay
	glutPostRedisplay();
	return;
}


/*
 // *********************************************
 // Selection de la map
 printf("Selectionnez la map voulue :\n");
 
 FILE * fIn=fopen("config/map.cfg","r");
 mapDetailLast=new mapDetail;
 fread(&(mapDetailLast->nom),sizeof(char),30,fIn);
 char mapUrl1[50];
 strcpy(mapUrl1,"./modelor/");
 strcat(mapUrl1,mapDetailLast->nom);
 strcat(mapUrl1,".mad");
 char*inf1=getStrFromMadMap(mapUrl1,'F',1);
 strcpy(mapDetailLast->comment,inf1);
 delete inf1;
 inf1=getStrFromMadMap(mapUrl1,'n',1);
 strcpy(mapDetailLast->name,inf1);
 delete inf1;
 mapDetailLast->nbClimat=getNbFromMadMap(mapUrl1,'C');
 mapDetailLast->tabClimat=new char[mapDetailLast->nbClimat];
 for(int ic=0 ; ic<mapDetailLast->nbClimat ; ic++)
 {
	 char*cCT=getStrFromMadMap(mapUrl1,'C',ic+1);
	 mapDetailLast->tabClimat[ic]=*cCT;
	 delete cCT;
 }
 //delete inf1;
 mapDetail*cur=mapDetailLast->NEXT;
 mapDetail*prec=mapDetailLast;
 
 while(!feof(fIn))
 {
	 char cTest[30];
	 fread(&cTest,sizeof(char),30,fIn);
	 if(!feof(fIn))
	 {
		 cur=new mapDetail;
		 prec->NEXT=cur;
		 cur->BACK=prec;
		 strcpy(cur->nom,cTest);      
		 char mapUrl[50];
		 strcpy(mapUrl,"./modelor/");
		 strcat(mapUrl,cur->nom);
		 strcat(mapUrl,".mad");
		 char*inf=getStrFromMadMap(mapUrl,'F',1);
		 strcpy(cur->comment,inf);
		 delete inf;
		 inf=getStrFromMadMap(mapUrl,'n',1);
		 strcpy(cur->name,inf);
		 delete inf;
		 cur->nbClimat=getNbFromMadMap(mapUrl,'C');
		 cur->tabClimat=new char [cur->nbClimat];
		 for(int ic=0 ; ic<cur->nbClimat ; ic++)
		 {
			 char*cCT=getStrFromMadMap(mapUrl,'C',ic+1);
			 cur->tabClimat[ic]=*cCT;
			 delete cCT;
		 }
		 
		 prec=cur;
		 cur=cur->NEXT;
	 }
 }
 fclose(fIn);
 
 cur=mapDetailLast;
 char c;
 while(c!='y')
 {
	 printf(" >> %s ( %d climats )? (y/s)\n",cur->name,cur->nbClimat);
	 printf("> %s\n",cur->comment);
	 cin>>c;
	 switch(c)
	 {
		 case 's':
			 if(cur->NEXT!=NULL)
				 cur=cur->NEXT;
			 else
				 cur=mapDetailLast;
			 break;
		 default :
			 c='y';
			 strcpy(MAPURL,"./modelor/");
			 strcat(MAPURL,cur->nom);
			 strcat(MAPURL,".mad");
	 };
 }
 c=0;
 while(c!='y')
 {
	 char typeC[10];
	 switch(cur->tabClimat[MAPCLIMAT-1])
	 {
		 case 'T' :
			 strcpy(typeC,"TempÍte");
			 break;
		 case 'S' :
			 strcpy(typeC,"Sable");
			 break;
		 case 'n' :
			 strcpy(typeC,"Neige");
			 break;
		 case 'C' :
			 strcpy(typeC,"Crue");
			 break;
		 case 'I' :
			 strcpy(typeC,"Innondation");
			 break;
		 case 's' :
			 strcpy(typeC,"SÈcheresse");
			 break;
		 case 'A' :
			 strcpy(typeC,"Aube");
			 break;
		 case 'E' :
			 strcpy(typeC,"Espace");
			 break;
		 case 'c' :
			 strcpy(typeC,"CrÈpuscule");
			 break;
		 case 'e' :
			 strcpy(typeC,"Enfer");
			 break;
		 case 'N' :
			 strcpy(typeC,"Nuit");
			 break;
		 default :
			 strcpy(typeC,"Normal");
	 }
	 printf("Souhaitez-vous le climat %d : %s ? (y/s)",MAPCLIMAT,typeC);
	 cin>>c;
	 switch(c)
	 {
		 case 's':
			 MAPCLIMAT++;
			 if(MAPCLIMAT>cur->nbClimat)
				 MAPCLIMAT=1;
				 break;
		 default :
			 c='y';
	 };
 }
 
 mapDetail*curdel=mapDetailLast;
 while(curdel!=NULL)
 {
	 mapDetailLast=mapDetailLast->NEXT;
	 delete curdel->tabClimat;
	 delete curdel;
	 curdel=mapDetailLast;
 }
 */
