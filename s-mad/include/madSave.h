/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* madSave.hpp **** auteur : Vincent Tourraine *********
**                                                         **
**                                                         **
*************************************************************/


char saveMadModel(madModel * mad)
{
  int i=0, y=0;
  unsigned char id=MAD_ID;
  FILE* file=fopen(mad->Url,"w");

  if(file==NULL)
    return 0;
  fwrite(&id, sizeof(unsigned char), 1, file);

  fwrite(&(mad->nbTag), sizeof(int), 1, file);
  fwrite(&(mad->typeAnim), sizeof(char), 1, file);
  fwrite(&(mad->nbObjets), sizeof(int), 1, file);

  for(i=0 ; i<mad->nbObjets ; i++)
    {
      int y=0;

      fwrite(&(mad->Objets[i].texture), sizeof(char), 50, file);
      fwrite(&(mad->Objets[i].typeSurf), sizeof(char), 1, file);
      fwrite(&(mad->Objets[i].nbVertices), sizeof(int), 1, file);

      for(y=0 ; y<mad->Objets[i].nbVertices ; y++)
	{
	  fwrite(&(mad->Objets[i].Vertices[y].x), sizeof(float), 1, file);
	  fwrite(&(mad->Objets[i].Vertices[y].y), sizeof(float), 1, file);
	  fwrite(&(mad->Objets[i].Vertices[y].z), sizeof(float), 1, file);
	  fwrite(&(mad->Objets[i].Vertices[y].tx), sizeof(float), 1, file);
	  fwrite(&(mad->Objets[i].Vertices[y].ty), sizeof(float), 1, file);
	}
    }
  
  if(mad->nbTag>0)
    {
      fwrite(&(mad->Tag), sizeof(char), 1, file);
      switch(mad->Tag)
	{
	case 'D' :
	  // TAG de DRONE
	  fwrite(&(mad->nbClimats), sizeof(int), 1, file);
	  fwrite(&(mad->Drone[0]), sizeof(char), 1, file);
	  fwrite(&(mad->Depart.x),sizeof(float), 1, file);
	  break;
	case 'S' :
	  // TAG de SHOKER
	  fwrite(&(mad->nbShokers), sizeof(int), 1, file);
	  fwrite(&(mad->Depart.y),sizeof(float), 1, file);
	  fwrite(&(mad->nbDrones), sizeof(int), 1, file);
	  fwrite(&(mad->Depart.x),sizeof(float), 1, file);
	  fwrite(&(mad->Drone[0]), sizeof(char), 1, file);
	  break;
	case 'W' :
	  // TAG de WING
	  fwrite(&(mad->Nom), sizeof(char), 20, file);

	  fwrite(&(mad->LiqR),sizeof(float),1,file);
	  fwrite(&(mad->LiqG),sizeof(float),1,file);
	  fwrite(&(mad->LiqB),sizeof(float),1,file);
	  fwrite(&(mad->LiqAlpha),sizeof(float),1,file);
	  fwrite(&(mad->Liq),sizeof(float),1,file);

	  fwrite(&(mad->Weapons[0]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[1]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[2]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[3]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[4]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[5]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[6]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[7]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[8]), sizeof(int), 1, file);
	  fwrite(&(mad->Weapons[9]), sizeof(int), 1, file);

	  fwrite(&(mad->Description),sizeof(char),100,file);

	  fwrite(&(mad->nbShokers),sizeof(int),1,file);
	  fwrite(&(mad->Shoker), sizeof(char), 50, file);
	  for(i=0 ; i<mad->nbShokers ; i++)
	    {
	      fwrite(&(mad->Shokers[i].x),sizeof(float),1,file);
	      fwrite(&(mad->Shokers[i].y),sizeof(float),1,file);
	      fwrite(&(mad->Shokers[i].z),sizeof(float),1,file);
	      fwrite(&(mad->Drones[i].x),sizeof(float),1,file);
	    }
	  break;
	case 'M' :
	  // TAG de MAP
	  fwrite(&(mad->Nom), sizeof(char), 20, file);
	  fwrite(&(mad->nbClimats), sizeof(int), 1, file);
	  for(y=0 ; y<mad->nbClimats ; y++)
	    fwrite(&(mad->Climats[y]), sizeof(char), 1, file);

	  fwrite(&(mad->Drone), sizeof(char), 50, file);
	  fwrite(&(mad->nbDrones), sizeof(int), 1, file);
	  for(y=0 ; y<mad->nbDrones ; y++)
	    {
	      fwrite(&(mad->Drones[y].x),sizeof(float),1,file);
	      fwrite(&(mad->Drones[y].y),sizeof(float),1,file);
	      fwrite(&(mad->Drones[y].z),sizeof(float),1,file);
	    }
	  fwrite(&(mad->Shoker), sizeof(char), 50, file);
	  fwrite(&(mad->nbShokers), sizeof(int), 1, file);
	  for(y=0 ; y<mad->nbShokers ; y++)
	    {
	      fwrite(&(mad->Shokers[y].x),sizeof(float),1,file);
	      fwrite(&(mad->Shokers[y].y),sizeof(float),1,file);
	      fwrite(&(mad->Shokers[y].z),sizeof(float),1,file);
	    }

	  fwrite(&(mad->Depart.x),sizeof(float),1,file);
	  fwrite(&(mad->Depart.y),sizeof(float),1,file);
	  fwrite(&(mad->Depart.z),sizeof(float),1,file);

	  fwrite(&(mad->Liq),sizeof(float),1,file);
	  fwrite(&(mad->LiqMin),sizeof(float),1,file);
	  fwrite(&(mad->LiqMax),sizeof(float),1,file);
	  fwrite(&(mad->LiqTexture), sizeof(char), 50, file);
	  fwrite(&(mad->LiqR),sizeof(float),1,file);
	  fwrite(&(mad->LiqG),sizeof(float),1,file);
	  fwrite(&(mad->LiqB),sizeof(float),1,file);
	  fwrite(&(mad->LiqAlpha),sizeof(float),1,file);

	  fwrite(&(mad->LimitXMin),sizeof(float),1,file);
	  fwrite(&(mad->LimitXMax),sizeof(float),1,file);
	  fwrite(&(mad->LimitYMin),sizeof(float),1,file);
	  fwrite(&(mad->LimitYMax),sizeof(float),1,file);
	  fwrite(&(mad->LimitZMin),sizeof(float),1,file);
	  fwrite(&(mad->LimitZMax),sizeof(float),1,file);

	  fwrite(&(mad->Description),sizeof(char),100,file);

	  break;
	}
    }

  return 1;
}
