

void Aff_Tag_Info_Drones(void)
{
  int I=0;
  char txt[100];
  for(I=0 ; I<M->nbDrones ; I++)
    {
      sprintf(txt,"Drone n%d\n  X : %f\n  Y : %f\n  Z : %f", I+1, M->Drones[I].x, M->Drones[I].y, M->Drones[I].z);
      AlertMsgInfo(txt);
    }
}

void Aff_Tag_Mod_Drones(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  guint response;
  gchar *sUtf8;
  char dep[201];
  GtkWidget *label;
  int I=0;

  for(I=0 ; I<M->nbDrones ; I++)
    {
      GtkWidget * entry[3];
      vbox=gtk_vbox_new(FALSE, 5);

      sprintf(dep,"Drone n%d\nPositions X / Y / Z", I+1);
      sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
      label = gtk_label_new (NULL);
      gtk_label_set_markup (GTK_LABEL (label), sUtf8);
      g_free(sUtf8);
      gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 5);

      entry[0] = EntryFromFloat(M->Drones[I].x);
      gtk_box_pack_start (GTK_BOX (vbox), entry[0], FALSE, FALSE, 5);
      entry[1] = EntryFromFloat(M->Drones[I].y);
      gtk_box_pack_start (GTK_BOX (vbox), entry[1], FALSE, FALSE, 5);
      entry[2] = EntryFromFloat(M->Drones[I].z);
      gtk_box_pack_start (GTK_BOX (vbox), entry[2], FALSE, FALSE, 5);

      
      dialog = gtk_dialog_new_with_buttons ("Modifier le Drone",
					    GTK_WINDOW (pWin),
					    GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					    GTK_STOCK_DELETE,
					    GTK_RESPONSE_CANCEL,
					    GTK_STOCK_GO_FORWARD,
					    GTK_RESPONSE_OK,
					    NULL);
      
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
      
      gtk_widget_show_all (vbox);
      
      response = gtk_dialog_run (GTK_DIALOG (dialog));
      
      if(response==GTK_RESPONSE_OK)
	{
	  M->Drones[I].x=atof(gtk_entry_get_text (GTK_ENTRY (entry[0])));
	  M->Drones[I].y=atof(gtk_entry_get_text (GTK_ENTRY (entry[1])));
	  M->Drones[I].z=atof(gtk_entry_get_text (GTK_ENTRY (entry[2])));
	}
      if(response==GTK_RESPONSE_CANCEL)
	{
	  int Y=I;
	  M->nbDrones--;
	  for(Y=I ; Y<M->nbDrones ; Y++)
	    {
	      M->Drones[Y].x=M->Drones[Y+1].x;
	      M->Drones[Y].y=M->Drones[Y+1].y;
	      M->Drones[Y].z=M->Drones[Y+1].z;
	    }
	  M->Drones=(Vertex3f*)realloc(M->Drones,M->nbDrones*sizeof(Vertex3f));

	  sprintf(dep,"Nombre de Drones : %d", M->nbDrones);
	  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
	  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
	  g_free(sUtf8);
	  I--;
	}

      gtk_widget_destroy (dialog);
    }
}


void Aff_Tag_Info_Drone(void)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  gint response;
  gchar *sUtf8;
  char dep[30];

  frame=gtk_frame_new("Valeur");
  sprintf(dep,"Valeur du Drone : %d", M->nbClimats);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Type");
  switch(M->Drone[0])
    {
    default :
      // Drone de base
      sUtf8 = g_locale_to_utf8("Drone de Base", -1, NULL, NULL, NULL);
    }
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Taille");
  sprintf(dep,"Rayon du Drone : %f", M->Depart.x);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);
  

  dialog = gtk_dialog_new_with_buttons ("Info sur le Tag",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
  
  gtk_widget_show_all (vbox);

  response = gtk_dialog_run (GTK_DIALOG (dialog));


  gtk_widget_destroy (dialog);

  return;
}

void Aff_Tag_Mod_Drone(void)
{
  GtkWidget *dialog;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  // Entrée : Valeur / Type / Taille / Type d'Anim
  GtkWidget *entry[4];
  gint response;
  

  frame=gtk_frame_new("Type d'Animation");
  entry[3]= gtk_combo_box_new_text ();
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry[3]), "Normal");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry[3]), "Map");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry[3]), "Shoker");
  switch(M->typeAnim)
    {
    case 'S' :
      gtk_combo_box_set_active (GTK_COMBO_BOX (entry[3]), 2);
      break;
    case 'M' :
      gtk_combo_box_set_active (GTK_COMBO_BOX (entry[3]), 1);
      break;
    default :
      gtk_combo_box_set_active (GTK_COMBO_BOX (entry[3]), 0);
    }
  gtk_container_add (GTK_CONTAINER (frame), entry[3]);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);
  frame=gtk_frame_new("Valeur");
  entry[0] = EntryFromInt(M->nbClimats);
  gtk_container_add (GTK_CONTAINER (frame), entry[0]);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Type");
  //entry[1] = EntryFromChar(M->nbClimats);
  //gtk_container_add (GTK_CONTAINER (frame), entry[1]);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Taille");
  entry[2] = EntryFromFloat(M->Depart.x);
  gtk_container_add (GTK_CONTAINER (frame), entry[2]);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);



  dialog = gtk_dialog_new_with_buttons ("Modifier le Tag",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);
  
  gtk_widget_show_all (vbox);

  response = gtk_dialog_run (GTK_DIALOG (dialog));
  if(response==GTK_RESPONSE_OK)
    {
      M->nbClimats=atoi(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      M->Depart.x=atof(gtk_entry_get_text (GTK_ENTRY (entry[2])));
      switch(gtk_combo_box_get_active (GTK_COMBO_BOX (entry[3])))
	{
	case 2 :
	  M->typeAnim='S';
	  break;
	case 1 :
	  M->typeAnim='M';
	  break;
	default :
	  M->typeAnim='0';
	}
    }

  gtk_widget_destroy (dialog);

  return;
}

void New_Tag_Drone(void)
{
  if(M->nbTag!=0)
    {
      AlertMsgWarning("Ce modele possede deja un Tag !");
      return;
    }
  M->Tag='D';
  M->nbTag=1;

  M->nbClimats=1;
  M->Depart.x=1;
  M->Drone[0]='0';
}
