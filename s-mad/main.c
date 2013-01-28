#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <time.h>


#include "include/headers.h"


int main(int argc, char **argv)
{
  gtk_init(&argc,&argv);

  pWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(pWin), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(pWin), 800, 500);
  gtk_window_set_title(GTK_WINDOW(pWin), "{S-Mad} // for SW3 Phoenixia");

  g_signal_connect(G_OBJECT(pWin), "destroy", G_CALLBACK(OnQuit), NULL);

  gtk_container_add(GTK_CONTAINER(pWin),AffBoxes());

  gtk_widget_show_all(pWin);

  srand(55);

  gtk_main();

  return EXIT_SUCCESS;
}
