/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
***** except.cpp **** auteur : Vincent Tourraine ********
**                                                         **
** Classes liées à la gestion des exceptions               **
**                                                         **
*************************************************************/


// Erreur liée à la destruction d'un drone
class ErrDeleteDrone
{
	public :
		// Id du drone dont la destruction est concernée
		int id;

		ErrDeleteDrone(int Id);
		~ErrDeleteDrone(void);
};

ErrDeleteDrone::ErrDeleteDrone(int Id)
{
	this->id=Id;
}

ErrDeleteDrone::~ErrDeleteDrone(void)
{
	//
}

// Collision avec un crystal
class CollCrystal
{
	public :
		// Id du crystal concernée
		int id;

		CollCrystal(int Id);
		~CollCrystal(void);
};

CollCrystal::CollCrystal(int Id)
{
	this->id=Id;
}

CollCrystal::~CollCrystal(void)
{
	//
}

// Crystal récolté
class RecolCrystal
{
	public :
		// Id du crystal concernée
		int id;

		RecolCrystal(int Id);
		~RecolCrystal(void);
};

RecolCrystal::RecolCrystal(int Id)
{
	this->id=Id;
}

RecolCrystal::~RecolCrystal(void)
{
	//
}


// Erreur dans le chargement d'un fichier
class ErrFile
{
	public :
		char url[50+1];

		ErrFile(char*urlerr);
		~ErrFile(void);
};

ErrFile::ErrFile(char*urlerr)
{
	strcpy(this->url,urlerr);
	logOut("[!] Alerte : Fichier '%s' inexistant ou éroné\n");//,urlerr);
}

ErrFile::~ErrFile(void)
{
	//
}


