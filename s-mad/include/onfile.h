
void OnClose(GtkWidget *pWidget, gpointer pData)
{
  if(M==NULL)
    return;
  
  if(oD!=-1)
	{
	  switch(gtk_combo_box_get_active (GTK_COMBO_BOX (entryD[0])))
	    {
	    case 3 :
	      M->Objets[oD].typeSurf='Q';
	      break;
	    case 0 :
	      M->Objets[oD].typeSurf='L';
	      break;
	    case 1 :
	      M->Objets[oD].typeSurf='T';
	      break;
	    case 2 :
	      M->Objets[oD].typeSurf='F';
	      break;
	    default :
	      M->Objets[oD].typeSurf='M';
	    }
	  strcpy(M->Objets[oD].texture, gtk_entry_get_text(GTK_ENTRY(entryD[1])));
	  }

  GtkWidget* pQuest=gtk_message_dialog_new(GTK_WINDOW(pWin),
					   GTK_DIALOG_MODAL,
					   GTK_MESSAGE_QUESTION,
					   GTK_BUTTONS_YES_NO,
					   "Voulez-vous sauvegarder le model %s",
					   M->Nom);
  switch(gtk_dialog_run(GTK_DIALOG(pQuest)))
    {
    case GTK_RESPONSE_YES :
      //sauver
      Save_File();
    case GTK_RESPONSE_NO :
      delMadModel(M);
      M=NULL;
      update_list();
      gtk_widget_destroy(pQuest);
       
      // upload frameD
      
      oD=-1;
      gtk_widget_destroy(VBoxD);
      VBoxD=gtk_vbox_new(FALSE,0);
      gtk_container_add (GTK_CONTAINER (FrameD), VBoxD);
    }
}


void OnNew(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * RadioType[2];
  guint response;

  if(M!=NULL)
    {
      AlertMsgWarning("Un fichier est deja ouvert !");
      return;
    }
 
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Selectionnez le type de fichier a creer :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  RadioType[0] = gtk_radio_button_new_with_label(NULL, "Vierge");
  gtk_box_pack_start (GTK_BOX (vbox), RadioType[0], FALSE, FALSE, 0);
  RadioType[1] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(RadioType[0]), "Map");
  gtk_box_pack_start (GTK_BOX (vbox), RadioType[1], FALSE, FALSE, 0);
  
  dialog = gtk_dialog_new_with_buttons ("Nouveau MAD",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_NEW,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (vbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));
      
  if(response==GTK_RESPONSE_OK)
    {
      GSList * Res = gtk_radio_button_get_group(GTK_RADIO_BUTTON(RadioType[0]));
      while(Res)
	{
	  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Res->data)))
	    {
	      if(strcmp(gtk_button_get_label(GTK_BUTTON(Res->data)),"Vierge")==0)
		{
		  M=(madModel *)malloc(sizeof(madModel));
		  strcpy(M->Url,"*");
		  strcpy(M->Nom,"New");
		  M->nbTag=0;
		  M->typeAnim='0';
		  M->nbObjets=0;

		  M->Objets=(sObjet *)malloc(sizeof(sObjet)*M->nbObjets);
		}
	      if(strcmp(gtk_button_get_label(GTK_BUTTON(Res->data)),"Map")==0)
		{
		  M=(madModel *)malloc(sizeof(madModel));
		  strcpy(M->Url,"*");
		  strcpy(M->Nom,"New");
		  M->nbTag=1;
		  M->typeAnim='M';
		  M->nbObjets=0;
		  M->Tag='M';
		  M->nbClimats=1;
		  M->Climats=(char*)malloc(1);
		  M->Climats[0]=CLIMAT_NORMAL;
		  M->nbDrones=1;
		  strcpy(M->Drone,"data/model/drone.mad");
		  M->Drones=(Vertex3f*)malloc(sizeof(Vertex3f));
		  M->Drones[0].x=0;
		  M->Drones[0].y=0;
		  M->Drones[0].z=100;
		  M->nbShokers=1;
		  strcpy(M->Shoker,"data/model/shoker.mad");
		  M->Shokers=(Vertex3f*)malloc(sizeof(Vertex3f));
		  M->Shokers[0].x=100;
		  M->Shokers[0].y=0;
		  M->Shokers[0].z=0;
		  M->Depart.x=0;
		  M->Depart.y=0;
		  M->Depart.z=0;
		  M->Liq=0;
		  M->LiqMin=-10;
		  M->LiqMax=10;
		  strcpy(M->LiqTexture,"./data/texture/env/mer.bmp");
		  M->LiqR=0;
		  M->LiqG=0;
		  M->LiqB=1;
		  M->LiqAlpha=0.8;
		  M->LimitXMin=-100;
		  M->LimitXMax=100;
		  M->LimitYMin=-100;
		  M->LimitYMax=100;
		  M->LimitZMin=-100;
		  M->LimitZMax=100;
		  strcpy(M->Description,"Nouvelle Map SW3");

		  M->Objets=(sObjet *)malloc(sizeof(sObjet)*M->nbObjets);
		}
	      Res=NULL;
	    }
	  else
	    Res=g_slist_next(Res);
	}
    }

  gtk_widget_destroy (dialog);

  return;
}

void OnSave(GtkWidget *pWidget, gpointer pData)
{
  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }
  if(strcmp(M->Url,"*")==0)
    {
      OnSaveAs(pWidget,pData);
      return;
    }

  Save_File();

  return;
}

void store_filenameSA (GtkWidget *widget, gpointer user_data) 
{
  GtkWidget *file_selector = GTK_WIDGET (user_data);
  const gchar *selected_filename;

  selected_filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));

  // OPEN
  strcpy(M->Url,selected_filename);
  int len=strlen(M->Url);
  if(len>=4)
    {
      if(M->Url[len-1]=='d' && M->Url[len-2]=='a' && M->Url[len-3]=='m' && M->Url[len-4]=='.')
	{}
      else
	strcat(M->Url,".mad");
    }
  else
    strcat(M->Url,".mad");

  Save_File();
}


void OnSaveAs(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget *file_selector;

  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }

  /* Create the selector */
   
  file_selector = gtk_file_selection_new ("Choisissez un nouveau nom de fichier");
  //gtk_file_selection_complete(GTK_FILE_SELECTION(file_selector),"*.mad");
   
  g_signal_connect (GTK_FILE_SELECTION (file_selector)->ok_button,
		    "clicked",
		    G_CALLBACK (store_filenameSA),
		    file_selector);
                           
  /* Ensure that the dialog box is destroyed when the user clicks a button. */
   
  g_signal_connect_swapped (GTK_FILE_SELECTION (file_selector)->ok_button,
			    "clicked",
			    G_CALLBACK (gtk_widget_destroy), 
			    file_selector);

  g_signal_connect_swapped (GTK_FILE_SELECTION (file_selector)->cancel_button,
			    "clicked",
			    G_CALLBACK (gtk_widget_destroy),
			    file_selector); 
   
  /* Display that dialog */
   
  gtk_widget_show (file_selector);

  return;
}
