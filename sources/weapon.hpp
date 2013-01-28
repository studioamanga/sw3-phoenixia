/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** weapon.hpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/

typedef struct sBullet
{
  swVertex pos, depl;
  float distMur, distParcourue;
  bool actif;
};


class cWeapon
{
private :
  cl_texture * Text;
  sBullet * Bullets;
  int nbBullets, nbMaxBullets, nbFire;
  float vit, att, taille, tailleExplo, portee;
  float tCadence, tLast;
  bool affTrainee, affBall;
  char nom[20];
  char noise[25];

public :
  cWeapon(float fVit=0.03, float fAtt=10, float fTaille=1, float fTailleExplo=10, float fPortee=2000, float fTCadence=500, int nFire=20, bool bAffTrainee=true, bool bAffBall=true, char * urlTexture=NULL, char * sNom=NULL, char * sNoise=NULL);
  ~cWeapon(void);

  void weaponInit(float fVit=1, float fAtt=1, float fTaille=1, float fTailleExplo=1, float fPortee=1, float fTCadence=1, int nFire=1, bool bAffTrainee=true, bool bAffBall=true, char * urlTexture=NULL, char * sNom=NULL, char * sNoise=NULL);
  char * getNom(void);
  int getFire(void);
  void Shoot(swVertex & vOrigine, float & aDir, float & aInclin, float & accel, float & rayon);
  void ctrlCollBullet(swVertex vPos, swVertex vDest) throw (ErrDeleteDrone,CollCrystal,RecolCrystal);
  void Fire (swVertex & vOrigine, float & aDir, float & aInclin, float & accel, float & rayon);
  void Update(void);
  void Aff(void);
};
