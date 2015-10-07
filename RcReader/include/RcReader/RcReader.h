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
		// Parse le fichier de ressource
		void parse();

	public:
		// Retourne le nom du fichier de ressource
		std::string GetFichierRc() const;
		// Nombre de ressource de type Dialog contenues dans le fichier de ressource
		int GetDialogCount();
		// Retourne la ressource de type Dialog en fonction de sa position dans la liste
		CRcResourceDialog* GetDialog(int iIndex);
		// Retourne la ressource de type Dialog en fonction de son identifiant (Nom)
		CRcResourceDialog* GetDialog(std::string resId);

	protected:
		std::string m_sFichierRc;
		std::vector<CRcResourceDialog*> m_lstDialog;
	};
}
