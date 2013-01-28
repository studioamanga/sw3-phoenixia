

void Aff_Tag_Info_Shokers(void)
{
  int I=0;
  char txt[100];
  for(I=0 ; I<M->nbShokers ; I++)
    {
      sprintf(txt,"Shoker n%d\n  X : %f\n  Y : %f\n  Z : %f", I+1, M->Shokers[I].x, M->Shokers[I].y, M->Shokers[I].z);
      AlertMsgInfo(txt);
    }
}


void Aff_Tag_Mod_Shokers(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  guint response;
  gchar *sUtf8;
  char dep[201];
  GtkWidget *label;
  int I=0;

  for(I=0 ; I<M->nbShokers ; I++)
    {
      GtkWidget * entry[3];
      vbox=gtk_vbox_new(FALSE, 5);

      sprintf(dep,"Shoker n%d\nPositions X / Y / Z", I+1);
      sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
      label = gtk_label_new (NULL);
      gtk_label_set_markup (GTK_LABEL (label), sUtf8);
      g_free(sUtf8);
      gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 5);

      entry[0] = EntryFromFloat(M->Shokers[I].x);
      gtk_box_pack_start (GTK_BOX (vbox), entry[0], FALSE, FALSE, 5);
      entry[1] = EntryFromFloat(M->Shokers[I].y);
      gtk_box_pack_start (GTK_BOX (vbox), entry[1], FALSE, FALSE, 5);
      entry[2] = EntryFromFloat(M->Shokers[I].z);
      gtk_box_pack_start (GTK_BOX (vbox), entry[2], FALSE, FALSE, 5);

      
      dialog = gtk_dialog_new_with_buttons ("Modifier le Shoker",
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
	  M->Shokers[I].x=atof(gtk_entry_get_text (GTK_ENTRY (entry[0])));
	  M->Shokers[I].y=atof(gtk_entry_get_text (GTK_ENTRY (entry[1])));
	  M->Shokers[I].z=atof(gtk_entry_get_text (GTK_ENTRY (entry[2])));
	}
      if(response==GTK_RESPONSE_CANCEL)
	{
	  int Y=I;
	  M->nbShokers--;
	  for(Y=I ; Y<M->nbShokers ; Y++)
	    {
	      M->Shokers[Y].x=M->Shokers[Y+1].x;
	      M->Shokers[Y].y=M->Shokers[Y+1].y;
	      M->Shokers[Y].z=M->Shokers[Y+1].z;
	    }
	  M->Shokers=(Vertex3f*)realloc(M->Shokers,M->nbShokers*sizeof(Vertex3f));

	  sprintf(dep,"Nombre de Shokers : %d", M->nbShokers);
	  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
	  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
	  g_free(sUtf8);
	  I--;
	}

      gtk_widget_destroy (dialog);
    }
}


void Aff_Tag_Info_Shoker(void)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  GtkWidget *vvbox;
  gint response;
  gchar *sUtf8;
  char dep[30];

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Caracteristiques");
  sprintf(dep,"Attaque du Shoker : %d", M->nbShokers);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);

  sprintf(dep,"Defense du Shoker : %d", M->nbDrones);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);

  sprintf(dep,"Vitesse du Shoker : %f", M->Depart.y);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);

  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Type");
  switch(M->Drone[0])
    {
    default :
      // Drone de base
      sUtf8 = g_locale_to_utf8("Shoker de Base", -1, NULL, NULL, NULL);
    }
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Taille");
  sprintf(dep,"Rayon du Shoker : %f", M->Depart.x);
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

void Aff_Tag_Mod_Shoker(void)
{
  GtkWidget *dialog;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  GtkWidget *label;
  GtkWidget *vvbox;
  // Entrée : Attaque / Défense / Vitesse / Type / Taille // type d'anim
  GtkWidget *entry[6];
  gint response;
  
  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Type d'Animation");
  entry[5]= gtk_combo_box_new_text ();
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry[5]), "Normal");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry[5]), "Map");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry[5]), "Shoker");
  switch(M->typeAnim)
    {
    case 'S' :
      gtk_combo_box_set_active (GTK_COMBO_BOX (entry[5]), 2);
      break;
    case 'M' :
      gtk_combo_box_set_active (GTK_COMBO_BOX (entry[5]), 1);
      break;
    default :
      gtk_combo_box_set_active (GTK_COMBO_BOX (entry[5]), 0);
    }
  gtk_container_add (GTK_CONTAINER (frame), entry[5]);
  gtk_box_pack_start (GTK_BOX (vvbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Caracteristiques");
  label = gtk_label_new ("Attaque :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  entry[0] = EntryFromInt(M->nbShokers);
  gtk_box_pack_start (GTK_BOX (vvbox), entry[0], FALSE, FALSE, 5);

  label = gtk_label_new ("Defense :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  entry[1] = EntryFromInt(M->nbDrones);
  gtk_box_pack_start (GTK_BOX (vvbox), entry[1], FALSE, FALSE, 5);

  label = gtk_label_new ("Vitesse :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  entry[2] = EntryFromFloat(M->Depart.y);
  gtk_box_pack_start (GTK_BOX (vvbox), entry[2], FALSE, FALSE, 5);

  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Type");
  //entry[3] = EntryFromChar(M->nbClimats);
  //gtk_container_add (GTK_CONTAINER (frame), entry[3]);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Taille");
  entry[4] = EntryFromFloat(M->Depart.x);
  gtk_container_add (GTK_CONTAINER (frame), entry[4]);
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
      M->nbShokers=atoi(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      M->nbDrones=atoi(gtk_entry_get_text (GTK_ENTRY (entry[1])));
      M->Depart.y=atof(gtk_entry_get_text (GTK_ENTRY (entry[2])));
      M->Depart.x=atof(gtk_entry_get_text (GTK_ENTRY (entry[4])));
      switch(gtk_combo_box_get_active (GTK_COMBO_BOX (entry[5])))
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


void New_Tag_Shoker(void)
{
  if(M->nbTag!=0)
    {
      AlertMsgWarning("Ce modele possede deja un Tag !");
      return;
    }
  M->Tag='S';
  M->nbTag=1;

  M->nbShokers=50;
  M->nbDrones=100;
  M->Depart.x=1;
  M->Depart.y=1;
  M->Drone[0]='0';
}
