
void OnRemObj(GtkWidget *pWidget, gpointer pData)
{
  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }

  if(M->nbObjets<=0 || oD==-1)
    {
      AlertMsgWarning("Impossible !");
      return;
    }

  int i;
  Vertex * Vert=M->Objets[oD].Vertices;
  for( i=oD ; i < (M->nbObjets-1) ; i++ )
    {
      M->Objets[i]=M->Objets[i+1];
    }
  M->nbObjets--;
  free(Vert);
  M->Objets = (sObjet *) realloc(M->Objets, sizeof(sObjet)*M->nbObjets);

  oD=-1;
  update_list();
}

void OnAddGrounder(GtkWidget *pWidget, gpointer pData)
{
  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }

  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * hbox;
  GtkWidget * hhbox;
  GtkWidget * label;
  GtkWidget * Xscale;
  GtkWidget * Zscale;
  GtkWidget * Yscale;
  GtkWidget * entry[6]; // oX oZ dX dZ mY border
  guint response;
  int nbTX=5, nbTZ=5, TY=10, oX=-100, oZ=-100, dX=100, dZ=100, border=100, mY=0;

  hbox=gtk_hbox_new(FALSE,0);

  vbox=gtk_vbox_new(FALSE,0);

  label=gtk_label_new("Choisissez les options du Grounder :\n");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  label=gtk_label_new("Nombre de tiles X et Z :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  Xscale=gtk_hscale_new_with_range(2,20,1);
  gtk_box_pack_start (GTK_BOX (vbox), Xscale, FALSE, FALSE, 0);
  Zscale=gtk_hscale_new_with_range(2,20,1);
  gtk_box_pack_start (GTK_BOX (vbox), Zscale, FALSE, FALSE, 0);
  label=gtk_label_new("Hauteur Y d'un tile :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  Yscale=gtk_hscale_new_with_range(1,100,1);
  gtk_box_pack_start (GTK_BOX (vbox), Yscale, FALSE, FALSE, 0);

  gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);


  vbox=gtk_vbox_new(FALSE,0);


  label=gtk_label_new("Coordonnees X et Z de l'origine :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,0);
  entry[0]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[0], FALSE, FALSE, 0);
  entry[1]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[1], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hhbox, FALSE, FALSE, 0);

  label=gtk_label_new("Coordonnees X et Z de la destination :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,0);
  entry[2]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[2], FALSE, FALSE, 0);
  entry[3]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[3], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hhbox, FALSE, FALSE, 0);

  label=gtk_label_new("Hauteur Y moyenne :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[4]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (vbox), entry[4], FALSE, FALSE, 0);

  label=gtk_label_new("Dimension du bord :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[5]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (vbox), entry[5], FALSE, FALSE, 0);
  

  gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
      
  dialog = gtk_dialog_new_with_buttons ("Options Grounder",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);
      
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (hbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));


  if(response==GTK_RESPONSE_OK)
    {
      GtkWidget * table;
      GtkWidget * button[20][20];
      int i,y;
      nbTX=gtk_range_get_value(GTK_RANGE(Xscale));
      nbTZ=gtk_range_get_value(GTK_RANGE(Zscale));
      TY=gtk_range_get_value(GTK_RANGE(Yscale));
      oX=atoi(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      oZ=atoi(gtk_entry_get_text (GTK_ENTRY (entry[1])));
      dX=atoi(gtk_entry_get_text (GTK_ENTRY (entry[2])));
      dZ=atoi(gtk_entry_get_text (GTK_ENTRY (entry[3])));
      mY=atoi(gtk_entry_get_text (GTK_ENTRY (entry[4])));
      border=atoi(gtk_entry_get_text (GTK_ENTRY (entry[5])));


      gtk_widget_destroy (dialog);


      table = gtk_table_new (nbTX, nbTZ, FALSE);

      for(i=0 ; i<nbTZ ; i++)
	{
	  for(y=0 ; y<nbTX ; y++)
	    {
	      button[y][i]=gtk_button_new_with_label("0");
	      gtk_table_attach_defaults (GTK_TABLE (table),
					 button[y][i],
					 y, y+1, i, i+1);
	      g_signal_connect(G_OBJECT(button[y][i]), "clicked", G_CALLBACK(OnModY), button[y][i]);
	    }
	}

      dialog = gtk_dialog_new_with_buttons ("Nouveau Grounder",
					    GTK_WINDOW (pWin),
					    GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					    GTK_STOCK_CANCEL,
					    GTK_RESPONSE_CANCEL,
					    GTK_STOCK_OK,
					    GTK_RESPONSE_OK,
					    NULL);
      
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), table, FALSE, FALSE, 0);

      gtk_widget_show_all (table);
      
      response = gtk_dialog_run (GTK_DIALOG (dialog));

      if(response==GTK_RESPONSE_OK)
	{
	  Vertex V[22][22];
	  int ix=0,iz=0;

	  for(ix=0 , iz=0 ; ; ix++)
	    {
	      if( ix > (nbTX+1) )
		{
		  ix=0;
		  iz++;
		  if( iz > (nbTZ+1) )
		    break;
		}
	      
	      // X
	      if(ix==0)
		V[ix][iz].x=(oX-border);
	      else
		if(ix==(nbTX+1))
		  V[ix][iz].x=(dX+border);
		else
		  V[ix][iz].x=(oX+((ix-1)*((dX-oX)/(nbTX-1))));

	      // Z
	      if(iz==0)
		V[ix][iz].z=(oZ-border);
	      else
		if(iz==(nbTZ+1))
		  V[ix][iz].z=(dZ+border);
		else
		  V[ix][iz].z=(oZ+((iz-1)*((dZ-oZ)/(nbTZ-1))));
	      
	      // Y
	      int wx, wz;
	      wx=(ix-1);
	      wz=(iz-1);
	      if(wx<0)
		wx=0;
	      if(wz<0)
		wz=0;
	      if(wx>=nbTX)
		wx=(nbTX-1);
	      if(wz>=nbTZ)
		wz=(nbTZ-1);
	      V[ix][iz].y=mY+(atoi(gtk_button_get_label(GTK_BUTTON(button[wx][wz]))))*TY;
	    }

	  M->nbObjets++;
	  M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
	  strcpy(M->Objets[M->nbObjets-1].texture, "data/texture/*.tga");
	  M->Objets[M->nbObjets-1].typeSurf='Q';
	  M->Objets[M->nbObjets-1].nbVertices=((nbTX+1)*(nbTZ+1)*4);
	  M->Objets[M->nbObjets-1].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[M->nbObjets-1].nbVertices);
	  for(ix=0 , iz=0, i=0 ; ; ix++)
	    {
	      if( ix > (nbTX) )
		{
		  ix=0;
		  iz++;
		  if( iz > (nbTZ) )
		    break;
		}
	      M->Objets[M->nbObjets-1].Vertices[i].x=V[ix][iz].x;
	      M->Objets[M->nbObjets-1].Vertices[i].y=V[ix][iz].y;
	      M->Objets[M->nbObjets-1].Vertices[i].z=V[ix][iz].z;
	      M->Objets[M->nbObjets-1].Vertices[i].tx=V[ix][iz].tx;
	      M->Objets[M->nbObjets-1].Vertices[i].ty=V[ix][iz].ty;
	      i++;
	      M->Objets[M->nbObjets-1].Vertices[i].x=V[ix+1][iz].x;
	      M->Objets[M->nbObjets-1].Vertices[i].y=V[ix+1][iz].y;
	      M->Objets[M->nbObjets-1].Vertices[i].z=V[ix+1][iz].z;
	      M->Objets[M->nbObjets-1].Vertices[i].tx=V[ix+1][iz].tx;
	      M->Objets[M->nbObjets-1].Vertices[i].ty=V[ix+1][iz].ty;
	      i++;
	      M->Objets[M->nbObjets-1].Vertices[i].x=V[ix+1][iz+1].x;
	      M->Objets[M->nbObjets-1].Vertices[i].y=V[ix+1][iz+1].y;
	      M->Objets[M->nbObjets-1].Vertices[i].z=V[ix+1][iz+1].z;
	      M->Objets[M->nbObjets-1].Vertices[i].tx=V[ix+1][iz+1].tx;
	      M->Objets[M->nbObjets-1].Vertices[i].ty=V[ix+1][iz+1].ty;
	      i++;
	      M->Objets[M->nbObjets-1].Vertices[i].x=V[ix][iz+1].x;
	      M->Objets[M->nbObjets-1].Vertices[i].y=V[ix][iz+1].y;
	      M->Objets[M->nbObjets-1].Vertices[i].z=V[ix][iz+1].z;
	      M->Objets[M->nbObjets-1].Vertices[i].tx=V[ix][iz+1].tx;
	      M->Objets[M->nbObjets-1].Vertices[i].ty=V[ix][iz+1].ty;
	      i++;
	    }
	}
    }
  
  gtk_widget_destroy (dialog);

  update_list();

  return;
}

