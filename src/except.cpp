/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
***** except.cpp **** auteur : Vincent Tourraine ********
**                                                         **
** Classes li�es � la gestion des exceptions               **
**                                                         **
*************************************************************/


// Erreur li�e � la destruction d'un drone
class ErrDeleteDrone
{
	public :
		// Id du drone dont la destruction est concern�e
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
		// Id du crystal concern�e
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

// Crystal r�colt�
class RecolCrystal
{
	public :
		// Id du crystal concern�e
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
	logOut("[!] Alerte : Fichier '%s' inexistant ou �ron�\n");//,urlerr);
}

ErrFile::~ErrFile(void)
{
	//
}


