//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant de donner un identifiant unique � chaque objet
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	17/6/2014 : 
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

		//! Op�rateur ==
		bool operator==(const CDObjUuid &source) const;
		//! Op�rateur !=
		bool operator!=(const CDObjUuid &source) const;


	protected:
		//! Constructeur par copie.
		CDObjUuid(const CDObjUuid &source) = delete;
		//! Op�rateur =
		CDObjUuid &operator=(const CDObjUuid &source) = delete;


	public:
		//! Retourne l'identifiant unique
		LPGUID GetLPGUID();

	private:
		UUID	m_uuid;
	};
}
