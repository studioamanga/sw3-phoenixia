
void Add_React(GtkWidget *pWidget, gpointer pData);
void Aff_React(GtkWidget *pWidget, gpointer pData);

void Aff_Tag_Info_Wing(void)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  GtkWidget *hbox=gtk_hbox_new(FALSE, 5);
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

  frame=gtk_frame_new("Caracteristiques");
  sprintf(dep,
	  "Rayon %f / Vitesse %f / Dir %f / Armure %f / Shield %f", 
	  M->LiqR, M->LiqG, M->LiqB, M->LiqAlpha, M->Liq);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Armes");
  sprintf(dep,
	  "1:%d / 2:%d / 3:%d / 4:%d / 5:%d / 6:%d / 7:%d / 8:%d / 9:%d / 10:%d",
	  M->Weapons[0], M->Weapons[1], M->Weapons[2], M->Weapons[3], M->Weapons[4], M->Weapons[5],
	  M->Weapons[6], M->Weapons[7], M->Weapons[8], M->Weapons[9]);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), sUtf8);
  g_free(sUtf8);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 5);

  frame=gtk_frame_new("Réacteurs :");
  sprintf(dep,
	  "Texture : %s, Nombre : %d", M->Shoker, M->nbShokers);
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



void Aff_Tag_Mod_Wing(void)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *vbox=gtk_vbox_new(FALSE, 5);
  GtkWidget *hbox=gtk_hbox_new(FALSE, 5);
  GtkWidget *vvbox;
  GtkWidget *hhbox;
  // Entrée : Nom / Url / Descr / Anim / rayon / vitesse / dir / armure / shield /
  //          10 armes / nb reacteurs / texture racteurs
  GtkWidget *entry[20];
  GtkWidget *button;
  gint response;
  //int I=0;
  char dep[50];
  

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
  frame=gtk_frame_new("Caracteristiques");
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Rayon");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[4] = EntryFromFloat(M->LiqR);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[4], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Vitesse");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[5] = EntryFromFloat(M->LiqG);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[5], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Dir");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[6] = EntryFromFloat(M->LiqB);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[6], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Armure");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[7] = EntryFromFloat(M->LiqAlpha);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[7], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Shield");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[8] = EntryFromFloat(M->Liq);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[8], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Armes");
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("1 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[9] = EntryFromInt(M->Weapons[0]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[9], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("2 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[10] = EntryFromInt(M->Weapons[1]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[10], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("3 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[11] = EntryFromInt(M->Weapons[2]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[11], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("4 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[12] = EntryFromInt(M->Weapons[3]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[12], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("5 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[13] = EntryFromInt(M->Weapons[4]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[13], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("6 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[14] = EntryFromInt(M->Weapons[5]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[14], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("7 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[15] = EntryFromInt(M->Weapons[6]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[15], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("8 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[16] = EntryFromInt(M->Weapons[7]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[16], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("9 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[17] = EntryFromInt(M->Weapons[8]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[17], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("10 :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[18] = EntryFromInt(M->Weapons[9]);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[18], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 5);

  vvbox=gtk_vbox_new(FALSE, 5);
  frame=gtk_frame_new("Reacteurs");
  hhbox=gtk_hbox_new(FALSE, 5);
  label = gtk_label_new ("Texture");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 5);
  entry[19] = EntryFromStr(M->Shoker);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[19], FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 5);
  sprintf(dep,"Nombre de Reacteurs : %d", M->nbShokers);
  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), dep);
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("A_jouter un Reacteur");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Add_React), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_with_mnemonic ("Lister les _Reacteurs");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Aff_React), label);
  gtk_box_pack_start (GTK_BOX (vvbox), button, FALSE, FALSE, 5);

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
      M->LiqR=atof(gtk_entry_get_text (GTK_ENTRY (entry[4])));
      M->LiqG=atof(gtk_entry_get_text (GTK_ENTRY (entry[5])));
      M->LiqB=atof(gtk_entry_get_text (GTK_ENTRY (entry[6])));
      M->LiqAlpha= atof(gtk_entry_get_text (GTK_ENTRY (entry[7])));
      M->Liq=atof(gtk_entry_get_text (GTK_ENTRY (entry[8])));
      M->Weapons[0]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[9])));
      M->Weapons[1]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[10])));
      M->Weapons[2]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[11])));
      M->Weapons[3]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[12])));
      M->Weapons[4]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[13])));
      M->Weapons[5]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[14])));
      M->Weapons[6]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[15])));
      M->Weapons[7]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[16])));
      M->Weapons[8]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[17])));
      M->Weapons[9]=atoi(gtk_entry_get_text (GTK_ENTRY (entry[18])));

      strcpy(M->Shoker,gtk_entry_get_text(GTK_ENTRY(entry[19])));
    }

  gtk_widget_destroy (dialog);

  return;
}

