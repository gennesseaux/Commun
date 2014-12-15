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
#include "DObject/DObjParent.h"

namespace DObject
{
	//! Constructeur
	CDObjBase::CDObjBase(unsigned long ulId /*= DefULong*/)
	{
		m_ulId = ulId;
	}

	//! Destructeur
	CDObjBase::~CDObjBase(void)
	{
		// Désactive la destruction automatisue depuis les listes
		m_bAutoDeleteFromList = false;

		while(m_mObjBaseEnfant.size())
		{
			IDObjBase* pIObjBase = m_mObjBaseEnfant[0];
			pIObjBase->RemoveParent(this);
		}

		while(m_mObjListeEnfant.size())
		{
			IDObjListe* pIObjListe = m_mObjListeEnfant[0];
			pIObjListe->RemoveParent(this);
		}

		// 
		while (GetParent<IDObjListe*>())
		{
			IDObjListe* pObjListe = GetParent<IDObjListe*>();

			// Enlève l'objet de la liste
			pObjListe->Remove(this);

			// Enlève le parent
			RemoveParent(pObjListe);
		}

		// 
		while (GetParent<IDObjBase*>())
		{
			IDObjBase* pIObjBase = GetParent<IDObjBase*>();

			// Enlève le parent
			RemoveParent(pIObjBase);
		}

		// Libération mémoire
		delete m_pParent; m_pParent = nullptr;
	}

	CDObjBase* CDObjBase::Delete()
	{
		delete this;
		return nullptr;
	}

