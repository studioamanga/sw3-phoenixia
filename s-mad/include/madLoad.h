/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* madLoad.hpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/


madModel * loadMadModel(char * url)
{
  int i=0;
  FILE* file;
  unsigned char id;
  madModel* mad=NULL;

  file=fopen(url,"r");
  if(file==NULL)
    return NULL;

  fread(&id, sizeof(unsigned char), 1, file);
  if(id!=MAD_ID)
    return NULL;

  mad=(madModel *)malloc(sizeof(madModel));
  strcpy(mad->Url,url);

  fread(&(mad->nbTag), sizeof(int), 1, file);
  fread(&(mad->typeAnim), sizeof(char), 1, file);
  fread(&(mad->nbObjets), sizeof(int), 1, file);

  mad->Objets=(sObjet *)malloc(sizeof(sObjet)*mad->nbObjets);
  for(i=0 ; i<mad->nbObjets ; i++)
    {
      fread(&(mad->Objets[i].texture), sizeof(char), 50, file);
      fread(&(mad->Objets[i].typeSurf), sizeof(char), 1, file);
      fread(&(mad->Objets[i].nbVertices), sizeof(int), 1, file);

      mad->Objets[i].Vertices=(Vertex *)malloc(sizeof(Vertex)*mad->Objets[i].nbVertices);
      int y=0;
      for(y=0 ; y<mad->Objets[i].nbVertices ; y++)
	{
	  fread(&(mad->Objets[i].Vertices[y].x), sizeof(float), 1, file);
	  fread(&(mad->Objets[i].Vertices[y].y), sizeof(float), 1, file);
	  fread(&(mad->Objets[i].Vertices[y].z), sizeof(float), 1, file);
	  fread(&(mad->Objets[i].Vertices[y].tx), sizeof(float), 1, file);
	  fread(&(mad->Objets[i].Vertices[y].ty), sizeof(float), 1, file);
	}
    }
  
  if(mad->nbTag>0)
    {
      fread(&(mad->Tag), sizeof(char), 1, file);
      switch(mad->Tag)
	{
	case 'D' :
	  // TAG de DRONE
	  // valeur
	  fread(&(mad->nbClimats), sizeof(int), 1, file);
	  // type
	  fread(&(mad->Drone[0]), sizeof(char), 1, file);
	  // taille
	  fread(&(mad->Depart.x),sizeof(float), 1, file);
	  break;
	case 'S' :
	  // TAG de SHOKER
	  // attaque
	  fread(&(mad->nbShokers), sizeof(int), 1, file);
	  // vitesse
	  fread(&(mad->Depart.y),sizeof(float), 1, file);
	  // défense
	  fread(&(mad->nbDrones), sizeof(int), 1, file);
	  // taille
	  fread(&(mad->Depart.x),sizeof(float), 1, file);
	  // type
	  fread(&(mad->Drone[0]), sizeof(char), 1, file);
	  break;
	case 'W' :
	  // TAG de WING
	  fread(&(mad->Nom), sizeof(char), 20, file);

	  fread(&(mad->LiqR),sizeof(float),1,file);
	  fread(&(mad->LiqG),sizeof(float),1,file);
	  fread(&(mad->LiqB),sizeof(float),1,file);
	  fread(&(mad->LiqAlpha),sizeof(float),1,file);
	  fread(&(mad->Liq),sizeof(float),1,file);

	  fread(&(mad->Weapons[0]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[1]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[2]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[3]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[4]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[5]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[6]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[7]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[8]), sizeof(int), 1, file);
	  fread(&(mad->Weapons[9]), sizeof(int), 1, file);

	  fread(&(mad->Description),sizeof(char),100,file);

	  fread(&(mad->nbShokers),sizeof(int),1,file);
	  fread(&(mad->Shoker), sizeof(char), 50, file);
	  mad->Drones=(Vertex3f*)malloc(mad->nbShokers*sizeof(Vertex3f));
	  mad->Shokers=(Vertex3f*)malloc(mad->nbShokers*sizeof(Vertex3f));
	  int i;
	  for(i=0 ; i<mad->nbShokers ; i++)
	    {
	      fread(&(mad->Shokers[i].x),sizeof(float),1,file);
	      fread(&(mad->Shokers[i].y),sizeof(float),1,file);
	      fread(&(mad->Shokers[i].z),sizeof(float),1,file);
	      fread(&(mad->Drones[i].x),sizeof(float),1,file);
	    }
	  break;
	case 'M' :
	  // TAG de MAP
	  fread(&(mad->Nom), sizeof(char), 20, file);
	  fread(&(mad->nbClimats), sizeof(int), 1, file);
	  mad->Climats=(char *) malloc(sizeof(char)*mad->nbClimats);
	  int y=0;
	  for(y=0 ; y<mad->nbClimats ; y++)
	    fread(&(mad->Climats[y]), sizeof(char), 1, file);

	  fread(&(mad->Drone), sizeof(char), 50, file);
	  fread(&(mad->nbDrones), sizeof(int), 1, file);
	  mad->Drones=(Vertex3f *) malloc(sizeof(Vertex3f)*mad->nbDrones);
	  for(y=0 ; y<mad->nbDrones ; y++)
	    {
	      fread(&(mad->Drones[y].x),sizeof(float),1,file);
	      fread(&(mad->Drones[y].y),sizeof(float),1,file);
	      fread(&(mad->Drones[y].z),sizeof(float),1,file);
	    }
	  fread(&(mad->Shoker), sizeof(char), 50, file);
	  fread(&(mad->nbShokers), sizeof(int), 1, file);
	  mad->Shokers=(Vertex3f *) malloc(sizeof(Vertex3f)*mad->nbShokers);
	  for(y=0 ; y<mad->nbShokers ; y++)
	    {
	      fread(&(mad->Shokers[y].x),sizeof(float),1,file);
	      fread(&(mad->Shokers[y].y),sizeof(float),1,file);
	      fread(&(mad->Shokers[y].z),sizeof(float),1,file);
	    }

	  fread(&(mad->Depart.x),sizeof(float),1,file);
	  fread(&(mad->Depart.y),sizeof(float),1,file);
	  fread(&(mad->Depart.z),sizeof(float),1,file);

	  fread(&(mad->Liq),sizeof(float),1,file);
	  fread(&(mad->LiqMin),sizeof(float),1,file);
	  fread(&(mad->LiqMax),sizeof(float),1,file);
	  fread(&(mad->LiqTexture), sizeof(char), 50, file);
	  fread(&(mad->LiqR),sizeof(float),1,file);
	  fread(&(mad->LiqG),sizeof(float),1,file);
	  fread(&(mad->LiqB),sizeof(float),1,file);
	  fread(&(mad->LiqAlpha),sizeof(float),1,file);

	  fread(&(mad->LimitXMin),sizeof(float),1,file);
	  fread(&(mad->LimitXMax),sizeof(float),1,file);
	  fread(&(mad->LimitYMin),sizeof(float),1,file);
	  fread(&(mad->LimitYMax),sizeof(float),1,file);
	  fread(&(mad->LimitZMin),sizeof(float),1,file);
	  fread(&(mad->LimitZMax),sizeof(float),1,file);

	  fread(&(mad->Description),sizeof(char),100,file);
	  
	  break;
	}
    }

  fclose(file);

  return mad;
}
