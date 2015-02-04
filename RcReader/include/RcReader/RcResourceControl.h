//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de base permettant de lire un fichier RC
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	18/12/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include <string>

// Inclusions
#include "RcReader/RcControlType.h"


namespace RcReader
{

	class CRcResourceControl
	{
	public:
 		//! Constructeur
 		CRcResourceControl(CRcControle rcControle , std::string sId);
 		CRcResourceControl(CRcControle rcControle , std::string sId, std::string sTexte);
		//! Destructeur
		virtual ~CRcResourceControl();

		//! Constructeur par copie
		CRcResourceControl(const CRcResourceControl &source);														
		//! Opérateur =
		CRcResourceControl &operator=(const CRcResourceControl &source);

	protected:
 		//! Constructeur
 		CRcResourceControl() = delete ;

	public:
		std::string GetId() const { return m_sId; }
		RcReader::CRcControle GetControle() const { return m_rcControle; }

	protected:
		CRcControle m_rcControle;
		std::string	m_sId;
		std::string	m_sTexte;
	};
}
