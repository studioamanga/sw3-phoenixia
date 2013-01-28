//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file util_timer.cpp
//! \brief D�finition de la classe CTimer, un gestionnaire d'�coulement du temps
// Modifi� par Studio AMANGA
//////////////////////////////////////////////////////////////////////////////



//! Le gestionnaire d'�coulement du temps
class CTimer 
{
private:
	long int m_fStartTime;

public:
	CTimer ();
	
	//! Initialise le timer � 0
	void Init ();
	//! Retourne le temps en second �coul� depuis la derni�re initialisation
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

// Retourne le temps ecoul� depuis la derni�re initialisation
long int CTimer::GetTime () const
{
	return (static_cast<long int> (GETTIME - m_fStartTime));
}
