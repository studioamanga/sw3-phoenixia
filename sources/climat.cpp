/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** climat.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Constantes et fonctions liées à la gestion des climats. **
**                                                         **
*************************************************************/

class cl_climat
{
private :
  float mer, merBegin, merEnd;
  float fog, fogBegin, fogEnd;
  float pluie, pluieBegin, pluieEnd;
  float varmer, varmerBegin, varmerEnd;

  float r,rBegin,rEnd;
  float g,gBegin,gEnd;
  float b,bBegin,bEnd;

  char Type;

public :
  cl_climat(float merB, float merBmin, float merBmax, char type);
  ~cl_climat(void);

  float getPluie(void);
  float getLiq(void);
  float getVarLiq(void);
  float getFog(void);
  float getFogBack();
  float getR(void);
  float getG(void);
  float getB(void);

  bool IsPluie(void);
  bool IsNeige(void);
  void Update(void);

};

#define CLIMAT_NORMAL '0'
#define CLIMAT_TEMPETE 'T'
#define CLIMAT_SABLE 'S'
#define CLIMAT_NUIT 'N'
#define CLIMAT_NEIGE 'n'
#define CLIMAT_CRUE 'C'
#define CLIMAT_INONDATION 'I'
#define CLIMAT_SECHERESSE 's'
#define CLIMAT_AUBE 'A'
#define CLIMAT_ESPACE 'E'
#define CLIMAT_CREPUSCULE 'c'
#define CLIMAT_ENFER 'e'


void cl_climat::Update(void)
{
  return;
}

bool cl_climat::IsNeige(void)
{
  if(Type==CLIMAT_NEIGE)
    return true;
  return false;
}

bool cl_climat::IsPluie(void)
{
  if(Type==CLIMAT_TEMPETE || Type==CLIMAT_INONDATION || Type==CLIMAT_CRUE)
    return true;
  return false;
}

float cl_climat::getR(void)
{
  return this->r;
}

float cl_climat::getG(void)
{
  return this->g;
}

float cl_climat::getB(void)
{
  return this->b;
}

float cl_climat::getLiq(void)
{
  return this->mer;
}

float cl_climat::getVarLiq(void)
{
  return this->varmer;
}

float cl_climat::getFog(void)
{
  return this->fog;
}

float cl_climat::getPluie(void)
{
  return this->pluie;
}

float cl_climat::getFogBack(void)
{
  if(this->fogBegin>fogEnd)
    return this->fogBegin+500;
  return this->fogEnd+500;
}



