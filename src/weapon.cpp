/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* weapon.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Classe des armes.                                       **
**                                                         **
*************************************************************/

//#include "weapon.hpp"

void cWeapon::ctrlCollBullet(swVertex vPos, swVertex vDest) throw (ErrDeleteDrone,CollCrystal,RecolCrystal)
{
  cl_drone * Dron=Crystals->Drones;
  float dRayon=Crystals->rayon;

  for(int i=0 ; i<Crystals->nbDrones ; i++)
    {
      swVertex polyColl[2];
      swVertex dronPos=Dron->getPos();
      polyColl[0]=vPos;
      polyColl[1]=vDest;
      if(SpherePolygonCollision(polyColl, dronPos, 2, dRayon+this->taille))
	{
	  MapColl->NbCrystals--;
	  Particule->AddExplosion(Dron->getPos(),15);
	  throw RecolCrystal(i);
	}
      Dron=Dron->NEXT;
    }

  Dron=Shokers->Drones;
  dRayon=Shokers->rayon;

  for(int i=0 ; i<Shokers->nbDrones ; i++)
    {
      swVertex polyColl[2];
      swVertex dronPos=Dron->getPos();
      polyColl[0]=vPos;
      polyColl[1]=vDest;
      if(SpherePolygonCollision(polyColl, dronPos, 2, dRayon+this->taille))
	{
	  Particule->AddExplosion(Dron->getPos(),30);
	  throw ErrDeleteDrone(i);
	}
      Dron=Dron->NEXT;
    }

  return;
}

cWeapon::cWeapon(float fVit, float fAtt, float fTaille, float fTailleExplo, float fPortee, float fTCadence, int nFire, bool bAffTrainee, bool bAffBall, char * urlTexture, char * sNom, char * sNoise)
{
  this->vit=fVit;
  this->att=fAtt;
  this->taille=fTaille;
  this->tailleExplo=fTailleExplo;
  this->portee=fPortee;
  this->tCadence=fTCadence;
  this->tLast=0;
  this->affTrainee=bAffTrainee;
  this->affBall=bAffBall;
  this->nbFire=nFire;

  this->nbBullets=0;
  this->nbMaxBullets=15;
  this->Bullets=(sBullet*)malloc(sizeof(sBullet)*(this->nbMaxBullets+2));

  this->Text=NULL;

  if(sNom==NULL)
    strcpy(this->nom,"Weapon");
  else
    strcpy(this->nom,sNom);

  if(sNoise==NULL)
    strcpy(this->noise,SOUND_WEAPON);
  else
    strcpy(this->noise,sNoise);
}

void cWeapon::weaponInit(float fVit, float fAtt, float fTaille, float fTailleExplo, float fPortee, float fTCadence, int nFire, bool bAffTrainee, bool bAffBall, char * urlTexture, char * sNom, char * sNoise)
{
  this->vit*=fVit;
  this->att*=fAtt;
  this->taille*=fTaille;
  this->tailleExplo*=fTailleExplo;
  this->portee*=fPortee;
  this->tCadence*=fTCadence;
  this->affTrainee=bAffTrainee;
  this->affBall=bAffBall;
  this->nbFire=nFire;

  if(this->affBall && Text==NULL)
    {
      if(urlTexture==NULL)
	Text=new cl_texture("data/texture/part/explo.tga");
      else
	Text=new cl_texture(urlTexture);
    }

  if(sNom==NULL)
    strcpy(this->nom,"Weapon");
  else
    strcpy(this->nom,sNom);

  if(sNoise==NULL)
    strcpy(this->noise,SOUND_WEAPON);
  else
    strcpy(this->noise,sNoise);
}

cWeapon::~cWeapon(void)
{
  free(this->Bullets);

  if(Text)
    delete Text;
}

char * cWeapon::getNom(void)
{
  return this->nom;
}

int cWeapon::getFire(void)
{
  return this->nbFire;
}

void cWeapon::Shoot(swVertex & vOrigine, float & aDir, float & aInclin, float & accel, float & rayon)
{
  if(this->nbFire==0)
    return;
  if(this->tLast<=0)
    {
      clSoundMan * Sound=clSoundMan::Create();
      Sound->JouerStream (this->noise, CANAL_ARME, false);
      //FSOUND_SetVolume(CANAL_ARME, VOLUME_FAIBLE);
      this->Fire(vOrigine, aDir, aInclin, accel, rayon);
      this->tLast=this->tCadence;
    }
}
void cWeapon::Fire(swVertex & vOrigine, float & aDir, float & aInclin, float & accel, float & rayon)
{
  int idPlace, nbPassed;
  for( idPlace=0, nbPassed=0 ; ; idPlace++ )
    {
      if(nbPassed==this->nbBullets || (!(this->Bullets[idPlace].actif)) )
	break;
      if(this->Bullets[idPlace].actif)
	nbPassed++;
    }

  this->Bullets[idPlace].pos=vOrigine+swVertex(Cos(aDir)*Cos(valAbs(aInclin))*(rayon+this->taille+4),
					       Sin(aInclin)*(rayon+this->taille+4),
					       -Sin(aDir)*Cos(valAbs(aInclin))*(rayon+this->taille+4));
  this->Bullets[idPlace].depl=swVertex(Cos(aDir)*Cos(valAbs(aInclin))*valAbs(accel),
				       Sin(aInclin)*valAbs(accel),
				       -Sin(aDir)*Cos(valAbs(aInclin))*valAbs(accel));
  swVertex objectif=this->Bullets[idPlace].pos+this->Bullets[idPlace].depl*this->portee;
  this->Bullets[idPlace].distMur=MapColl->bulletDistMur(this->Bullets[idPlace].pos,
							objectif);
  if(this->Bullets[idPlace].distMur==(INF_THEO))
    this->Bullets[idPlace].distMur=this->portee;
  //printf("Mur : %f\n", this->Bullets[idPlace].distMur);
  this->Bullets[idPlace].distParcourue=0;
  this->Bullets[idPlace].actif=true;

  this->nbBullets++;
  // On controle la taille du tableau des balles
  if(this->nbBullets==this->nbMaxBullets)
    {
      this->nbMaxBullets*=2;
      this->Bullets=(sBullet*)realloc(this->Bullets, sizeof(sBullet)*(this->nbMaxBullets+2));
    }
  this->nbFire--;
}

