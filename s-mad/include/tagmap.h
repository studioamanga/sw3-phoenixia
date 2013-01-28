

void Aff_Tag_Info_Map(void)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  GtkWidget *hbox=gtk_hbox_new(FALSE, 5);
  GtkWidget *vvbox;
  GtkWidget *button;
  gint response;
  gchar *sUtf8;
  char dep[201];
  //int I=0;
  //char coo[101];
  

  frame=gtk_frame_new("Nom");
  sUtf8 = g_locale_to_utf8(M->Nom, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Url");
  sUtf8 = g_locale_to_utf8(M->Url, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Type d'Animation");
  switch(M->typeAnim)
    {
    case 'S' :
      sUtf8 = g_locale_to_utf8("Shoker", -1, NULL, NULL, NULL);
      break;
    case 'M' :
      sUtf8 = g_locale_to_utf8("Map", -1, NULL, NULL, NULL);
      break;
    default :
      sUtf8 = g_locale_to_utf8("Normal", -1, NULL, NULL, NULL);
    }
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);

  frame=gtk_frame_new("Description");
  sUtf8 = g_locale_to_utf8(M->Description, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  hbox=gtk_hbox_new(FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Climats");
  sprintf(dep,"Nombre de Climats : %d", M->nbClimats);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Climats");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_Tag_Info_Climats), NULL);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Drones");
  sprintf(dep,"Texture : %s\nNombre de Drones : %d", M->Drone, M->nbDrones);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Drones");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_Tag_Info_Drones), NULL);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);


  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Shokers");
  sprintf(dep,"Texture : %s\nNombre de Shokers : %d", M->Shoker, M->nbShokers);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Shokers");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_Tag_Info_Shokers), NULL);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);

  frame=gtk_frame_new("Depart");
  sprintf(dep,"X : %f / Y : %f / Z : %f",M->Depart.x, M->Depart.y, M->Depart.z);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Limites");
  sprintf(dep,"X : %f/%f / Y : %f/%f / Z : %f/%f",M->LimitXMin,M->LimitXMax,M->LimitYMin,M->LimitYMax,M->LimitZMin,M->LimitZMax);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Liquide");
  sprintf(dep,"Hauteur moyenne : %f / Hauteur minimale : %f / Hauteur maximale %f\nTexture : %s",M->Liq, M->LiqMin, M->LiqMax, M->LiqTexture);
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


void Aff_Tag_Info_Climats(void)
{
  int I=0;
  char txt[100];
  for(I=0 ; I<M->nbClimats ; I++)
    {
      sprintf(txt,"Climat n%d\n", I+1);
      switch(M->Climats[I])
	{
	case CLIMAT_NORMAL :
	  strcat(txt,"  Normal\n");
	  break;
	case CLIMAT_TEMPETE :
	  strcat(txt,"  Tempête\n");
	  break;
	case CLIMAT_SABLE :
	  strcat(txt,"  Sable\n");
	  break;
	case CLIMAT_NUIT :
	  strcat(txt,"  Nuit\n");
	  break;
	case CLIMAT_NEIGE :
	  strcat(txt,"  Neige\n");
	  break;
	  case CLIMAT_CRUE :
	  strcat(txt,"  Crue\n");
	  break;
	case CLIMAT_INONDATION :
	  strcat(txt,"  Inondation\n");
	  break;
	case CLIMAT_SECHERESSE :
	  strcat(txt,"  Sécheresse\n");
	  break;
	case CLIMAT_AUBE :
	  strcat(txt,"  Aube\n");
	  break;
	case CLIMAT_ESPACE :
	  strcat(txt,"  Espace\n");
	  break;
	case CLIMAT_CREPUSCULE :
	  strcat(txt,"  Crépuscule");
	  break;
	case CLIMAT_ENFER :
	  strcat(txt,"  Enfer\n");
	  break;
	default :
	  strcat(txt,"  Climat inc.\n");
	}
      AlertMsgInfo(txt);
    }
}


void Aff_Tag_Mod_Map(void)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  GtkWidget *hbox=gtk_hbox_new(FALSE, 5);
  GtkWidget *vvbox;
  GtkWidget *hhbox;
  GtkWidget *button;
  // Entrée : Nom / Url / Descr / Anim / Drone / Shoker / 3 Dep / 6 Lim / 4 Liq
  GtkWidget *entry[19];
  gint response;
  gchar *sUtf8;
  char dep[101];
  //int I=0;
  //char coo[101];
  

  frame=gtk_frame_new("Nom");
  entry[0] = EntryFromStr(M->Nom);
  gtk_container_add (GTK_CONTAINER (frame), entry[0]);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Url");
  entry[1] = EntryFromStr(M->Url);
  gtk_container_add (GTK_CONTAINER (frame), entry[1]);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

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
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);

  frame=gtk_frame_new("Description");
  entry[2] = EntryFromStr(M->Description);
  gtk_container_add (GTK_CONTAINER (frame), entry[2]);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  hbox=gtk_hbox_new(FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Climats");
  sprintf(dep,"Nombre de Climats : %d", M->nbClimats);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("_Ajouter un Climat");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Add_Climat), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Climats");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_Tag_Mod_Climats), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Drones");
  label = gtk_label_new ("Texture :");
  entry[4] = EntryFromStr(M->Drone);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), entry[4], FALSE, FALSE, 5);
  sprintf(dep,"Nombre de Drones : %d", M->nbDrones);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("A_jouter un Drone");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Add_Drone), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Drones");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_Tag_Mod_Drones), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);


  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Shokers");
  label = gtk_label_new ("Texture :");
  entry[5] = EntryFromStr(M->Shoker);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), entry[5], FALSE, FALSE, 5);
  sprintf(dep,"Nombre de Shokers : %d", M->nbShokers);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Aj_outer un Shoker");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Add_Shoker), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Shokers");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_Tag_Mod_Shokers), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);

  hbox=gtk_hbox_new(FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Depart");
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("X");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[6] = EntryFromFloat(M->Depart.x);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[6], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Y");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[7] = EntryFromFloat(M->Depart.y);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[7], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Z");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[8] = EntryFromFloat(M->Depart.z);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[8], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Limites");
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("X Minimum");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[9] = EntryFromFloat(M->LimitXMin);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[9], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("X Maximum");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[10] = EntryFromFloat(M->LimitXMax);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[10], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Y Minimum");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[11] = EntryFromFloat(M->LimitYMin);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[11], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Y Maximum");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[12] = EntryFromFloat(M->LimitYMax);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[12], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Z Minimum");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[13] = EntryFromFloat(M->LimitZMin);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[13], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Z Maximum");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[14] = EntryFromFloat(M->LimitZMax);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[14], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);


  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Liquide");
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Hauteur moyenne");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[15] = EntryFromFloat(M->Liq);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[15], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Hauteur minimale");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[16] = EntryFromFloat(M->LiqMin);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[16], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Hauteur maximale");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[17] = EntryFromFloat(M->LiqMax);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[17], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Texture");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[18] = EntryFromStr(M->LiqTexture);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[18], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);
  

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
      strcpy(M->Nom,gtk_entry_get_text(GTK_ENTRY(entry[0])));
      strcpy(M->Url,gtk_entry_get_text(GTK_ENTRY(entry[1])));
      strcpy(M->Description,gtk_entry_get_text(GTK_ENTRY(entry[2])));
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
      strcpy(M->Drone,gtk_entry_get_text(GTK_ENTRY(entry[4])));
      strcpy(M->Shoker,gtk_entry_get_text(GTK_ENTRY(entry[5])));
      M->Depart.x=atof(gtk_entry_get_text (GTK_ENTRY (entry[6])));
      M->Depart.y=atof(gtk_entry_get_text (GTK_ENTRY (entry[7])));
      M->Depart.z=atof(gtk_entry_get_text (GTK_ENTRY (entry[8])));
      M->LimitXMin=atof(gtk_entry_get_text (GTK_ENTRY (entry[9])));
      M->LimitXMax=atof(gtk_entry_get_text (GTK_ENTRY (entry[10])));
      M->LimitYMin=atof(gtk_entry_get_text (GTK_ENTRY (entry[11])));
      M->LimitYMax=atof(gtk_entry_get_text (GTK_ENTRY (entry[12])));
      M->LimitZMin=atof(gtk_entry_get_text (GTK_ENTRY (entry[13])));
      M->LimitZMax=atof(gtk_entry_get_text (GTK_ENTRY (entry[14])));
      M->Liq=atof(gtk_entry_get_text (GTK_ENTRY (entry[15])));
      M->LiqMin=atof(gtk_entry_get_text (GTK_ENTRY (entry[16])));
      M->LiqMax=atof(gtk_entry_get_text (GTK_ENTRY (entry[17])));
      strcpy(M->LiqTexture,gtk_entry_get_text(GTK_ENTRY(entry[18])));
    }

  gtk_widget_destroy (dialog);

  return;
}

