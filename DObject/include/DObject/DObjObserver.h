//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Pattern Observer dédié à la gestion des objets
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	08/07/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include <list>

// Inclusions
#include "DObject/DObjGlobal.h"


namespace DObject
{

	class DObjObservable;

	class DObjObservateur
	{
		friend class DObjObservable;

	public:
		//! Constructeur
		DObjObservateur() = default;
		//! Destructeur
		virtual ~DObjObservateur();

	public:
		//! Ajout dans la liste des objets à observer
		void RegisterObservable(DObjObservable* obs);
		//! Supprime dans la liste des objets à observer
		void RemoveObservable(DObjObservable* obs);

		//! Retourne le nombre d'observables
		size_t GetObservableCount();


	public:
		//! 
		virtual void OnNotify(const DObjObservable* observable) const {};
		//!
		virtual void OnNotifyEstModifie(const DObjObservable* observable) const {};
		virtual void OnNotifyPourSupprimer(const DObjObservable* observable) const {};
		virtual void OnNotifySupprimer(const DObjObservable* observable) const {};

	protected:
		//! gestion interne de la liste
		virtual void OnObjEnfantModifier(const DObjObservable* observable) = 0;
		virtual void OnObjEnfantPourSupprimer(const DObjObservable* observable) = 0;
		virtual void OnObjEnfantSupprimer(const DObjObservable* observable) = 0;


	protected:
		std::vector<DObjObservable*> m_observableListe;
	};


	class DObjObservable
	{
	public:
		//! Constructeur
		DObjObservable() = default;
		//! Destructeur
		virtual ~DObjObservable();

	public:
		//! Ajout dans la liste des observateurs qui observe l'objet
		void RegisterObservateur(DObjObservateur* obs);
		//! Supprime de la liste des observateurs qui observe l'objet
		void RemoveObservateur(DObjObservateur* obs);

		//! Retourne le nombre d'observateurs
		size_t GetObservateurCount();

		//! Retrourne l'observateur à l'index désiré
		DObjObservateur* GetObservateur(size_t iIndex);

	protected:
		//! Notifications
		void NotifierObservateur();
		void NotifierObservateur(NotificationEnfant Event);

	protected:
		std::vector<DObjObservateur*> m_observateurListe;
	};

}