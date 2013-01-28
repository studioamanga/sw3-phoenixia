

void store_filename (GtkWidget *widget, gpointer user_data) 
{
   GtkWidget *file_selector = GTK_WIDGET (user_data);
   const gchar *selected_filename;

   selected_filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));

   // OPEN
   char url[201];
   strcpy(url,selected_filename);
   Open_File(url);
}

void OnOpen_create_file_selection (void) 
{

   GtkWidget *file_selector;

   /* Create the selector */
   
   file_selector = gtk_file_selection_new ("Selectionnez un fichier mad");
   //gtk_file_selection_complete(GTK_FILE_SELECTION(file_selector),"*.mad");
   
   g_signal_connect (GTK_FILE_SELECTION (file_selector)->ok_button,
                     "clicked",
                     G_CALLBACK (store_filename),
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
}
