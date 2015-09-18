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
#include "DObject/DObjState.h"


namespace DObject
{
	//! Constructeur par recopie
	CDObjState::CDObjState(const CDObjState& source)
	{
		ClonnerDonnees(source);
	}

	//! Op�rateur =
	CDObjState& CDObjState::operator=(const CDObjState& source)
	{
		if(this != &source)
			ClonnerDonnees(source);

		return *this;
	}

	//! Clone les donn�es de l'objet.
	void CDObjState::ClonnerDonnees(const CDObjState &source)
	{
		m_bInitaliser		= source.m_bInitaliser;
		m_bModifier			= source.m_bModifier;
		m_bPourSupprimer	= source.m_bPourSupprimer;
		m_bAcquis			= source.m_bAcquis;
		m_bSupprimer		= source.m_bSupprimer;
	}

	//! Op�rateur ==
	bool CDObjState::operator==( const CDObjState &source ) const
	{
		return	m_bInitaliser==source.m_bInitaliser 
			&& m_bModifier==source.m_bModifier 
			&& m_bPourSupprimer == source.m_bPourSupprimer
			&& m_bAcquis == source.m_bAcquis
			&& m_bSupprimer == source.m_bSupprimer;
	}

	//! Op�rateur !=
	bool CDObjState::operator!=( const CDObjState &source ) const
	{
		return !(*this == source);
	}

	bool CDObjState::EstInitialiser() const
	{
		return m_bInitaliser;
	}

	//! Indique si l'objet est initialis�
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

	//! Indique si l'objet � �t� modifi�
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

	//! Indique si l'objet est marqu� pour suppression
	void CDObjState::SetPourSupprimer( bool bPourSupprimer )
	{
		bool bNotifer = (m_bPourSupprimer != bPourSupprimer);

		// Le changement d'�tat de suppression
		// implique que l'item est modifi�.
		if (bNotifer)
			SetModifier(true);

		m_bPourSupprimer = bPourSupprimer;
	}

	bool CDObjState::EstAcquis() const
	{
		return m_bAcquis;
	}

	//! Indique si l'objet � �t� acquis
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

	//! Indique si l'objet � �t� supprim�
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

	//! Indique si l'objet est un nouvelle objet : c'est � dire en cours de cr�ation
	bool CDObjState::EstNouveau() const
	{
		return (!m_bAcquis && m_bModifier);
	}

	//! Force l'objet � croire qu'il est nouveau
	void CDObjState::SetNouveau()
	{
		m_bInitaliser		= false;
		m_bAcquis			= false;
		m_bSupprimer		= false;

		SetModifier(true);
		SetPourSupprimer(false);
	}

	//! Indique si l'objet peut �tre initialis�
	bool CDObjState::PeutEtreInitialiser()
	{
		// Un objet peut �tre initialis� si :
		//  - Il n'est pas initialis�

		return (!m_bInitaliser);
	}

	//! Indique si l'objet doit �tre initialis�
	bool CDObjState::DoitEtreInitialiser()
	{
		// Un objet doit �tre initialis� si :
		//  - Il n'est pas initialis�
		//  - Il n'est pas acquis
		//  - ou si il n'est pas marqu� pour suppression
		//  - ou si il n'est pas nouveau

		return !(m_bInitaliser || m_bAcquis || m_bPourSupprimer || EstNouveau());
	}

	//! Indique si l'objet peut �tre sauv�
	bool CDObjState::PeutEtreSauver()
	{
		// Un objet peut �tre sauv� si :
		//  - Il n'est pas marqu� pour suppression

		return (!m_bPourSupprimer);
	}

	//! Indique si l'objet peut �tre supprim�
	bool CDObjState::DoitEtreSauver()
	{
		// Un objet doit �tre sauv� si :
		//	- Il est modifi�
		//  - Il n'est pas marqu� pour suppression

		return ((m_bModifier || m_bEnfantModifier) && !m_bPourSupprimer);
	}

	//! Indique si l'objet doit �tre sauv�
	bool CDObjState::PeutEtreSupprimer()
	{
		// Un objet peut �tre supprim� si :
		//  - Il est marqu� pour suppression

		return (m_bPourSupprimer);
	}

	//! Indique si l'objet doit �tre sauv�
	bool CDObjState::DoitEtreSupprimer()
	{
		// Un objet doit �tre supprim� si :
		//	- Il est acquis
		//  - Il est marqu� pour suppression
		//	- Il est modifi�
		//	- Il n'est pas supprim�

		return (m_bAcquis && m_bPourSupprimer && m_bModifier && !m_bSupprimer);
	}

}
