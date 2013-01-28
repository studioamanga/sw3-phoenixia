

void OnModY(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * scale;
  guint response;
 
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Selectionnez une valeur pour la hauteur de ce point :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  scale=gtk_hscale_new_with_range(-50,50,1);
  gtk_box_pack_start (GTK_BOX (vbox), scale, FALSE, FALSE, 0);
  gtk_range_set_value(GTK_RANGE(scale),atoi(gtk_button_get_label(GTK_BUTTON(pData))));
      
  dialog = gtk_dialog_new_with_buttons ("Modifier la hauteur",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (vbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));
      
  if(response==GTK_RESPONSE_OK)
    {
      char val[4]="0";
      int va=gtk_range_get_value(GTK_RANGE(scale));
      sprintf(val,"%d",va);
      gtk_button_set_label(GTK_BUTTON((GtkWidget*)pData),val);

      gtk_widget_show_all((GtkWidget*)pData);
    }
  if(response==GTK_RESPONSE_CANCEL)
    {
    }

  gtk_widget_destroy (dialog);

}


void OnModYBuild(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * scale;
  guint response;
 
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Selectionnez une valeur pour la hauteur de ce build :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  scale=gtk_hscale_new_with_range(0,100,1);
  gtk_box_pack_start (GTK_BOX (vbox), scale, FALSE, FALSE, 0);
  gtk_range_set_value(GTK_RANGE(scale),atoi(gtk_button_get_label(GTK_BUTTON(pData))));
      
  dialog = gtk_dialog_new_with_buttons ("Modifier la hauteur",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (vbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));
      
  if(response==GTK_RESPONSE_OK)
    {
      char val[4]="0";
      int va=gtk_range_get_value(GTK_RANGE(scale));
      sprintf(val,"%d",va);
      gtk_button_set_label(GTK_BUTTON((GtkWidget*)pData),val);

      gtk_widget_show_all((GtkWidget*)pData);
    }
  if(response==GTK_RESPONSE_CANCEL)
    {
    }

  gtk_widget_destroy (dialog);

}



void OnMoveObj(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * entry[3];
  GtkWidget * hbox;
  guint response;
 
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Entrez les coordonnees du vecteur de translation :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" X :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[0]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hbox), entry[0], FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" Y :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[1]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hbox), entry[1], FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" Z :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[2]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hbox), entry[2], FALSE, FALSE, 0);
  /*
  label=gtk_label_new("Entrez l'angle en degre de la rotation :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" X :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[3]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hbox), entry[3], FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" Y :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[4]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hbox), entry[4], FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" Z :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[5]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hbox), entry[5], FALSE, FALSE, 0);
  */
      
  dialog = gtk_dialog_new_with_buttons ("Deplacer un objet",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_JUMP_TO,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (vbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));
      
  if(response==GTK_RESPONSE_OK)
    {
      float x, y, z;
      int i;

      x=atof(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      y=atof(gtk_entry_get_text (GTK_ENTRY (entry[1])));
      z=atof(gtk_entry_get_text (GTK_ENTRY (entry[2])));

      
      for(i=0 ; i<M->Objets[oD].nbVertices ; i++ )
	{
	  M->Objets[oD].Vertices[i].x+=x;
	  M->Objets[oD].Vertices[i].y+=y;
	  M->Objets[oD].Vertices[i].z+=z;
	}
      
    }

  gtk_widget_destroy (dialog);

}