void OnAddSkySphere(GtkWidget *pWidget, gpointer pData)
{
  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }
  if(M->typeAnim!='M')
    {
      AlertMsgWarning("Ce fichier n'est pas un fichier MAP !");
    }

  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * vvbox;
  GtkWidget * label;
  GtkWidget * scaleR;
  GtkWidget * scaleResol;
  GtkWidget * scaleText;
  GtkWidget * texture;
  GtkWidget * nbStars;
  GtkWidget * frame;
  guint response;
  vbox=gtk_vbox_new(FALSE,10);
  vvbox=gtk_vbox_new(FALSE,5);

  frame=gtk_frame_new("Parametres de la SkySphere");
  gtk_container_add (GTK_CONTAINER (frame), vvbox);
  label=gtk_label_new("Rayon de la SkyBox :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  scaleR=gtk_hscale_new_with_range(500,10000,10);
  gtk_box_pack_start (GTK_BOX (vvbox), scaleR, FALSE, FALSE, 5);
  label=gtk_label_new("Resolution de la SkyBox ( niveau de details ) :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  scaleResol=gtk_hscale_new_with_range(10,100,1);
  gtk_box_pack_start (GTK_BOX (vvbox), scaleResol, FALSE, FALSE, 5);

  label=gtk_label_new("\nTexture de la SkyBox :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  texture=EntryFromStr("Url de la texture");
  gtk_box_pack_start (GTK_BOX (vvbox), texture, FALSE, FALSE, 5);
  label=gtk_label_new("Taille de la Texture :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  scaleText=gtk_hscale_new_with_range(0,100,1);
  gtk_box_pack_start (GTK_BOX (vvbox), scaleText, FALSE, FALSE, 5);


  label=gtk_label_new("Nombe d'etoiles :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 5);
  if(M->nbObjets>0 && M->Objets[0].typeSurf=='M')
    nbStars=EntryFromInt(M->Objets[0].Vertices[0].tx);
  else
    nbStars=EntryFromInt(0);

  gtk_box_pack_start (GTK_BOX (vvbox), nbStars, FALSE, FALSE, 5);

  if(M->nbObjets>0)
    if(M->Objets[0].typeSurf=='M')
      {
	gtk_range_set_value(GTK_RANGE(scaleR),M->Objets[0].Vertices[0].x);
	gtk_range_set_value(GTK_RANGE(scaleResol),M->Objets[0].Vertices[0].y);
	gtk_range_set_value(GTK_RANGE(scaleText),M->Objets[0].Vertices[0].z);
	gtk_entry_set_text (GTK_ENTRY (texture), M->Objets[0].texture); 
      }

  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 10);

      
  dialog = gtk_dialog_new_with_buttons ("Ajouter/Modifier une SkySphere",
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
      if(M->nbObjets==0)
	{
	  M->nbObjets++;
	  M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
	  strcpy(M->Objets[0].texture, gtk_entry_get_text (GTK_ENTRY (texture))); 
	  M->Objets[0].typeSurf='M';
	  M->Objets[0].nbVertices=1;
	  M->Objets[0].Vertices=(Vertex *)malloc(sizeof(Vertex));
	  M->Objets[0].Vertices[0].x=gtk_range_get_value(GTK_RANGE(scaleR));
	  M->Objets[0].Vertices[0].y=gtk_range_get_value(GTK_RANGE(scaleResol));
	  M->Objets[0].Vertices[0].z=gtk_range_get_value(GTK_RANGE(scaleText));
	  M->Objets[0].Vertices[0].tx=atoi(gtk_entry_get_text (GTK_ENTRY (nbStars)));
	  M->Objets[0].Vertices[0].ty=0;
	}
      else
	{
	  if(M->Objets[0].typeSurf=='M')
	    {
	      M->Objets[0].Vertices[0].x=gtk_range_get_value(GTK_RANGE(scaleR));
	      M->Objets[0].Vertices[0].y=gtk_range_get_value(GTK_RANGE(scaleResol));
	      M->Objets[0].Vertices[0].z=gtk_range_get_value(GTK_RANGE(scaleText));
	      M->Objets[0].Vertices[0].tx=atoi(gtk_entry_get_text (GTK_ENTRY (nbStars)));
	      strcpy(M->Objets[0].texture, gtk_entry_get_text (GTK_ENTRY (texture))); 
	    }
	  else
	    {
	      int i;
	      M->nbObjets++;
	      M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
	      for(i=(M->nbObjets-1) ; i>0 ; i--)
		{
		  M->Objets[i]=M->Objets[i-1];
		}
	      strcpy(M->Objets[0].texture, gtk_entry_get_text (GTK_ENTRY (texture))); 
	      M->Objets[0].typeSurf='M';
	      M->Objets[0].nbVertices=1;
	      M->Objets[0].Vertices=(Vertex *)malloc(sizeof(Vertex));
	      M->Objets[0].Vertices[0].x=gtk_range_get_value(GTK_RANGE(scaleR));
	      M->Objets[0].Vertices[0].y=gtk_range_get_value(GTK_RANGE(scaleResol));
	      M->Objets[0].Vertices[0].z=gtk_range_get_value(GTK_RANGE(scaleText));
	      M->Objets[0].Vertices[0].tx=atoi(gtk_entry_get_text (GTK_ENTRY (nbStars)));
	      M->Objets[0].Vertices[0].ty=0;
	    }
	}

      update_list();
    }
  
  gtk_widget_destroy (dialog);

  update_list();

  return;
}

void store_filenameAO (GtkWidget *widget, gpointer user_data) 
{
  GtkWidget *file_selector = GTK_WIDGET (user_data);
  const gchar *selected_filename;
  int i, nbObj;
  FILE* file;
  unsigned char id;

  selected_filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));

  file=fopen(selected_filename,"r");
  if(file==NULL)
    {
      AlertMsgWarning("Erreur lors de\nl'ouverture du fichier !");
      return;
    }
  fread(&id, sizeof(unsigned char), 1, file);
  if(id!=136)
    {
      AlertMsgWarning("Ce fichier n'est pas\nau format *.mad !");
      return;
    }

  fread(&nbObj, sizeof(int), 1, file);
  fread(&id, sizeof(char), 1, file);
  fread(&nbObj, sizeof(int), 1, file);

  M->nbObjets+=nbObj;
  M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
  for(i=(M->nbObjets - nbObj ) ; i<M->nbObjets ; i++)
    {
      int y=0;
      fread(&(M->Objets[i].texture), sizeof(char), 50, file);
      fread(&(M->Objets[i].typeSurf), sizeof(char), 1, file);
      fread(&(M->Objets[i].nbVertices), sizeof(int), 1, file);

      M->Objets[i].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[i].nbVertices);
      for(y=0 ; y<M->Objets[i].nbVertices ; y++)
	{
	  fread(&(M->Objets[i].Vertices[y].x), sizeof(float), 1, file);
	  fread(&(M->Objets[i].Vertices[y].y), sizeof(float), 1, file);
	  fread(&(M->Objets[i].Vertices[y].z), sizeof(float), 1, file);
	  fread(&(M->Objets[i].Vertices[y].tx), sizeof(float), 1, file);
	  fread(&(M->Objets[i].Vertices[y].ty), sizeof(float), 1, file);
	}
    }
  
  fclose(file);

  
  update_list();
}


