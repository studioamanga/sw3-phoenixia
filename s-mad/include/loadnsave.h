

void Open_File(char * url)
{  
  if(M!=NULL)
    {
      AlertMsgWarning("Un mad est déjà ouvert !");
      return;
    }

  M=loadMadModel(url);

  if(M==NULL)
    {
      AlertMsgWarning("Erreur lors de\nl'ouverture du fichier !");
      return;
    }
  update_list();
}

void Save_File(void)
{
  if(M==NULL)
    return;

  if(!saveMadModel(M))
    AlertMsgWarning("Erreur lors de\nl'ouverture du fichier !");

  return;
}
