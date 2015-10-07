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
		//! Identifiant de la ressource de type Dialog
		std::string GetId() const;
		//! Nombre de contrôles dans la ressource
		int GetControlCount();
		//! Retourne le contrôle contenu dans la ressource en fonction de sa position dans la liste
		CRcResourceControl* GetControl(int iIndex);
		//! Retourne le contrôle contenu dans la ressource en fonction de son identifiant (Nom)
		CRcResourceControl* GetControl(std::string ctrlId);

	public:
		static bool CompareId(const CRcResourceDialog* _Left, const CRcResourceDialog* _Right) { return (_Left->m_sId < _Right->m_sId); }

	protected:
		std::string	m_sId;
		std::vector<CRcResourceControl*> m_lstControl;
	};
}