	CDObjBase* CDObjBase::Delete(CDObjBase* pObjBase)
	{
		return pObjBase->Delete();
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

	////! Constructeur de déplacement
	//CDObjBase::CDObjBase(CDObjBase&& source)
	//{
	//	m_ulId = source.m_ulId;

	//	source.m_ulId = DefULong;
	//}

	////! Opérateur de déplacement
	//CDObjBase& CDObjBase::operator=(CDObjBase&& source)
	//{
	//	if(this != &source)
	//	{
	//		m_ulId = source.m_ulId;

	//		source.m_ulId = DefULong;
	//	}

	//	return *this;
	//}

	//! Clone les données de l'objet.
	void CDObjBase::ClonnerDonnees(const CDObjBase &source)
	{
		CDObjEtat::ClonnerDonnees(source);

		m_ulId = source.m_ulId;
	}

	//! Retourne l'identifiant de l'objet
	long CDObjBase::GetId() const
	{
		return m_ulId;
	}

	//! Indique si l'objet est initialisé
	bool CDObjBase::EstInitialiser() const
	{
		return CDObjEtat::EstInitialiser();
	}
	void CDObjBase::SetInitaliser(bool bInitaliser)
	{
		CDObjEtat::SetInitaliser(bInitaliser);
	}

	//! Indique si l'objet à été modifié
	bool CDObjBase::EstModifier() const
	{
		return CDObjEtat::EstModifier();
	}
	void CDObjBase::SetModifier(bool bModifier)
	{
		CDObjEtat::SetModifier(bModifier);
	}

	//! Indique si l'item à des objets membre modifiés
	bool CDObjBase::SontEnfantsModifier() const
	{
		return CDObjEtat::SontEnfantsModifier();
	}
	void CDObjBase::SetEnfantsModifier(bool bEnfantModifier)
	{
		CDObjEtat::SetEnfantsModifier(bEnfantModifier);
	}

	//! Indique si l'objet est marqué pour suppression.
	bool CDObjBase::EstPourSupprimer() const
	{
		return CDObjEtat::EstPourSupprimer();
	}
	void CDObjBase::SetPourSupprimer(bool bPourSupprimer)
	{
		CDObjEtat::SetPourSupprimer(bPourSupprimer);
	}

	//! Indique si l'objet à été acquis
	bool CDObjBase::EstAcquis() const
	{
		return CDObjEtat::EstAcquis();
	}
	void CDObjBase::SetAcquis(bool bAcquis)
	{
		CDObjEtat::SetAcquis(bAcquis);
	}

	//! Indique si l'objet à été supprimé
	bool CDObjBase::EstSupprimer() const
	{
		return CDObjEtat::EstSupprimer();
	}
	void CDObjBase::SetSupprimer(bool bSupprimer)
	{
		CDObjEtat::SetSupprimer(bSupprimer);

		// Notification
		if (bSupprimer)
			NotifierObservateur(NotificationEnfant::EnfantSupprimer);
	}

	//! Indique si l'objet est un nouvel objet : c'est à dire en cours de création.
	bool CDObjBase::EstNouveau() const
	{
		return CDObjEtat::EstNouveau() || (m_ulId==DefULong?true:false);
	}

	//! Force l'objet à croire qu'il est nouveau.
	void CDObjBase::SetNouveau()
	{
		CDObjEtat::SetNouveau();
		m_ulId=DefULong;
	}

	//! Indique si l'objet peut être initialisé
	bool CDObjBase::PeutEtreInitialiser()
	{
		return CDObjEtat::PeutEtreInitialiser();
	}

	//! Indique si l'objet doit être initialisé
	bool CDObjBase::DoitEtreInitialiser()
	{
		return CDObjEtat::DoitEtreInitialiser();
	}

	//! Indique si l'objet peut être sauvé
	bool CDObjBase::PeutEtreSauver()
	{
		return CDObjEtat::PeutEtreSauver();
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjBase::DoitEtreSauver()
	{
		return CDObjEtat::DoitEtreSauver();
	}

	//! Indique si l'objet peut être supprimé
	bool CDObjBase::PeutEtreSupprimer()
	{
		return CDObjEtat::PeutEtreSupprimer();
	}

	//! Indique si l'objet doit être sauvé
	bool CDObjBase::DoitEtreSupprimer()
	{
		return CDObjEtat::DoitEtreSupprimer();
	}

 	//! Ajout d'un parent de type CDObjEtat*
	void CDObjBase::AddParent(CDObjEtat* pObjEtat)
 	{
		if (!m_pParent)
			m_pParent = new CDObjParent();

		IDObjBase* pIObjBase = dynamic_cast<IDObjBase*>(pObjEtat);
		if (pIObjBase)
		{
			m_pParent->Add(pIObjBase);
			pIObjBase->AddEnfant(this);
		}

		IDObjListe* pObjListe = dynamic_cast<IDObjListe*>(pObjEtat);
		if (pObjListe)
		{
			m_pParent->Add(pObjListe);
			pObjListe->AddEnfant(this);
		}

		this->RegisterObservateur(m_pParent);
 	}

	void CDObjBase::RemoveParent(CDObjEtat* pObjEtat)
	{
		if (!m_pParent)
			return;

		IDObjBase* pIObjBase = dynamic_cast<IDObjBase*>(pObjEtat);
		if (pIObjBase)
		{
			m_pParent->Remove(pIObjBase);
			pIObjBase->RemoveEnfant(this);
		}

		IDObjListe* pObjListe = dynamic_cast<IDObjListe*>(pObjEtat);
		if (pObjListe)
		{
			m_pParent->Remove(pObjListe);
			pObjListe->RemoveEnfant(this);
		}

		if (m_pParent->GetCount()==0)
			this->RemoveObservateur(m_pParent);
	}

	void CDObjBase::AddEnfant(CDObjEtat* pObjEtat)
	{
		IDObjBase* pIObjEnfant = dynamic_cast<IDObjBase*>(pObjEtat);
		if (pIObjEnfant)
		{
 			bool bExiste = false;
 			for (auto &enfant : m_mObjBaseEnfant)
 			{
 				IDObjBase* pParent = enfant;
 				if (pParent == pIObjEnfant)
 					bExiste = true;
 			}
 			if (!bExiste)
 				m_mObjBaseEnfant.emplace_back(pIObjEnfant);
		}
		
		IDObjListe* pIObjListe = dynamic_cast<IDObjListe*>(pObjEtat);
		if (pIObjListe)
		{
 			bool bExiste = false;
 			for (auto &enfant : m_mObjListeEnfant)
 			{
 				IDObjListe* pParent = enfant;
 				if (pParent == pIObjListe)
 					bExiste = true;
 			}
 			if (!bExiste)
 				m_mObjListeEnfant.emplace_back(pIObjListe);
		}
	}
	
	void CDObjBase::RemoveEnfant(CDObjEtat* pObjEtat)
	{
		IDObjBase* pIObjEnfant = dynamic_cast<IDObjBase*>(pObjEtat);
		if (pIObjEnfant)
		{
			auto it = std::find(m_mObjBaseEnfant.begin(), m_mObjBaseEnfant.end(), pIObjEnfant);

			if(it != m_mObjBaseEnfant.end())
				m_mObjBaseEnfant.erase(it);
		}
		
		IDObjListe* pObjListe = dynamic_cast<IDObjListe*>(pObjEtat);
		if (pObjListe)
		{
			auto it = std::find(m_mObjListeEnfant.begin(), m_mObjListeEnfant.end(), pObjListe);

			if(it != m_mObjListeEnfant.end())
				m_mObjListeEnfant.erase(it);
		}
	}

}
