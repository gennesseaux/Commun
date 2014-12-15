//	-----------------------------------------------------------------------------
//
//	 Classe			:	CCDObjParent\n
//	 Fichier		: 	CDObjParent.h\n
//
//	 Auteur			:	GENNESSEAUX Jocelyn\n
//
//	 Description	:	Classe de gestion des relations parents enfants\n
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/7/2014 : 
//	-----------------------------------------------------------------------------


#pragma once


// Inclusions
#include <string>
#include <map>
#include <typeinfo>

// Inclusions
#include "DObject/DObjObserver.h"
#include "DObject/IDObjBase.h"
#include "DObject/IDObjListe.h"


namespace DObject
{
	template<class TypeClass = CDObjBase> class CDObjListe;

	class CDObjParent : public DObjObservateur
	{
	public:
		//! Constructeur
		CDObjParent(void) = default;
		//! Destructeur
		virtual ~CDObjParent(void) = default;

		//! Constructeur par copie.
		CDObjParent(const CDObjParent &source);
		//! Opérateur =
		CDObjParent &operator=(const CDObjParent &source) = delete;

	public:
		//! Ajout d'un parent de type IDObjBase*
		void Add(IDObjBase* pIObjEnfant);
		//! Ajout d'un parent de type IDObjListe*
		void Add(IDObjListe* pIObjEnfantListe);

		//! Retire un parent de type IDObjBase*
		void Remove(IDObjBase* pIObjEnfant);
		//! Retire un parent de type IDObjListe*
		void Remove(IDObjListe* pIObjEnfantListe);

		//! Retourne le nombre de parents
		size_t GetCount();


		//! Retourne le parent
		template<class T> T Get();

		//!
		virtual void OnObjEnfantModifier(const DObjObservable* observable);

		//!
		virtual void OnObjEnfantPourSupprimer(const DObjObservable* observable);

		//!
		virtual void OnObjEnfantSupprimer(const DObjObservable* observable);

	private:
		std::vector<IDObjBase*>			m_mObjBaseParent;
		std::vector<IDObjListe*>		m_mObjListeParent;
	};


	//! Retourne le parent
	template<class T>
	T DObject::CDObjParent::Get()
	{
 		//
 		for (auto &parent : m_mObjBaseParent)
 		{
 			T pObjBase = dynamic_cast<T>(parent);
 			if (pObjBase)
 				return dynamic_cast<T>(parent);
 		}
 
 		//
 		for (auto &parent : m_mObjListeParent)
 		{
 			T pObjBaseListe = dynamic_cast<T>(parent);
 			if (pObjBaseListe)
 				return dynamic_cast<T>(parent);
 		}

		return nullptr;
	}
}
