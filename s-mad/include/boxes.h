

GtkWidget * AffMenuIco(void);

GtkWidget * AffTreeObjs(void)
{
  GtkWidget * frame = gtk_frame_new (NULL);
  GtkWidget * sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (frame), sw);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
				       GTK_SHADOW_ETCHED_IN);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
				  GTK_POLICY_AUTOMATIC,
				  GTK_POLICY_AUTOMATIC);
  Model=Store();
  TreeView=DrawTree(Model);
  gtk_container_add (GTK_CONTAINER (sw), TreeView);

  gtk_frame_set_shadow_type (GTK_FRAME(frame), GTK_SHADOW_IN);
  gtk_widget_set_size_request (frame, 400, 60);
  
  return frame;
}

GtkWidget * AffBoxes(void)
{
  GtkWidget *logo;
  GtkWidget *VBox=gtk_vbox_new(FALSE, 0);

  // Barre de menu
  gtk_box_pack_start(GTK_BOX(VBox), AffMenu(), FALSE, FALSE, 0);

  // Menu
  gtk_box_pack_start(GTK_BOX(VBox), AffMenuIco(), FALSE, FALSE, 0);

  // Espace de travail
  GtkWidget * hpaned = gtk_hpaned_new ();
  gtk_box_pack_start (GTK_BOX (VBox), hpaned, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER(hpaned), 5);


  gtk_paned_add1 (GTK_PANED (hpaned), AffTreeObjs());


  FrameD=gtk_frame_new(NULL);
  gtk_frame_set_shadow_type (GTK_FRAME(FrameD), GTK_SHADOW_IN);
  gtk_widget_set_size_request (FrameD, 400, 200);
  gtk_paned_add2 (GTK_PANED (hpaned), FrameD);
  GtkWidget * vbox=gtk_vbox_new(FALSE,0);
  VBoxD=vbox;
  logo=gtk_image_new_from_file("data/logo.gif");
  gtk_box_pack_start(GTK_BOX(vbox), logo, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (FrameD), vbox);

  // Barre d'état
  gtk_box_pack_start(GTK_BOX(VBox), gtk_statusbar_new(), FALSE, FALSE, 0);

  return VBox;
}

void AlertMsgWarning(char*msg)
 {
    GtkWidget *pQuestion;

    gchar *sUtf8 = g_locale_to_utf8(msg, -1, NULL, NULL, NULL);
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(pWin),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_WARNING,
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

void AlertMsgInfo(char*msg)
 {
    GtkWidget *pQuestion;

    gchar *sUtf8 = g_locale_to_utf8(msg, -1, NULL, NULL, NULL);
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(pWin),
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

GtkWidget * AffMenuIco(void)
{
  GtkWidget * Toolbar;
  GtkToolItem * Item;

  Toolbar= gtk_toolbar_new();

  Item= gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Nouveau");
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
  g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnNew), NULL);

  Item= gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
  gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Ouvrir");
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
  g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnOpen_create_file_selection), NULL);

  Item= gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Sauver");
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
  g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnSave), NULL);

  Item = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);

  Item= gtk_tool_button_new_from_stock(GTK_STOCK_PROPERTIES);
  gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Modifier\nle Tag");
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
  g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(Aff_Tag_Mod), NULL);


  Item = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);

  Item= gtk_tool_button_new_from_stock(GTK_STOCK_ADD);
  gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Ajouter\nun Objet");
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
  g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnAddObj), NULL);

  Item= gtk_tool_button_new_from_stock(GTK_STOCK_ADD);
  gtk_tool_button_set_label(GTK_TOOL_BUTTON(Item),"Ajouter un\nGrounder");
  gtk_toolbar_insert(GTK_TOOLBAR(Toolbar),GTK_TOOL_ITEM(Item),-1);
  g_signal_connect(G_OBJECT(Item), "clicked", G_CALLBACK(OnAddGrounder), NULL);

  

  return Toolbar;
}
