// ---------------------------------------------------------------------------- -
//
//	 Classe			:	CCDObjParent\n
//	 Fichier		: 	CDObjParent.h\n
//
//	 Auteur			:	GENNESSEAUX Jocelyn\n
//
//	 Description	:	Classe de gestion des relations parents enfants\n
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	20/10/2014 : 
//	-----------------------------------------------------------------------------


// Inclusions
#include "DObject/DObjParent.h"


//! Constructeur par copie.
DObject::CDObjParent::CDObjParent(const CDObjParent &source)
{
	m_mObjBaseParent = source.m_mObjBaseParent;
	m_mObjListeParent = source.m_mObjListeParent;
}

//! Ajout d'un parent de type IDObjBase*
void DObject::CDObjParent::Add(IDObjBase* pIObjBase)
{
	bool bExiste = false;
	for (auto &parent : m_mObjBaseParent)
	{
		IDObjBase* pParent = parent;
		if (pParent == pIObjBase)
			bExiste = true;
	}
	if (!bExiste)
		m_mObjBaseParent.emplace_back(pIObjBase);
}

//! Ajout d'un parent de type IDObjListe*
void DObject::CDObjParent::Add(IDObjListe* pObjBaseListe)
{
	bool bExiste = false;
	for (auto &parent : m_mObjListeParent)
	{
		IDObjListe* pParent = parent;
		if (pParent == pObjBaseListe)
			bExiste = true;
	}
	if (!bExiste)
		m_mObjListeParent.emplace_back(pObjBaseListe);
}

void DObject::CDObjParent::Remove(IDObjBase* pIObjBase)
{
	auto it = std::find(m_mObjBaseParent.begin(), m_mObjBaseParent.end(), pIObjBase);

	if (it != m_mObjBaseParent.end())
		m_mObjBaseParent.erase(it);
}

void DObject::CDObjParent::Remove(IDObjListe* pObjListe)
{
	auto it = std::find(m_mObjListeParent.begin(), m_mObjListeParent.end(), pObjListe);

	if (it != m_mObjListeParent.end())
		m_mObjListeParent.erase(it);
}

size_t DObject::CDObjParent::GetCount()
{
	return m_mObjBaseParent.size() + m_mObjListeParent.size();
}

void DObject::CDObjParent::OnObjEnfantModifier(const DObjObservable* observable)
{
	for (auto &parent : m_mObjBaseParent)
	{
		IDObjBase* pIObjBase = parent;
		pIObjBase->SetEnfantsModifier(true);
	}
	for (auto &parent : m_mObjListeParent)
	{
		IDObjListe* pObjBaseListe = parent;
		pObjBaseListe->SetEnfantsModifier(true);
	}
}

void DObject::CDObjParent::OnObjEnfantPourSupprimer(const DObjObservable* observable)
{
	for (auto &parent : m_mObjBaseParent)
	{
		IDObjBase* pIObjBase = parent;
		pIObjBase->SetEnfantsModifier(true);
	}
	for (auto &parent : m_mObjListeParent)
	{
		IDObjListe* pObjBaseListe = parent;
		pObjBaseListe->UpdateValideSuppression((CDObjBase*)observable);
		pObjBaseListe->SetEnfantsModifier(true);
	}
}

void DObject::CDObjParent::OnObjEnfantSupprimer(const DObjObservable* observable)
{
	IDObjBase* pIObjBase = dynamic_cast<IDObjBase*>((DObjObservable*)observable);
	if (pIObjBase)
	{
		while (m_mObjBaseParent.size())
		{
			IDObjBase* pObjBase = m_mObjBaseParent[0];
			pObjBase->RemoveParent(pIObjBase);
		}
		while (m_mObjListeParent.size())
		{
			IDObjListe* pObjBaseListe = m_mObjListeParent[0];
			pObjBaseListe->RemoveParent(pIObjBase);
			pObjBaseListe->Remove(pIObjBase);
		}
		return;
	}

	IDObjListe* pObjBaseListe = dynamic_cast<IDObjListe*>((DObjObservable*)observable);
	if (pObjBaseListe)
	{
		while (m_mObjBaseParent.size())
		{
			IDObjBase* pObjBase = m_mObjBaseParent[0];
			pObjBase->RemoveParent(pObjBaseListe);
		}
		while (m_mObjListeParent.size())
		{
			IDObjListe* pObjBaseListe = m_mObjListeParent[0];
			pObjBaseListe->RemoveParent(pObjBaseListe);
		}
		return;
	}
}




