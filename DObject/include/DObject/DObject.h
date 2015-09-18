//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	02/09/2015 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include <vector>

// Inclusions
#include "DObjGlobal.h"
#include "DObject/IDObjEventNotification.h"
#include "Outils/NotificationClientRegistry.h"


namespace DObject
{
	class CDObject : public IDObjEventNotification, public Outils::NotificationClientEventRegistry<DObjEvent>
	{
	public:
		//! Constructeur
		CDObject(CDObject* pOwner = nullptr);
		//! Destructeur
		virtual ~CDObject(void);
		//! Constructeur par copie
		CDObject(const CDObject &source);														
		//! Opérateur =
		CDObject &operator=(const CDObject &source);
		//! Clone les données (Utilisé par le constructeur par copie et l'opérateur =)
		void ClonnerDonnees(const CDObject &source);

	// Gestion des relations parent enfant
	public:
		//! Ajout d'un parent
		virtual void AddOwner(CDObject* pOwner);
		//! Ajout d'un enfant
		virtual void AddChild(CDObject* pChild);
		//! Suppression d'un parent
		virtual void RemoveOwner(CDObject* pOwner);
		//! Suppression d'un enfant
		virtual void RemoveChild(CDObject* pChild);

		//! Nombre de parent
		size_t GetOwnerCount() const;
		//! Nombre d'enfant
		size_t GetChildCount() const;

		//! Test le lien de parenté
		bool IsOwner(CDObject* pObject) const;
		//! Test le lien de parenté
		bool IsChild(CDObject* pObject) const;

		//! Test le lien de parenté
		bool HasOwner(CDObject* pObject) const;
		//! Test le lien de parenté
		bool HasChild(CDObject* pObject) const;

		//! Retourne la liste des parents
		std::vector<CDObject*>&& GetOwners();
		//! Retourne la liste des enfants
		std::vector<CDObject*>&& GetChilds();

		//! Retourne le premier parent
		CDObject* GetOwner();
		//! Retourne un parent en fonction de son index dans la liste
		CDObject* GetOwner(unsigned int iIndex);
		//! Retourne un enfant en fonction de son index dans la liste
		CDObject* GetChild(unsigned int iIndex);

	private:
		// Gestion des relations parent enfant
		std::vector<CDObject*> m_vOwners;
		std::vector<CDObject*> m_vChilds;
	};
 }
