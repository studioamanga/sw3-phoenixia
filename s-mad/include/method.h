

GtkWidget * EntryFromFloat(float f)
{
  GtkWidget *entry;
  gchar *sUtf8;
  char dep[21];

  entry = gtk_entry_new ();
  sprintf(dep,"%f",f);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_entry_set_text (GTK_ENTRY (entry), sUtf8); 
  g_free(sUtf8);

  return entry;
}

GtkWidget * EntryFromInt(int i)
{
  GtkWidget *entry;
  gchar *sUtf8;
  char dep[21];

  entry = gtk_entry_new ();
  sprintf(dep,"%d",i);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_entry_set_text (GTK_ENTRY (entry), sUtf8); 
  g_free(sUtf8);

  return entry;
}

GtkWidget * EntryFromStr(char *s)
{
  GtkWidget *entry;
  gchar *sUtf8;
  char dep[101];

  entry = gtk_entry_new ();
  sprintf(dep,"%s",s);
  sUtf8 = g_locale_to_utf8(dep, -1, NULL, NULL, NULL);
  gtk_entry_set_text (GTK_ENTRY (entry), sUtf8); 
  g_free(sUtf8);

  return entry;
}

// Recherche d'un nombre alléatoire flottant
float RandFloat (float fMin, float fMax)
{
	return (rand () / (float)RAND_MAX * (fMax - fMin)) + fMin;
}

// Recherche d'un nombre alléatoire entier
int RandInt (int iMin, int iMax)
{
	return (int)(rand () / (float)RAND_MAX * (iMax - iMin)) + iMin;
}

