//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Définition des constantes ou méthodes globales
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/07/2014 : 
//	-----------------------------------------------------------------------------


// Inclusions
#include "DObject/DObjState.h"
#include "DObject/DObjEtat.h"
#include "DObject/DObjBase.h"
#include "DObject/DObjListe.h"


namespace DObject
{
	//! Constructeur
	CDObjState::CDObjState(CDObjEtat* pObjEtat)
	{
		m_pObjEtat				= pObjEtat;
		m_pObjBase				= nullptr;
		m_bAutoDeleteFromList	= false;
		m_ulId					= DefULong;

		m_bInitaliser		= pObjEtat->m_bInitaliser;
 		m_bModifier			= pObjEtat->m_bModifier;
 		m_bPourSupprimer	= pObjEtat->m_bPourSupprimer;
 		m_bAcquis			= pObjEtat->m_bAcquis;
 		m_bSupprimer		= pObjEtat->m_bSupprimer;
	}

	//! Constructeur
	DObject::CDObjState::CDObjState(CDObjBase* pObjBase)
	{
		m_pObjEtat				= nullptr;
		m_pObjBase				= pObjBase;
		m_bAutoDeleteFromList	= pObjBase->m_bAutoDeleteFromList;
		m_ulId					= pObjBase->m_ulId;

		m_bInitaliser		= pObjBase->m_bInitaliser;
 		m_bModifier			= pObjBase->m_bModifier;
 		m_bPourSupprimer	= pObjBase->m_bPourSupprimer;
 		m_bAcquis			= pObjBase->m_bAcquis;
 		m_bSupprimer		= pObjBase->m_bSupprimer;
	}

	CDObjState::CDObjState(const CDObjState &source)
	{
		m_pObjEtat				= source.m_pObjEtat;
		m_pObjBase				= source.m_pObjBase;
		m_bAutoDeleteFromList	= source.m_bAutoDeleteFromList;
		m_ulId					= source.m_ulId;

		m_bInitaliser			= source.m_bInitaliser;
		m_bModifier				= source.m_bModifier;
		m_bPourSupprimer		= source.m_bPourSupprimer;
		m_bAcquis				= source.m_bAcquis;
		m_bSupprimer			= source.m_bSupprimer;
	}

	void CDObjState::Restore()
	{
		if (m_pObjEtat)
		{
			m_pObjEtat->m_bInitaliser		= m_bInitaliser;
			m_pObjEtat->m_bModifier			= m_bModifier;
			m_pObjEtat->m_bPourSupprimer	= m_bPourSupprimer;
			m_pObjEtat->m_bAcquis			= m_bAcquis;
			m_pObjEtat->m_bSupprimer		= m_bSupprimer;
		}

		if (m_pObjBase)
		{
			m_pObjBase->m_bAutoDeleteFromList	= m_bAutoDeleteFromList;
			m_pObjBase->m_ulId					= m_ulId;

			m_pObjBase->m_bInitaliser		= m_bInitaliser;
			m_pObjBase->m_bModifier			= m_bModifier;
			m_pObjBase->m_bPourSupprimer	= m_bPourSupprimer;
			m_pObjBase->m_bAcquis			= m_bAcquis;
			m_pObjBase->m_bSupprimer		= m_bSupprimer;
		}
	}

	//! Destructeur
	CDObjStateListe::~CDObjStateListe()
	{
		// m_vState
		m_vState.clear();

 		// m_vStateToDelete
 		size_t iCount = m_vStateToDelete.size();
		for (auto & pObjSate : m_vStateToDelete)
			delete pObjSate;
		m_vStateToDelete.clear();
	}

	//! Ajout dans la liste
	void CDObjStateListe::Add(CDObjState& objSate)
	{
		m_vState.emplace_back(objSate);
	}

	//! Ajout dans la liste
	void CDObjStateListe::Add(CDObjBase* pObjBase)
	{
		m_vStateToDelete.emplace_back(new CDObjState(pObjBase));
	}

	//! Ajout dans la liste
	void CDObjStateListe::Add(CDObjBaseListe* pObjListe)
	{
 		for (size_t i = 0; i < pObjListe->GetCount(); i++)
 			Add(pObjListe->GetAt(i));
	}

	void CDObjStateListe::Restore()
	{
		// m_vState
		for (auto & objSate : m_vState)
			objSate.Restore();
		// m_vStateToDelete
		for (auto & pObjSate : m_vStateToDelete)
			pObjSate->Restore();
	}

}
