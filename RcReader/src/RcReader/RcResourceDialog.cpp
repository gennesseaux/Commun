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
#include "RcReader/RcResourceDialog.h"

// Inclusions
#include <algorithm>

namespace RcReader
{
	//! Constructeur
	CRcResourceDialog::CRcResourceDialog(std::string sId) : m_sId(sId)
	{
	}

	//! Destructeur
	CRcResourceDialog::~CRcResourceDialog()
	{
	}

	//! Ajout d'un control
	void CRcResourceDialog::AddControl(CRcControle& rcControle, std::string sId)
	{
		m_lstControl.emplace_back(CRcResourceControl(rcControle,sId));
	}

	//! Ajout d'un control
	void CRcResourceDialog::AddControl(CRcControle& rcControle, std::string sId, std::string& sTexte)
	{
		m_lstControl.emplace_back(CRcResourceControl(rcControle,sId,sTexte));
	}

}
