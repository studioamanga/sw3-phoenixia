
int getIdSurfType(int i);

void UpdateFrameD(GtkWidget *pWidget, gpointer pData)
{
  //int i=0;
  int o=0;
  GtkWidget * frame;
  GtkWidget * hbox;
  GtkTreeIter iter;
  GtkTreeView *treeview;
  GtkTreeModel *model;
  GtkTreeSelection *selection;
  static GtkTreePath *path;
  GtkWidget * Toolbar;
  GtkToolItem * Item;

  if(M==NULL)
    return;

  // SAVE
  if(entryD[0]!=NULL && oD!=-1)
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

      treeview = (GtkTreeView *)pData;
      model = gtk_tree_view_get_model (treeview);
      selection = gtk_tree_view_get_selection (treeview);
      //path = gtk_tree_path_new_from_indices (oD);
      gtk_tree_model_get_iter (model, &iter, path);
      gtk_list_store_set (GTK_LIST_STORE (model), &iter, TEXTURE, M->Objets[oD].texture, -1);
      char typeNom[21];
      switch(M->Objets[oD].typeSurf)
	{
	case 'M' :
	  strcpy(typeNom,"SkySphere");
	  break;
	default :
	  strcpy(typeNom,"Quad");
	}
      gtk_list_store_set (GTK_LIST_STORE (model), &iter, NOM, typeNom, -1);
      gtk_tree_path_free (path);
    }

  treeview = (GtkTreeView *)pData;
  model = gtk_tree_view_get_model (treeview);
  selection = gtk_tree_view_get_selection (treeview);

  if (gtk_tree_selection_get_selected (selection, NULL, &iter))
    {
      path = gtk_tree_model_get_path (model, &iter);

      gtk_tree_model_get_iter (model, &iter, path);
      gtk_tree_model_get (model, &iter, ID, &o, -1);
      
      //gtk_tree_path_free (path);
    }
  // GET ID OBJET

  
  gtk_widget_destroy(VBoxD);
  VBoxD=gtk_vbox_new(FALSE,0);
  gtk_container_add (GTK_CONTAINER (FrameD), VBoxD);

  if(M!=NULL)
    {
      GtkWidget * texture;
      char urlText[80];

      Toolbar= gtk_toolbar_new();


      Item= gtk_tool_button_new_from_stock(GTK_STOCK_JUMP_TO);
      gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Deplacer\ncet Objet");
      gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
      g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnMoveObj), NULL);

      Item= gtk_tool_button_new_from_stock(GTK_STOCK_REFRESH);
      gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Flipper\ncet Objet");
      gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
      g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnFlipObj), NULL);

      Item= gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
      gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Egaliser\nla texture");
      gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
      g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnEquaTex), NULL);

      Item= gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
      gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Supprimer\ncet Objet");
      gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
      g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnRemObj), NULL);


      gtk_box_pack_start(GTK_BOX(VBoxD), Toolbar, FALSE, FALSE, 5);

      hbox=gtk_hbox_new(FALSE, 5);
      frame=gtk_frame_new("Type de Surface");
      gtk_container_add (GTK_CONTAINER (frame), hbox);
      gtk_box_pack_start(GTK_BOX(VBoxD), frame, FALSE, FALSE, 5);
      entryD[0]=gtk_combo_box_new_text ();
      gtk_combo_box_append_text (GTK_COMBO_BOX (entryD[0]), "Triangles");
      gtk_combo_box_append_text (GTK_COMBO_BOX (entryD[0]), "Triangle Strip");
      gtk_combo_box_append_text (GTK_COMBO_BOX (entryD[0]), "Triangle Fan");
      gtk_combo_box_append_text (GTK_COMBO_BOX (entryD[0]), "Quads");
      gtk_combo_box_append_text (GTK_COMBO_BOX (entryD[0]), "SkyBox");
      gtk_combo_box_set_active (GTK_COMBO_BOX (entryD[0]), getIdSurfType(o));
      gtk_box_pack_start(GTK_BOX(hbox), entryD[0], FALSE, FALSE, 5);
      

      hbox=gtk_vbox_new(FALSE, 5);
      frame=gtk_frame_new("Texture");
      gtk_container_add (GTK_CONTAINER (frame), hbox);
      gtk_box_pack_start(GTK_BOX(VBoxD), frame, FALSE, FALSE, 5);
      entryD[1]=EntryFromStr(M->Objets[o].texture);
      gtk_box_pack_start(GTK_BOX(hbox), entryD[1], FALSE, FALSE, 5);

      strcpy(urlText,SW3DIR);
      strcat(urlText,M->Objets[o].texture);
      texture=gtk_image_new_from_file(urlText);
      gtk_box_pack_start(GTK_BOX(hbox), texture, FALSE, FALSE, 5);

      oD=o;
    }

  gtk_widget_show_all(FrameD);

  update_list();


  return;
}


int getIdSurfType(int i)
{
  switch(M->Objets[i].typeSurf)
    {
    case 'Q' :
      return 3;
    case 'L' :
      return 0;
    case 'T' :
      return 1;
    case 'F' :
      return 2;
    case 'M' :
      return 4;
    }
  return 0;
}

