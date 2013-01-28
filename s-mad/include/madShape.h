/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******* madShape.h **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

// Ajoute à un model Mad un tunnel
// Motif : (z,y,ty)
// Vertices : (x,y,z / sz,sy,ry)
void madAddTunnel(madModel * mad, int motifNbVertices, Vertex3f * motifVertices, char * urlTexture, float factTexture, float factPos, int nbVertices, Vertex3f * verticesPos, Vertex3f * verticesScaleNRot)
{
  int iV=0, iM=0, curV=0;
  float last=0;
  factTexture=factTexture*0.01;
  mad->Objets=(sObjet *)realloc(mad->Objets, sizeof(sObjet)*(mad->nbObjets+1));
  strcpy(mad->Objets[mad->nbObjets].texture, urlTexture);
  mad->Objets[mad->nbObjets].typeSurf='Q';
  mad->Objets[mad->nbObjets].nbVertices=(nbVertices-1)*(motifNbVertices-1)*4;
  mad->Objets[mad->nbObjets].Vertices=(Vertex *)malloc(sizeof(Vertex)*mad->Objets[mad->nbObjets].nbVertices);

  for(iM=0 ; iM<(nbVertices-1) ; iM++)
    {
      float dist=sqrt((verticesPos[iM].x-verticesPos[iM+1].x)*(verticesPos[iM].x-verticesPos[iM+1].x)*factPos*factPos+
		      (verticesPos[iM].y-verticesPos[iM+1].y)*(verticesPos[iM].y-verticesPos[iM+1].y)*factPos*factPos+
		      (verticesPos[iM].z-verticesPos[iM+1].z)*(verticesPos[iM].z-verticesPos[iM+1].z)*factPos*factPos);
      dist=dist*factTexture+last;
      for(iV=0 ; iV<(motifNbVertices-1) ; iV++)
	{
	  mad->Objets[mad->nbObjets].Vertices[curV].x=factPos*(
	    verticesPos[iM].x+(motifVertices[iV].x*verticesScaleNRot[iM].x*sin(verticesScaleNRot[iM].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV].y=factPos*(
	    verticesPos[iM].y+(motifVertices[iV].y*verticesScaleNRot[iM].y));
	  mad->Objets[mad->nbObjets].Vertices[curV].z=factPos*(
	    verticesPos[iM].z+(motifVertices[iV].x*verticesScaleNRot[iM].x*cos(verticesScaleNRot[iM].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV].tx=0;
	  mad->Objets[mad->nbObjets].Vertices[curV].ty=motifVertices[iV].z;

	  mad->Objets[mad->nbObjets].Vertices[curV+1].x=factPos*(
	    verticesPos[iM].x+(motifVertices[iV+1].x*verticesScaleNRot[iM].x*sin(verticesScaleNRot[iM].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV+1].y=factPos*(
	    verticesPos[iM].y+(motifVertices[iV+1].y*verticesScaleNRot[iM].y));
	  mad->Objets[mad->nbObjets].Vertices[curV+1].z=factPos*(
	    verticesPos[iM].z+(motifVertices[iV+1].x*verticesScaleNRot[iM].x*cos(verticesScaleNRot[iM].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV+1].tx=0;
	  mad->Objets[mad->nbObjets].Vertices[curV+1].ty=motifVertices[iV+1].z;

	  mad->Objets[mad->nbObjets].Vertices[curV+2].x=factPos*(
	    verticesPos[iM+1].x+(motifVertices[iV+1].x*verticesScaleNRot[iM+1].x*sin(verticesScaleNRot[iM+1].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV+2].y=factPos*(
	    verticesPos[iM+1].y+(motifVertices[iV+1].y*verticesScaleNRot[iM+1].y));
	  mad->Objets[mad->nbObjets].Vertices[curV+2].z=factPos*(
	    verticesPos[iM+1].z+(motifVertices[iV+1].x*verticesScaleNRot[iM+1].x*cos(verticesScaleNRot[iM+1].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV+2].tx=dist;
	  mad->Objets[mad->nbObjets].Vertices[curV+2].ty=motifVertices[iV+1].z;

	  mad->Objets[mad->nbObjets].Vertices[curV+3].x=factPos*(
	    verticesPos[iM+1].x+(motifVertices[iV].x*verticesScaleNRot[iM+1].x*sin(verticesScaleNRot[iM+1].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV+3].y=factPos*(
	    verticesPos[iM+1].y+(motifVertices[iV].y*verticesScaleNRot[iM+1].y));
	  mad->Objets[mad->nbObjets].Vertices[curV+3].z=factPos*(
	    verticesPos[iM+1].z+(motifVertices[iV].x*verticesScaleNRot[iM+1].x*cos(verticesScaleNRot[iM+1].z*0.017453)));
	  mad->Objets[mad->nbObjets].Vertices[curV+3].tx=dist;
	  mad->Objets[mad->nbObjets].Vertices[curV+3].ty=motifVertices[iV].z;
	  curV+=4;
	}
      last=dist;
    }

  mad->nbObjets++;
  return;
}