cl_climat::cl_climat(float merB, float merBmin, float merBmax, char type)
{
  Type=type;
  clSoundMan * Sound=clSoundMan::Create();

  switch(type)
    {
    case CLIMAT_ENFER :
      this->merEnd=this->merBegin=this->mer=merBmin;

       this->varmerBegin=this->varmer=this->varmerEnd=0;

       this->fogBegin=this->fog=this->fogEnd=400;

       this->pluieBegin=this->pluie=this->pluieEnd=0;


       this->r=this->rBegin=this->rEnd=1.0;
       this->g=this->gBegin=this->gEnd=0.0;
       this->b=this->bBegin=this->bEnd=0.0;
      break;

    case CLIMAT_CREPUSCULE :
      this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=2;

       this->fogBegin=this->fog=this->fogEnd=500;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=0.0;
       this->g=this->gBegin=this->gEnd=0.0;
       this->b=this->bBegin=this->bEnd=0.3;
      break;

    case CLIMAT_ESPACE :
      this->merEnd=this->merBegin=this->mer=merBmin;

       this->varmerBegin=this->varmer=this->varmerEnd=0;

       this->fogBegin=this->fog=this->fogEnd=5000;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=0.0;
       this->g=this->gBegin=this->gEnd=0.0;
       this->b=this->bBegin=this->bEnd=0.0;
      break;

    case CLIMAT_AUBE :
      this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=2;

       this->fogBegin=this->fog=this->fogEnd=200;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=0.0;
       this->g=this->gBegin=this->gEnd=0.0;
       this->b=this->bBegin=this->bEnd=0.1;
      break;

    case CLIMAT_SECHERESSE :
      this->merEnd=this->merBegin=this->mer=merBmin;

       this->varmerBegin=this->varmer=this->varmerEnd=0;

       this->fogBegin=this->fog=this->fogEnd=5000;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=1.0;
       this->g=this->gBegin=this->gEnd=0.867;
       this->b=this->bBegin=this->bEnd=0.133;
      break;

    case CLIMAT_INONDATION :
      this->merEnd=this->merBegin=this->mer=merBmax;

       this->varmerBegin=this->varmer=this->varmerEnd=3;

       this->fogBegin=this->fog=this->fogEnd=400;

       this->pluieBegin=this->pluie=this->pluieEnd=40;

       this->r=this->rBegin=this->rEnd=0.09;
       this->g=this->gBegin=this->gEnd=0.2;
       this->b=this->bBegin=this->bEnd=0.9;

       Sound->JouerStream (SOUND_RAIN, CANAL_ENV, true);
       FSOUND_SetVolume(CANAL_ENV, VOLUME_MOYEN);
      break;

    case CLIMAT_CRUE :
      this->merEnd=this->merBegin=this->mer=merBmax;

       this->varmerBegin=this->varmer=this->varmerEnd=3;

       this->fogBegin=this->fog=this->fogEnd=200;

       this->pluieBegin=this->pluie=this->pluieEnd=5;

       this->r=this->rBegin=this->rEnd=0.09;
       this->g=this->gBegin=this->gEnd=0.2;
       this->b=this->bBegin=this->bEnd=0.59;

       Sound->JouerStream (SOUND_RAIN, CANAL_ENV, true);
       FSOUND_SetVolume(CANAL_ENV, VOLUME_FAIBLE);
      break;

    case CLIMAT_TEMPETE :
      this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=3;

       this->fogBegin=this->fog=this->fogEnd=150;

       this->pluieBegin=this->pluie=this->pluieEnd=20;

       this->r=this->rBegin=this->rEnd=0.445;
       this->g=this->gBegin=this->gEnd=0.586;
       this->b=this->bBegin=this->bEnd=0.69;

       Sound->JouerStream (SOUND_THUNDER, CANAL_ENV, true);
       FSOUND_SetVolume(CANAL_ENV, VOLUME_FORT);
      break;

    case CLIMAT_NEIGE :
      this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=0;

       this->fogBegin=this->fog=this->fogEnd=100;

       this->pluieBegin=this->pluie=this->pluieEnd=10;

       this->r=this->rBegin=this->rEnd=1.0;
       this->g=this->gBegin=this->gEnd=1.0;
       this->b=this->bBegin=this->bEnd=1.0;

       Sound->JouerStream (SOUND_WIND, CANAL_ENV, true);
       FSOUND_SetVolume(CANAL_ENV, VOLUME_MOYEN);
      break;

    case CLIMAT_NUIT :
      this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=1;

       this->fogBegin=this->fog=this->fogEnd=0;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=0.0;
       this->g=this->gBegin=this->gEnd=0.0;
       this->b=this->bBegin=this->bEnd=0.0;
      break;

    case CLIMAT_SABLE :
      this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=1;

       this->fogBegin=this->fog=this->fogEnd=1000;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=1.0;
       this->g=this->gBegin=this->gEnd=0.86;
       this->b=this->bBegin=this->bEnd=0.359;

       Sound->JouerStream (SOUND_WIND, CANAL_ENV, true);
       FSOUND_SetVolume(CANAL_ENV, VOLUME_FAIBLE);
      break;

    default :
       this->merEnd=this->merBegin=this->mer=merB;

       this->varmerBegin=this->varmer=this->varmerEnd=2;

       this->fogBegin=this->fog=this->fogEnd=900;

       this->pluieBegin=this->pluie=this->pluieEnd=0;

       this->r=this->rBegin=this->rEnd=0.43;
       this->g=this->gBegin=this->gEnd=0.754;
       this->b=this->bBegin=this->bEnd=0.985;
      break;
    };
}

cl_climat::~cl_climat(void)
{
}

char * getClimatName(char clim)
{
  char * typeC=new char[15];
  switch(clim)
    {
    case 'T' :
      strcpy(typeC,"Tempete");
      break;
    case 'S' :
      strcpy(typeC,"Sable");
      break;
    case 'n' :
      strcpy(typeC,"Neige");
      break;
    case 'C' :
      strcpy(typeC,"Crue");
      break;
    case 'I' :
      strcpy(typeC,"Innondation");
      break;
    case 's' :
      strcpy(typeC,"Secheresse");
      break;
    case 'A' :
      strcpy(typeC,"Aube");
      break;
    case 'E' :
      strcpy(typeC,"Espace");
      break;
    case 'c' :
      strcpy(typeC,"Crepuscule");
      break;
    case 'e' :
      strcpy(typeC,"Enfer");
      break;
    case 'N' :
      strcpy(typeC,"Nuit");
      break;
    default :
      strcpy(typeC,"Normal");
    }

  return typeC;
}
