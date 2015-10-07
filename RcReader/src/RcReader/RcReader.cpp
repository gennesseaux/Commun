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
#include "RcReader/RcControlType.h"

// Inclusions : Poco
#include <Poco/Foundation.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/FileStream.h>
#include <Poco/String.h>
#include <Poco/StringTokenizer.h>

// Inclusions : STL
#include <assert.h>
#include <algorithm>
#include <Outils/StringTools.h>

using namespace StringTools;

namespace
{
	std::string& prepare(std::string& str)
	{
		std::string strTemp = str;
		strTemp= strTemp.substr(strTemp.find(" "),strTemp.length());
		Poco::trimLeftInPlace<std::string>(strTemp);
		str = str.substr(0,str.find(" ")) + ',' + strTemp;
		str.erase(remove(str.begin(), str.end(), '"'), str.end());
		return str;
	}

	std::string& prepare_ctrl(std::string& str)
	{
		str = str.substr(str.find(" "),str.length());
		Poco::trimLeftInPlace<std::string>(str);
		str.erase(remove(str.begin(), str.end(), '"'), str.end());
		return str;
	}
}

namespace RcReader
{
	//! Constructeur
	CRcReader::CRcReader(std::string sCheminFichierRC)
	{
		try
		{
			Poco::File f(sCheminFichierRC);
			if(!f.exists()) return;
			if(!f.isFile()) return;

			m_sFichierRc = sCheminFichierRC;
			parse();
		}
		catch(...) {}
	}

	//! Destructeur
	CRcReader::~CRcReader()
	{
		while(m_lstDialog.size())
		{
			delete m_lstDialog[m_lstDialog.size()-1];
			m_lstDialog.pop_back();
		}
	}

	std::istream& getligne(Poco::FileInputStream& fistream, std::string& sLigne)
	{
		std::istream& istr = getline(_STD move(fistream), sLigne, fistream.widen('\n'));
		sLigne.erase(remove(sLigne.begin(), sLigne.end(), '\0'), sLigne.end());
		return istr;
	}

