//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de base d'un objet
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	18/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include "DObject/IDObjBase.h"


namespace DObject
{
	class CDObjParent;

	class CDObjBase : public IDObjBase
	{
		friend class CDObjState;

	public:
		//! Constructeur
		CDObjBase(unsigned long ulId = DefULong);
		//! Destructeur est d�clar� protected, il faut utiliser une des m�thodes delete ci-dessus.
		virtual ~CDObjBase(void);
		//! Constructeur par copie
		CDObjBase(const CDObjBase &source);														
		//! Op�rateur =
		CDObjBase &operator=(const CDObjBase &source);
		////! Constructeur de d�placement
		//CDObjBase(CDObjBase&& source);														
		////! Op�rateur de d�placement
		//CDObjBase &operator=(CDObjBase&& source);
		//! Clone les donn�es (Utilis� par le constructeur par copie et l'op�rateur =)
		void ClonnerDonnees(const CDObjBase &source);

		//! Delete
		CDObjBase* Delete();
		//! Delete
		static CDObjBase* Delete(CDObjBase* pObjBase);

	public:
		//! Initialise les donn�es de l'objet.
		virtual void InitialiserDonnees() = 0;
		//! Initialisation de l'objet
		virtual bool Initialiser() = 0;
		//! V�rifie la coh�rence des donn�es de l'instance et retourne un �ventuel message d'erreur.
		//! Il est conseill� d'utiliser cette m�thode avant Sauver.
		virtual bool Verifier(std::string* sMsg = NULL) = 0;
		//! Enregistre l'instance en base.
		virtual bool Sauver() = 0;
		//! Supprime l'instance en base.
		virtual bool Supprimer() = 0;


	// Accesseurs
	public:
		//! Retourne l'identifiant de l'objet
		virtual long GetId() const final;

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
		//! Ajout d'un parent de type CDObjEtat*
		void AddParent(CDObjEtat* pObjEtat);
		//! Retire un parent de type CDObjEtat*
		void RemoveParent(CDObjEtat* pObjEtat);
		//! Retourne le parent de type CDObjBase* ou CDObjBaseListe*
		template<class T> T GetParent();


	public:
		//! Pr�dicat de comparaison des objet 
		static bool CompareIdPredicate(const CDObjBase* _Left, const CDObjBase* _Right) { return (_Left->m_ulId < _Right->m_ulId); }
		static bool CompareModifiePredicate(const CDObjBase* _Left, const CDObjBase* _Right) { return (_Left->EstModifier() < _Right->EstModifier()); }
		static bool ComparePourSupprimerPredicate(const CDObjBase* _Left, const CDObjBase* _Right) { return (_Left->EstPourSupprimer() < _Right->EstPourSupprimer()); }

	public:
		//! Autorise les listes � d�trure l'objet
		bool m_bAutoDeleteFromList = true;

	protected:
		//! Identifiant de l'objet
		unsigned long	m_ulId;

 		//! Parent de l'objet
		CDObjParent*	m_pParent = nullptr;
	};
 
 	//! Retourne le parent de type CDObjEtat*
 	template<class T>
 	T DObject::CDObjBase::GetParent()
 	{
		if (!m_pParent)
			return nullptr;

		return m_pParent->Get<T>();
	}

}
