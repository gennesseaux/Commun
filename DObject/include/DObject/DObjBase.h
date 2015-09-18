//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de base d'un objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	18/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include "DObject/DObjGlobal.h"
#include "DObject/DObject.h"
#include "DObject/DObjState.h"
#include "DObject/DObjUuid.h"
#include "DObject/DObjSaveGuard.h"


namespace DObject
{
	class CDObjBase : public CDObject, public CDObjState, public CDObjUuid
	{
		friend class CDObjMemState;

	public:
		//! Constructeur
		CDObjBase(unsigned long ulId = DefULong, CDObject* pOwner = nullptr);
		//! Destructeur
		virtual ~CDObjBase(void);

		//! Constructeur par copie
		CDObjBase(const CDObjBase &source);														
		//! Opérateur =
		CDObjBase &operator=(const CDObjBase &source);
		//! Clone les données (Utilisé par le constructeur par copie et l'opérateur =)
		void ClonnerDonnees(const CDObjBase &source);

		//! Delete
		CDObjBase* Delete();
		//! Delete
		static CDObjBase* Delete(CDObjBase* pObjBase);

		//! Pointeur vers CDObject
		virtual CDObject* GetDObject();


	// Gestion des données
	public:
		//! Initialise les données de l'objet.
		virtual void InitialiserDonnees() = 0;
		//! Initialisation de l'objet
		virtual bool Initialiser() = 0;
		//! Vérifie la cohérence des données de l'instance et retourne un éventuel message d'erreur.
		//! Il est conseillé d'utiliser cette méthode avant Sauver.
		virtual bool Verifier(std::string* sMsg = NULL) = 0;
		//! Enregistre l'instance en base.
		virtual bool Sauver() = 0;
		//! Supprime l'instance en base.
		virtual bool Supprimer() = 0;

	// Gestion des évènements
	protected:
		//! Notification d'évènement
		virtual void OnEvent(DObjEvent& event, CDObject* sender) final;


	// Accesseurs
	public:
		//! Retourne l'identifiant de l'objet
		virtual long GetId() const final;

		//! Indique si l'objet est initialisé
		virtual bool EstInitialiser() const final;
		virtual void SetInitaliser(bool bInitaliser = true) final;

		//! Indique si l'objet à été modifié
		virtual bool EstModifier() const final;
		virtual void SetModifier(bool bModifier = true) final;

		//! Indique si l'item à des objets membre modifiés
		virtual bool SontEnfantsModifier() const final;
		virtual void SetEnfantsModifier(bool bEnfantModifier = true) final;

		//! Indique si l'objet est marqué pour suppression.
		virtual bool EstPourSupprimer() const final;
		virtual void SetPourSupprimer(bool bPourSupprimer = true) final;
		virtual void SetPourSupprimer(bool bPourSupprimer, bool bCascadeChild) final;

		//! Indique si l'objet à été acquis
		virtual bool EstAcquis() const final;
		virtual void SetAcquis(bool bAcquis = true) final;

		//! Indique si l'objet à été supprimé
		virtual bool EstSupprimer() const final;
		virtual void SetSupprimer(bool bSupprimer = true) final;

		//! Indique si l'objet est un nouvel objet : c'est à dire en cours de création.
		virtual bool EstNouveau() const final;
		//! Force l'objet à croire qu'il est nouveau.
		virtual void SetNouveau() final;

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
		//! Prédicat de comparaison des objet 
		static bool CompareIdPredicate(const CDObjBase* _Left, const CDObjBase* _Right) { return (_Left->m_ulId < _Right->m_ulId); }
		static bool CompareModifiePredicate(const CDObjBase* _Left, const CDObjBase* _Right) { return (_Left->EstModifier() < _Right->EstModifier()); }
		static bool ComparePourSupprimerPredicate(const CDObjBase* _Left, const CDObjBase* _Right) { return (_Left->EstPourSupprimer() < _Right->EstPourSupprimer()); }

	public:
		//! Autorise les listes à détruire l'objet
		bool m_bAutoDeleteFromList = true;

	protected:
		//! Identifiant de l'objet
		unsigned long	m_ulId;
	};
 }
