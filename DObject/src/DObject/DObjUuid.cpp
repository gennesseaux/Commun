//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe permettant de donner un identifiant unique à chaque objet
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	17/6/2014 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "DObject/DObjUuid.h"

namespace DObject
{
	//! Constructeur
	CDObjUuid::CDObjUuid(void)
	{
		::UuidCreateNil(&m_uuid);
		::UuidCreate(&m_uuid);
	}

	//! Destructeur
	CDObjUuid::~CDObjUuid(void)
	{
	}

	//! Opérateur ==
	bool CDObjUuid::operator==( const CDObjUuid &source ) const
	{
		return	m_uuid.Data1==source.m_uuid.Data1 
			&& m_uuid.Data2==source.m_uuid.Data2 
			&& m_uuid.Data3==source.m_uuid.Data3 
			&& m_uuid.Data4==source.m_uuid.Data4;
	}

	//! Opérateur !=
	bool CDObjUuid::operator!=( const CDObjUuid &source ) const
	{
		return !(*this == source);
	}

	//! Retourne l'identifiant unique
	LPGUID CDObjUuid::GetLPGUID()
	{
		return &m_uuid;
	}
}
