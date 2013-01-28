/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********** cfg.cpp **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

void LoadCfg(void)
{
  FILE * fIn=fopen("config/config.cfg", "r");
  if(fIn==NULL)
    return;

  fread(&NIV_DETAIL, sizeof(int), 1, fIn);
  for(int i=0 ; i<NB_INPUT ; i++)
    fread(&(myInput[i]), sizeof(char), 1, fIn);

  fread(&SCREEN_X, sizeof(int), 1, fIn);
  fread(&SCREEN_Y, sizeof(int), 1, fIn);
  fread(&SCREEN_FULL, sizeof(bool), 1, fIn);
  if(SCREEN_FULL)
    glutFullScreen();
  else
    glutReshapeWindow(SCREEN_X,SCREEN_Y);

  bool aM, aN;
  fread(&aM, sizeof(bool), 1, fIn);
  fread(&aN, sizeof(bool), 1, fIn);
  clSoundMan * Sound=clSoundMan::Create();
  Sound->MuteInit(aM, aN);

  fclose(fIn);
}

void SaveCfg(void)
{
  FILE * fOut=fopen("config/config.cfg", "w");
  if(fOut==NULL)
    return;

  fwrite(&NIV_DETAIL, sizeof(int), 1, fOut);
  for(int i=0 ; i<NB_INPUT ; i++)
    fwrite(&(myInput[i]), sizeof(char), 1, fOut);

  fwrite(&SCREEN_X, sizeof(int), 1, fOut);
  fwrite(&SCREEN_Y, sizeof(int), 1, fOut);
  fwrite(&SCREEN_FULL, sizeof(bool), 1, fOut);

  clSoundMan * Sound=clSoundMan::Create();
  bool aM=Sound->IsActiveMusic(), aN=Sound->IsActiveNoise();
  fwrite(&aM, sizeof(bool), 1, fOut);
  fwrite(&aN, sizeof(bool), 1, fOut);

  fclose(fOut);
}