void Add_Climat(GtkWidget *pWidget, gpointer pData)
{
  gchar *sUtf8;
  char dep[101];

  M->nbClimats++;

  M->Climats=(char*)realloc(M->Climats,M->nbClimats*sizeof(char));
  M->Climats[M->nbClimats-1]=CLIMAT_NORMAL;

  sprintf(dep,"Nombre de Climats : %d", M->nbClimats);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
  g_free(sUtf8);
}

void Add_Drone(GtkWidget *pWidget, gpointer pData)
{
  gchar *sUtf8;
  char dep[101];

  M->nbDrones++;

  M->Drones=(Vertex3f*)realloc(M->Drones,M->nbDrones*sizeof(Vertex3f));
  M->Drones[M->nbDrones-1].x=0;
  M->Drones[M->nbDrones-1].y=0;
  M->Drones[M->nbDrones-1].z=0;

  sprintf(dep,"Nombre de Drones : %d", M->nbDrones);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
  g_free(sUtf8);
}

void Add_Shoker(GtkWidget *pWidget, gpointer pData)
{
  gchar *sUtf8;
  char dep[101];

  M->nbShokers++;

  M->Shokers=(Vertex3f*)realloc(M->Shokers,M->nbShokers*sizeof(Vertex3f));
  M->Shokers[M->nbShokers-1].x=0;
  M->Shokers[M->nbShokers-1].y=0;
  M->Shokers[M->nbShokers-1].z=0;

  sprintf(dep,"Nombre de Shokers : %d", M->nbShokers);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
  g_free(sUtf8);
}

