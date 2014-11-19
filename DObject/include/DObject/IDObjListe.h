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
#include "DObject/DObjObserver.h"
#include "DObject/DObjBase.h"
#include "DObject/DObjState.h"


namespace DObject
{
	class IDObjListe : public CDObjEtat
	{
		friend class CDObjParent;

	protected:
		virtual ~IDObjListe() { };

	public:
		//! Initialisation de l'objet
		virtual bool Initialiser() = 0;


	public:
		//! Suppression d'un objet dans la liste.
		virtual void Remove(IDObjBase* pIObjBase) = 0;
		//! Suppression d'un objet dans la liste.
		virtual void RemoveFromUUID(LPGUID uuid) = 0;

	public:
		//! Ajout d'un parent de type CDObjEtat*
		virtual void AddParent(CDObjEtat* pObjEtat) = 0;
		//! Retire un parent de type CDObjEtat*
		virtual void RemoveParent(CDObjEtat* pObjEtat) = 0;

	//! Gestion interne de la liste des objets
	private:
		//! Mise à jour des compteurs d'objets valides ou pour suppression
		virtual void UpdateValideSuppression(CDObjBase* pObjBase) = 0;
	};

}