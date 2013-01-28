


GArray *Strs = NULL;
typedef struct
{
  char nom[30];
}Str;

int nbStrs=0;

enum
  {
    NAME,
    NUMBERMA
  };


void add_itemMA (GtkWidget *button, char*name, gpointer data)
{
  Str S1;
  GtkTreeIter iter;
  GtkTreeModel *model = (GtkTreeModel *)data;

  g_return_if_fail (Strs != NULL);

  strcpy(S1.nom,name);
  g_array_append_vals (Strs, &S1, 1);
  nbStrs++;

  gtk_list_store_append (GTK_LIST_STORE (model), &iter);
  gtk_list_store_set (GTK_LIST_STORE (model), &iter,
		      NAME, S1.nom,
		      -1);
}

void OnAddMA(GtkWidget *button, gpointer data)
{
  GtkWidget *dialog;
  GtkWidget *hbox;
  GtkWidget *stock;
  GtkWidget *table;
  GtkWidget *local_entry1;
  GtkWidget *label;
  gint response;

  dialog = gtk_dialog_new_with_buttons ("Nom de la Map",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					GTK_STOCK_CANCEL,
                                        GTK_RESPONSE_CANCEL,
					NULL);

  hbox = gtk_hbox_new (FALSE, 8);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 8);
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 0);

  stock = gtk_image_new_from_stock (GTK_STOCK_DIALOG_QUESTION, GTK_ICON_SIZE_DIALOG);
  gtk_box_pack_start (GTK_BOX (hbox), stock, FALSE, FALSE, 0);

  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacings (GTK_TABLE (table), 4);
  gtk_table_set_col_spacings (GTK_TABLE (table), 4);
  gtk_box_pack_start (GTK_BOX (hbox), table, TRUE, TRUE, 0);
  label = gtk_label_new_with_mnemonic ("_Nom de la Map :");
  gtk_table_attach_defaults (GTK_TABLE (table),
			     label,
			     0, 1, 0, 1);
  local_entry1 = gtk_entry_new ();
  //gtk_entry_set_text (GTK_ENTRY (local_entry1), "");
  gtk_table_attach_defaults (GTK_TABLE (table), local_entry1, 1, 2, 0, 1);
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), local_entry1);

  
  gtk_widget_show_all (hbox);
  response = gtk_dialog_run (GTK_DIALOG (dialog));

  if (response == GTK_RESPONSE_OK)
    {
      char cc[30];
      char ctest[50];
      strcpy(cc,gtk_entry_get_text (GTK_ENTRY (local_entry1)));
      strcpy(ctest,MAPDIR);
      strcat(ctest,cc);
      strcat(ctest,".mad");
      // test
      FILE*fTest=fopen(ctest,"r");
      int u=0;
      for(u=0 ; u<nbStrs ; u++)
	{
	  if(strcmp(cc,g_array_index (Strs, Str, u).nom)==0)
	    {
	      u=-1;
	      break;
	    }
	}
      if(fTest==NULL)
	{
	  AlertMsgWarning("Map inexistante dans le répertoire '/maps/' !");
	}
      else
	{
	  if(u==-1)
	    {
	      AlertMsgWarning("Cette Map est déjà présente dans la liste !");
	    }
	  else
	    {
	      fclose(fTest);
	      add_itemMA(button, cc, data);
	    }
	}
    }

  gtk_widget_destroy (dialog);
}

void remove_itemMA (GtkWidget *widget, gpointer data)
{
  GtkTreeIter iter;
  GtkTreeView *treeview = (GtkTreeView *)data;
  GtkTreeModel *model = gtk_tree_view_get_model (treeview);
  GtkTreeSelection *selection = gtk_tree_view_get_selection (treeview);

  if (gtk_tree_selection_get_selected (selection, NULL, &iter))
    {
      gint i;
      GtkTreePath *path;

      path = gtk_tree_model_get_path (model, &iter);
      i = gtk_tree_path_get_indices (path)[0];
      gtk_list_store_remove (GTK_LIST_STORE (model), &iter);

      g_array_remove_index (Strs, i);
      nbStrs--;

      gtk_tree_path_free (path);
    }
}

void OnRemoveMA(GtkWidget *button, gpointer data)
{
  remove_itemMA(button, data);
}

void OnHelpMA(GtkWidget *wWid, gpointer data)
 {
    GtkWidget *pQuestion;

    gchar *sUtf8 = g_locale_to_utf8("\n{MAP-ADD} // for SW3 Phoenixia\n\nCet utilitaire vous permet de gérer la liste des Maps dans SW3 Phoenixia.\nPour ajouter une Map, cliquez sur le bouton '+' et entrez le nom du fichier, sans l'extension ( exemple : 'psanct', le fichier doit se trouver dans le répertoire des Maps : '/maps/' ).\nPour supprimer une Map, sélectionnez celle de votre choix dans la liste et cliquez sur le bouton '-'.\n\nMAP-ADD v0.9\nby Studio AMANgA", -1, NULL, NULL, NULL);
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        sUtf8);
    g_free(sUtf8);

    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_OK:
            gtk_widget_destroy(pQuestion);
            break;
    }
}

