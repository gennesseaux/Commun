//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	18/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once


// Inclusions
#include "DObject/DObjListe.h"



//! Destructeur
template<class TypeClass>
DObject::CDObjListe<TypeClass>::~CDObjListe(void)
{
	// Retire tous les �l�ments de la liste
	RemoveAll();
}

//! Pointeur vers CDObject
template<class TypeClass /*= CDObjBase*/>
DObject::CDObject* DObject::CDObjListe<TypeClass>::GetDObject()
{
	return (CDObject*)this;
}


//! Verification
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::Verifier(std::string* sMsg = NULL)
{
	for(auto& pObj : m_liste)
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
	// Sauvegarde chaque objets de la liste
	for (size_t i = 0; i < m_liste.size() ; i++)
	{
		auto pObj = m_liste[i];

		if (pObj->EstPourSupprimer() == false && !pObj->Sauver())
			return false;
		
		if (pObj->EstPourSupprimer() == true && !pObj->Supprimer())
			return false;
	}

	return true;
}

//! Suppression
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::Supprimer()
{
	// Marque les objets pour suppression 
	// et supprime chaque objets de la liste
	for(unsigned i=m_liste.size(); i-->0;)
	{
		auto pObj = m_liste[i];
		if (!pObj->Supprimer())
			return false;
	}

	return true;
}

//! Ajout dans la liste
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::Add(TypeClass* pObj)
{
	// R�cup�re l'objet de base
	CDObjBase* pObjBase = static_cast<CDObjBase*>(pObj);

	// Ajout de l'objet � la liste
	CDObjBase* pObjBaseInListe = GetFromUUID(pObjBase->GetLPGUID());
	if (pObjBaseInListe == nullptr)
		m_liste.emplace_back(pObj);
	// L'objet ne peut �tre ajout� plus d'une fois � la liste
	else
		return 0;

	// L'objet est ajout� par cons�quent la liste est modifi�e
	SetModifier(true);

	// La liste devient parent de l'objet
	pObjBase->AddOwner(this);

	// Incr�mentation des compteurs
	bool bPourSupprimer = pObjBase->EstPourSupprimer();
	m_iCountValide += static_cast<int>(!bPourSupprimer);
	m_iCountPourSupprimer += static_cast<int>(bPourSupprimer);

	//
	LPGUID lpuuid = pObjBase->GetLPGUID();
	bPourSupprimer ? m_pourSupprimer.emplace_back(lpuuid) : m_valide.emplace_back(lpuuid);

	// Test de coh�rence
	assert(m_iCountValide == m_valide.size());
	assert(m_iCountPourSupprimer == m_pourSupprimer.size());
	assert(m_iCountValide + m_iCountPourSupprimer == m_liste.size());

	return m_liste.size();
}

//! Ajout d'une liste � la liste
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

//! Insertion d'un �l�ment dans la liste.
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::InsertAt(size_t nIndex, TypeClass* pObj)
{
	// R�cup�re l'objet de base
	CDObjBase* pObjBase = static_cast<CDObjBase*>(pObj);

	// Augmentation de la taille allou�e � la liste
	m_liste.reserve(GetCount() + 2);

	// On ajoute l'objet � la liste avec la m�thode Add afin d'avoir un point d'entr� unique dans la liste.
	// Ensuite on d�place l'objet � la position demand�.
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

	// Des objets �tant ajout�s par cons�quent la liste est modifi�e
	SetModifier(true);
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::RemoveAt(size_t nIndex)
{
	// R�cup�re l'objet de base
	CDObjBase* pDObjBase = m_liste[nIndex];

	// Suppression de l'objet dans la liste
	m_liste.erase(m_liste.begin() + nIndex);

	//
	LPGUID lpuuid = pDObjBase->GetLPGUID();
	auto its = std::find_if(m_pourSupprimer.begin(), m_pourSupprimer.end(), [=](LPGUID puuid){ return puuid == lpuuid; });
	if (its != m_pourSupprimer.end()) m_pourSupprimer.erase(its);
	auto itv = std::find_if(m_valide.begin(), m_valide.end(), [=](LPGUID puuid){ return puuid == lpuuid; });
	if (itv != m_valide.end()) m_valide.erase(itv);

	// Mise � jour des compteurs
	m_iCountValide = m_valide.size();
	m_iCountPourSupprimer = m_pourSupprimer.size();

	//
	pDObjBase->RemoveOwner(this);

	// L'objet est supprim� par cons�quent la liste est modifi�e
	SetModifier(true);

	// Delete de l'objet si il n'est plus observer
	if (pDObjBase->GetOwnerCount()==0 && pDObjBase->m_bAutoDeleteFromList)
		return dynamic_cast<TypeClass*>(pDObjBase->Delete());

	return dynamic_cast<TypeClass*>(pDObjBase);
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::Remove(TypeClass* pObj)
{
	LPGUID lpuuid = pObj->GetLPGUID();
	auto it = std::find_if(m_liste.begin(), m_liste.end(), [=](CDObjBase* pObj){ return lpuuid == pObj->GetLPGUID(); });
	if (it != m_liste.end())
	{
		size_t i = it - m_liste.begin();
		return RemoveAt(i);
	}
	return pObj;
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::RemoveFromId(unsigned long ulId)
{
	return Remove(GetFromId(ulId));
}

//! Suppression d'un objet dans la liste.
template<class TypeClass>
TypeClass* DObject::CDObjListe<TypeClass>::RemoveFromUUID(LPGUID uuid)
{
	return Remove(GetFromUUID(uuid));
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
	return 0;
}

//! Nombre d'objet dans la liste
template<class TypeClass>
size_t DObject::CDObjListe<TypeClass>::GetSize()
{
	return m_liste.size();
}

//! Suppression d'un enfant
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::RemoveChild(CDObject* pChild)
{
	CDObject::RemoveChild(pChild);

	this->Remove((TypeClass*)pChild);
}


//! Mise � jour des items valides ou pour suppression
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::OnEvent(DObjEvent& event, CDObject* sender)
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

			UpdateValideSuppression((CDObjBase*)sender);

			this->OnModifier(sender,this);
		} break;

		case DObjEvent::ObjetSupprimerEvent:
		{
			// DObjSaveGuard se charge des suppressions de pointeurs
			this->OnSupprimer(sender,this);
		} break;
	}
}

