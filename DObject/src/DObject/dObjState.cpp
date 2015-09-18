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
#include "DObject/DObjState.h"


namespace DObject
{
	//! Constructeur par recopie
	CDObjState::CDObjState(const CDObjState& source)
	{
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObjState& CDObjState::operator=(const CDObjState& source)
	{
		if(this != &source)
			ClonnerDonnees(source);

		return *this;
	}

	//! Clone les données de l'objet.
	void CDObjState::ClonnerDonnees(const CDObjState &source)
	{
		m_bInitaliser		= source.m_bInitaliser;
		m_bModifier			= source.m_bModifier;
		m_bPourSupprimer	= source.m_bPourSupprimer;
		m_bAcquis			= source.m_bAcquis;
		m_bSupprimer		= source.m_bSupprimer;
	}

	//! Opérateur ==
	bool CDObjState::operator==( const CDObjState &source ) const
	{
		return	m_bInitaliser==source.m_bInitaliser 
			&& m_bModifier==source.m_bModifier 
			&& m_bPourSupprimer == source.m_bPourSupprimer
			&& m_bAcquis == source.m_bAcquis
			&& m_bSupprimer == source.m_bSupprimer;
	}

	//! Opérateur !=
	bool CDObjState::operator!=( const CDObjState &source ) const
	{
		return !(*this == source);
	}

	bool CDObjState::EstInitialiser() const
	{
		return m_bInitaliser;
	}

	//! Indique si l'objet est initialisé
	void CDObjState::SetInitaliser( bool bInitaliser )
	{
		if(bInitaliser)
		{
			m_bInitaliser		= true;
			m_bModifier			= false;
			m_bSupprimer		= false;

			SetPourSupprimer(false);
		}
		else
		{
			m_bInitaliser		= false;
		}
	}

	bool CDObjState::EstModifier() const
	{
		return m_bModifier;
	}

	//! Indique si l'objet à été modifié
	void CDObjState::SetModifier(bool bModifier)
	{
		bool bNotifer = (m_bModifier != bModifier);

		m_bModifier = bModifier;
	}

	bool CDObjState::SontEnfantsModifier() const
	{
		return m_bEnfantModifier;
	}

	void CDObjState::SetEnfantsModifier(bool bEnfantModifier)
	{
		m_bEnfantModifier = bEnfantModifier;
	}

	bool CDObjState::EstPourSupprimer() const
	{
		return m_bPourSupprimer;
	}

	//! Indique si l'objet est marqué pour suppression
	void CDObjState::SetPourSupprimer( bool bPourSupprimer )
	{
		bool bNotifer = (m_bPourSupprimer != bPourSupprimer);

		// Le changement d'état de suppression
		// implique que l'item est modifié.
		if (bNotifer)
			SetModifier(true);

		m_bPourSupprimer = bPourSupprimer;
	}

	bool CDObjState::EstAcquis() const
	{
		return m_bAcquis;
	}

	//! Indique si l'objet à été acquis
	void CDObjState::SetAcquis(bool bAcquis)
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

	bool CDObjState::EstSupprimer() const
	{
		return m_bSupprimer;
	}

	//! Indique si l'objet à été supprimé
	void CDObjState::SetSupprimer(bool bSupprimer)
	{
		if (bSupprimer)
		{
			m_bSupprimer		= true;

			m_bModifier			= false;
			m_bPourSupprimer	= false;
		}
		else
		{
			m_bSupprimer		= false;
		}
	}

	//! Indique si l'objet est un nouvelle objet : c'est à dire en cours de création
	bool CDObjState::EstNouveau() const
	{
		return (!m_bAcquis && m_bModifier);
	}

	//! Force l'objet à croire qu'il est nouveau
	void CDObjState::SetNouveau()
	{
		m_bInitaliser		= false;
		m_bAcquis			= false;
		m_bSupprimer		= false;

		SetModifier(true);
		SetPourSupprimer(false);
	}

	//! Indique si l'objet peut être initialisé
	bool CDObjState::PeutEtreInitialiser()
	{
		// Un objet peut être initialisé si :
		//  - Il n'est pas initialisé

		return (!m_bInitaliser);
	}

	//! Indique si l'objet doit être initialisé
	bool CDObjState::DoitEtreInitialiser()
	{
		// Un objet doit être initialisé si :
		//  - Il n'est pas initialisé
		//  - Il n'est pas acquis
		//  - ou si il n'est pas marqué pour suppression
		//  - ou si il n'est pas nouveau

		return !(m_bInitaliser || m_bAcquis || m_bPourSupprimer || EstNouveau());
	}

	//! Indique si l'objet peut être sauvé
	bool CDObjState::PeutEtreSauver()
	{
		// Un objet peut être sauvé si :
		//  - Il n'est pas marqué pour suppression

		return (!m_bPourSupprimer);
	}

	//! Indique si l'objet peut être supprimé
	bool CDObjState::DoitEtreSauver()
	{
		// Un objet doit être sauvé si :
		//	- Il est modifié
		//  - Il n'est pas marqué pour suppression

		return ((m_bModifier || m_bEnfantModifier) && !m_bPourSupprimer);
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjState::PeutEtreSupprimer()
	{
		// Un objet peut être supprimé si :
		//  - Il est marqué pour suppression

		return (m_bPourSupprimer);
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjState::DoitEtreSupprimer()
	{
		// Un objet doit être supprimé si :
		//	- Il est acquis
		//  - Il est marqué pour suppression
		//	- Il est modifié
		//	- Il n'est pas supprimé

		return (m_bAcquis && m_bPourSupprimer && m_bModifier && !m_bSupprimer);
	}

}
