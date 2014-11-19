//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Définition des constantes ou méthodes globales
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/07/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include <vector>


namespace DObject
{
	class CDObjEtat;
	class CDObjBase;
	class CDObjBaseListe;

	class CDObjState
	{
	public:
		//! Constructeur
		CDObjState(CDObjEtat* pObjEtat);
		//! Constructeur
		CDObjState(CDObjBase* pObjBase);
		//! Destructeur
		virtual ~CDObjState(void) = default;

		//! Constructeur par copie.
		CDObjState(const CDObjState &source);


	protected:
		//! Constructeur
		CDObjState(void) = delete;
		//! Opérateur =
		CDObjState &operator=(const CDObjState &source) = delete;

	public:
		//! Restaure l'état de l'objet
		void Restore();

	private:
		// CDObjBase
		CDObjEtat*		m_pObjEtat = nullptr;
		CDObjBase*		m_pObjBase = nullptr;
		bool			m_bAutoDeleteFromList = true;
		unsigned long	m_ulId;

		// CDObjEtat
		bool		m_bInitaliser = false;
		bool		m_bModifier = false;
		bool		m_bPourSupprimer = false;
		bool		m_bAcquis = false;
		bool		m_bSupprimer = false;
	};



	class CDObjStateListe
	{
	public:
		//! Constructeur
		CDObjStateListe() = default;
		//! Destructeur
		virtual ~CDObjStateListe();

	public:
		//! Ajout dans la liste
		void Add(CDObjState& pObjSate);
		//! Ajout dans la liste
		void Add(CDObjBase* pObjBase);
		//! Ajout dans la liste
		void Add(CDObjBaseListe* pObjListe);
		//! Restaure l'état des objets
		void Restore();


	private:
		std::vector<CDObjState> m_vState;
		std::vector<CDObjState*> m_vStateToDelete;
	};
}