void cWeapon::Update(void)
{
  float factVit=valAbs(GETTIMER*this->vit);
  float depX, depY, depZ;
  for(int iB=0, nB=0 ; nB<this->nbBullets ; iB++)
    {
      if(this->Bullets[iB].actif)
	{
	  // On fait avancer la balle
	  depX=this->Bullets[iB].depl.x*factVit;
	  depY=this->Bullets[iB].depl.y*factVit;
	  depZ=this->Bullets[iB].depl.z*factVit;
	  // En testant qu'elle ne provoque aucune collision
	  try
	    {
	      ctrlCollBullet( this->Bullets[iB].pos,this->Bullets[iB].pos+swVertex(depX,depY,depZ));
	    }
	  // Si il collecte un Crystal
	  catch(RecolCrystal Err)
	    {
	      menuSetComment("[*] Crystal recolte [*]", 3000);
	      Crystals->Delete(Err.id);
	      this->Bullets[iB].actif=false;
	      this->nbBullets--;
	      continue;
	    }
	  // Si il rencontre un Shoker
	  catch(ErrDeleteDrone Err)
	    {
	      menuSetComment("[!] Shoker detruit [!]", 3000);
	      Shokers->Delete(Err.id);
	      this->Bullets[iB].actif=false;
	      this->nbBullets--;
	      continue;
	    }
	  catch(...)
	    {
	      printf("Erreur L210\n");
	    }
	  this->Bullets[iB].pos.x+=depX;
	  this->Bullets[iB].pos.y+=depY;
	  this->Bullets[iB].pos.z+=depZ;
	  this->Bullets[iB].distParcourue+=sqrt(depX*depX + depY*depY + depZ*depZ);

	  // Si la balle est rendu dans une paroi, on la fait exploser
	  if(this->Bullets[iB].distParcourue>this->Bullets[iB].distMur)
	    {
	      if(this->Bullets[iB].distMur<this->portee)
		{
		  Particule->AddSpark(this->Bullets[iB].pos,3);
		}
	      this->Bullets[iB].actif=false;
	      this->nbBullets--;
	      continue;
	    }
	  nB++;
	}
    }

  this->tLast-=GETTIMER;

}

void cWeapon::Aff(void)
{
  if(this->nbBullets==0)
    return;
  if(this->affTrainee)
    {
      glDisable(GL_TEXTURE_2D);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glColor3f(1,0,0);
      glBegin(GL_LINES);  
      for(int iB=0, nB=0 ; nB<this->nbBullets ; iB++)
	{
	  if(this->Bullets[iB].actif)
	    {
	      glVertex3f(this->Bullets[iB].pos.x-(this->Bullets[iB].depl.x*10),
			 this->Bullets[iB].pos.y-(this->Bullets[iB].depl.y*10),
			 this->Bullets[iB].pos.z-(this->Bullets[iB].depl.z*10));
	      glVertex3f(this->Bullets[iB].pos.x,
			 this->Bullets[iB].pos.y,
			 this->Bullets[iB].pos.z);
	      //printf("%d : %f %f %f (%f)\n",
	      //	 iB+1,
	      //     this->Bullets[iB].pos.x, this->Bullets[iB].pos.y, this->Bullets[iB].pos.z,
	      //     this->Bullets[iB].distParcourue);
	      nB++;
	    }
	}
      glEnd();
      //glDisable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
    }

  if(this->affBall)
    {
      glColor4f(1,1,1,0.9);
      Text->setTexture();

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);

      if(ISARB)
	{
	  glEnable (GL_POINT_SPRITE_ARB);
	  glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	  glPointSize (100);
	  glBegin (GL_POINTS);
	}

      else
	glBegin(GL_QUADS);  

      for(int iB=0, nB=0 ; nB<this->nbBullets ; iB++)
	if(this->Bullets[iB].actif)
	  {
	    affPoint(Bullets[iB].pos.x, Bullets[iB].pos.y, Bullets[iB].pos.z, taille);
	    nB++;
	  }
      glEnd();

      if(ISARB)
	glDisable (GL_POINT_SPRITE_ARB);
      glDisable(GL_BLEND);
      //glEnable (GL_DEPTH_TEST);
    }
}
