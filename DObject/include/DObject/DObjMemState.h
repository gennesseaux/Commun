//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	D�finition des constantes ou m�thodes globales
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	17/07/2014 : 
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
		//! Op�rateur =
		CDObjMemState &operator=(const CDObjMemState &source) = delete;

	public:
		//! Restaure l'�tat de l'objet
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
	//	//! Op�rateur =
	//	CDObjMemStateListe &operator=(const CDObjMemStateListe &source) = delete;


	//public:
	//	//! Ajout dans la liste
	//	void Add(CDObjState* pObjState);
	//	//! Restaure l'�tat des objets
	//	void Restore();


	//private:
	//	std::vector<CDObjMemState*> m_vState;
	//};
}


