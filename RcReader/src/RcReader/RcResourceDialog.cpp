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
		while(m_lstControl.size())
		{
			delete m_lstControl[m_lstControl.size()-1];
			m_lstControl.pop_back();
		}
	}

	//! Ajout d'un control
	void CRcResourceDialog::AddControl(CRcControle& rcControle, std::string sId)
	{
		m_lstControl.emplace_back(new CRcResourceControl(rcControle,sId));
	}

	//! Ajout d'un control
	void CRcResourceDialog::AddControl(CRcControle& rcControle, std::string sId, std::string& sTexte)
	{
		m_lstControl.emplace_back(new CRcResourceControl(rcControle,sId,sTexte));
	}

	//! Identifiant de la ressource de type Dialog
	std::string CRcResourceDialog::GetId() const
	{
		return m_sId;
	}

	//! Nombre de contrôles dans la ressource
	int CRcResourceDialog::GetControlCount()
	{
		return m_lstControl.size();
	}

	//! Retourne le contrôle contenu dans la ressource en fonction de sa position dans la liste
	CRcResourceControl* CRcResourceDialog::GetControl(int iIndex)
	{
		return m_lstControl[iIndex];
	}

	//! Retourne le contrôle contenu dans la ressource en fonction de son identifiant (Nom)
	CRcResourceControl* CRcResourceDialog::GetControl(std::string ctrlId)
	{
		auto it = std::find_if(m_lstControl.begin(),m_lstControl.end(),[=](CRcResourceControl* pResControl) { return pResControl->GetId().compare(ctrlId) == 0; });
		if(it != m_lstControl.end())
			return *it;
		return nullptr;
	}

}
