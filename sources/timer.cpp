//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file util_timer.cpp
//! \brief Définition de la classe CTimer, un gestionnaire d'écoulement du temps
// Modifié par Studio AMANGA
//////////////////////////////////////////////////////////////////////////////



//! Le gestionnaire d'écoulement du temps
class CTimer 
{
private:
	long int m_fStartTime;

public:
	CTimer ();
	
	//! Initialise le timer à 0
	void Init ();
	//! Retourne le temps en second écoulé depuis la dernière initialisation
	long int GetTime () const;
};

CTimer::CTimer ()
{

}

// Initialisation du timer
void CTimer::Init ()
{
	m_fStartTime = GETTIME;
}

// Retourne le temps ecoulé depuis la dernière initialisation
long int CTimer::GetTime () const
{
	return (static_cast<long int> (GETTIME - m_fStartTime));
}
