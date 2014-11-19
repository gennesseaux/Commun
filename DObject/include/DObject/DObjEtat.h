//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant la gestion des différents état que peut prendre un objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include "DObject/DObjGlobal.h"
#include "DObject/DObjObserver.h"
#include "DObject/DObjState.h"


namespace DObject
{
	class CDObjEtat : public DObjObservable
	{
		friend class CDObjState;

	public:
		//! Constructeur
		CDObjEtat(void) = default;
		//! Destructeur
		virtual ~CDObjEtat(void) = default;

		//! Constructeur par copie.
		CDObjEtat(const CDObjEtat &source);
		//! Opérateur =
		CDObjEtat &operator=(const CDObjEtat &source);
		//! Opérateur ==
		bool operator==(const CDObjEtat &source) const;
		//! Opérateur !=
		bool operator!=(const CDObjEtat &source) const;
		//! Clone les données de l'objet.
		void ClonnerDonnees(const CDObjEtat &source);

	public:
		//! Indique si l'objet est initialisé
		virtual bool EstInitialiser() const;
		virtual void SetInitaliser(bool bInitaliser = true);

		//! Indique si l'objet à été modifié
		virtual bool EstModifier() const;
		virtual void SetModifier(bool bModifier = true);

		//! Indique si l'objet à été modifié
		virtual bool SontEnfantsModifier() const;
		virtual void SetEnfantsModifier(bool bEnfantModifier = true);

		//! Indique si l'objet est marqué pour suppression.
		virtual bool EstPourSupprimer() const;
		virtual void SetPourSupprimer(bool bPourSupprimer = true);

		//! Indique si l'objet à été acquis
		virtual bool EstAcquis() const;
		virtual void SetAcquis(bool bAcquis = true);

		//! Indique si l'objet à été supprimé
		virtual bool EstSupprimer() const;
		virtual void SetSupprimer(bool bSupprimer = true);

		//! Indique si l'objet est un nouvelle objet : c'est à dire en cours de création.
		virtual bool EstNouveau() const;
		//! Force l'objet à croire qu'il est nouveau.
		virtual void SetNouveau();

		//! Indique si l'objet peut être initialisé
		virtual bool PeutEtreInitialiser();
		//! Indique si l'objet doit être initialisé
		virtual bool DoitEtreInitialiser();

		//! Indique si l'objet peut être sauvé
		virtual bool PeutEtreSauver();
		//! Indique si l'objet doit être sauvé
		virtual bool DoitEtreSauver();

		//! Indique si l'objet peut être supprimé
		virtual bool PeutEtreSupprimer();
		//! Indique si l'objet doit être supprimé
		virtual bool DoitEtreSupprimer();

	private:
		bool	m_bInitaliser		= false;
		bool	m_bModifier			= false;
		bool	m_bEnfantModifier	= false;
		bool	m_bPourSupprimer	= false;


		bool	m_bAcquis			= false;
		bool	m_bSupprimer		= false;
	};
}
