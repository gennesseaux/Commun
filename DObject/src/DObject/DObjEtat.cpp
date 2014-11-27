//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant la gestion des différents état que peut prendre un objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/6/2014 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "DObject/DObjEtat.h"


namespace DObject
{
	//! Constructeur par recopie
	CDObjEtat::CDObjEtat(const CDObjEtat& source)
	{
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObjEtat& CDObjEtat::operator=(const CDObjEtat& source)
	{
		if(this != &source)
		{
			ClonnerDonnees(source);
		}

		return *this;
	}

	////! Constructeur de déplacement
	//CDObjEtat::CDObjEtat(CDObjEtat&& source)
	//{
	//	m_bInitaliser = source.m_bInitaliser;
	//	m_bModifier = source.m_bModifier;
	//	m_bPourSupprimer = source.m_bPourSupprimer;
	//	m_bAcquis = source.m_bAcquis;
	//	m_bSupprimer = source.m_bSupprimer;

	//	source.m_bInitaliser = false;
	//	source.m_bModifier = false;
	//	source.m_bPourSupprimer = false;
	//	source.m_bAcquis = false;
	//	source.m_bSupprimer = false;
	//}

	////! Opérateur de déplacement
	//CDObjEtat& CDObjEtat::operator=(CDObjEtat&& source)
	//{
	//	if(this != &source)
	//	{
	//		m_bInitaliser = source.m_bInitaliser;
	//		m_bModifier = source.m_bModifier;
	//		m_bPourSupprimer = source.m_bPourSupprimer;
	//		m_bAcquis = source.m_bAcquis;
	//		m_bSupprimer = source.m_bSupprimer;

	//		source.m_bInitaliser = false;
	//		source.m_bModifier = false;
	//		source.m_bPourSupprimer = false;
	//		source.m_bAcquis = false;
	//		source.m_bSupprimer = false;
	//	}

	//	return *this;
	//}

	//! Opérateur ==
	bool CDObjEtat::operator==( const CDObjEtat &source ) const
	{
		return	m_bInitaliser==source.m_bInitaliser 
			&& m_bModifier==source.m_bModifier 
			&& m_bPourSupprimer == source.m_bPourSupprimer
			&& m_bAcquis == source.m_bAcquis
			&& m_bSupprimer == source.m_bSupprimer;
	}

	//! Opérateur !=
	bool CDObjEtat::operator!=( const CDObjEtat &source ) const
	{
		return !(*this == source);
	}

	//! Clone les données de l'objet.
	void CDObjEtat::ClonnerDonnees(const CDObjEtat &source)
	{
		m_bInitaliser		= source.m_bInitaliser;
		m_bModifier			= source.m_bModifier;
		m_bPourSupprimer	= source.m_bPourSupprimer;
		m_bAcquis			= source.m_bAcquis;
		m_bSupprimer		= source.m_bSupprimer;
	}

	bool CDObjEtat::EstInitialiser() const
	{
		return m_bInitaliser;
	}

	//! Indique si l'objet est initialisé
	void CDObjEtat::SetInitaliser( bool bInitaliser )
	{
		if(bInitaliser)
		{
			m_bInitaliser		= true;
			m_bSupprimer		= false;

			SetPourSupprimer(false);
		}
		else
		{
			m_bInitaliser		= false;
		}
	}

	bool CDObjEtat::EstModifier() const
	{
		return m_bModifier;
	}

	//! Indique si l'objet à été modifié
	void CDObjEtat::SetModifier(bool bModifier)
	{
		bool bNotifer = (m_bModifier != bModifier);

		m_bModifier = bModifier;

		// Notification
		if (bModifier && bNotifer)
			NotifierObservateur(NotificationEnfant::EnfantModifier);
	}

	bool CDObjEtat::SontEnfantsModifier() const
	{
		return m_bEnfantModifier;
	}

	void CDObjEtat::SetEnfantsModifier(bool bEnfantModifier)
	{
		m_bEnfantModifier = bEnfantModifier;
	}

	bool CDObjEtat::EstPourSupprimer() const
	{
		return m_bPourSupprimer;
	}

	//! Indique si l'objet est marqué pour suppression
	void CDObjEtat::SetPourSupprimer( bool bPourSupprimer )
	{
		bool bNotifer = (m_bPourSupprimer != bPourSupprimer);

		// Le changement d'état de suppression
		// implique que l'item est modifié.
		if (bNotifer)
			SetModifier(true);

		m_bPourSupprimer = bPourSupprimer;

		// Notification
		if (bNotifer)
			NotifierObservateur(NotificationEnfant::EnfantPourSupprimer);
	}

	bool CDObjEtat::EstAcquis() const
	{
		return m_bAcquis;
	}

	//! Indique si l'objet à été acquis
	void CDObjEtat::SetAcquis(bool bAcquis)
	{
		if (bAcquis)
		{
			m_bInitaliser		= true;
			m_bAcquis			= true;

			SetModifier(false);
			SetPourSupprimer(false);
		}
		else
		{
			m_bAcquis			= false;
		}
	}

	bool CDObjEtat::EstSupprimer() const
	{
		return m_bSupprimer;
	}

	//! Indique si l'objet à été supprimé
	void CDObjEtat::SetSupprimer(bool bSupprimer)
	{
		if (bSupprimer)
		{
			m_bSupprimer		= true;

			SetModifier(false);
			SetPourSupprimer(false);
		}
		else
		{
			m_bSupprimer		= false;
		}
	}

	//! Indique si l'objet est un nouvelle objet : c'est à dire en cours de création
	bool CDObjEtat::EstNouveau() const
	{
		return (!m_bAcquis && m_bModifier);
	}

	//! Force l'objet à croire qu'il est nouveau
	void CDObjEtat::SetNouveau()
	{
		m_bInitaliser		= false;
		m_bAcquis			= false;
		m_bSupprimer		= false;

		SetModifier(true);
		SetPourSupprimer(false);
	}

	//! Indique si l'objet peut être initialisé
	bool CDObjEtat::PeutEtreInitialiser()
	{
		// Un objet peut être initialisé si :
		//  - Il n'est pas initialisé

		return (!m_bInitaliser);
	}

	//! Indique si l'objet doit être initialisé
	bool CDObjEtat::DoitEtreInitialiser()
	{
		// Un objet doit être initialisé si :
		//  - Il n'est pas initialisé
		//  - Il n'est pas acquis
		//  - ou si il n'est pas marqué pour suppression
		//  - ou si il n'est pas nouveau

		return !(m_bInitaliser || m_bAcquis || m_bPourSupprimer || EstNouveau());
	}

	//! Indique si l'objet peut être sauvé
	bool CDObjEtat::PeutEtreSauver()
	{
		// Un objet peut être sauvé si :
		//  - Il n'est pas marqué pour suppression

		return (!m_bPourSupprimer);
	}

	//! Indique si l'objet peut être supprimé
	bool CDObjEtat::DoitEtreSauver()
	{
		// Un objet doit être sauvé si :
		//	- Il est modifié
		//  - Il n'est pas marqué pour suppression

		return ((m_bModifier || m_bEnfantModifier) && !m_bPourSupprimer);
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjEtat::PeutEtreSupprimer()
	{
		// Un objet peut être supprimé si :
		//  - Il est marqué pour suppression

		return (m_bPourSupprimer);
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjEtat::DoitEtreSupprimer()
	{
		// Un objet doit être supprimé si :
		//	- Il est acquis
		//  - Il est marqué pour suppression
		//	- Il est modifié
		//	- Il n'est pas supprimé

		return (m_bAcquis && m_bPourSupprimer && m_bModifier && !m_bSupprimer);
	}

}
