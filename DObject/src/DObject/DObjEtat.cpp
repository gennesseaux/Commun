//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant la gestion des diff�rents �tat que peut prendre un objet
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	17/6/2014 : 
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

	//! Op�rateur =
	CDObjEtat& CDObjEtat::operator=(const CDObjEtat& source)
	{
		if(this != &source)
		{
			ClonnerDonnees(source);
		}

		return *this;
	}

	////! Constructeur de d�placement
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

	////! Op�rateur de d�placement
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

	//! Op�rateur ==
	bool CDObjEtat::operator==( const CDObjEtat &source ) const
	{
		return	m_bInitaliser==source.m_bInitaliser 
			&& m_bModifier==source.m_bModifier 
			&& m_bPourSupprimer == source.m_bPourSupprimer
			&& m_bAcquis == source.m_bAcquis
			&& m_bSupprimer == source.m_bSupprimer;
	}

	//! Op�rateur !=
	bool CDObjEtat::operator!=( const CDObjEtat &source ) const
	{
		return !(*this == source);
	}

	//! Clone les donn�es de l'objet.
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

	//! Indique si l'objet est initialis�
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

	//! Indique si l'objet � �t� modifi�
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

	//! Indique si l'objet est marqu� pour suppression
	void CDObjEtat::SetPourSupprimer( bool bPourSupprimer )
	{
		bool bNotifer = (m_bPourSupprimer != bPourSupprimer);

		// Le changement d'�tat de suppression
		// implique que l'item est modifi�.
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

	//! Indique si l'objet � �t� acquis
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

	//! Indique si l'objet � �t� supprim�
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

	//! Indique si l'objet est un nouvelle objet : c'est � dire en cours de cr�ation
	bool CDObjEtat::EstNouveau() const
	{
		return (!m_bAcquis && m_bModifier);
	}

	//! Force l'objet � croire qu'il est nouveau
	void CDObjEtat::SetNouveau()
	{
		m_bInitaliser		= false;
		m_bAcquis			= false;
		m_bSupprimer		= false;

		SetModifier(true);
		SetPourSupprimer(false);
	}

	//! Indique si l'objet peut �tre initialis�
	bool CDObjEtat::PeutEtreInitialiser()
	{
		// Un objet peut �tre initialis� si :
		//  - Il n'est pas initialis�

		return (!m_bInitaliser);
	}

	//! Indique si l'objet doit �tre initialis�
	bool CDObjEtat::DoitEtreInitialiser()
	{
		// Un objet doit �tre initialis� si :
		//  - Il n'est pas initialis�
		//  - Il n'est pas acquis
		//  - ou si il n'est pas marqu� pour suppression
		//  - ou si il n'est pas nouveau

		return !(m_bInitaliser || m_bAcquis || m_bPourSupprimer || EstNouveau());
	}

	//! Indique si l'objet peut �tre sauv�
	bool CDObjEtat::PeutEtreSauver()
	{
		// Un objet peut �tre sauv� si :
		//  - Il n'est pas marqu� pour suppression

		return (!m_bPourSupprimer);
	}

	//! Indique si l'objet peut �tre supprim�
	bool CDObjEtat::DoitEtreSauver()
	{
		// Un objet doit �tre sauv� si :
		//	- Il est modifi�
		//  - Il n'est pas marqu� pour suppression

		return ((m_bModifier || m_bEnfantModifier) && !m_bPourSupprimer);
	}

	//! Indique si l'objet doit �tre sauv�
	bool CDObjEtat::PeutEtreSupprimer()
	{
		// Un objet peut �tre supprim� si :
		//  - Il est marqu� pour suppression

		return (m_bPourSupprimer);
	}

	//! Indique si l'objet doit �tre sauv�
	bool CDObjEtat::DoitEtreSupprimer()
	{
		// Un objet doit �tre supprim� si :
		//	- Il est acquis
		//  - Il est marqu� pour suppression
		//	- Il est modifi�
		//	- Il n'est pas supprim�

		return (m_bAcquis && m_bPourSupprimer && m_bModifier && !m_bSupprimer);
	}

}
