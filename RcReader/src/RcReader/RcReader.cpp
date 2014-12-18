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
#include "RcReader/RcReader.h"

// Inclusions : Poco
#include <Poco/Foundation.h>
#include <Poco/File.h>
#include <Poco/FileStream.h>
#include <Poco/String.h>
#include <Poco/StringTokenizer.h>

namespace
{
	bool starts_with(const std::string& s1, const std::string& s2)
	{
		return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
	}
}

namespace RcReader
{
	//! Constructeur
	CRcReader::CRcReader(std::string sCheminFichierRC)
	{
		m_sFichierRc = sCheminFichierRC;

		Poco::File f(sCheminFichierRC);
		if(f.exists())
			parse();
	}

	//! Destructeur
	CRcReader::~CRcReader()
	{
	}

	void CRcReader::parse()
	{
		// Ouverture du fichier
		Poco::FileInputStream fistr(m_sFichierRc);

		// Lecture du fichier si l'ouverture à réussi
		if(fistr)
		{
			std::string sLigne;

			// Parcours toutes les lignes du fichier
			// afin d'en extraire les ressources
			while(std::getline(fistr, sLigne))
			{
				if(sLigne.empty()) continue;;

				// Décomposition de la ligne en utilisant un tokenizer
				Poco::StringTokenizer tokens(sLigne," ",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);

				// ACCELERATORS : Defines menu accelerator keys.
				if(tokens.count()>1 && tokens[1]=="ACCELERATORS" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// BITMAP : Defines a bitmap by naming it and specifying
				// the name of the file that contains it. (To use a particular
				// bitmap, the application requests it by name.)
				else if(tokens.count()>1 && tokens[1]=="BITMAP" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// CURSOR Defines a cursor or animated cursor by naming
				// it and specifying the name of the file that contains
				// it. (To use a particular cursor, the application
				// requests it by name.)
				else if(tokens.count()>1 && tokens[1]=="CURSOR" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// DIALOG DIALOGEX : Defines a template that an application
				// can use to create dialog boxes.
				else if(tokens.count()>1 && (tokens[1]=="DIALOG" || tokens[1]=="DIALOGEX") && tokens[0]!="//")
				{
					std::string sNameID = sLigne.substr(0,sLigne.find(" "));

					CRcResourceDialog* pResourceDialog = new CRcResourceDialog(sNameID);
					m_lstDialog.emplace_back(pResourceDialog);

					//
					// http://msdn.microsoft.com/en-us/library/windows/desktop/aa381002(v=vs.85).aspx
					//
					while(getline(fistr, sLigne))
					{
						Poco::trimLeftInPlace(sLigne);

						// 
						if(starts_with(sLigne,"STYLE"))			{ continue; }

						// 
						else if(starts_with(sLigne,"EXSTYLE"))	{ continue; }

						// 
						else if(starts_with(sLigne,"CAPTION"))	{ continue; }

						// 
						else if(starts_with(sLigne,"FONT"))		{ continue; }

						// 
						else if(starts_with(sLigne,"BEGIN"))	{ continue; }

						// Fin de la récupération des controles
						else if(starts_with(sLigne,"END"))		{ break; }


						// Generic Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa380911(v=vs.85).aspx
						//		CONTROL text, id, class, style, x, y, width, height [, extended-style]
 						if(starts_with(sLigne,"CONTROL"))
 						{
 							int toto = 0;
						}

						// Static Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381021(v=vs.85).aspx
						//		LTEXT text, id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,"LTEXT") || starts_with(sLigne,"RTEXT") || starts_with(sLigne,"CTEXT"))
 						{
 							int toto = 0;
						}

						// Button Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381036(v=vs.85).aspx
						//		PUSHBUTTON text, id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,"AUTO3STATE") || starts_with(sLigne,"AUTOCHECKBOX") || starts_with(sLigne,"AUTORADIOBUTTON")
								|| starts_with(sLigne,"CHECKBOX") || starts_with(sLigne,"PUSHBOX") || starts_with(sLigne,"PUSHBUTTON")
								|| starts_with(sLigne,"DEFPUSHBUTTON") || starts_with(sLigne,"RADIOBUTTON") || starts_with(sLigne,"STATE3")
								|| starts_with(sLigne,"USERBUTTON"))
 						{
 							int toto = 0;
						}

						// Edit Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381009(v=vs.85).aspx
						//		EDITTEXT id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,"EDITTEXT") || starts_with(sLigne,"BEDIT") || starts_with(sLigne,"HEDIT") || starts_with(sLigne,"IEDIT"))
 						{
 							int toto = 0;
						}

						// Combo Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa380889(v=vs.85).aspx
						//		COMBOBOX id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,"COMBOBOX"))
 						{
 							int toto = 0;
						}

						// GroupBox Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381014(v=vs.85).aspx
						//		GROUPBOX text, id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,"GROUPBOX"))
 						{
 							int toto = 0;
						}

						// icon Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381017(v=vs.85).aspx
						//		ICON text, id, x, y [, width, height, style [, extended-style]]
 						else if(starts_with(sLigne,"ICON"))
 						{
 							int toto = 0;
						}

						else
						{
 							int toto = 0;
						}

					}

					int toto = 0;
				}

				// DESIGNINFO : 
				else if(tokens.count()>1 && tokens[1]=="DESIGNINFO" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// FONT	Specifies the name of a file that contains a font.
				else if(tokens.count()>1 && tokens[1]=="FONT" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// HTML : Specifies an HTML file.
				else if(tokens.count()>1 && tokens[1]=="HTML" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// ICON : Defines an icon or animated icon by naming it
				// and specifying the name of the file that contains it.
				// (To use a particular icon, the application requests it by name.)
				else if(tokens.count()>1 && tokens[1]=="ICON" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// MENU MENUEX : Defines the appearance and function of
				// a menu.
				else if(tokens.count()>1 && (tokens[1]=="MENU" || tokens[1]=="MENUEX") && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// MESSAGETABLE : Defines a message table by naming it
				// and specifying the name of the file that contains it.
				// The file is a binary resource file generated by the
				// message compiler.
				else if(tokens.count()>1 && tokens[1]=="MESSAGETABLE" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// POPUP : Defines a menu item that can contain menu
				// items and submenus.
				else if(tokens.count()>1 && tokens[1]=="POPUP" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// RCDATA : Defines data resources. Data resources
				// let you include binary data in the executable file.
				else if(tokens.count()>1 && tokens[1]=="RCDATA" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// STRINGTABLE : Defines string resources.
				// String resources are Unicode or ASCII strings
				// that can be loaded from the executable file.
				else if(tokens.count()>1 && tokens[1]=="STRINGTABLE" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// TEXTINCLUDE : A special resource that is interpreted 
				// by Visual C++. For more information, see TN035.
				else if(tokens.count()>1 && tokens[1]=="TEXTINCLUDE" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// VERSIONINFO : Defines a version-information resource.
				// Contains information such as the version number,
				// intended operating system, and so on.
				else if(tokens.count()>1 && tokens[1]=="VERSIONINFO" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getline(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}
			}

			// Fermeture du fichier
			fistr.close();
		}
	}

}
