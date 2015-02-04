//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de base permettant de lire un fichier RC
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	18/12/2014 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "RcReader/RcResourceControl.h"

namespace RcReader
{
	//! Constructeur
	CRcResourceControl::CRcResourceControl(CRcControle rcControle , std::string sId)
			: m_rcControle(rcControle), m_sId(sId)
	{
	}
	//! Constructeur
	CRcResourceControl::CRcResourceControl(CRcControle rcControle , std::string sId, std::string sTexte)
			: m_rcControle(rcControle), m_sId(sId), m_sTexte(sTexte)
	{
	}

	//! Destructeur
	CRcResourceControl::~CRcResourceControl()
	{
	}
	
	//! Constructeur par copie
	CRcResourceControl::CRcResourceControl(const CRcResourceControl &source)
	{
		m_rcControle = source.m_rcControle;
		m_sId = source.m_sId;
		m_sTexte = source.m_sTexte;
	}

	//! Opérateur =
	CRcResourceControl & CRcResourceControl::operator=(const CRcResourceControl &source)
	{
		m_rcControle = source.m_rcControle;
		m_sId = source.m_sId;
		m_sTexte = source.m_sTexte;

		return *this;
	}

}
