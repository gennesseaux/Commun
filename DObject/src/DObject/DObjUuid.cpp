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

	//! Constructeur par recopie
	CDObjUuid::CDObjUuid(const CDObjUuid& source)
	{
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObjUuid& CDObjUuid::operator=(const CDObjUuid& source)
	{
		if(this != &source)
			ClonnerDonnees(source);

		return *this;
	}

	//! Clone les données de l'objet.
	void CDObjUuid::ClonnerDonnees(const CDObjUuid &source)
	{
		RPC_WSTR szUuid = NULL;
		if(::UuidToString(&source.m_uuid,&szUuid) != RPC_S_OK)
		{
			::RpcStringFree(&szUuid);
			::UuidCreateNil(&m_uuid);
		}

		if(::UuidFromString(szUuid,&m_uuid) != RPC_S_OK)
		{
			::RpcStringFree(&szUuid);
			::UuidCreateNil(&m_uuid);
		}
		::RpcStringFree(&szUuid);
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
