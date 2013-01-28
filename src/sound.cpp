/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* sound.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Constantes et fonctions liées à la gestion des Sons.    **
**                                                         **
*************************************************************/

#include "sound.hpp"

clSoundMan* clSoundMan::Manager = 0;

clSoundMan::clSoundMan ()
{
  activeMusic=activeNoise = true;

  // On initialise Fmod : Fréquence de sortie, nombre de canaux utilisés et option (non util pour nous)
  //FSOUND_Init (44100, CANAL_MAX, 0);

  // On initialise tous les canaux de sons à 0 pour pouvoir vérifier qu'ils sont utilisés ou non.
  for (int Canal = CANAL_NULL; Canal < CANAL_MAX; Canal++)
    Sound[Canal] = 0;
}

clSoundMan::~clSoundMan ()
{
  // On libère tous les canaux
  for (int Canal = CANAL_NULL; Canal < CANAL_MAX; Canal++)
    if (Sound[Canal])
	{}//FSOUND_Stream_Close (Sound[Canal]);
}


clSoundMan* clSoundMan::Create ()
{
  if (Manager == 0)
    Manager = new clSoundMan;
  return Manager;
}


void clSoundMan::Kill ()
{
  if (Manager != 0)
    {
      delete Manager;
      Manager = 0;
    }
}

void clSoundMan::JouerStream (const char* url, ECanaux Canal, bool Loop)
{
  if ( (!activeMusic) && (Canal == CANAL_MUSIQUE) )
    return;
  if ( (!activeNoise) && (Canal != CANAL_MUSIQUE) )
    return;

  if (Sound[Canal])
  {}//FSOUND_Stream_Close (Sound[Canal]);

  if (Loop)
    {
      //FSOUND_SetLoopMode (0, FSOUND_LOOP_NORMAL);
      //Sound[Canal] = FSOUND_Stream_Open (url, FSOUND_LOOP_NORMAL, 0, 0);
    }
  else
  {}//Sound[Canal] = FSOUND_Stream_Open (url, FSOUND_NORMAL, 0, 0);

  //FSOUND_Stream_Play (Canal, Sound[Canal]);
}

void clSoundMan::CtrlMusicActive(bool force)
{
  if( (!activeMusic) || force )
    {
      //FSOUND_Stream_Stop (Sound[CANAL_MUSIQUE]);
      //FSOUND_Stream_Close(Sound[CANAL_MUSIQUE]);
      Sound[CANAL_MUSIQUE]=NULL;
    }
}

void clSoundMan::CtrlNoiseActive(bool force)
{
  if( (!activeNoise) || force )
    for(int i=(CANAL_MUSIQUE+1) ; i<CANAL_MAX ; i++)
      {
	//FSOUND_Stream_Stop (Sound[i]);
	//FSOUND_Stream_Close(Sound[i]);
	Sound[i]=NULL;
      }
}
