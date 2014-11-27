//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant la gestion des diff�rents �tat que peut prendre un objet
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	17/6/2014 : 
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
		//! Op�rateur =
		CDObjEtat &operator=(const CDObjEtat &source);
		////! Constructeur de d�placement.
		//CDObjEtat(CDObjEtat&& source);
		////! Op�rateur de d�placement
		//CDObjEtat &operator=(CDObjEtat&& source);

		//! Op�rateur ==
		bool operator==(const CDObjEtat &source) const;
		//! Op�rateur !=
		bool operator!=(const CDObjEtat &source) const;
		//! Clone les donn�es de l'objet.
		void ClonnerDonnees(const CDObjEtat &source);

	public:
		//! Indique si l'objet est initialis�
		virtual bool EstInitialiser() const;
		virtual void SetInitaliser(bool bInitaliser = true);

		//! Indique si l'objet � �t� modifi�
		virtual bool EstModifier() const;
		virtual void SetModifier(bool bModifier = true);

		//! Indique si l'objet � �t� modifi�
		virtual bool SontEnfantsModifier() const;
		virtual void SetEnfantsModifier(bool bEnfantModifier = true);

		//! Indique si l'objet est marqu� pour suppression.
		virtual bool EstPourSupprimer() const;
		virtual void SetPourSupprimer(bool bPourSupprimer = true);

		//! Indique si l'objet � �t� acquis
		virtual bool EstAcquis() const;
		virtual void SetAcquis(bool bAcquis = true);

		//! Indique si l'objet � �t� supprim�
		virtual bool EstSupprimer() const;
		virtual void SetSupprimer(bool bSupprimer = true);

		//! Indique si l'objet est un nouvelle objet : c'est � dire en cours de cr�ation.
		virtual bool EstNouveau() const;
		//! Force l'objet � croire qu'il est nouveau.
		virtual void SetNouveau();

		//! Indique si l'objet peut �tre initialis�
		virtual bool PeutEtreInitialiser();
		//! Indique si l'objet doit �tre initialis�
		virtual bool DoitEtreInitialiser();

		//! Indique si l'objet peut �tre sauv�
		virtual bool PeutEtreSauver();
		//! Indique si l'objet doit �tre sauv�
		virtual bool DoitEtreSauver();

		//! Indique si l'objet peut �tre supprim�
		virtual bool PeutEtreSupprimer();
		//! Indique si l'objet doit �tre supprim�
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