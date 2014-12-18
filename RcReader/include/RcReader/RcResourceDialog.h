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

namespace RcReader
{

	class CRcResourceDialog
	{
	public:
 		//! Constructeur
 		CRcResourceDialog(std::string sNameId);
		//! Destructeur
		virtual ~CRcResourceDialog();

	protected:
 		//! Constructeur
 		CRcResourceDialog();
		//! Constructeur par copie
		CRcResourceDialog(const CRcResourceDialog &source);														
		//! Opérateur =
		CRcResourceDialog &operator=(const CRcResourceDialog &source);

	protected:
		std::string	m_sNameId;
	};
}
