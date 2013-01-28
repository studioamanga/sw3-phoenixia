


GtkWidget * AffMenu(void)
{
  GtkWidget * MenuBar;
  GtkWidget * EditMenuItem;
  GtkWidget * EditMenu;
  GtkWidget * MenuItem;
  GtkWidget * Label;
  GtkWidget * pImage;
  //gchar *sUtf8;


  MenuBar=gtk_menu_bar_new();
  
  // Menu 'Fichier'
  EditMenuItem=gtk_menu_item_new_with_mnemonic("_Fichier");
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), EditMenuItem);

  EditMenu=gtk_menu_new();
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(EditMenuItem), EditMenu);

  
  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Nouveau");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_NEW, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnNew), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ouvrir");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_OPEN, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnOpen_create_file_selection), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Enregistrer");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_SAVE, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnSave), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Enregistrer sous...");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_SAVE_AS, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnSaveAs), NULL);

  MenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Map-Add");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_EXECUTE, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnMapAdd), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Wing-Add");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_EXECUTE, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnWingAdd), NULL);

  MenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  /*
  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Fermer");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnClose), NULL);
  */
  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Quitter");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnQuit), NULL);





  // Menu 'Tag'
  EditMenuItem=gtk_menu_item_new_with_mnemonic("_Tag");
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), EditMenuItem);

  EditMenu=gtk_menu_new();
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(EditMenuItem), EditMenu);

  
  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Info sur le Tag");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_DIALOG_INFO, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(Aff_Tag_Info), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Modifier le Tag");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_PROPERTIES, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(Aff_Tag_Mod), NULL);

  MenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Tag Map");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(New_Tag_Map), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Tag Wing");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(New_Tag_Wing), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Tag Drone");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(New_Tag_Drone), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Tag Shoker");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(New_Tag_Shoker), NULL);

  MenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Supprimer le Tag");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_REMOVE, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(Remove_Tag), NULL);


  // Menu 'Objets'
  EditMenuItem=gtk_menu_item_new_with_mnemonic("_Objets");
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), EditMenuItem);

  EditMenu=gtk_menu_new();
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(EditMenuItem), EditMenu);


  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Objet");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnAddObj), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter une SkySphere");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnAddSkySphere), NULL);

  MenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Grounder");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnAddGrounder), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Builder");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnAddBuilder), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un Champs");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnChamps), NULL);

  MenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un ShapeSphere");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnShapeSphere), NULL);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("Ajouter un ShapeDisc");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnShapeDisc), NULL);
  

  // Menu 'Aide'
  EditMenuItem=gtk_menu_item_new_with_label("Aide");
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), EditMenuItem);
  
  EditMenu=gtk_menu_new();
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(EditMenuItem), EditMenu);

  MenuItem = gtk_image_menu_item_new();
  Label = gtk_label_new("A propos");
  gtk_container_add(GTK_CONTAINER(MenuItem), Label);
  pImage = gtk_image_new_from_stock(GTK_STOCK_HELP, GTK_ICON_SIZE_MENU);
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItem), pImage);
  gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), MenuItem);
  g_signal_connect(G_OBJECT(MenuItem), "activate", G_CALLBACK(OnAide), NULL);


  return MenuBar;
}
