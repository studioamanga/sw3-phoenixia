
GArray *cellObjs = NULL;
typedef struct
{
  int id;
  char type;
  char texture[50];
  int nbSurfaces;
  int nbVertices;
}cellObj;

int nbCellObjs=0;

enum
  {
    ID,
    NOM,
    TEXTURE,
    NBSURFACES,
    NBVERTICES,
    NUMBER
  };

void add_item (int id, char type, char* texture, int nbVertices )
{
  cellObj o1;
  GtkTreeIter iter;
  GtkTreeModel *model = Model;

  g_return_if_fail (cellObjs != NULL);

  strcpy(o1.texture,texture);
  o1.id=id;
  o1.type=type;
  o1.nbVertices=nbVertices;
  if(type=='Q')
    o1.nbSurfaces=o1.nbVertices/4;
  else
    if(type=='M')
      o1.nbSurfaces=1;
    else
      o1.nbSurfaces=o1.nbVertices/3;
  g_array_append_vals (cellObjs, &o1, 1);
  nbCellObjs++;

  char typeNom[21];
  switch(type)
    {
    case 'M' :
      strcpy(typeNom,"SkySphere");
      break;
    default :
      strcpy(typeNom,"Quad");
    }

  gtk_list_store_append (GTK_LIST_STORE (model), &iter);
  gtk_list_store_set (GTK_LIST_STORE (model), &iter,
		      ID, o1.id,
		      NOM, typeNom,
		      TEXTURE, o1.texture,
		      NBSURFACES, o1.nbSurfaces,
		      NBVERTICES, o1.nbVertices,
		      -1);
}

void update_list (void)
{
  //GtkTreeIter iter;
  int i;

  gtk_list_store_clear(GTK_LIST_STORE(Model));
 
  if(M==NULL)
    return;

  for(i=0 ; i<M->nbObjets ; i++)
    {
      add_item(i, M->Objets[i].typeSurf, M->Objets[i].texture, M->Objets[i].nbVertices );
    }

  return;
}


void remove_item (GtkWidget *widget, gpointer data)
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

      g_array_remove_index (cellObjs, i);
      nbCellObjs--;

      gtk_tree_path_free (path);
    }
}

GtkTreeModel * Store(void)
{
  GtkListStore * StoreModel = gtk_list_store_new(NUMBER, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
  //GtkTreeIter Iter;

  cellObjs = g_array_sized_new (FALSE, FALSE, sizeof (cellObj), 1);

  //g_return_if_fail (cellObjs != NULL);

  return GTK_TREE_MODEL(StoreModel);
}

GtkWidget *  DrawTree(GtkTreeModel * Model)
{
  GtkWidget * TreeView=gtk_tree_view_new_with_model(Model);

  GtkCellRenderer * Render=gtk_cell_renderer_text_new();
  GtkTreeViewColumn * Col=gtk_tree_view_column_new_with_attributes("ID", Render, "text", ID, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(TreeView), Col);

  Render=gtk_cell_renderer_text_new();
  Col=gtk_tree_view_column_new_with_attributes("Type d'objet", Render, "text", NOM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(TreeView), Col);

  Render=gtk_cell_renderer_text_new();
  Col=gtk_tree_view_column_new_with_attributes("Texture", Render, "text", TEXTURE, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(TreeView), Col);

  Render=gtk_cell_renderer_text_new();
  Col=gtk_tree_view_column_new_with_attributes("Nb de surfaces", Render, "text", NBSURFACES, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(TreeView), Col);

  Render=gtk_cell_renderer_text_new();
  Col=gtk_tree_view_column_new_with_attributes("Nb de vertices", Render, "text", NBVERTICES, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(TreeView), Col);

  g_signal_connect(G_OBJECT(TreeView), "cursor-changed", G_CALLBACK(UpdateFrameD), TreeView);

  return TreeView;
}

