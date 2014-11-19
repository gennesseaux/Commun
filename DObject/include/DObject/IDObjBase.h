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
#include "DObject/DObjEtat.h"
#include "DObject/DObjUuid.h"
#include "DObject/DObjState.h"


namespace DObject
{
	class IDObjBase : public CDObjEtat, public CDObjUuid
	{
	protected:
		virtual ~IDObjBase() { };

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

	public:
		//! Ajout d'un parent de type CDObjEtat*
		virtual void AddParent(CDObjEtat* pObjEtat) = 0;
		//! Retire un parent de type CDObjEtat*
		virtual void RemoveParent(CDObjEtat* pObjEtat) = 0;
	};

}