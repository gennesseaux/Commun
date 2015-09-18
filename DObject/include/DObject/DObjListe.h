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
#include "DObject/DObjGlobal.h"
#include "DObject/DObject.h"
#include "DObject/DObjState.h"
#include "DObject/DObjUuid.h"
#include "DObject/DObjSaveGuard.h"

// Inclusions
#include "Outils/TypeManip.h"
#include "Outils/static_check.h"


namespace DObject
{
	enum class ObjEtat { Valide, PourSupprimer };

	// Classe template pour le stockage des objets
	template<class TypeClass = CDObjBase>
	class CDObjListe : public CDObject, public CDObjState
	{
	public:
		//! Constructeur
		CDObjListe(CDObject* pOwner = nullptr) : CDObject(pOwner) { STATIC_CHECK(SUPERSUBCLASS(CDObjBase, TypeClass), Not_CDObjBase); };
		//! Destructeur
		virtual ~CDObjListe(void);
		//! Constructeur par copie.
		CDObjListe(const CDObjListe &source) = delete;
		//! Op�rateur =
		CDObjListe &operator=(const CDObjListe &source) = delete;
		//! Clone les donn�es
		void ClonnerDonnees(const CDObjListe &source) { 
			CDObjState::ClonnerDonnees(source);
			CDObject::ClonnerDonnees(source);
			Copy(source);
		};

		//! Pointeur vers CDObject
		virtual CDObject* GetDObject();

	// Gestion des donn�es
	public:
		//! Initialise les donn�es de l'objet.
		virtual void InitialiserDonnees() = 0;
		//! Initialisation de l'objet
		virtual bool Initialiser() = 0;
		//! Verification
		bool Verifier(std::string* sMsg = NULL);
		//! Sauvegarde
		bool Sauver();
		//! Suppression
		bool Supprimer();

	// Gestion des relations parent enfant
	public:
		//! Suppression d'un enfant
		virtual void RemoveChild(CDObject* pChild);

	// Gestion des �v�nements
	public:
		//! Notification d'�v�nement
		virtual void OnEvent(DObjEvent& event, CDObject* sender) final;

	// Gestion de la liste
	public:
		//! Ajout dans la liste
		size_t Add(TypeClass* pObj);
		
		//! Ajout d'une liste � la liste
		size_t Append(const CDObjListe& source);

		//! Insertion d'un �l�ment dans la liste.
		void InsertAt(size_t nIndex, TypeClass* pObj);

		//! Copie d'une liste dans la liste
		void Copy(const CDObjListe& source);

		//! Suppression d'un objet dans la liste.
		TypeClass* RemoveAt(size_t nIndex);

		//! Suppression d'un objet dans la liste.
		TypeClass* Remove(TypeClass* pObj);

		//! Suppression d'un objet dans la liste.
		TypeClass* RemoveFromId(unsigned long ulId);

		//! Suppression d'un objet dans la liste.
		TypeClass* RemoveFromUUID(LPGUID uuid);

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

	// Accesseurs
	public:
		//! Indique si l'objet est initialis�
		virtual bool EstInitialiser() const final;
		virtual void SetInitaliser(bool bInitaliser = true) final;
		
		//! Indique si l'objet � �t� modifi�
		virtual bool EstModifier() const final;
		virtual void SetModifier(bool bModifier = true) final;
		
		//! Indique si l'item � des objets membre modifi�s
		virtual bool SontEnfantsModifier() const final;
		virtual void SetEnfantsModifier(bool bEnfantModifier = true) final;
		
		//! Indique si l'objet est marqu� pour suppression.
		virtual bool EstPourSupprimer() const final;
		virtual void SetPourSupprimer(bool bPourSupprimer = true) final;
		virtual void SetPourSupprimer(bool bPourSupprimer, bool bCascadeChild) final;
		virtual void SetPourSupprimer(bool bPourSupprimer, bool bCascadeChild, bool bChildOnly) final;
		
		//! Indique si l'objet � �t� acquis
		virtual bool EstAcquis() const final;
		virtual void SetAcquis(bool bAcquis = true) final;

		//! Indique si l'objet � �t� supprim�
		virtual bool EstSupprimer() const final;
		virtual void SetSupprimer(bool bSupprimer = true) final;
		
		//! Indique si l'objet est un nouvel objet : c'est � dire en cours de cr�ation.
		virtual bool EstNouveau() const final;
		//! Force l'objet � croire qu'il est nouveau.
		virtual void SetNouveau() final;

		//! Indique si l'objet peut �tre initialis�
		virtual bool PeutEtreInitialiser() final;
		//! Indique si l'objet doit �tre initialis�
		virtual bool DoitEtreInitialiser() final;

		//! Indique si l'objet peut �tre sauv�
		virtual bool PeutEtreSauver() final;
		//! Indique si l'objet doit �tre sauv�
		virtual bool DoitEtreSauver() final;

		//! Indique si l'objet peut �tre supprim�
		virtual bool PeutEtreSupprimer() final;
		//! Indique si l'objet doit �tre supprim�
		virtual bool DoitEtreSupprimer() final;

	public:
		//! R�allocation de la taille de la liste
		void Reserve(int iTaille) { m_liste.reserve(iTaille);  };

	//! Gestion interne de la liste des objets
	private:
		//! Mise � jour des compteurs d'objets valides ou pour suppression
		void UpdateValideSuppression(CDObjBase* pObjBase);

	//! Donn�es
	private:
		//! Conteneur
		std::vector<TypeClass*>	m_liste;
		std::vector<LPGUID>		m_valide;
		std::vector<LPGUID>		m_pourSupprimer;

		//! Compteurs
		size_t m_iCountValide			= 0;
		size_t m_iCountPourSupprimer	= 0;
	};
}

// Inclusions du fichier template contenant l'impl�mentation de la classe
#include "DObjListe.tpl.h"
