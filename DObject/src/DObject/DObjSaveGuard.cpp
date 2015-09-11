//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	10/09/2015 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "DObject/DObjSaveGuard.h"

namespace DObject
{
	//! Constructeur
	DObjSaveGuard::DObjSaveGuard()
	{
	}

	//! Destructeur
	DObjSaveGuard::~DObjSaveGuard(void)
	{
	}
	
	void DObjSaveGuard::clear()
	{
		for(unsigned i=_memState.size(); i-->0;)
			delete _memState[i];
		_pDObjState = nullptr;
		_memState.clear();
		_toDelete.clear();
	}

	void DObjSaveGuard::Start(CDObjState* pDObjState)
	{
		if(SaveGuard()._pDObjState == nullptr)
		{
			SaveGuard().clear();
			SaveGuard()._pDObjState = pDObjState;
		}

		SaveGuard()._memState.emplace_back(new CDObjMemState(pDObjState));
	}

	bool DObjSaveGuard::Sucess(CDObjState* pDObjState)
	{
		if(pDObjState->EstSupprimer())
			SaveGuard()._toDelete.emplace_back(pDObjState);

		// Fin avec succés de la sauvegarde ou de la suppression
		if(SaveGuard()._pDObjState == pDObjState)
		{
			// Notifications
			for(unsigned i=0; i<SaveGuard()._memState.size(); i++)
			{
				CDObjState* pObjStateTemp = SaveGuard()._memState[i]->m_pObjState;

				if(pObjStateTemp->m_bSupprimer)		pObjStateTemp->GetDObject()->notifyClient(DObjEvent::ObjetSupprimerEvent);
				else if(pObjStateTemp->m_bAcquis)	pObjStateTemp->GetDObject()->notifyClient(DObjEvent::ObjetSauverEvent);
			}

			// Suppression des pointeurs
			for(unsigned i=SaveGuard()._toDelete.size(); i-->0;)
				delete SaveGuard()._toDelete[i]->GetDObject();
			SaveGuard().clear();
		}

		return true;
	}

	bool DObjSaveGuard::Error(CDObjState* pDObjState)
	{
		// Fin avec erreur de la sauvegarde ou de la suppression
		if(SaveGuard()._pDObjState == pDObjState)
		{
			for(unsigned i=SaveGuard()._memState.size(); i-->0;)
				SaveGuard()._memState[i]->Restore();
			SaveGuard().clear();
		}

		return false;
	}

}