	// Parse le fichier de ressource
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
			while(getligne(fistr, sLigne))
			{
				if(sLigne.empty()) continue;

				// Décomposition de la ligne en utilisant un tokenizer
				Poco::StringTokenizer tokens(sLigne," ",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);

				// ACCELERATORS : Defines menu accelerator keys.
				if(tokens.count()>1 && tokens[1]=="ACCELERATORS" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
					{
						Poco::trimLeftInPlace(sLigne);

						// Cas des contrôles sur plusieurs lignes
						if(end_with(sLigne,",") || end_with(sLigne,",\r") || end_with(sLigne,",\r\n"))
						{
							remove_from_end(sLigne,"\r"); remove_from_end(sLigne,"\r\n");
							// Ajout de la ligne suivante
							std::string nextLigne; getligne(fistr, nextLigne); Poco::trimLeftInPlace(nextLigne);
							sLigne += nextLigne;
						}

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
							prepare_ctrl(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							// Contrôle de type Button
							if(ctrlTokens[2] == "Button")
							{
								std::string bsStyle = ctrlTokens[3];
								std::string sControle = bsStyle.substr(3,bsStyle.size()-3);
								CRcControle rcControle(sControle);

								pResourceDialog->AddControl(rcControle,ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcButton
							else if(ctrlTokens[2] == "MfcButton")
							{
								pResourceDialog->AddControl(CRcControle(MfcButton),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcColorButton
							else if(ctrlTokens[2] == "MfcColorButton")
							{
								pResourceDialog->AddControl(CRcControle(MfcColorButton),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcEditBrowse
							else if(ctrlTokens[2] == "MfcEditBrowse")
							{
								pResourceDialog->AddControl(CRcControle(MfcEditBrowse),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcFontComboBox
							else if(ctrlTokens[2] == "MfcFontComboBox")
							{
								pResourceDialog->AddControl(CRcControle(MfcFontComboBox),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcLink
							else if(ctrlTokens[2] == "MfcLink")
							{
								pResourceDialog->AddControl(CRcControle(MfcLink),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcMaskedEdit
							else if(ctrlTokens[2] == "MfcMaskedEdit")
							{
								pResourceDialog->AddControl(CRcControle(MfcMaskedEdit),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcMenuButton
							else if(ctrlTokens[2] == "MfcMenuButton")
							{
								pResourceDialog->AddControl(CRcControle(MfcMenuButton),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcPropertyGrid
							else if(ctrlTokens[2] == "MfcPropertyGrid")
							{
								pResourceDialog->AddControl(CRcControle(MfcPropertyGrid),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcShellList
							else if(ctrlTokens[2] == "MfcShellList")
							{
								pResourceDialog->AddControl(CRcControle(MfcShellList),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type MfcVSListBox
							else if(ctrlTokens[2] == "MfcVSListBox")
							{
								pResourceDialog->AddControl(CRcControle(MfcVSListBox),ctrlTokens[1],ctrlTokens[0]);
							}
							
							// Contrôle de type msctls_netaddress
							else if(ctrlTokens[2] == "msctls_netaddress")
							{
								pResourceDialog->AddControl(CRcControle(msctls_netaddress),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type msctls_progress32
							else if(ctrlTokens[2] == "msctls_progress32")
							{
								pResourceDialog->AddControl(CRcControle(msctls_progress32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type msctls_trackbar32
							else if(ctrlTokens[2] == "msctls_trackbar32")
							{
								pResourceDialog->AddControl(CRcControle(msctls_trackbar32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type RichEdit20W
							else if(ctrlTokens[2] == "RichEdit20W")
							{
								// Contrôle non pris en charge pour le moment
								pResourceDialog->AddControl(CRcControle(RichEdit20W),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type Static
							else if(ctrlTokens[2] == "Static")
							{
								pResourceDialog->AddControl(CRcControle(Static),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysAnimate32
							else if(ctrlTokens[2] == "SysAnimate32")
							{
								pResourceDialog->AddControl(CRcControle(SysAnimate32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysDateTimePick32
							else if(ctrlTokens[2] == "SysDateTimePick32")
							{
								pResourceDialog->AddControl(CRcControle(SysDateTimePick32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysIPAddress32
							else if(ctrlTokens[2] == "SysIPAddress32")
							{
								pResourceDialog->AddControl(CRcControle(SysIPAddress32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysLink
							else if(ctrlTokens[2] == "SysLink")
							{
								pResourceDialog->AddControl(CRcControle(SysLink),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysListView32
							else if(ctrlTokens[2] == "SysListView32")
							{
								pResourceDialog->AddControl(CRcControle(SysListView32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysMonthCal32
							else if(ctrlTokens[2] == "SysMonthCal32")
							{
								pResourceDialog->AddControl(CRcControle(SysMonthCal32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysTabControl32
							else if(ctrlTokens[2] == "SysTabControl32")
							{
								pResourceDialog->AddControl(CRcControle(SysTabControl32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Contrôle de type SysTreeView32
							else if(ctrlTokens[2] == "SysTreeView32")
							{
								pResourceDialog->AddControl(CRcControle(SysTreeView32),ctrlTokens[1],ctrlTokens[0]);
							}

							// Par défaut, les controles qui ne sont pas connus sont considérés comme un controle static
							else
							{
								pResourceDialog->AddControl(CRcControle(Static),ctrlTokens[1],ctrlTokens[0]);
							}
						}

						// Static Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381021(v=vs.85).aspx
						//		LTEXT text, id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,CRcControle::ToString(LTEXT)) || starts_with(sLigne,CRcControle::ToString(RTEXT)) || starts_with(sLigne,CRcControle::ToString(CTEXT)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[2],ctrlTokens[1]);
						}

						// Button Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381036(v=vs.85).aspx
						//		PUSHBUTTON text, id, x, y, width, height [, style [, extended-style]]
 						else if(	starts_with(sLigne,CRcControle::ToString(AUTO3STATE))			|| starts_with(sLigne,CRcControle::ToString(AUTOCHECKBOX)) 
									|| starts_with(sLigne,CRcControle::ToString(AUTORADIOBUTTON))	|| starts_with(sLigne,CRcControle::ToString(CHECKBOX)) 
									|| starts_with(sLigne,CRcControle::ToString(PUSHBOX))			|| starts_with(sLigne,CRcControle::ToString(PUSHBUTTON))
									|| starts_with(sLigne,CRcControle::ToString(DEFPUSHBUTTON))		|| starts_with(sLigne,CRcControle::ToString(RADIOBUTTON))
									|| starts_with(sLigne,CRcControle::ToString(STATE3))			|| starts_with(sLigne,CRcControle::ToString(USERBUTTON))
									|| starts_with(sLigne,CRcControle::ToString(SPLITBUTTON))		|| starts_with(sLigne,CRcControle::ToString(COMMANDLINK)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[2],ctrlTokens[1]);
						}

						// Edit Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381009(v=vs.85).aspx
						//		EDITTEXT id, x, y, width, height [, style [, extended-style]]
 						else if(	starts_with(sLigne,CRcControle::ToString(EDITTEXT))				|| starts_with(sLigne,CRcControle::ToString(BEDIT)) 
									|| starts_with(sLigne,CRcControle::ToString(HEDIT))				|| starts_with(sLigne,CRcControle::ToString(IEDIT)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[1]);
						}

						// Combo Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa380889(v=vs.85).aspx
						//		COMBOBOX id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,CRcControle::ToString(COMBOBOX)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[1]);
						}

						// GroupBox Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381014(v=vs.85).aspx
						//		GROUPBOX text, id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,CRcControle::ToString(GROUPBOX)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[2],ctrlTokens[1]);
						}

						// ListBox Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381020(v=vs.85).aspx
						//		LISTBOX id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,CRcControle::ToString(LISTBOX)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[1]);
						}

						// Icon Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381017(v=vs.85).aspx
						//		ICON text, id, x, y [, width, height, style [, extended-style]]
 						else if(starts_with(sLigne,CRcControle::ToString(ICON)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[2],ctrlTokens[1]);
						}

						// Scrollbar Control Statements : http://msdn.microsoft.com/en-us/library/windows/desktop/aa381046(v=vs.85).aspx
						//		SCROLLBAR id, x, y, width, height [, style [, extended-style]]
 						else if(starts_with(sLigne,CRcControle::ToString(SCROLLBAR)))
 						{
							prepare(sLigne);
							Poco::StringTokenizer ctrlTokens(sLigne,",");

							pResourceDialog->AddControl(CRcControle(ctrlTokens[0]),ctrlTokens[1]);
						}

						else
						{
							// Controle inconnue !!!
							assert(1);
						}
					}
				}

				// DESIGNINFO : 
				else if(tokens.count()>1 && tokens[1]=="DESIGNINFO" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getligne(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// FONT	Specifies the name of a file that contains a font.
				else if(tokens.count()>1 && tokens[1]=="FONT" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getligne(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}

				// HTML : Specifies an HTML file.
				else if(tokens.count()>1 && tokens[1]=="HTML" && tokens[0]!="//")
				{
					// Pas implémenté
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
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
					while(getligne(fistr, sLigne))
					{
						if(starts_with(sLigne,"END"))		{ break; }
						else								{ continue; }
					}
				}
			}

			// Fermeture du fichier
			fistr.close();
		}

		// Une fois récupérées les ressources sont triées par ordre alphabétique
		std::sort(m_lstDialog.begin(), m_lstDialog.end(), CRcResourceDialog::CompareId);
	}

	// Retourne le nom du fichier de ressource
	std::string CRcReader::GetFichierRc() const
	{
		return m_sFichierRc;
	}

	// Nombre de ressource de type Dialog contenues dans le fichier de ressource
	int CRcReader::GetDialogCount()
	{
		return m_lstDialog.size();
	}

	// Retourne la ressource de type Dialog en fonction de sa position dans la liste
	CRcResourceDialog* CRcReader::GetDialog(int iIndex)
	{
		return m_lstDialog[iIndex];
	}

	// Retourne la ressource de type Dialog en fonction de son identifiant (Nom)
	CRcResourceDialog* CRcReader::GetDialog(std::string resId)
	{
		auto it = std::find_if(m_lstDialog.begin(),m_lstDialog.end(),[=](CRcResourceDialog* pResDialog) { return pResDialog->GetId().compare(resId) == 0; });
		if(it != m_lstDialog.end())
			return *it;
		return nullptr;
	}

}
