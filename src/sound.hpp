/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* sound.hpp **** auteur : Vincent Tourraine *********
**                                                         **
** Constantes et fonctions liÈes ‡ la gestion des Sons.    **
**                                                         **
*************************************************************/


//#include "fmod.h"

#define VOLUME_TFAIBLE 10
#define VOLUME_FAIBLE  75
#define VOLUME_MOYEN   128
#define VOLUME_FORT    200
#define VOLUME_TFORT   256

// SONS de BASE
//
// CANAL_MUSIQUE
#define MUSIC_MENU   "data/music/maintheme.ogg"
#define MUSIC_THEME  "data/music/theme.ogg"
//
// CANAL_BRUITS
#define SOUND_VALID   "data/music/valid.wav"
#define SOUND_TOUCHE  "data/music/touche.wav"
#define SOUND_VIRAGE  "data/music/virage.ogg"
#define SOUND_EXPLO   "data/music/explo.wav"
//
// CANAL_ARME
#define SOUND_SHIELD  "data/music/shield.ogg"
#define SOUND_WEAPON  "data/music/weapon.wav"
//
// CANAL_JOUEUR1
#define SOUND_WING    "data/music/wing.ogg"
//
// CANAL_ENV
#define SOUND_RAIN    "data/music/rain.wav"
#define SOUND_THUNDER "data/music/thunder.wav"
#define SOUND_WIND    "data/music/vents.ogg"
//

typedef enum
{
  CANAL_NULL = 0,
  CANAL_MUSIQUE = 0,
  CANAL_JOUEUR,
  CANAL_ENNEMIS,
  CANAL_BONUS,
  CANAL_ARME,
  CANAL_ENV,
  CANAL_BRUITS,
  CANAL_MAX
} ECanaux;

class clSoundMan
{
private:
  static clSoundMan *Manager;

  //FSOUND_STREAM* Sound[CANAL_MAX];
	void* Sound[CANAL_MAX];
  bool activeMusic;
  bool activeNoise;

  clSoundMan ();
  ~clSoundMan ();

public:
  static clSoundMan* Create ();
  static void	Kill ();

  // Controle que la musique ne doit pas etre desactivee
  void CtrlMusicActive(bool force=false);
  // Controle que les sons ne doivent pas etre desactives
  void CtrlNoiseActive(bool force=false);
  //! Lecture d'un son
  void JouerStream (const char* url, ECanaux Canal, bool Loop = false);
  //! Active/DÈsactive la musique
  void SwapMuteMusic () {activeMusic = !activeMusic; CtrlMusicActive();}
  //! Retourne l'Ètat d'activation
  bool IsActiveMusic () {return activeMusic;}
  //! Active/DÈsactive des bruitages
  void SwapMuteNoise () {activeNoise = !activeNoise;}
  //! Retourne l'Ètat d'activation
  bool IsActiveNoise () {return activeNoise;}
  //! Initialisation des Ètats
  void MuteInit (bool music, bool noise) {activeMusic=music; activeNoise=noise; CtrlMusicActive();}
};