void OnSaveMA(GtkWidget *button, gpointer data)
{
  FILE*fIn=fopen(CFGDIR,"w");
  if(fIn==NULL)
    {
      AlertMsgWarning("Erreur dans la sauvegarde des changements !");
      return;
    }
  int u=0;
  for(u=0 ; u<nbStrs ; u++)
    {
      fwrite(g_array_index (Strs, Str, u).nom,sizeof(char),30,fIn);
    }
  fclose(fIn);

  AlertMsgInfo("Sauvegarde des changements réussie");
}

void OnQuitMA(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget* pQuest=gtk_message_dialog_new(GTK_WINDOW(pWin), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous sauvegarder les changements ?");
  switch(gtk_dialog_run(GTK_DIALOG(pQuest)))
    {
    case GTK_RESPONSE_YES :
      OnSaveMA(NULL,NULL);
    case GTK_RESPONSE_NO :
      gtk_widget_destroy (pQuest);
    }
}

GtkTreeModel * StoreMA(void)
{
  GtkListStore * StoreModel = gtk_list_store_new(1,G_TYPE_STRING);
  GtkTreeIter Iter;

  Strs = g_array_sized_new (FALSE, FALSE, sizeof (Str), 1);

  //g_return_if_fail (Strs != NULL);

  FILE*fIn=fopen(CFGDIR,"r");
  Str S0;
  do
    {
      fread(S0.nom,sizeof(char),30,fIn);
      if(!feof(fIn))
      {
	g_array_append_vals (Strs, &S0, 1);
	nbStrs++;
      }
    }
  while (!feof(fIn));
  fclose(fIn);

  int i=0;
  for(i=0 ; i<nbStrs ; i++)
    {
      gtk_list_store_append(StoreModel, &Iter);
      gtk_list_store_set(StoreModel, &Iter, NAME, g_array_index (Strs, Str, i).nom, -1);
    }

  return GTK_TREE_MODEL(StoreModel);
}

GtkWidget *  DrawTreeMA(GtkTreeModel * Modelma)
{
  GtkWidget * TreeView=gtk_tree_view_new_with_model(Modelma);

  GtkCellRenderer * Render=gtk_cell_renderer_text_new();
  //g_object_set(G_OBJECT(Render), );
  GtkTreeViewColumn * Col=gtk_tree_view_column_new_with_attributes("Nom de la Map", Render, "text", NAME, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(TreeView), Col);

  return TreeView;
}


void OnMapAdd(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * vbox=gtk_vbox_new(FALSE, 10);

  // Liste
  GtkWidget * frame = gtk_frame_new ("Liste des Maps");
  
  GtkWidget * sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (frame), sw);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
				       GTK_SHADOW_ETCHED_IN);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
				  GTK_POLICY_AUTOMATIC,
				  GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 10);
  GtkTreeModel * ModelMA=StoreMA();
  GtkWidget * TreeViewMA=DrawTreeMA(ModelMA);
  gtk_container_add (GTK_CONTAINER (sw), TreeViewMA);

  // Boutons
  frame = gtk_frame_new ("Actions");
  GtkWidget * vbbox = gtk_vbox_new(FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 20);
  gtk_container_add (GTK_CONTAINER (frame), vbbox);

  GtkWidget * bbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), GTK_BUTTONBOX_SPREAD);
  gtk_box_set_spacing (GTK_BOX (bbox), 30);
  gtk_box_pack_start(GTK_BOX(vbbox), bbox, FALSE, FALSE, 0);

  GtkWidget * button = gtk_button_new_from_stock (GTK_STOCK_ADD);
  gtk_container_add (GTK_CONTAINER (bbox), button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnAddMA), ModelMA);

  button = gtk_button_new_from_stock (GTK_STOCK_REMOVE);
  gtk_container_add (GTK_CONTAINER (bbox), button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnRemoveMA), TreeViewMA);

  bbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), GTK_BUTTONBOX_SPREAD);
  gtk_box_set_spacing (GTK_BOX (bbox), 30);
  gtk_box_pack_start(GTK_BOX(vbbox), bbox, FALSE, FALSE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_SAVE);
  gtk_container_add (GTK_CONTAINER (bbox), button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnSaveMA), NULL);

  button = gtk_button_new_from_stock (GTK_STOCK_HELP);
  gtk_container_add (GTK_CONTAINER (bbox), button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnHelpMA), pWin);


  GtkWidget *dialog;
  //GtkWidget *stock;
  //GtkWidget *table;
  //GtkWidget *local_entry1;
  //GtkWidget *label;
  gint response;

  dialog = gtk_dialog_new_with_buttons ("Map-Add",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), vbox, FALSE, FALSE, 0);

  

  
  gtk_widget_show_all (vbox);
  response = gtk_dialog_run (GTK_DIALOG (dialog));

  OnQuitMA(NULL,NULL);

  gtk_widget_destroy (dialog);

  return;
}