void OnAddObj(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget *file_selector;

  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }

  /* Create the selector */
   
  file_selector = gtk_file_selection_new ("Choisissez un objet mad a inclure :");
   
  g_signal_connect (GTK_FILE_SELECTION (file_selector)->ok_button,
		    "clicked",
		    G_CALLBACK (store_filenameAO),
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

void OnShapeSphere(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * entry[2];
  GtkWidget * scaleResol;
  guint response;

  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }
 
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Entrez le rayon de la sphere :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[0]=EntryFromInt(100);
  gtk_box_pack_start (GTK_BOX (vbox), entry[0], FALSE, FALSE, 0);

  label=gtk_label_new("Entrez le facteur de la texture :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[1]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (vbox), entry[1], FALSE, FALSE, 0);

  label=gtk_label_new("Resolution ( niveau de details ) :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 5);
  scaleResol=gtk_hscale_new_with_range(10,100,1);
  gtk_box_pack_start (GTK_BOX (vbox), scaleResol, FALSE, FALSE, 5);

      
  dialog = gtk_dialog_new_with_buttons ("Shaper de Sphere",
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
      int resol=gtk_range_get_value(GTK_RANGE(scaleResol));
      float Rext=atof(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      float Rint=atof(gtk_entry_get_text (GTK_ENTRY (entry[1])));

      M->nbObjets++;
      M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
      int i=M->nbObjets-1;
      
      strcpy(M->Objets[i].texture, "data/texture/");
      M->Objets[i].typeSurf='Q';
      M->Objets[i].nbVertices=0;

      int re;
      float angy=-(PI/2);
      for(re=0 ; re<=(resol/2) ; re++)
	{
	  float angx=0;
	  int Re;
	  for(Re=0 ; Re<resol ; Re++)
	    {
	      angx+=((2*PI)/resol);
	      M->Objets[i].nbVertices+=4;
	    }
	  angy+=((2*PI)/resol);
	}

      M->Objets[i].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[i].nbVertices);
      int y=0;
      angy=-(PI/2);
      for(re=0 ; re<=(resol/2) ; re++)
	{
	  float angx=0;
	  int Re;
	  for(Re=0 ; Re<resol ; Re++)
	    {
	      if(angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		M->Objets[i].Vertices[y].tx = 0.5*Rint;
	      else
		M->Objets[i].Vertices[y].tx = angx/(2*PI)*Rint;
	      M->Objets[i].Vertices[y].ty = (angy+(PI/2))/(PI)*Rint;
	      M->Objets[i].Vertices[y].x = cos(angx)*Rext*cos(angy);
	      if(angy>=(PI/2)-0.01 )
		M->Objets[i].Vertices[y].y = sin(angy)*Rext+0.5;
	      else
		M->Objets[i].Vertices[y].y = sin(angy)*Rext;
	      M->Objets[i].Vertices[y].z = sin(angx)*Rext*cos(angy);
	      y++;
	      angx+=((2*PI)/resol);

	      if(angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		M->Objets[i].Vertices[y].tx = 0.5*Rint;
	      else
		M->Objets[i].Vertices[y].tx = angx/(2*PI)*Rint;
	      M->Objets[i].Vertices[y].ty = (angy+(PI/2))/(PI)*Rint;
	      M->Objets[i].Vertices[y].x = cos(angx)*Rext*cos(angy);
	      M->Objets[i].Vertices[y].y = sin(angy)*Rext;
	      M->Objets[i].Vertices[y].z = sin(angx)*Rext*cos(angy);
	      y++;
	      angy+=((2*PI)/resol);

	      if(angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		M->Objets[i].Vertices[y].tx = 0.5*Rint;
	      else
		M->Objets[i].Vertices[y].tx = angx/(2*PI)*Rint;
	      M->Objets[i].Vertices[y].ty = (angy+(PI/2))/(PI)*Rint;
	      M->Objets[i].Vertices[y].x = cos(angx)*Rext*cos(angy);
	      M->Objets[i].Vertices[y].y = sin(angy)*Rext;
	      M->Objets[i].Vertices[y].z = sin(angx)*Rext*cos(angy);
	      y++;
	      angx-=((2*PI)/resol);

	      if(angy<=(-PI/2) || angy>=(PI/2)-0.01 )
		M->Objets[i].Vertices[y].tx = 0.5*Rint;
	      else
		M->Objets[i].Vertices[y].tx = angx/(2*PI)*Rint;
	      M->Objets[i].Vertices[y].ty = (angy+(PI/2))/(PI)*Rint;
	      M->Objets[i].Vertices[y].x = cos(angx)*Rext*cos(angy);
	      if(angy>=(PI/2)-0.01 )
		M->Objets[i].Vertices[y].y = sin(angy)*Rext-0.5;
	      else
		M->Objets[i].Vertices[y].y = sin(angy)*Rext;
	      M->Objets[i].Vertices[y].z = sin(angx)*Rext*cos(angy);
	      y++;
	      angx+=((2*PI)/resol);
	      angy-=((2*PI)/resol);
	    }
	  angy+=((2*PI)/resol);
	}
    }

  update_list();
  gtk_widget_destroy (dialog);

}


void OnShapeDisc(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * label;
  GtkWidget * entry[2];
  GtkWidget * scaleResol;
  guint response;

  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }
 
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Entrez le rayon externe du Disc :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[0]=EntryFromInt(100);
  gtk_box_pack_start (GTK_BOX (vbox), entry[0], FALSE, FALSE, 0);

  label=gtk_label_new("Entrez le rayon interne du Disc :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[1]=EntryFromInt(50);
  gtk_box_pack_start (GTK_BOX (vbox), entry[1], FALSE, FALSE, 0);

  label=gtk_label_new("Resolution ( niveau de details ) :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 5);
  scaleResol=gtk_hscale_new_with_range(10,100,1);
  gtk_box_pack_start (GTK_BOX (vbox), scaleResol, FALSE, FALSE, 5);

      
  dialog = gtk_dialog_new_with_buttons ("Shaper de Disc",
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
      int resol=gtk_range_get_value(GTK_RANGE(scaleResol));
      float Rext=atof(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      float Rint=atof(gtk_entry_get_text (GTK_ENTRY (entry[1])));

      M->nbObjets++;
      M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
      int i=M->nbObjets-1;
      
      strcpy(M->Objets[i].texture, "data/texture/");
      M->Objets[i].typeSurf='Q';
      M->Objets[i].nbVertices=resol*4;

      M->Objets[i].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[i].nbVertices);

      float ang=0;
      int y=0, re=0;
      for( ; re<resol ; re++)
	{
	  M->Objets[i].Vertices[y].x=cos(ang)*Rext;
	  M->Objets[i].Vertices[y].y=0;
	  M->Objets[i].Vertices[y].z=sin(ang)*Rext;
	  M->Objets[i].Vertices[y].tx=1;
	  M->Objets[i].Vertices[y].ty=0;
	  y++;
	  M->Objets[i].Vertices[y].x=cos(ang)*Rint;
	  M->Objets[i].Vertices[y].y=0;
	  M->Objets[i].Vertices[y].z=sin(ang)*Rint;
	  M->Objets[i].Vertices[y].tx=1;
	  M->Objets[i].Vertices[y].ty=1;
	  y++;
	  ang+=((2*PI)/resol);
	  M->Objets[i].Vertices[y].x=cos(ang)*Rint;
	  M->Objets[i].Vertices[y].y=0;
	  M->Objets[i].Vertices[y].z=sin(ang)*Rint;
	  M->Objets[i].Vertices[y].tx=0;
	  M->Objets[i].Vertices[y].ty=1;
	  y++;
	  M->Objets[i].Vertices[y].x=cos(ang)*Rext;
	  M->Objets[i].Vertices[y].y=0;
	  M->Objets[i].Vertices[y].z=sin(ang)*Rext;
	  M->Objets[i].Vertices[y].tx=0;
	  M->Objets[i].Vertices[y].ty=0;
	  y++;
	}
    }

  update_list();
  gtk_widget_destroy (dialog);

}

void OnChamps(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * entry[14];
  GtkWidget * vvbox;
  GtkWidget * hhbox;
  GtkWidget * label;
  GtkWidget * frame;
  guint response;

  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }
 
  vbox=gtk_vbox_new(FALSE, 5);

  frame = gtk_frame_new("Model");
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
  vvbox=gtk_vbox_new(FALSE,5);
  hhbox=gtk_hbox_new(FALSE,5);

  label=gtk_label_new("Url du model :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[0]=EntryFromStr("../data/model/*.mad");
  gtk_box_pack_start (GTK_BOX (hhbox), entry[0], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  //hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Nombre d'entites :");
  gtk_box_pack_start (GTK_BOX (vvbox), label, FALSE, FALSE, 0);
  entry[1]=gtk_hscale_new_with_range(1,100,1);
  gtk_box_pack_start (GTK_BOX (vvbox), entry[1], FALSE, FALSE, 0);
  //gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame), vvbox);

  frame = gtk_frame_new("Aleatoire");
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
  vvbox=gtk_vbox_new(FALSE,5);

  hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Pos X :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[2]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[2], FALSE, FALSE, 0);
  entry[3]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[3], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Pos Y :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[4]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[4], FALSE, FALSE, 0);
  entry[5]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[5], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Pos Z :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[6]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[6], FALSE, FALSE, 0);
  entry[7]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[7], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Scale X :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[8]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[8], FALSE, FALSE, 0);
  entry[9]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[9], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Scale Y :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[10]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[10], FALSE, FALSE, 0);
  entry[11]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[11], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("Scale Z :");
  gtk_box_pack_start (GTK_BOX (hhbox), label, FALSE, FALSE, 0);
  entry[12]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[12], FALSE, FALSE, 0);
  entry[13]=EntryFromInt(1);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[13], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vvbox), hhbox, FALSE, FALSE, 0);

  gtk_container_add (GTK_CONTAINER (frame), vvbox);


      
  dialog = gtk_dialog_new_with_buttons ("Champs d'entites",
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
      FILE * mod;
      int nb=gtk_range_get_value(GTK_RANGE(entry[1]));
      float posxmin=atof(gtk_entry_get_text (GTK_ENTRY (entry[2])));
      float posxmax=atof(gtk_entry_get_text (GTK_ENTRY (entry[3])));
      float posymin=atof(gtk_entry_get_text (GTK_ENTRY (entry[4])));
      float posymax=atof(gtk_entry_get_text (GTK_ENTRY (entry[5])));
      float poszmin=atof(gtk_entry_get_text (GTK_ENTRY (entry[6])));
      float poszmax=atof(gtk_entry_get_text (GTK_ENTRY (entry[7])));
      float scaxmin=atof(gtk_entry_get_text (GTK_ENTRY (entry[8])));
      float scaxmax=atof(gtk_entry_get_text (GTK_ENTRY (entry[9])));
      float scaymin=atof(gtk_entry_get_text (GTK_ENTRY (entry[10])));
      float scaymax=atof(gtk_entry_get_text (GTK_ENTRY (entry[11])));
      float scazmin=atof(gtk_entry_get_text (GTK_ENTRY (entry[12])));
      float scazmax=atof(gtk_entry_get_text (GTK_ENTRY (entry[13])));
      char urlmodel[60];
      strcpy(urlmodel,gtk_entry_get_text (GTK_ENTRY (entry[0])));

      M->nbObjets++;
      M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
      int i=M->nbObjets-1;

      mod=fopen(urlmodel,"r");
      if(mod==NULL)
	{
	  AlertMsgWarning("Model inexistant !");
	  return;
	}
      unsigned char control;
      fread(&control,sizeof(unsigned char),1,mod);
      if(control!=136)
	{
	  AlertMsgWarning("Model incorrect !");
	  return;
	}
      fseek(mod, sizeof(int)+sizeof(char), SEEK_CUR);
      
      int nbsurf=0;
      fread(&nbsurf,sizeof(int),1,mod);
      if(nbsurf>1)
	AlertMsgInfo("Seul le premier objet est pris");

      char text[50];
      fread(&text, sizeof(char), 50, mod);
      strcpy(M->Objets[i].texture, text);

      char type;
      fread(&type, sizeof(char), 1, mod);
      M->Objets[i].typeSurf=type;

      int nb_vert;
      fread(&nb_vert, sizeof(int), 1, mod);
      M->Objets[i].nbVertices=nb_vert*nb;
      M->Objets[i].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[i].nbVertices);


      int y=0;
      for( y=0; y<nb ; y++ )
	{
	  float fX=RandFloat(posxmin,posxmax);
	  float fY=RandFloat(posymin,posymax);
	  float fZ=RandFloat(poszmin,poszmax);
	  float fXS=RandFloat(scaxmin,scaxmax);
	  float fYS=RandFloat(scaymin,scaymax);
	  float fZS=RandFloat(scazmin,scazmax);
	  int v=0;
	  fseek(mod, sizeof(char)*53+sizeof(int)*3, SEEK_SET);
	  for( v=0; v<nb_vert ; v++)
	    {
	      float cx,cy,cz,ctx,cty;
	      fread(&cx, sizeof(float), 1, mod);
	      fread(&cy, sizeof(float), 1, mod);
	      fread(&cz, sizeof(float), 1, mod);
	      fread(&ctx, sizeof(float), 1, mod);
	      fread(&cty, sizeof(float), 1, mod);
	      M->Objets[i].Vertices[v+y*nb_vert].x=cx*fXS+fX;
	      M->Objets[i].Vertices[v+y*nb_vert].y=cy*fYS+fY;
	      M->Objets[i].Vertices[v+y*nb_vert].z=cz*fZS+fZ;
	      M->Objets[i].Vertices[v+y*nb_vert].tx=ctx;
	      M->Objets[i].Vertices[v+y*nb_vert].ty=cty;
	      //printf("%f\n",M->Objets[i].Vertices[v+y*nb_vert].x);
	      //printf("%f\n",M->Objets[i].Vertices[v+y*nb_vert].y);
	      //printf("%f\n",M->Objets[i].Vertices[v+y*nb_vert].z);
	      //printf("%f\n",M->Objets[i].Vertices[v+y*nb_vert].tx);
	      //printf("%f\n\n\n",M->Objets[i].Vertices[v+y*nb_vert].ty);
	    }
	}
    }

  update_list();
  gtk_widget_destroy (dialog);

}


void OnAddBuilder(GtkWidget *pWidget, gpointer pData)
{
  if(M==NULL)
    {
      AlertMsgInfo("Aucun fichier ouvert");
      return;
    }

  GtkWidget * dialog;
  GtkWidget * vbox;
  GtkWidget * hbox;
  GtkWidget * hhbox;
  GtkWidget * label;
  GtkWidget * Xscale;
  GtkWidget * Zscale;
  GtkWidget * Yscale;
  GtkWidget * Tscale;
  GtkWidget * entry[8]; // oX oZ dX dZ mY way textwall textroof
  guint response;
  int nbTX=5, nbTZ=5, TY=10, oX=-100, oZ=-100, dX=100, dZ=100, border=100, mY=0;

  hbox=gtk_hbox_new(FALSE,0);

  vbox=gtk_vbox_new(FALSE,0);

  label=gtk_label_new("Choisissez les options du Builder :\n");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

  label=gtk_label_new("Nombre de tiles X et Z :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  Xscale=gtk_hscale_new_with_range(2,20,1);
  gtk_box_pack_start (GTK_BOX (vbox), Xscale, FALSE, FALSE, 0);
  Zscale=gtk_hscale_new_with_range(2,20,1);
  gtk_box_pack_start (GTK_BOX (vbox), Zscale, FALSE, FALSE, 0);
  label=gtk_label_new("Hauteur Y d'un tile :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  Yscale=gtk_hscale_new_with_range(1,100,1);
  gtk_box_pack_start (GTK_BOX (vbox), Yscale, FALSE, FALSE, 0);
  label=gtk_label_new("Ratio des Textures d'un tile (*100) :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  Tscale=gtk_hscale_new_with_range(1,100,1);
  gtk_box_pack_start (GTK_BOX (vbox), Tscale, FALSE, FALSE, 0);

  gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);


  vbox=gtk_vbox_new(FALSE,0);


  label=gtk_label_new("Coordonnees X et Z de l'origine :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,0);
  entry[0]=EntryFromInt(-100);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[0], FALSE, FALSE, 0);
  entry[1]=EntryFromInt(-100);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[1], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hhbox, FALSE, FALSE, 0);

  label=gtk_label_new("Coordonnees X et Z de la destination :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  hhbox=gtk_hbox_new(FALSE,0);
  entry[2]=EntryFromInt(100);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[2], FALSE, FALSE, 0);
  entry[3]=EntryFromInt(100);
  gtk_box_pack_start (GTK_BOX (hhbox), entry[3], FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hhbox, FALSE, FALSE, 0);

  label=gtk_label_new("Hauteur Y de base :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[4]=EntryFromInt(0);
  gtk_box_pack_start (GTK_BOX (vbox), entry[4], FALSE, FALSE, 0);

  label=gtk_label_new("Dimension des Ways :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[5]=EntryFromInt(10);
  gtk_box_pack_start (GTK_BOX (vbox), entry[5], FALSE, FALSE, 0);

  label=gtk_label_new("Texture des Murs :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[6]=EntryFromStr("data/textures/*");
  gtk_box_pack_start (GTK_BOX (vbox), entry[6], FALSE, FALSE, 0);

  label=gtk_label_new("Texture des Toits :");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
  entry[7]=EntryFromStr("data/textures/*");
  gtk_box_pack_start (GTK_BOX (vbox), entry[7], FALSE, FALSE, 0);
  

  gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
      
  dialog = gtk_dialog_new_with_buttons ("Options Builder",
					GTK_WINDOW (pWin),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					NULL);
      
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 0);
      
  gtk_widget_show_all (hbox);
      
  response = gtk_dialog_run (GTK_DIALOG (dialog));


  if(response==GTK_RESPONSE_OK)
    {
      GtkWidget * table;
      GtkWidget * button[20][20];
      int i,y;
      float rText;
      char urlTextWall[60];
      char urlTextRoof[60];
      nbTX=gtk_range_get_value(GTK_RANGE(Xscale));
      nbTZ=gtk_range_get_value(GTK_RANGE(Zscale));
      TY=gtk_range_get_value(GTK_RANGE(Yscale));
      rText=gtk_range_get_value(GTK_RANGE(Tscale));
      rText=rText/100;
      oX=atoi(gtk_entry_get_text (GTK_ENTRY (entry[0])));
      oZ=atoi(gtk_entry_get_text (GTK_ENTRY (entry[1])));
      dX=atoi(gtk_entry_get_text (GTK_ENTRY (entry[2])));
      dZ=atoi(gtk_entry_get_text (GTK_ENTRY (entry[3])));
      mY=atoi(gtk_entry_get_text (GTK_ENTRY (entry[4])));
      border=atoi(gtk_entry_get_text (GTK_ENTRY (entry[5])));
      strcpy(urlTextWall,gtk_entry_get_text(GTK_ENTRY(entry[6])));
      strcpy(urlTextRoof,gtk_entry_get_text(GTK_ENTRY(entry[7])));

      gtk_widget_destroy (dialog);


      table = gtk_table_new (nbTX, nbTZ, FALSE);

      for(i=0 ; i<nbTZ ; i++)
	{
	  for(y=0 ; y<nbTX ; y++)
	    {
	      button[y][i]=gtk_button_new_with_label("0");
	      gtk_table_attach_defaults (GTK_TABLE (table),
					 button[y][i],
					 y, y+1, i, i+1);
	      g_signal_connect(G_OBJECT(button[y][i]), "clicked", G_CALLBACK(OnModYBuild), button[y][i]);
	    }
	}

      dialog = gtk_dialog_new_with_buttons ("Nouveau Builder",
					    GTK_WINDOW (pWin),
					    GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					    GTK_STOCK_CANCEL,
					    GTK_RESPONSE_CANCEL,
					    GTK_STOCK_OK,
					    GTK_RESPONSE_OK,
					    NULL);
      
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), table, FALSE, FALSE, 0);

      gtk_widget_show_all (table);
      
      response = gtk_dialog_run (GTK_DIALOG (dialog));

      if(response==GTK_RESPONSE_OK)
	{
	  int hauteurs[22][22];
	  int ix=0, iz=0, i=0;
	  float largeurX=((dX-oX)-(border*(nbTX-1)))/(nbTX), largeurZ=((dZ-oZ)-(border*(nbTZ-1)))/(nbTZ);
	  int nbBuild=nbTX*nbTZ;

	  for(ix=0 ; ix<nbTX ; ix++)
	    for(iz=0 ; iz<nbTZ ; iz++)
	      {
		hauteurs[ix][iz]=atoi(gtk_button_get_label(GTK_BUTTON(button[ix][iz])))*TY;
		if(hauteurs[ix][iz]==0)
		  nbBuild--;
	      }

	  M->nbObjets++;
	  M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
	  strcpy(M->Objets[M->nbObjets-1].texture, urlTextWall);
	  M->Objets[M->nbObjets-1].typeSurf='Q';
	  M->Objets[M->nbObjets-1].nbVertices=(nbBuild*4*4);
	  M->Objets[M->nbObjets-1].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[M->nbObjets-1].nbVertices);

	  for(ix=0 ; ix<nbTX ; ix++)
	    for(iz=0 ; iz<nbTZ ; iz++)
	      {
		float fx=(ix*(largeurX+border)), fz=(iz*(largeurZ+border));
		if(hauteurs[ix][iz]!=0)
		  {
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=largeurX*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=largeurX*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;

		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=-largeurX*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz];
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=-largeurX*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;


		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=-largeurZ*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=-largeurZ*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;

		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=largeurZ*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=largeurZ*rText;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=hauteurs[ix][iz]+mY;
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=hauteurs[ix][iz]*rText;
		    i++;
		  }
	      }
	  M->nbObjets++;
	  M->Objets=(sObjet *)realloc(M->Objets, sizeof(sObjet)*M->nbObjets);
	  strcpy(M->Objets[M->nbObjets-1].texture, urlTextRoof);
	  M->Objets[M->nbObjets-1].typeSurf='Q';
	  M->Objets[M->nbObjets-1].nbVertices=(nbBuild*4);
	  M->Objets[M->nbObjets-1].Vertices=(Vertex *)malloc(sizeof(Vertex)*M->Objets[M->nbObjets-1].nbVertices);
	  i=0;
	  for(ix=0 ; ix<nbTX ; ix++)
	    for(iz=0 ; iz<nbTZ ; iz++)
	      {
		float fx=(ix*(largeurX+border)), fz=(iz*(largeurZ+border));
		if(hauteurs[ix][iz]!=0)
		  {
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY+hauteurs[ix][iz];
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY+hauteurs[ix][iz];
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=1;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=0;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx+largeurX;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY+hauteurs[ix][iz];
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=1;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=1;
		    i++;
		    M->Objets[M->nbObjets-1].Vertices[i].x=fx;
		    M->Objets[M->nbObjets-1].Vertices[i].y=mY+hauteurs[ix][iz];
		    M->Objets[M->nbObjets-1].Vertices[i].z=fz+largeurZ;
		    M->Objets[M->nbObjets-1].Vertices[i].tx=0;
		    M->Objets[M->nbObjets-1].Vertices[i].ty=1;
		    i++;
		  }
	      }
	}
    }
  
  gtk_widget_destroy (dialog);

  update_list();

  return;
}
