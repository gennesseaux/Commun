//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Pattern Observer dédié à la gestion des objets
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	08/07/2014 : 
//	-----------------------------------------------------------------------------


// Inclusions
#include "DObject/DobjObserver.h"

namespace DObject
{

	//! Destructeur
	DObjObservateur::~DObjObservateur()
	{
		size_t iCount = m_observableListe.size();
		while (iCount > 0)
		{
			auto it = m_observableListe.begin();
			(*it)->RemoveObservateur(this);
			--iCount;
		}
	}

	//! Ajout dans la liste des objets à observer
	void DObjObservateur::RegisterObservable(DObjObservable* obs)
	{
		auto it = std::find(m_observableListe.begin(), m_observableListe.end(), obs);

		// On ajoute que si l'observé n'est pas déjà présent dans la liste
		if (it == m_observableListe.end())
			m_observableListe.push_back(obs);
	}

	//! Supprime dans la liste des objets à observer
	void DObjObservateur::RemoveObservable(DObjObservable* obs)
	{
		auto it = std::find(m_observableListe.begin(), m_observableListe.end(), obs);

		if (it != m_observableListe.end())
			m_observableListe.erase(it);
	}

	//! Retourne le nombre d'observables
	size_t DObjObservateur::GetObservableCount()
	{
		return m_observableListe.size();
	}





	//! Destructeur
	DObjObservable::~DObjObservable()
	{
		assert(m_observateurListe.size() == 0);
	}

	//! Ajout dans la liste des observateurs qui observe l'objet
	void DObjObservable::RegisterObservateur(DObjObservateur* obs)
	{
		auto it = std::find(m_observateurListe.begin(), m_observateurListe.end(), obs);

		//on ajoute l'observateur à notre liste 
		if (it == m_observateurListe.end())
			m_observateurListe.push_back(obs);

		//et on lui donne un nouvel objet observé.
		obs->RegisterObservable(this);
	}

	//! Supprime de la liste des observateurs qui observe l'objet
	void DObjObservable::RemoveObservateur(DObjObservateur* obs)
	{
		auto it = std::find(m_observateurListe.begin(), m_observateurListe.end(), obs);

		if (it != m_observateurListe.end())
			m_observateurListe.erase(it);

		obs->RemoveObservable(this);
	}

	//! Retourne le nombre d'observateurs
	size_t DObjObservable::GetObservateurCount()
	{
		return m_observateurListe.size();
	}

	//! Retrourne l'observateur à l'index désiré
	DObjObservateur* DObjObservable::GetObservateur(size_t iIndex)
	{
		return m_observateurListe[iIndex];
	}

	//! Notifications
	void DObjObservable::NotifierObservateur()
	{
		for (auto it = m_observateurListe.begin(); it != m_observateurListe.end(); ++it)
		{
			(*it)->OnNotify(this);
		}
	}

	//! Notifications
	void DObjObservable::NotifierObservateur(NotificationEnfant Event)
	{
		if (Event == NotificationEnfant::EnfantSupprimer)
		{
			while (m_observateurListe.size())
			{
				DObjObservateur* obs = m_observateurListe[0];
				obs->OnNotifySupprimer(this);
				obs->OnObjEnfantSupprimer(this);
			}
		}
		else
		{
			for (auto it = m_observateurListe.begin(); it != m_observateurListe.end(); ++it)
			{
				switch (Event)
				{
				case NotificationEnfant::EnfantModifier:			{(*it)->OnObjEnfantModifier(this);		(*it)->OnNotifyEstModifie(this); }		break;
				case NotificationEnfant::EnfantPourSupprimer:		{(*it)->OnObjEnfantPourSupprimer(this);	(*it)->OnNotifyPourSupprimer(this); }	break;
				default:											{(*it)->OnNotify(this); }														break;
				}
			}
		}
	}
}
