/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** inout.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Fonctions liées aux traitements d'entrée/sortie (in/out)**
**                                                         **
*************************************************************/

int getNbFromMadMap(char * url, char what='C', int which=1) throw (ErrFile)
{
	int nb=0, nbtag=0;

	FILE * fOut=fopen(url,"r");
	if(fOut==NULL)
		throw ErrFile(url);

	unsigned char control;
	fread(&control,sizeof(unsigned char),1,fOut);
	if(control!=136)
		throw ErrFile(url);

	fread(&nbtag,sizeof(int),1,fOut);
	if(nbtag==0)
	  return 0;

	fseek(fOut, sizeof(char), SEEK_CUR);
	int nbsurf=0;
	fread(&nbsurf,sizeof(int),1,fOut);
	for(int i=0 ; i<nbsurf ; i++)
	  {
	    fseek(fOut, sizeof(char)*51, SEEK_CUR);
	    int nbvertices=0;
	    fread(&nbvertices,sizeof(int),1,fOut);
	    fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
	  }

	char tag;
	fread(&tag, sizeof(char),1,fOut);
	if(tag!='M')
	{
	  fclose(fOut);
	  throw ErrFile(url);
	}

	fseek(fOut, sizeof(char)*20, SEEK_CUR);

	fread(&nb, sizeof(int), 1, fOut);
	if(what=='C')
	  {
	    fclose(fOut);
	    return nb;
	  }
	
	fseek(fOut, sizeof(char)*nb, SEEK_CUR);

	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	if(what=='D')
	  {
	    fclose(fOut);
	    return nb;
	  }
	fseek(fOut, (sizeof(float)*3)*nb, SEEK_CUR);

	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	if(what=='S')
	  {
	    fclose(fOut);
	    return nb;
	  }
	fseek(fOut, (sizeof(float)*3)*(nb+3), SEEK_CUR);
       

	float fl;
	fread(&fl,sizeof(float),1,fOut);
	if(what=='L')
	  {
	    fclose(fOut);
	    return int(fl);
	  }
	fseek(fOut, sizeof(float)*2, SEEK_CUR);
	
	fclose(fOut);

	return nb;
}
float getRealFromMadMap(char * url, char what='C', int which=1) throw (ErrFile)
{
	int nb=0, nbtag=0;

	FILE * fOut=fopen(url,"r");
	if(fOut==NULL)
		throw ErrFile(url);

	unsigned char control;
	fread(&control,sizeof(unsigned char),1,fOut);
	if(control!=136)
		throw ErrFile(url);

	fread(&nbtag,sizeof(int),1,fOut);
	if(nbtag==0)
	  return 0;

	fseek(fOut, sizeof(char), SEEK_CUR);
	int nbsurf=0;
	fread(&nbsurf,sizeof(int),1,fOut);
	for(int i=0 ; i<nbsurf ; i++)
	  {
	    fseek(fOut, sizeof(char)*51, SEEK_CUR);
	    int nbvertices=0;
	    fread(&nbvertices,sizeof(int),1,fOut);
	    fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
	  }

	char tag;
	fread(&tag, sizeof(char),1,fOut);
	if(tag!='M')
	{
	  fclose(fOut);
	  throw ErrFile(url);
	}

	fseek(fOut, sizeof(char)*20, SEEK_CUR);

	fread(&nb, sizeof(int), 1, fOut);
	fseek(fOut, sizeof(char)*nb, SEEK_CUR);

	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	fseek(fOut, (sizeof(float)*3)*nb, SEEK_CUR);

	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	fseek(fOut, (sizeof(float)*3)*(nb), SEEK_CUR);
       
	if(what=='P')
	  {
	    fseek(fOut,sizeof(float)*(which-1),SEEK_CUR);
	    float fp;
	    fread(&fp,sizeof(float),1,fOut);
	    fclose(fOut);
	    return fp;
	  }
	else
	  {
	    fseek(fOut,sizeof(float)*3,SEEK_CUR);
	  }

	float fl;
	fread(&fl,sizeof(float),1,fOut);
	if(what=='L'&&which==1)
	  {
	    fclose(fOut);
	    return fl;
	  }
	fread(&fl,sizeof(float),1,fOut);
	if(what=='L'&&which==2)
	  {
	    fclose(fOut);
	    return fl;
	  }
	fread(&fl,sizeof(float),1,fOut);
	if(what=='L'&&which==3)
	  {
	    fclose(fOut);
	    return fl;
	  }
	fseek(fOut,sizeof(char)*50,SEEK_CUR);
	if(what=='K')
	  {
	    for(int i=1 ; i<=4 ; i++)
	      {
		float f2;
		fread(&f2,sizeof(float),1,fOut);
		if(which==i&&what=='K')
		  {
		    fclose(fOut);
		    return f2;
		  }
	      }
	  }
	fseek(fOut,sizeof(float)*4,SEEK_CUR);

	if(what=='B')
	  {
	    for(int i=1 ; i<=6 ; i++)
	      {
		float f2;
		fread(&f2,sizeof(float),1,fOut);
		if(which==i&&what=='B')
		  {
		    fclose(fOut);
		    return f2;
		  }
	      }
	  }

	fclose(fOut);

	return nb;
}

