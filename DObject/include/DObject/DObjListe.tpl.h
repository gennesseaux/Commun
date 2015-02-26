//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	18/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once


// Inclusions
#include "DObject/DObjListe.h"
#include "DObject/DObjParent.h"



//! Destructeur
template<class TypeClass>
DObject::CDObjListe<TypeClass>::~CDObjListe(void)
{
	// Retire tous les enfants
	RemoveEnfants();

	// Retire tous les éléments de la liste
	RemoveAll();

	// Libération mémoire
	delete m_pParent; m_pParent = nullptr;
}


//! Verification
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::Verifier(std::string* sMsg = NULL)
{
	for (auto & pObj : m_liste)
	{
		//
		if (pObj->EstPourSupprimer() == false && !pObj->Verifier(sMsg))
			return false;
	}
	return true;
}

//! Sauvegarde
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::Sauver()
{
	if (DoitEtreSauver() == false) return true;
	if (PeutEtreSauver() == false) return false;

	// Mémorisation de l'etat de la liste avant sauvegarde
	CDObjState		state(this);

	// Sauvegarde chaque objets de la liste
	size_t iCount = m_liste.size();
	size_t i = 0;
	while (i < iCount)
	{
		auto pObj = m_liste[i];

		if (pObj->EstPourSupprimer() == false && !pObj->Sauver())
		{
			state.Restore(); return false;
		}

		if (pObj->EstPourSupprimer() == true)
		{
			--i; --iCount;
		}

		if (pObj->EstPourSupprimer() == true && !pObj->Supprimer())
		{
			state.Restore(); return false;
		}

		++i;
	}

	return true;
}

//! Suppression
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::Supprimer()
{
	if (DoitEtreSupprimer() == false) return true;
	if (PeutEtreSupprimer() == false) return false;

	// Mémorisation de l'etat de la liste avant sauvegarde
	CDObjState		state(this);

	// Marque les objets pour suppression 
	// et supprime chaque objets de la liste
	size_t iCount = m_liste.size();
	while (iCount > 0)
	{
		auto pObj = m_liste[0];

		if (!pObj->Supprimer())
		{
			state.Restore(); return false;
		}

		--iCount;
	}

	return true;
}




//! Ajout dans la liste
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::Add(TypeClass* pObj)
{
	// Récupère l'objet de base
	CDObjBase* pObjBase = static_cast<CDObjBase*>(pObj);

	// Ajout de l'objet à la liste
	CDObjBase* pObjListe = GetFromUUID(pObjBase->GetLPGUID());
	if (pObjListe == nullptr)
		m_liste.emplace_back(pObj);
	// L'objet ne peut être ajouté plus d'une fois à la liste
	else
		return 0;

	// L'objet est ajouté par conséquent la liste est modifiée
	SetModifier(true);

	// La liste devient parent de l'objet
	pObjBase->AddParent(this);

	// Incrémentation des compteurs
	bool bPourSupprimer = pObjBase->EstPourSupprimer();
	m_iCountValide += static_cast<int>(!bPourSupprimer);
	m_iCountPourSupprimer += static_cast<int>(bPourSupprimer);

	//
	LPGUID lpuuid = pObjBase->GetLPGUID();
	bPourSupprimer ? m_pourSupprimer.emplace_back(lpuuid) : m_valide.emplace_back(lpuuid);

	// Test de cohérence
	assert(m_iCountValide == m_valide.size());
	assert(m_iCountPourSupprimer == m_pourSupprimer.size());
	assert(m_iCountValide + m_iCountPourSupprimer == m_liste.size());

	return m_liste.size();
}

//! Ajout d'une liste à la liste
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::Append(const CDObjListe& source)
{
	CDObjListe& src = (CDObjListe&)source;

	//
	size_t iAppendIndex = GetCount();

	//
	m_liste.reserve(GetCount() + src.GetCount());

	for (size_t i = 0; i < src.GetCount(); i++)
		Add(src.GetAt(i));

	return iAppendIndex;
}

