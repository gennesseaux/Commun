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
#include "RcReader/RcControlType.h"
#include "RcReader/RcResourceControl.h"

namespace RcReader
{

	class CRcResourceDialog
	{
		friend class CRcReader;

	public:
 		//! Constructeur
 		CRcResourceDialog(std::string sId);
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
		//! Ajout d'un control
		void AddControl(CRcControle& rcControle , std::string sId);
		void AddControl(CRcControle& rcControle , std::string sId, std::string& sTexte);

	public:
		std::string GetId() const { return m_sId; }

		int GetControlCount() { return m_lstControl.size(); }
		CRcResourceControl& GetControl(int iIndex) { return m_lstControl[iIndex]; }

	public:
		static bool CompareId(const CRcResourceDialog* _Left, const CRcResourceDialog* _Right) { return (_Left->m_sId < _Right->m_sId); }

	protected:
		std::string	m_sId;
		std::vector<CRcResourceControl> m_lstControl;
	};
}