void Add_React(GtkWidget *pWidget, gpointer pData)
{
  gchar *sUtf8;
  char dep[101];

  M->nbShokers++;

  if(M->Drones==NULL)
    {
      M->Drones=(Vertex3f*)malloc(M->nbShokers*sizeof(Vertex3f));
      M->Shokers=(Vertex3f*)malloc(M->nbShokers*sizeof(Vertex3f));
    }
  else
    {
      M->Drones=(Vertex3f*)realloc(M->Drones,M->nbShokers*sizeof(Vertex3f));
      M->Shokers=(Vertex3f*)realloc(M->Shokers,M->nbShokers*sizeof(Vertex3f));
    }
  M->Drones[M->nbShokers-1].x=1;
  M->Shokers[M->nbShokers-1].x=-1;
  M->Shokers[M->nbShokers-1].y=0;
  M->Shokers[M->nbShokers-1].z=0;

  sprintf(dep,"Nombre de Reacteurs : %d", M->nbShokers);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
  g_free(sUtf8);
}

void Aff_React(GtkWidget *pWidget, gpointer pData)
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
      GtkWidget * entry[4];
      vbox=gtk_vbox_new(FALSE, 5);

      sprintf(dep,"Reacteur n%d\nPositions X / Y / Z\nTaille", I+1);
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
      entry[3] = EntryFromFloat(M->Drones[I].x);
      gtk_box_pack_start (GTK_BOX (vbox), entry[3], FALSE, FALSE, 5);

      
      dialog = gtk_dialog_new_with_buttons ("Modifier le Reacteur",
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
	  M->Drones[I].x=atof(gtk_entry_get_text (GTK_ENTRY (entry[3])));
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
	      M->Drones[Y].x=M->Drones[Y+1].x;
	    }
	  M->Shokers=(Vertex3f*)realloc(M->Shokers,M->nbShokers*sizeof(Vertex3f));
	  M->Drones=(Vertex3f*)realloc(M->Drones,M->nbShokers*sizeof(Vertex3f));

	  sprintf(dep,"Nombre de Reacteurs : %d", M->nbShokers);
	  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
	  gtk_label_set_markup (GTK_LABEL ((GtkWidget*) pData), sUtf8);
	  g_free(sUtf8);
	  I--;
	}

      gtk_widget_destroy (dialog);
    }
}


void New_Tag_Wing(void)
{
  if(M->nbTag!=0)
    {
      AlertMsgWarning("Ce modele possede deja un Tag !");
      return;
    }
  M->Tag='W';
  M->nbTag=1;

  // nb de réacteurs / emplacements des réacteurs / taille des réacteurs en x / url de la texture
  M->nbShokers=0;
  M->Shokers=NULL;
  M->Drones=NULL;
  strcpy(M->Shoker,"data/texture/part/*.tga");
  // taille(rayon) / vitesse / dir / armure / shield
  M->LiqR=2;
  M->LiqG=10;
  M->LiqB=1;
  M->LiqAlpha=100;
  M->Liq=4;
  // coord tirs 1 et 2
  M->LimitXMin=0;
  M->LimitYMin=0;
  M->LimitZMin=0;
  M->LimitXMax=0;
  M->LimitYMax=0;
  M->LimitZMax=0;
  // Armes
  M->Weapons[0]=-1;
  M->Weapons[1]=-1;
  M->Weapons[2]=-1;
  M->Weapons[3]=-1;
  M->Weapons[4]=-1;
  M->Weapons[5]=-1;
  M->Weapons[6]=-1;
  M->Weapons[7]=-1;
  M->Weapons[8]=-1;
  M->Weapons[9]=-1;
 
  strcpy(M->Description,"Nouveau Wing SW3");
  strcpy(M->Nom,"wing");
}