//! Insertion d'un élément dans la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::InsertAt(size_t nIndex, TypeClass* pObj)
{
	// Récupère l'objet de base
	CDObjBase* pObjBase = static_cast<CDObjBase*>(pObj);

	// Augmentation de la taille allouée à la liste
	m_liste.reserve(GetCount() + 2);

	// On ajoute l'objet à la liste avec la méthode Add afin d'avoir un point d'entré unique dans la liste.
	// Ensuite on déplace l'objet à la position demandé.
	if (Add(pObj)>0 && nIndex < m_liste.size())
	{
 		m_liste.emplace(m_liste.begin() + nIndex, pObj);
 		m_liste.erase(m_liste.end()-1);
	}
}

//! Copie d'une liste dans la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::Copy(const CDObjListe& source)
{
	// Vide le contenu existant
	RemoveAll();

	for (size_t i = 0; i < source.m_liste.size(); i++)
		Add(source.m_liste[i]);

	// Des objets étant ajoutés par conséquent la liste est modifiée
	SetModifier(true);
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::RemoveAt(size_t nIndex)
{
	// Récupère l'objet de base
	CDObjBase* pObjBase = m_liste[nIndex];

	// Suppression de la liste
	m_liste.erase(m_liste.begin() + nIndex);

	// décrémentation des compteurs
	bool bPourSupprimer = pObjBase->EstPourSupprimer();
	m_iCountValide -= static_cast<int>(!bPourSupprimer);
	m_iCountPourSupprimer -= static_cast<int>(bPourSupprimer);

	//
	LPGUID lpuuid = pObjBase->GetLPGUID();
	auto its = std::find_if(m_pourSupprimer.begin(), m_pourSupprimer.end(), [=](LPGUID puuid){ return puuid == lpuuid; });
	if (its != m_pourSupprimer.end()) m_pourSupprimer.erase(its);
	auto itv = std::find_if(m_valide.begin(), m_valide.end(), [=](LPGUID puuid){ return puuid == lpuuid; });
	if (itv != m_valide.end()) m_valide.erase(itv);

	//
	pObjBase->RemoveParent(this);

	// Delete de l'objet si il n'est plus observer
	if (pObjBase->GetObservateurCount() == 0 && pObjBase->m_bAutoDeleteFromList)
		pObjBase->Delete();

	// L'objet est supprimé par conséquent la liste est modifiée
	SetModifier(true);
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::Remove(IDObjBase* pIObjBase)
{
	LPGUID lpuuid = pIObjBase->GetLPGUID();
	auto it = std::find_if(m_liste.begin(), m_liste.end(), [=](CDObjBase* pObj){ return lpuuid == pObj->GetLPGUID(); });
	if (it != m_liste.end())
	{
		size_t i = it - m_liste.begin();
		RemoveAt(i);
	}
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::RemoveFromId(unsigned long ulId)
{
	Remove(GetFromId(ulId));
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::RemoveFromUUID(LPGUID uuid)
{
	Remove(GetFromUUID(uuid));
}

//! Suppression de tous les objets de la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::RemoveAll()
{
	size_t iCount = m_liste.size();
	while (iCount > 0)
	{
		RemoveAt(0);
		--iCount;
	}
}

//! Retrouve un objet de la liste
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::GetAt(size_t iIndex)
{
	return m_liste[iIndex];
}

//! Retrouve un objet de la liste
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::GetAt(size_t iIndex, ObjEtat etat)
{
	if (etat == ObjEtat::Valide && iIndex < m_iCountValide)
	{
		LPGUID lpuuid = m_valide[iIndex];
		auto it = std::find_if(m_liste.begin(), m_liste.end(), [=](CDObjBase* obj){ return lpuuid == obj->GetLPGUID(); });
		return (it != m_liste.end()) ? *it : nullptr;
	}

	if (etat == ObjEtat::PourSupprimer && iIndex < m_iCountPourSupprimer)
	{
		LPGUID lpuuid = m_pourSupprimer[iIndex];
		auto it = std::find_if(m_liste.begin(), m_liste.end(), [=](CDObjBase* obj){ return lpuuid == obj->GetLPGUID(); });
		return (it != m_liste.end()) ? *it : nullptr;
	}

	return nullptr;
}

//! Retourne le pointeur sur l'objet en fonction de son Id.
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::GetFromId(unsigned long ulId)
{
	auto it = std::find_if(m_liste.begin(), m_liste.end(), [=](CDObjBase* obj){ return ulId == obj->GetId(); });
	return (it != m_liste.end()) ? *it : nullptr;
}

//! Retourne le pointeur sur l'objet en fonction de son UUID.
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::GetFromUUID(LPGUID uuid)
{
	auto it = std::find_if(m_liste.begin(), m_liste.end(), [=](CDObjBase* obj){ return uuid == obj->GetLPGUID(); });
	return (it != m_liste.end()) ? *it : nullptr;
}

//! Nombre d'objet dans la liste
//! ATTENTION : La liste s'initialise automatiquement.
//! Pour ne pas initialiser la liste, utiliser GetSize()
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::GetCount()
{
	if (DoitEtreInitialiser())
		Initialiser();

	return m_liste.size();
}

//! Nombre d'objet dans la liste
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::GetCount(ObjEtat etat)
{
	switch (etat)
	{
	case DObject::ObjEtat::Valide:				return m_iCountValide;			break;
	case DObject::ObjEtat::PourSupprimer:		return m_iCountPourSupprimer;	break;
	}
}

//! Nombre d'objet dans la liste
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::GetSize()
{
	return m_liste.size();
}

//! Mise à jour des items valides ou pour suppression
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::UpdateValideSuppression(CDObjBase* pObjBase)
{
	// 
	bool bPourSupprimer = pObjBase->EstPourSupprimer();

	//
	LPGUID lpuuid = pObjBase->GetLPGUID();
	if(bPourSupprimer)
	{
		auto it = std::find(m_valide.begin(), m_valide.end(), lpuuid);
		if (it != m_valide.end())	
		{
			m_valide.erase(it);
			m_pourSupprimer.emplace_back(lpuuid);

			m_iCountValide -= 1;
			m_iCountPourSupprimer += 1;
		}
	}
	else
	{
		auto it = std::find(m_pourSupprimer.begin(), m_pourSupprimer.end(), lpuuid);
		if (it != m_pourSupprimer.end())	
		{
			m_pourSupprimer.erase(it);
			m_valide.emplace_back(lpuuid);

			m_iCountValide += 1;
			m_iCountPourSupprimer -= 1;
		}
	}

	assert(m_iCountValide == m_valide.size());
	assert(m_iCountPourSupprimer == m_pourSupprimer.size());
	assert(m_iCountValide + m_iCountPourSupprimer == m_liste.size());
}




// Méthodes de trie de la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SortById()
{
	std::sort(m_liste.begin(), m_liste.end(), CDObjBase::CompareIdPredicate);
}

// Méthodes de trie de la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SortByModifie()
{
	std::sort(m_liste.begin(), m_liste.end(), CDObjBase::CompareModifiePredicate);
}

// Méthodes de trie de la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SortByPourSupprimer()
{
	std::sort(m_liste.begin(), m_liste.end(), CDObjBase::ComparePourSupprimerPredicate);
}

//! Indique si l'objet est marqué pour suppression.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetPourSupprimer(bool bPourSupprimer, bool bPropagerAuxEnfants)
{
	CDObjEtat::SetPourSupprimer(bPourSupprimer);

	if (bPropagerAuxEnfants)
	{
		for (auto & pObj : m_liste)
			pObj->SetPourSupprimer(bPourSupprimer);
	}
}

//! Indique si l'objet à été supprimé.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetSupprimer(bool bSupprimer)
{
	CDObjEtat::SetSupprimer(bSupprimer);

	// Notification
	if (bSupprimer)
		NotifierObservateur(NotificationEnfant::EnfantSupprimer);
}

//! Indique si l'objet peut être initialisé
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::PeutEtreInitialiser()
{
	return CDObjEtat::PeutEtreInitialiser();
}

//! Indique si l'objet doit être initialisé
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::DoitEtreInitialiser()
{
	return CDObjEtat::DoitEtreInitialiser();
}

//! Indique si l'objet peut être sauvé
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::PeutEtreSauver()
{
	return (m_liste.size() && CDObjEtat::PeutEtreSauver());
}

//! Indique si l'objet doit être sauvé
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::DoitEtreSauver()
{
	return (m_liste.size() && CDObjEtat::DoitEtreSauver());
}

//! Indique si l'objet peut être supprimé
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::PeutEtreSupprimer()
{
	return (m_liste.size() && CDObjEtat::PeutEtreSupprimer());
}

//! Indique si l'objet doit être supprimé
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::DoitEtreSupprimer()
{
	// Un objet doit être supprimé si :
	//  - Il est marqué pour suppression
	//	- Il est modifié
	//	- Il n'est pas supprimé

	return (m_liste.size() && EstPourSupprimer() && EstModifier() && !EstSupprimer());
}

//! Ajout d'un parent de type CDObjEtat*
template<class TypeClass /*= CDObjBase*/>
void DObject::CDObjListe<TypeClass>::AddParent(CDObjEtat* pObjEtat)
{
	if (!m_pParent)
		m_pParent = new CDObjParent();

	IDObjBase* pIObjBase = dynamic_cast<IDObjBase*>(pObjEtat);
	if(pIObjBase)
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

//! Retire un parent de type CDObjEtat*
template<class TypeClass /*= CDObjBase*/>
void DObject::CDObjListe<TypeClass>::RemoveParent(CDObjEtat* pObjEtat)
{
	if (!m_pParent)
		return;

	IDObjBase* pIObjBase = dynamic_cast<IDObjBase*>(pObjEtat);
	if(pIObjBase)
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

//! Retire tous les enfants
template<class TypeClass /*= CDObjBase*/>
void DObject::CDObjListe<TypeClass>::RemoveEnfants()
{
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
	while (GetParent<IDObjBase*>())
	{
		IDObjBase* pIObjBase = GetParent<IDObjBase*>();

		// Enlève le parent
		RemoveParent(pIObjBase);
	}

	// 
	while (GetParent<IDObjListe*>())
	{
		IDObjListe* pObjListe = GetParent<IDObjListe*>();

		// Enlève le parent
		RemoveParent(pObjListe);
	}
}

template<class TypeClass /*= CDObjBase*/>
void DObject::CDObjListe<TypeClass>::AddEnfant(CDObjEtat* pObjEtat)
{
	IDObjBase* pIObjEnfant = dynamic_cast<IDObjBase*>(pObjEtat);
	if(pIObjEnfant)
	{
		bool bExiste = false;
		for(auto &enfant : m_mObjBaseEnfant)
		{
			IDObjBase* pParent = enfant;
			if(pParent == pIObjEnfant)
				bExiste = true;
		}
		if(!bExiste)
			m_mObjBaseEnfant.emplace_back(pIObjEnfant);
	}

	IDObjListe* pIObjListe = dynamic_cast<IDObjListe*>(pObjEtat);
	if(pIObjListe)
	{
		bool bExiste = false;
		for(auto &enfant : m_mObjListeEnfant)
		{
			IDObjListe* pParent = enfant;
			if(pParent == pIObjListe)
				bExiste = true;
		}
		if(!bExiste)
			m_mObjListeEnfant.emplace_back(pIObjListe);
	}
}

template<class TypeClass /*= CDObjBase*/>
void DObject::CDObjListe<TypeClass>::RemoveEnfant(CDObjEtat* pObjEtat)
{
	IDObjBase* pIObjEnfant = dynamic_cast<IDObjBase*>(pObjEtat);
	if(pIObjEnfant)
	{
		auto it = std::find(m_mObjBaseEnfant.begin(), m_mObjBaseEnfant.end(), pIObjEnfant);

		if(it != m_mObjBaseEnfant.end())
			m_mObjBaseEnfant.erase(it);
	}

	IDObjListe* pObjListe = dynamic_cast<IDObjListe*>(pObjEtat);
	if(pObjListe)
	{
		auto it = std::find(m_mObjListeEnfant.begin(), m_mObjListeEnfant.end(), pObjListe);

		if(it != m_mObjListeEnfant.end())
			m_mObjListeEnfant.erase(it);
	}
}

//! Retourne le parent de type CDObjBase* ou CDObListe<>*
template<class TypeClass /*= CDObjBase*/>
template<class T>
T DObject::CDObjListe<TypeClass>::GetParent()
{
	if (!m_pParent)
		return nullptr;

	return m_pParent->Get<T>();
}