vertex getVertexFromMadMap(char * url, char what='C', int which=1) throw (ErrFile)
{
	int nb=0, nbtag=0;
	vertex v(0,0,0);

	FILE * fOut=fopen(url,"r");
	if(fOut==NULL)
		throw ErrFile(url);

	unsigned char control;
	fread(&control,sizeof(unsigned char),1,fOut);
	if(control!=136)
		throw ErrFile(url);

	fread(&nbtag,sizeof(int),1,fOut);
	if(nbtag==0)
	  return vertex(0,0,0);

	fseek(fOut, sizeof(char), SEEK_CUR);
	int nbsurf=0;
	fread(&nbsurf,sizeof(int),1,fOut);
	for(int i=0 ; i<nbsurf ; i++)
	  {
	    fseek(fOut, sizeof(char)*51, SEEK_CUR);
	    int nbvertices=0;
	    fread(&nbvertices,sizeof(int),1,fOut);
	    fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
	  }

	char tag;
	fread(&tag, sizeof(char),1,fOut);
	if(tag!='M')
	{
	  fclose(fOut);
	  return vertex(0,0,0);
	}

	fseek(fOut, sizeof(char)*20, SEEK_CUR);

	fread(&nb, sizeof(int), 1, fOut);
	fseek(fOut, sizeof(char)*nb, SEEK_CUR);

	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	if(what=='D')
	  {
	    if(which>nb)
	      which=1;
	    for(int y=0 ; y<nb ; y++)
	      {
		if(which==y+1)
		  {
		    fread(&v.x,sizeof(float),1,fOut);
		    fread(&v.y,sizeof(float),1,fOut);
		    fread(&v.z,sizeof(float),1,fOut);
		    fclose(fOut);
		    return v;
		  }
		fseek(fOut, sizeof(float)*3,SEEK_CUR);
	      }
	  }
	fseek(fOut, (sizeof(float)*3)*nb, SEEK_CUR);

	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	if(what=='S')
	  {
	    if(which>nb)
	      which=1;
	    for(int y=0 ; y<nb ; y++)
	      {
		if(which==y+1)
		  {
		    fread(&v.x,sizeof(float),1,fOut);
		    fread(&v.y,sizeof(float),1,fOut);
		    fread(&v.z,sizeof(float),1,fOut);
		    fclose(fOut);
		    return v;
		  }
		fseek(fOut, sizeof(float)*3,SEEK_CUR);
	      }
	  }
	fseek(fOut, (sizeof(float)*3)*nb, SEEK_CUR);
       
	
	if(what=='P')
	{
	  fread(&(v.x),sizeof(float),1,fOut);
	  fread(&(v.y),sizeof(float),1,fOut);
	  fread(&(v.z),sizeof(float),1,fOut);

	  fclose(fOut);
	  return v;
	}

	fseek(fOut,sizeof(float)*3,SEEK_CUR);

	if(what=='L')
	  {
	    float fl;
	    fread(&fl,sizeof(float),1,fOut);
	    fclose(fOut);
	    return vertex(fl,fl,fl);
	  }


	fclose(fOut);

	return v;
}

char * getStrFromMadMap(char * url, char what='C', int which=1) throw (ErrFile)
{
	int nb=0, nbtag=0;
	
	FILE * fOut=fopen(url,"r");
	if(fOut==NULL)
		throw ErrFile(url);

	unsigned char control;
	fread(&control,sizeof(unsigned char),1,fOut);
	if(control!=136)
		throw ErrFile(url);

	fread(&nbtag,sizeof(int),1,fOut);
	if(nbtag==0)
	  return NULL;

	fseek(fOut, sizeof(char), SEEK_CUR);
	int nbsurf=0;
	fread(&nbsurf,sizeof(int),1,fOut);
	for(int i=0 ; i<nbsurf ; i++)
	  {
	    fseek(fOut, sizeof(char)*51, SEEK_CUR);
	    int nbvertices=0;
	    fread(&nbvertices,sizeof(int),1,fOut);
	    fseek(fOut, sizeof(float)*5*nbvertices, SEEK_CUR);
	  }

	char tag;
	fread(&tag, sizeof(char),1,fOut);
	if(tag!='M')
	{
	  fclose(fOut);
	  return NULL;
	}

	if(what=='n')
	  {
	    char *na=new char[21];
	    fread(na,sizeof(char),20,fOut);
	    fclose(fOut);
	    return na;
	  }
	fseek(fOut, sizeof(char)*20, SEEK_CUR);

	fread(&nb, sizeof(int), 1, fOut);
	if(what=='C')
	  {
	    if(which>nb)
	      which=1;
	    for(int y=0 ; y<nb ; y++)
	      {
		if(which==y+1)
		  {
		    char * ca=new char;
		    fread(ca,sizeof(char),1,fOut);
		    fclose(fOut);
		    return ca;
		  }
		fseek(fOut, sizeof(char),SEEK_CUR);
	      }
	  }
	fseek(fOut, sizeof(char)*nb, SEEK_CUR);

	if(what=='D')
	  {
	    char *urld=new char[51];
	    fread(urld,sizeof(char),50,fOut);
	    fclose(fOut);
	    return urld;
	  }
	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	fseek(fOut, (sizeof(float)*3)*nb, SEEK_CUR);

	if(what=='S')
	  {
	    char *urls=new char[51];
	    fread(urls,sizeof(char),50,fOut);
	    fclose(fOut);
	    return urls;
	  }
	fseek(fOut, sizeof(char)*50, SEEK_CUR);
	fread(&nb, sizeof(int), 1, fOut);
	fseek(fOut, (sizeof(float)*3)*(nb+1)+(sizeof(float)*3), SEEK_CUR);
       

	if(what=='L')
	  {
	    char *urlL=new char[51];
	    fread(urlL,sizeof(char),50,fOut);
	    fclose(fOut);
	    return urlL;
	  }
	fseek(fOut,sizeof(char)*50+(sizeof(float)*10),SEEK_CUR);

	if(what=='F')
	  {
	    char * desc=new char[100];
	    fread(desc,sizeof(char),100,fOut);
	    fclose(fOut);
	    return desc;
	  }
	fclose(fOut);

	return NULL;
}
