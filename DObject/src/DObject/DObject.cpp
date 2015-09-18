//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	02/09/2015 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "DObject/DObject.h"

namespace DObject
{
	//! Constructeur
	CDObject::CDObject(CDObject* pOwner /*= nullptr*/)
	{
		if(pOwner!=nullptr) this->AddOwner(pOwner);
	}

	//! Destructeur
	CDObject::~CDObject(void)
	{
		notifyClient(DObjEvent::ObjetSupprimerEvent);

		for(unsigned int i=m_vOwners.size();i-->0;)
			this->RemoveOwner(m_vOwners[i]);
		for(unsigned int i=m_vChilds.size();i-->0;)
			this->RemoveChild(m_vChilds[i]);
	}

	//! Constructeur par recopie
	CDObject::CDObject(const CDObject& source)
	{
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObject& CDObject::operator=(const CDObject& source)
	{
		return *this;
	}
	
	void CDObject::ClonnerDonnees(const CDObject &source)
	{
		for(unsigned int i=0;i<source.m_vOwners.size();i++)
			this->AddOwner(source.m_vOwners[i]);
		for(unsigned i=0;i<source.m_vChilds.size();i++)
			this->AddChild(source.m_vChilds[i]);
	}

	//! Ajout d'un parent
	void CDObject::AddOwner(CDObject* pOwner)
	{
		auto it = std::find(m_vOwners.begin(),m_vOwners.end(),pOwner);

		if(it == m_vOwners.end())
		{
			m_vOwners.emplace_back(pOwner);

			pOwner->AddChild(this);
		}
	}

	//! Ajout d'un enfant
	void CDObject::AddChild(CDObject* pChild)
	{
		auto it = std::find(m_vChilds.begin(),m_vChilds.end(),pChild);

		if(it == m_vChilds.end())
		{
			m_vChilds.emplace_back(pChild);

			pChild->AddOwner(this);

			pChild->registerClient(DObjEvent::ObjetModifierEvent,std::bind(&CDObject::OnEvent, this, DObjEvent::ObjetModifierEvent, pChild));
			pChild->registerClient(DObjEvent::ObjetSauverEvent,std::bind(&CDObject::OnEvent, this, DObjEvent::ObjetSauverEvent, pChild));
			pChild->registerClient(DObjEvent::ObjetPourSupprimerEvent,std::bind(&CDObject::OnEvent, this, DObjEvent::ObjetPourSupprimerEvent, pChild));
			pChild->registerClient(DObjEvent::ObjetSupprimerEvent,std::bind(&CDObject::OnEvent, this, DObjEvent::ObjetSupprimerEvent, pChild));
		}
	}

	//! Suppression d'un parent
	void CDObject::RemoveOwner(CDObject* pOwner)
	{
		auto it = std::find(m_vOwners.begin(),m_vOwners.end(),pOwner);

		if(it != m_vOwners.end())
		{
			m_vOwners.erase(it);

			pOwner->RemoveChild(this);
		}
	}

	//! Suppression d'un enfant
	void CDObject::RemoveChild(CDObject* pChild)
	{
		auto it = std::find(m_vChilds.begin(),m_vChilds.end(),pChild);

		if(it != m_vChilds.end())
		{
			m_vChilds.erase(it);

			pChild->RemoveOwner(this);

			pChild->removeClient(DObjEvent::ObjetModifierEvent);
			pChild->removeClient(DObjEvent::ObjetSauverEvent);
			pChild->removeClient(DObjEvent::ObjetPourSupprimerEvent);
			pChild->removeClient(DObjEvent::ObjetSupprimerEvent);
		}
	}

	//! Nombre de parent
	size_t CDObject::GetOwnerCount() const
	{
		return m_vOwners.size();
	}

	//! Nombre d'enfant
	size_t CDObject::GetChildCount() const
	{
		return m_vChilds.size();
	}

	//! Test le lien de parenté
	bool CDObject::IsOwner(CDObject* pObject) const
	{
		auto it = std::find(pObject->GetOwners().begin(),pObject->GetOwners().end(),this);
		return it != pObject->GetOwners().end();
	}

	//! Test le lien de parenté
	bool CDObject::IsChild(CDObject* pObject) const
	{
		auto it = std::find(pObject->GetChilds().begin(),pObject->GetChilds().end(),this);
		return it != pObject->GetChilds().end();
	}

	//! Test le lien de parenté
	bool CDObject::HasOwner(CDObject* pObject) const
	{
		auto it = std::find(m_vOwners.begin(),m_vOwners.end(),pObject);
		return it != m_vOwners.end();
	}

	//! Test le lien de parenté
	bool CDObject::HasChild(CDObject* pObject) const
	{
		auto it = std::find(m_vChilds.begin(),m_vChilds.end(),pObject);
		return it != m_vChilds.end();
	}

	//! Retourne la liste des parents
	std::vector<CDObject*>&& CDObject::GetOwners()
	{
		return std::move(m_vOwners);
	}

	//! Retourne la liste des enfants
	std::vector<CDObject*>&& CDObject::GetChilds()
	{
		return std::move(m_vChilds);
	}

	//! Retourne le premier parent
	CDObject* CDObject::GetOwner()
	{
		return m_vOwners.size()>=1 ? m_vOwners[0] : nullptr;
	}

	//! Retourne un parent en fonction de son indxex dans la liste
	CDObject* CDObject::GetOwner(unsigned int iIndex)
	{
		return m_vOwners[iIndex];
	}

	//! Retourne un enfant en fonction de son indxex dans la liste
	CDObject* CDObject::GetChild(unsigned int iIndex)
	{
		return m_vChilds[iIndex];
	}

}
