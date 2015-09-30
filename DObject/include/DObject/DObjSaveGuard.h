//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	10/09/2015 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include <vector>

// Inclusions
#include "DObject/DObjState.h"
#include "DObject/DObjMemState.h"

namespace DObject
{
	class DObjSaveGuard
	{
	public:
		static DObjSaveGuard& SaveGuard()
		{
			// Since it's a static variable, if the class has already been created,
			// It won't be created again.
			// And it **is** thread-safe in C++11.

			static DObjSaveGuard _instance;

			// Return a reference to our instance.
			return _instance;
		}

	protected:
		//! Constructeur
		DObjSaveGuard();
		//! Destructeur
		virtual ~DObjSaveGuard(void);

	protected:
		DObjSaveGuard(DObjSaveGuard const&) = delete;             // Copy construct
		DObjSaveGuard(DObjSaveGuard&&) = delete;                  // Move construct
		DObjSaveGuard& operator=(DObjSaveGuard const&) = delete;  // Copy assign
		DObjSaveGuard& operator=(DObjSaveGuard &&) = delete;      // Move assign

	public:
		// todo
		static void Start(CDObjState* pDObjState);
		// todo
		static bool Sucess(CDObjState* pDObjState);
		// todo
		static bool Error(CDObjState* pDObjState);

	protected:
		void clear();

	protected:
		CDObjState* _pDObjState = nullptr;
		std::vector<CDObjMemState*> _memState;
		std::vector<CDObjState*> _toDelete;
	};
}