void OnFlipObj(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * entry[6];
  GtkWidget * frame;
  GtkWidget * hbox;
  guint response;
 
  hbox=gtk_hbox_new(FALSE, 5);
  frame=gtk_frame_new("Origine");

  vbox=gtk_vbox_new(FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);
  label=gtk_label_new("Intervertir l'axe...");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  entry[0]=gtk_radio_button_new_with_label(NULL,"X");
  gtk_box_pack_start (GTK_BOX (vbox), entry[0], FALSE, FALSE, 0);
  entry[1]=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(entry[0]),"Y");
  gtk_box_pack_start (GTK_BOX (vbox), entry[1], FALSE, FALSE, 0);
  entry[2]=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(entry[1]),"Z");
  gtk_box_pack_start (GTK_BOX (vbox), entry[2], FALSE, FALSE, 0);

  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 0);

  vbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Destination");
  gtk_container_add (GTK_CONTAINER (frame), vbox);
  label=gtk_label_new("...avec l'axe");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  entry[3]=gtk_radio_button_new_with_label(NULL,"X");
  gtk_box_pack_start (GTK_BOX (vbox), entry[3], FALSE, FALSE, 0);
  entry[4]=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(entry[3]),"Y");
  gtk_box_pack_start (GTK_BOX (vbox), entry[4], FALSE, FALSE, 0);
  entry[5]=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(entry[4]),"Z");
  gtk_box_pack_start (GTK_BOX (vbox), entry[5], FALSE, FALSE, 0);

  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 0);
 
      
  dialog = gtk_dialog_new_with_buttons ("Flipper un objet",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_REFRESH,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (hbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));
      
  if(response==GTK_RESPONSE_OK)
    {
      char cFrom, cTo;
      int i;
      const gchar *toogled;
      GSList * pList=gtk_radio_button_get_group(GTK_RADIO_BUTTON(entry[0]));
      while(pList)
	{
	  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
	    {
	      toogled = gtk_button_get_label(GTK_BUTTON(pList->data));
	      pList=NULL;
	    }
	  else
	    pList = g_slist_next(pList);
	}
      if(strcmp(toogled,"X")==0)
	cFrom='X';
      else
	if(strcmp(toogled,"Y")==0)
	  cFrom='Y';
	else
	  cFrom='Z';

      pList=gtk_radio_button_get_group(GTK_RADIO_BUTTON(entry[3]));
      while(pList)
	{
	  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
	    {
	      toogled = gtk_button_get_label(GTK_BUTTON(pList->data));
	      pList=NULL;
	    }
	  else
	    pList = g_slist_next(pList);
	}
      if(strcmp(toogled,"X")==0)
	cTo='X';
      else
	if(strcmp(toogled,"Y")==0)
	  cTo='Y';
	else
	  cTo='Z';

      for(i=0 ; i<M->Objets[oD].nbVertices ; i++ )
	{
	  float *ori;
	  float *dest;
	  float tamp;
	  switch(cFrom)
	    {
	    case 'X':
	      ori=&(M->Objets[oD].Vertices[i].x);
	      break;
	    case 'Y':
	      ori=&(M->Objets[oD].Vertices[i].y);
	      break;
	    default :
	      ori=&(M->Objets[oD].Vertices[i].z);
	    }
	  switch(cTo)
	    {
	    case 'X':
	      dest=&(M->Objets[oD].Vertices[i].x);
	      break;
	    case 'Y':
	      dest=&(M->Objets[oD].Vertices[i].y);
	      break;
	    default :
	      dest=&(M->Objets[oD].Vertices[i].z);
	    }
	  tamp=*ori;
	  *ori=*dest;
	  *dest=tamp;
	  //printf("%f > %f\n",*ori,*dest);
	}
    }

  gtk_widget_destroy (dialog);

}

void OnEquaTex(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * entry[2];
  GtkWidget * hbox;
  guint response;
 
  if(M==NULL || oD==-1)
    return;

  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Entrez le facteur de texture (x100) :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" X :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[0]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hbox), entry[0], FALSE, FALSE, 0);

  hbox=gtk_hbox_new(FALSE,5);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  label=gtk_label_new(" Z :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  entry[1]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hbox), entry[1], FALSE, FALSE, 0);


      
  dialog = gtk_dialog_new_with_buttons ("Egaliser une texture",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (vbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));
      
  if(response==GTK_RESPONSE_OK)
    {
      float x, z;
      int i;

      x=atof(gtk_entry_get_text (GTK_ENTRY (entry[0])))/100;
      z=atof(gtk_entry_get_text (GTK_ENTRY (entry[1])))/100;

      
      for(i=0 ; i<M->Objets[oD].nbVertices ; i++ )
	{
	  M->Objets[oD].Vertices[i].tx=M->Objets[oD].Vertices[i].x*x;
	  M->Objets[oD].Vertices[i].ty=M->Objets[oD].Vertices[i].z*z;
	}
      
    }

  gtk_widget_destroy (dialog);

}
