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
#include <vector>

// Inclusions
#include "RcReader/RcResourceDialog.h"
#include "RcReader/RcResourceControl.h"


namespace RcReader
{

	class CRcReader
	{
	public:
 		//! Constructeur
 		CRcReader(std::string sCheminFichierRC);
		//! Destructeur
		virtual ~CRcReader();

	protected:
		//! Constructeur
		CRcReader() = delete;
		//! Constructeur par copie
		CRcReader(const CRcReader &source) = delete;														
		//! Opérateur =
		CRcReader &operator=(const CRcReader &source) = delete;

	protected:
		void parse();

	public:
		std::string GetFichierRc() const { return m_sFichierRc; }
		int GetDialogCount() { return m_lstDialog.size(); }
		CRcResourceDialog* GetDialog(int iIndex) { return m_lstDialog[iIndex]; }

	protected:
		std::string m_sFichierRc;
		std::vector<CRcResourceDialog*> m_lstDialog;
	};
}
