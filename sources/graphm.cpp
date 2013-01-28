/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** graphm.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions relatives à l'affichage en général, à la      **
** gestion du clavier, ou à l'initialisation des données   **
** globales.                                               **
**                                                         **
*************************************************************/

void InitJ(void);

// Gestion d'initialisation globale
void InitM(void)
{
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
	  strcpy(typeC,"Tempête");
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
	  strcpy(typeC,"Sécheresse");
	  break;
	case 'A' :
	  strcpy(typeC,"Aube");
	  break;
	case 'E' :
	  strcpy(typeC,"Espace");
	  break;
	case 'c' :
	  strcpy(typeC,"Crépuscule");
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

  // *********************************************

  Disp=DISP_JEU;
  InitJ();

  return;
}


// Fonction d'affichage de la scène
void DisplayM(void)
{  
  // Nettoyage du tampon ( par la couleur noire )
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Réinitialisation de la matrice de vue
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  // Configuration de la caméra ( position, orientation et cadrage )
  gluLookAt(0,0,0,
	    0,0,0,
	    0,1,0);

  glDepthMask(GL_TRUE);

  //3d

  glDepthMask(GL_TRUE);
  /*
  // ************** Mask
  OrthoMode(0,0,SCREEN_X,SCREEN_Y);
  glColor4f(1,1,1,1);
  
  glDisable(GL_DEPTH_TEST);
  if(LIGHTON)
    glDisable(GL_LIGHTING);
  glBlendFunc(GL_DST_COLOR,GL_ZERO);

  glEnable(GL_BLEND);
  
  tmask->setTexture();
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,0);
  glTexCoord2f(0.0f, 0.5f);
  glVertex2f(0,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.5f);
  glVertex2f(SCREEN_X/2,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(SCREEN_X/2,0);
  

  glBlendFunc(GL_ONE,GL_ONE);
  tcache->setTexture();


  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,0);
  glTexCoord2f(0.0f, 0.5f);
  glVertex2f(0,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.5f);
  glVertex2f(SCREEN_X/2,SCREEN_Y/4);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(SCREEN_X/2,0);

  glTexCoord2f(0.78f, 0.82f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y*0.8);
  glTexCoord2f(1.0f, 0.82f);
  glVertex2f(SCREEN_X,SCREEN_Y*0.8);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(SCREEN_X,SCREEN_Y);
  glTexCoord2f(0.78f, 1.0f);
  glVertex2f(SCREEN_X*0.8,SCREEN_Y); 

  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  if(LIGHTON)
    glEnable(GL_LIGHTING);
  glEnable(GL_FOG);

  PerspectiveMode();
  */
  // Inversion des buffers ( multi-buffering )
  glutSwapBuffers();


  return;
}


// Fonction de remise à jour
void IdleM(void)
{
  // Forcer le reDisplay
  glutPostRedisplay();
  return;
}
