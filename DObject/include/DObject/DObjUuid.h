//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant de donner un identifiant unique à chaque objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include "rpc.h"

// Linkage automatique avec la lib Rpcrt4
#pragma comment(lib, "Rpcrt4.lib")


namespace DObject
{
	class CDObjUuid
	{
	public:
		//! Constructeur
		CDObjUuid(void);
		//! Destructeur
		virtual ~CDObjUuid(void);

		//! Constructeur par copie.
		CDObjUuid(const CDObjUuid &source);
		//! Opérateur =
		CDObjUuid &operator=(const CDObjUuid &source);

		//! Clone les données de l'objet.
		void ClonnerDonnees(const CDObjUuid &source);

		//! Opérateur ==
		bool operator==(const CDObjUuid &source) const;
		//! Opérateur !=
		bool operator!=(const CDObjUuid &source) const;


	public:
		//! Retourne l'identifiant unique
		LPGUID GetLPGUID();

	private:
		UUID	m_uuid;
	};
}
