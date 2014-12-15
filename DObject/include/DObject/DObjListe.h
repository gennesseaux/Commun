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
#include "DObject/IDObjListe.h"

// Inclusions
#include "Outils/TypeManip.h"
#include "Outils/static_check.h"


namespace DObject
{
	enum class ObjEtat { Valide, PourSupprimer };

	//
	class CDObjParent;

	// Classe template pour le stockage des objets
	template<class TypeClass = CDObjBase>
	class CDObjListe : public IDObjListe
	{
	public:
		//! Constructeur
		CDObjListe(void) { STATIC_CHECK(SUPERSUBCLASS(CDObjBase, TypeClass), Not_CDObjBase); };
		//! Destructeur
		virtual ~CDObjListe(void);
		//! Constructeur par copie.
		CDObjListe(const CDObjListe &source) = delete;
		//! Opérateur =
		CDObjListe &operator=(const CDObjListe &source) = delete;

	public:
		//! Initialisation de l'objet
		virtual bool Initialiser() = 0;
		//! Verification
		bool Verifier(std::string* sMsg = NULL);
		//! Sauvegarde
		bool Sauver();
		//! Suppression
		bool Supprimer();


	public:
		//! Ajout dans la liste
		size_t Add(TypeClass* pObj);
		
		//! Ajout d'une liste à la liste
		size_t Append(const CDObjListe& source);

		//! Insertion d'un élément dans la liste.
		void InsertAt(size_t nIndex, TypeClass* pObj);

		//! Copie d'une liste dans la liste
		void Copy(const CDObjListe& source);

		//! Suppression d'un objet dans la liste.
		void RemoveAt(size_t nIndex);

		//! Suppression d'un objet dans la liste.
		void Remove(IDObjBase* pIObjBase);

		//! Suppression d'un objet dans la liste.
		void RemoveFromId(unsigned long ulId);

		//! Suppression d'un objet dans la liste.
		void RemoveFromUUID(LPGUID uuid);

		//! Suppression de tous les objets de la liste.
		void RemoveAll();

		//! Retrouve un objet de la liste
		TypeClass* GetAt(size_t iIndex);
		//! Retrouve un objet de la liste
		TypeClass* GetAt(size_t iIndex, ObjEtat etat);

		//! Retourne le pointeur sur l'objet en fonction de son Id.
		TypeClass* GetFromId(unsigned long ulId);

		//! Retourne le pointeur sur l'objet en fonction de son UUID.
		TypeClass* GetFromUUID(LPGUID uuid);

		//! Nombre d'objet dans la liste
		size_t GetCount();
		//! Nombre d'objet dans la liste
		size_t GetCount(ObjEtat etat);
		//! Nombre d'objet dans la liste
		size_t GetSize();

		//! Tri par ID
		void SortById();
		void SortByModifie();
		void SortByPourSupprimer();

	// Surcharges de CDObjEtat
	public:
		//! Indique si l'objet est marqué pour suppression.
		void SetPourSupprimer(bool bPourSupprimer = true, bool bPropagerAuxEnfants = false);

		//! Indique si l'objet peut être initialisé
		virtual bool PeutEtreInitialiser() final;
		//! Indique si l'objet doit être initialisé
		virtual bool DoitEtreInitialiser() final;

		//! Indique si l'objet peut être sauvé
		virtual bool PeutEtreSauver() final;
		//! Indique si l'objet doit être sauvé
		virtual bool DoitEtreSauver() final;

		//! Indique si l'objet peut être supprimé
		virtual bool PeutEtreSupprimer() final;
		//! Indique si l'objet doit être supprimé
		virtual bool DoitEtreSupprimer() final;

	public:
		//! Ajout d'un parent de type CDObjEtat*
		void AddParent(CDObjEtat* pObjEtat);
		//! Retire un parent de type CDObjEtat*
		void RemoveParent(CDObjEtat* pObjEtat);
		//! Retourne le parent de type CDObjBase* ou CDObjBaseListe*
		template<class T> T GetParent();
	protected:
		//!
		void AddEnfant(CDObjEtat* pObjEtat);
		//!
		void RemoveEnfant(CDObjEtat* pObjEtat);

	public:
		//! Réallocation de la taille de la liste
		void Reserve(int iTaille) { m_liste.reserve(iTaille);  };

	//! Notifications
	protected:
		virtual void OnNotifyEstModifie(const DObjObservable* observable) const {};
		virtual void OnNotifyPourSupprimer(const DObjObservable* observable) const {};
		virtual void OnNotifySupprimer(const DObjObservable* observable) const {};

	//! Gestion interne de la liste des objets
	private:
		//! Mise à jour des compteurs d'objets valides ou pour suppression
		void UpdateValideSuppression(CDObjBase* pObjBase);

	//! Données
	private:
		//! Conteneur
		std::vector<TypeClass*>	m_liste;
		std::vector<LPGUID>		m_valide;
		std::vector<LPGUID>		m_pourSupprimer;

		//! Compteurs
		size_t m_iCountValide			= 0;
		size_t m_iCountPourSupprimer	= 0;

 		//! Parent de l'objet
 		CDObjParent* m_pParent			= nullptr;
		std::vector<IDObjBase*>		m_mObjBaseEnfant;
		std::vector<IDObjListe*>	m_mObjListeEnfant;
	};


	// Classe CDObjBaseListe
	class CDObjBaseListe : public CDObjListe<CDObjBase>
	{
		virtual bool Initialiser() { return true; }
	};

}

// Inclusions du fichier template contenant l'implémentation de la classe
#include "DObjListe.tpl.h"
