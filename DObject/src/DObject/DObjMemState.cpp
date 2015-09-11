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
#include "DObject/DObjMemState.h"
#include "DObject/DObjSaveGuard.h"
#include "DObject/DObjState.h"
#include "DObject/DObjBase.h"
#include "DObject/DObjListe.h"



namespace DObject
{
	//! Constructeur
	DObject::CDObjMemState::CDObjMemState(CDObjState* pObjState)
	{
		m_pObjState			= pObjState;

		m_bInitaliser		= pObjState->m_bInitaliser;
 		m_bModifier			= pObjState->m_bModifier;
 		m_bPourSupprimer	= pObjState->m_bPourSupprimer;
 		m_bAcquis			= pObjState->m_bAcquis;
 		m_bSupprimer		= pObjState->m_bSupprimer;
	}

	void CDObjMemState::Restore()
	{
		m_pObjState->m_bInitaliser		= m_bInitaliser;
		m_pObjState->m_bModifier		= m_bModifier;
		m_pObjState->SetPourSupprimer(m_bPourSupprimer);
		m_pObjState->m_bAcquis			= m_bAcquis;
		m_pObjState->m_bSupprimer		= m_bSupprimer;
	}





	////! Destructeur
	//CDObjMemStateListe::~CDObjMemStateListe()
	//{
	//	for(unsigned i=m_vState.size();i-->0;)
	//		delete m_vState[i];
	//	m_vState.clear();
	//}

	////! Ajout dans la liste
	//void CDObjMemStateListe::Add(CDObjState* pObjState)
	//{
	//	m_vState.emplace_back(new CDObjMemState(pObjState));
	//}

	//void CDObjMemStateListe::Restore()
	//{
	//	for(auto pObjMemState : m_vState)
	//		pObjMemState->Restore();
	//}
}
