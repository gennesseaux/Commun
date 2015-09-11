//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de base d'un objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	18/6/2014 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "DObject/DObjBase.h"
#include "DObject/DObjListe.h"

namespace DObject
{
	//! Constructeur
	CDObjBase::CDObjBase(unsigned long ulId /*= DefULong*/, CDObject* pOwner /*= nullptr*/) : CDObject(pOwner)
	{
		m_ulId = ulId;
	}

	//! Destructeur
	CDObjBase::~CDObjBase(void)
	{
		// Désactive la destruction automatique depuis les listes
		m_bAutoDeleteFromList = false;
	}

	//! Delete
	CDObjBase* CDObjBase::Delete()
	{
		delete this;
		return nullptr;
	}

	//! Delete
	CDObjBase* CDObjBase::Delete(CDObjBase* pObjBase)
	{
		return pObjBase->Delete();
	}
	
	//! Pointeur vers CDObject
	CDObject* CDObjBase::GetDObject()
	{
		return dynamic_cast<CDObject*>(this);
	}


	//! Constructeur par recopie
	CDObjBase::CDObjBase(const CDObjBase& source)
	{
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObjBase& CDObjBase::operator=(const CDObjBase& source)
	{
		if(this != &source)
		{
			ClonnerDonnees(source);
		}

		return *this;
	}

	//! Clone les données de l'objet.
	void CDObjBase::ClonnerDonnees(const CDObjBase &source)
	{
		CDObjState::ClonnerDonnees(source);

		m_ulId = source.m_ulId;
	}
	
	//! Notification d'évènement
	void CDObjBase::OnEvent(DObjEvent& event,CDObject* sender)
	{
		switch(event)
		{
			case DObjEvent::ObjetModifierEvent:
			{
				SetEnfantsModifier(true);

				this->OnModifier(sender,this);
			} break;

			case DObjEvent::ObjetSauverEvent:
			{
				this->OnSauver(sender,this);
			} break;

			case DObjEvent::ObjetPourSupprimerEvent:
			{
				SetEnfantsModifier(true);

				this->OnModifier(sender,this);
			} break;

			case DObjEvent::ObjetSupprimerEvent:
			{
				// DObjSaveGuard se charge des suppressions de pointeurs
				this->OnSupprimer(sender,this);
			} break;
		}
	}

	//! Retourne l'identifiant de l'objet
	long CDObjBase::GetId() const
	{
		return m_ulId;
	}

	//! Indique si l'objet est initialisé
	bool CDObjBase::EstInitialiser() const
	{
		return CDObjState::EstInitialiser();
	}
	void CDObjBase::SetInitaliser(bool bInitaliser)
	{
		CDObjState::SetInitaliser(bInitaliser);
	}

	//! Indique si l'objet à été modifié
	bool CDObjBase::EstModifier() const
	{
		return CDObjState::EstModifier();
	}
	void CDObjBase::SetModifier(bool bModifier)
	{
		bool bNotifer = (CDObjState::EstModifier() != bModifier);

		CDObjState::SetModifier(bModifier);

		// Notification
		if (bModifier && bNotifer)
			notifyClient(DObjEvent::ObjetModifierEvent);
	}

	//! Indique si l'item à des objets membre modifiés
	bool CDObjBase::SontEnfantsModifier() const
	{
		return CDObjState::SontEnfantsModifier();
	}
	void CDObjBase::SetEnfantsModifier(bool bEnfantModifier)
	{
		CDObjState::SetEnfantsModifier(bEnfantModifier);
	}

	//! Indique si l'objet est marqué pour suppression.
	bool CDObjBase::EstPourSupprimer() const
	{
		return CDObjState::EstPourSupprimer();
	}
	void CDObjBase::SetPourSupprimer(bool bPourSupprimer)
	{
		bool bNotifer = (CDObjState::EstPourSupprimer() != bPourSupprimer);

		CDObjState::SetPourSupprimer(bPourSupprimer);

		// Notification
		if(bNotifer)
			notifyClient(DObjEvent::ObjetPourSupprimerEvent);
	}

	void CDObjBase::SetPourSupprimer(bool bPourSupprimer, bool bCascadeChild)
	{
		SetPourSupprimer(bPourSupprimer);

		if(bCascadeChild)
		{
			for(auto pDObject : GetChilds())
			{
				// Le dynamic_cast n'étant pas possible sur une classe template,
				// On suppose alors que si l'objet enfant n'est pas de type CDObjBase,
				// c'est alors un CDObjListe
				CDObjBase* pDObjBase = dynamic_cast<CDObjBase*>(pDObject);
				if(pDObjBase)
					pDObjBase->SetPourSupprimer(bPourSupprimer);
				else
					((CDObjListe<CDObjBase>*)pDObject)->SetPourSupprimer(bPourSupprimer,bCascadeChild);
			}
		}
	}

	//! Indique si l'objet à été acquis
	bool CDObjBase::EstAcquis() const
	{
		return CDObjState::EstAcquis();
	}
	void CDObjBase::SetAcquis(bool bAcquis)
	{
		CDObjState::SetAcquis(bAcquis);
	}

	//! Indique si l'objet à été supprimé
	bool CDObjBase::EstSupprimer() const
	{
		return CDObjState::EstSupprimer();
	}
	void CDObjBase::SetSupprimer(bool bSupprimer)
	{
		CDObjState::SetSupprimer(bSupprimer);
	}

	//! Indique si l'objet est un nouvel objet : c'est à dire en cours de création.
	bool CDObjBase::EstNouveau() const
	{
		return CDObjState::EstNouveau() || (m_ulId==DefULong?true:false);
	}

	//! Force l'objet à croire qu'il est nouveau.
	void CDObjBase::SetNouveau()
	{
		CDObjState::SetNouveau();
		m_ulId=DefULong;
	}

	//! Indique si l'objet peut être initialisé
	bool CDObjBase::PeutEtreInitialiser()
	{
		return CDObjState::PeutEtreInitialiser();
	}

	//! Indique si l'objet doit être initialisé
	bool CDObjBase::DoitEtreInitialiser()
	{
		return CDObjState::DoitEtreInitialiser();
	}

	//! Indique si l'objet peut être sauvé
	bool CDObjBase::PeutEtreSauver()
	{
		return CDObjState::PeutEtreSauver();
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjBase::DoitEtreSauver()
	{
		return CDObjState::DoitEtreSauver();
	}

	//! Indique si l'objet peut être supprimé
	bool CDObjBase::PeutEtreSupprimer()
	{
		return CDObjState::PeutEtreSupprimer();
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjBase::DoitEtreSupprimer()
	{
		return CDObjState::DoitEtreSupprimer();
	}
}