int getIdClimat(char id)
{
  int id2=0;
  switch(id)
	{
	case CLIMAT_NORMAL :
	  id2=0;
	  break;
	case CLIMAT_TEMPETE :
	  id2=1;
	  break;
	case CLIMAT_SABLE :
	  id2=2;
	  break;
	case CLIMAT_NUIT :
	  id2=3;
	  break;
	case CLIMAT_NEIGE :
	  id2=4;
	  break;
	case CLIMAT_CRUE :
	  id2=5;
	  break;
	case CLIMAT_INONDATION :
	  id2=6;
	  break;
	case CLIMAT_SECHERESSE :
	  id2=7;
	  break;
	case CLIMAT_AUBE :
	  id2=8;
	  break;
	case CLIMAT_ESPACE :
	  id2=9;
	  break;
	case CLIMAT_CREPUSCULE :
	  id2=10;
	  break;
	case CLIMAT_ENFER :
	  id2=11;
	  break;
	default :
	  id2=0;      
	}
  return id2;
}

char getIndexClimat(int index)
{
  char c;
  switch(index)
    {
    case 0 :
      c=CLIMAT_NORMAL;
      break;
    case 1 :
      c=CLIMAT_TEMPETE;
      break;
    case 2 :
      c=CLIMAT_SABLE;
      break;
    case 3 :
      c=CLIMAT_NUIT;
      break;
    case 4 :
      c=CLIMAT_NEIGE;
      break;
    case 5 :
      c=CLIMAT_CRUE;
      break;
    case 6 :
      c=CLIMAT_INONDATION;
      break;
    case 7 :
      c=CLIMAT_SECHERESSE;
      break;
    case 8 :
      c=CLIMAT_AUBE;
      break;
    case 9 :
      c=CLIMAT_ESPACE;
      break;
    case 10 :
      c=CLIMAT_CREPUSCULE;
      break;
    case 11 :
      c=CLIMAT_ENFER;
      break;
    default :
      c=CLIMAT_NORMAL;
    }
  return c;
}


void Aff_Tag_Mod_Climats(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  guint response;
  gchar *sUtf8;
  char dep[201];
  GtkWidget *label;
  int I=0;
 
  for(I=0 ; I<M->nbClimats ; I++)
    {
      GtkWidget * combo_box = gtk_combo_box_new_text ();
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Normal");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Tempete");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Sable");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Nuit");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Neige");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Crue");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Inondation");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Secheresse");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Aube");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Espace");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Crepuscule");
      gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box), "Enfer");
      gtk_combo_box_set_active (GTK_COMBO_BOX (combo_box), getIdClimat(M->Climats[I]));

      vbox=gtk_vbox_new(FALSE, 5);

      sprintf(dep,"Climat n%d", I+1);
      sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
      label = gtk_label_new (NULL);
      gtk_label_set_markup (GTK_LABEL (label), sUtf8);
      g_free(sUtf8);
      gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 5);

      gtk_box_pack_start (GTK_BOX (vbox), combo_box, FALSE, FALSE, 5);

      
      dialog = gtk_dialog_new_with_buttons ("Modifier le Climat",
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
	  M->Climats[I]=getIndexClimat(gtk_combo_box_get_active (GTK_COMBO_BOX (combo_box)));
	}
      if(response==GTK_RESPONSE_CANCEL)
	{
	  int Y=I;
	  M->nbClimats--;
	  for(Y=I ; Y<M->nbClimats ; Y++)
	    {
	      M->Climats[Y]=M->Climats[Y+1];
	    }
	  M->Climats=(char*)realloc(M->Climats,M->nbClimats*sizeof(char));

	  sprintf(dep,"Nombre de Climats : %d", M->nbClimats);
	  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
	  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
	  g_free(sUtf8);
	  I--;
	}

      gtk_widget_destroy (dialog);
    }
}

void New_Tag_Map(void)
{
  if(M->nbTag!=0)
    {
      AlertMsgWarning("Ce modele possede deja un Tag !");
      return;
    }
  M->Tag='M';
  M->nbTag=1;

  M->typeAnim='M';
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
  strcpy(M->LiqTexture,"data/texture/env/mer.bmp");
  M->LiqR=0;
  M->LiqG=0;
  M->LiqB=1;
  M->LiqAlpha=0.8;
  M->LimitXMin=-1000;
  M->LimitXMax=1000;
  M->LimitYMin=-1000;
  M->LimitYMax=1000;
  M->LimitZMin=-1000;
  M->LimitZMax=1000;
  strcpy(M->Description,"Nouvelle Map SW3");
  strcpy(M->Nom,"map");
}
