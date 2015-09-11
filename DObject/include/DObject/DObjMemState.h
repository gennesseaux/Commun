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
	class CDObjState;

	class CDObjMemState
	{
		friend class DObjSaveGuard;

	public:
		//! Constructeur
		CDObjMemState(CDObjState* pObjState);
		//! Destructeur
		virtual ~CDObjMemState(void) = default;



	protected:
		//! Constructeur
		CDObjMemState(void) = delete;
		//! Constructeur par copie.
		CDObjMemState(const CDObjMemState &source) = delete;
		//! Opérateur =
		CDObjMemState &operator=(const CDObjMemState &source) = delete;

	public:
		//! Restaure l'état de l'objet
		void Restore();

	private:
		// CDObjBase
		CDObjState*		m_pObjState = nullptr;

		// CDObjEtat
		bool			m_bInitaliser = false;
		bool			m_bModifier = false;
		bool			m_bPourSupprimer = false;
		bool			m_bAcquis = false;
		bool			m_bSupprimer = false;
	};


	//class CDObjMemStateListe
	//{
	//public:
	//	//! Constructeur
	//	CDObjMemStateListe() = default;
	//	//! Destructeur
	//	virtual ~CDObjMemStateListe();

	//	
	//protected:
	//	//! Constructeur par copie.
	//	CDObjMemStateListe(const CDObjMemStateListe &source) = delete;
	//	//! Opérateur =
	//	CDObjMemStateListe &operator=(const CDObjMemStateListe &source) = delete;


	//public:
	//	//! Ajout dans la liste
	//	void Add(CDObjState* pObjState);
	//	//! Restaure l'état des objets
	//	void Restore();


	//private:
	//	std::vector<CDObjMemState*> m_vState;
	//};
}