//! Mise � jour des items valides ou pour suppression
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




// M�thodes de trie de la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SortById()
{
	std::sort(m_liste.begin(), m_liste.end(), CDObjBase::CompareIdPredicate);
}

// M�thodes de trie de la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SortByModifie()
{
	std::sort(m_liste.begin(), m_liste.end(), CDObjBase::CompareModifiePredicate);
}

// M�thodes de trie de la liste
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SortByPourSupprimer()
{
	std::sort(m_liste.begin(), m_liste.end(), CDObjBase::ComparePourSupprimerPredicate);
}

// Indique si l'objet est initialis�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::EstInitialiser() const
{
	return CDObjState::EstInitialiser();
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetInitaliser(bool bInitaliser)
{
	CDObjState::SetInitaliser(bInitaliser);
}

// Indique si l'objet � �t� modifi�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::EstModifier() const
{
	return CDObjState::EstModifier();
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetModifier(bool bModifier)
{
	bool bNotifer = (CDObjState::EstModifier() != bModifier);

	CDObjState::SetModifier(bModifier);

	// Notification
	if(bModifier && bNotifer)
		notifyClient(DObjEvent::ObjetModifierEvent);
}

// Indique si l'item � des objets membre modifi�s
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::SontEnfantsModifier() const
{
	return CDObjState::SontEnfantsModifier();
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetEnfantsModifier(bool bEnfantModifier)
{
	CDObjState::SetEnfantsModifier(bEnfantModifier);
}

// Indique si l'objet est marqu� pour suppression
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::EstPourSupprimer() const
{
	return CDObjState::EstPourSupprimer();
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetPourSupprimer(bool bPourSupprimer)
{
	bool bNotifer = (CDObjState::EstPourSupprimer() != bPourSupprimer);

	CDObjState::SetPourSupprimer(bPourSupprimer);

	// Notification
	if(bNotifer)
		notifyClient(DObjEvent::ObjetPourSupprimerEvent);
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetPourSupprimer(bool bPourSupprimer, bool bCascadeChild)
{
	return SetPourSupprimer(bPourSupprimer,bCascadeChild,false);
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetPourSupprimer(bool bPourSupprimer, bool bCascadeChild, bool bChildOnly)
{
	if(!bChildOnly)
		SetPourSupprimer(bPourSupprimer);

	if (bCascadeChild)
	{
		for(auto pDObject : m_liste)
			pDObject->SetPourSupprimer(bPourSupprimer);

		for(auto pDObject : GetChilds())
		{
			CDObjBase* pDObjBase = dynamic_cast<CDObjBase*>(pDObject);
			if(pDObjBase) pDObjBase->SetPourSupprimer(bPourSupprimer);
			CDObjListe<TypeClass>* pDObjListe = dynamic_cast<CDObjListe<TypeClass>*>(pDObject);
			if(pDObjListe) pDObjListe->SetPourSupprimer(bPourSupprimer,bCascadeChild);
		}
	}
}

// Indique si l'objet � �t� acquis
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::EstAcquis() const
{
	return CDObjState::EstAcquis();
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetAcquis(bool bAcquis)
{
	CDObjState::SetAcquis(bAcquis);
}

// Indique si l'objet � �t� acquis
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::EstSupprimer() const
{
	return CDObjState::EstSupprimer();
}
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetSupprimer(bool bSupprimer)
{
	CDObjState::SetSupprimer(bSupprimer);
}

// Indique si l'objet est un nouvel objet : c'est � dire en cours de cr�ation
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::EstNouveau() const
{
	return CDObjState::EstNouveau();
}
//! Force l'objet � croire qu'il est nouveau
template<class TypeClass>
void DObject::CDObjListe<TypeClass>::SetNouveau()
{
	CDObjState::SetNouveau();
}

//! Indique si l'objet peut �tre initialis�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::PeutEtreInitialiser()
{
	return CDObjState::PeutEtreInitialiser();
}

//! Indique si l'objet doit �tre initialis�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::DoitEtreInitialiser()
{
	return CDObjState::DoitEtreInitialiser();
}

//! Indique si l'objet peut �tre sauv�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::PeutEtreSauver()
{
	return (m_liste.size() && CDObjState::PeutEtreSauver());
}

//! Indique si l'objet doit �tre sauv�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::DoitEtreSauver()
{
	return (m_liste.size() && CDObjState::DoitEtreSauver());
}

//! Indique si l'objet peut �tre supprim�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::PeutEtreSupprimer()
{
	return (m_liste.size() && CDObjState::PeutEtreSupprimer());
}

//! Indique si l'objet doit �tre supprim�
template<class TypeClass>
bool DObject::CDObjListe<TypeClass>::DoitEtreSupprimer()
{
	// Un objet doit �tre supprim� si :
	//  - Il est marqu� pour suppression
	//	- Il est modifi�
	//	- Il n'est pas supprim�

	return (m_liste.size() && EstPourSupprimer() && EstModifier() && !EstSupprimer());
}

