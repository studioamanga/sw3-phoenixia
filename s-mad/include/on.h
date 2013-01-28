
#include "onfile.h"
#include "onmod.h"
#include "onobj.h"

void OnQuit(GtkWidget *pWidget, gpointer pData)
{
  OnClose(NULL,NULL);

  gtk_main_quit();
}

void OnAide(GtkWidget *pWidget, gpointer pData)
{
  GtkWidget *pQuestion;

  gchar *sUtf8 = g_locale_to_utf8("\n{S-MAD} // for SW3 Phoenixia\n\nCet utilitaire vous permet de gérer les fichiers *.mad conçus pour stocker des models 3D pour SW3. Vous pouvez ainsi créer de nouveaux models, ou bien encore modifier les fichiers existants.\n\nS-Mad v0.2\nby Studio AMANgA\n\nhttp://studioamanga.free.fr\nstudioamanga@free.fr", -1, NULL, NULL, NULL);
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
