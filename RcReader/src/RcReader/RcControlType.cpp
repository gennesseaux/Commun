//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	19/12/2014 : 
//	-----------------------------------------------------------------------------

// Inclusions
#include "RcReader/RcControlType.h"

#define ENUMSTRING(enumVal) #enumVal

namespace RcReader
{

	// Constructeur
	CRcControle::CRcControle()
	{
		m_type = Inconnu;
		m_sType = "";
	}

	// Constructeur
	CRcControle::CRcControle(RcControlType type)
	{
		m_type = type;

		switch(type)
		{
			// Generic Control (recensés à ce jour 08/01/2015)
			case RcReader::Button:				m_sType = ENUMSTRING(Button);				break;
			case RcReader::MfcButton:			m_sType = ENUMSTRING(MfcButton);			break;
			case RcReader::MfcColorButton:		m_sType = ENUMSTRING(MfcColorButton);		break;
			case RcReader::MfcEditBrowse:		m_sType = ENUMSTRING(MfcEditBrowse);		break;
			case RcReader::MfcFontComboBox:		m_sType = ENUMSTRING(MfcFontComboBox);		break;
			case RcReader::MfcLink:				m_sType = ENUMSTRING(MfcLink);				break;
			case RcReader::MfcMaskedEdit:		m_sType = ENUMSTRING(MfcMaskedEdit);		break;
			case RcReader::MfcMenuButton:		m_sType = ENUMSTRING(MfcMenuButton);		break;
			case RcReader::MfcPropertyGrid:		m_sType = ENUMSTRING(MfcPropertyGrid);		break;
			case RcReader::MfcShellList:		m_sType = ENUMSTRING(MfcShellList);			break;
			case RcReader::MfcVSListBox:		m_sType = ENUMSTRING(MfcVSListBox);			break;
			case RcReader::msctls_netaddress:	m_sType = ENUMSTRING(msctls_netaddress);	break;
			case RcReader::msctls_progress32:	m_sType = ENUMSTRING(msctls_progress32);	break;
			case RcReader::msctls_trackbar32:	m_sType = ENUMSTRING(msctls_trackbar32);	break;
			case RcReader::RichEdit20W:			m_sType = ENUMSTRING(RichEdit20W);			break;
			case RcReader::Static:				m_sType = ENUMSTRING(Static);				break;
			case RcReader::SysAnimate32:		m_sType = ENUMSTRING(SysAnimate32);			break;
			case RcReader::SysDateTimePick32:	m_sType = ENUMSTRING(SysDateTimePick32);	break;
			case RcReader::SysIPAddress32:		m_sType = ENUMSTRING(SysIPAddress32);		break;
			case RcReader::SysLink:				m_sType = ENUMSTRING(SysLink);				break;
			case RcReader::SysListView32:		m_sType = ENUMSTRING(SysListView32);		break;
			case RcReader::SysMonthCal32:		m_sType = ENUMSTRING(SysMonthCal32);		break;
			case RcReader::SysTabControl32:		m_sType = ENUMSTRING(SysTabControl32);		break;
			case RcReader::SysTreeView32:		m_sType = ENUMSTRING(SysTreeView32);		break;

			// Static Control
			case RcReader::LTEXT:				m_sType = ENUMSTRING(LTEXT);			break;
			case RcReader::RTEXT:				m_sType = ENUMSTRING(RTEXT);			break;
			case RcReader::CTEXT:				m_sType = ENUMSTRING(CTEXT);			break;

			// Button Control
			case RcReader::AUTO3STATE:			m_sType = ENUMSTRING(AUTO3STATE);		break;
			case RcReader::AUTOCHECKBOX:		m_sType = ENUMSTRING(AUTOCHECKBOX);		break;
			case RcReader::AUTORADIOBUTTON:		m_sType = ENUMSTRING(AUTORADIOBUTTON);	break;
			case RcReader::CHECKBOX:			m_sType = ENUMSTRING(CHECKBOX);			break;
			case RcReader::PUSHBOX:				m_sType = ENUMSTRING(PUSHBOX);			break;
			case RcReader::PUSHBUTTON:			m_sType = ENUMSTRING(PUSHBUTTON);		break;
			case RcReader::DEFPUSHBUTTON:		m_sType = ENUMSTRING(DEFPUSHBUTTON);	break;
			case RcReader::RADIOBUTTON:			m_sType = ENUMSTRING(RADIOBUTTON);		break;
			case RcReader::STATE3:				m_sType = ENUMSTRING(STATE3);			break;
			case RcReader::USERBUTTON:			m_sType = ENUMSTRING(USERBUTTON);		break;
			case RcReader::SPLITBUTTON:			m_sType = ENUMSTRING(SPLITBUTTON);		break;
			case RcReader::COMMANDLINK:			m_sType = ENUMSTRING(COMMANDLINK);		break;

			// Edit Control
			case RcReader::EDITTEXT:			m_sType = ENUMSTRING(EDITTEXT);			break;
			case RcReader::BEDIT:				m_sType = ENUMSTRING(BEDIT);			break;
			case RcReader::HEDIT:				m_sType = ENUMSTRING(HEDIT);			break;
			case RcReader::IEDIT:				m_sType = ENUMSTRING(IEDIT);			break;

			// Combo Control
			case RcReader::COMBOBOX:			m_sType = ENUMSTRING(COMBOBOX);			break;

			// GroupBox Control
			case RcReader::GROUPBOX:			m_sType = ENUMSTRING(GROUPBOX);			break;

			// ListBox Control
			case RcReader::LISTBOX:				m_sType = ENUMSTRING(LISTBOX);			break;

			// Icon Control
			case RcReader::ICON:				m_sType = ENUMSTRING(ICON);				break;

			// Scrollbar Control
			case RcReader::SCROLLBAR :			m_sType = ENUMSTRING(SCROLLBAR );		break;

			default:							m_sType = "";							break;
		}
	}

	CRcControle::CRcControle(std::string sType)
	{
		m_sType = sType;

		// Generic Control
		if(m_sType.find(ENUMSTRING(MfcButton))!=std::string::npos)					{ m_type = MfcButton;			m_sType = ENUMSTRING(MfcButton);		}
		else if(m_sType.find(ENUMSTRING(MfcColorButton))!=std::string::npos)		{ m_type = MfcColorButton;		m_sType = ENUMSTRING(MfcColorButton);	}
		else if(m_sType.find(ENUMSTRING(MfcMenuButton))!=std::string::npos)			{ m_type = MfcMenuButton;		m_sType = ENUMSTRING(MfcMenuButton);	}
		else if(m_sType.find(ENUMSTRING(Button))!=std::string::npos)				{ m_type = Button;				m_sType = ENUMSTRING(Button);			}
		else if(m_sType.find(ENUMSTRING(MfcEditBrowse))!=std::string::npos)			{ m_type = MfcEditBrowse;		m_sType = ENUMSTRING(MfcEditBrowse);	}
		else if(m_sType.find(ENUMSTRING(MfcFontComboBox))!=std::string::npos)		{ m_type = MfcFontComboBox;		m_sType = ENUMSTRING(MfcFontComboBox);	}
		else if(m_sType.find(ENUMSTRING(MfcLink))!=std::string::npos)				{ m_type = MfcLink;				m_sType = ENUMSTRING(MfcLink);			}
		else if(m_sType.find(ENUMSTRING(MfcMaskedEdit))!=std::string::npos)			{ m_type = MfcMaskedEdit;		m_sType = ENUMSTRING(MfcMaskedEdit);	}
		else if(m_sType.find(ENUMSTRING(MfcPropertyGrid))!=std::string::npos)		{ m_type = MfcPropertyGrid;		m_sType = ENUMSTRING(MfcPropertyGrid);	}
		else if(m_sType.find(ENUMSTRING(MfcShellList))!=std::string::npos)			{ m_type = MfcShellList;		m_sType = ENUMSTRING(MfcShellList);		}
		else if(m_sType.find(ENUMSTRING(MfcVSListBox))!=std::string::npos)			{ m_type = MfcVSListBox;		m_sType = ENUMSTRING(MfcVSListBox);		}
		else if(m_sType.find(ENUMSTRING(msctls_netaddress))!=std::string::npos)		{ m_type = msctls_netaddress;	m_sType = ENUMSTRING(msctls_netaddress);}
		else if(m_sType.find(ENUMSTRING(msctls_progress32))!=std::string::npos)		{ m_type = msctls_progress32;	m_sType = ENUMSTRING(msctls_progress32);}
		else if(m_sType.find(ENUMSTRING(msctls_trackbar32))!=std::string::npos)		{ m_type = msctls_trackbar32;	m_sType = ENUMSTRING(msctls_trackbar32);}
		else if(m_sType.find(ENUMSTRING(RichEdit20W))!=std::string::npos)			{ m_type = RichEdit20W;			m_sType = ENUMSTRING(RichEdit20W);		}
		else if(m_sType.find(ENUMSTRING(Static))!=std::string::npos)				{ m_type = Static;				m_sType = ENUMSTRING(Static);			}
		else if(m_sType.find(ENUMSTRING(SysAnimate32))!=std::string::npos)			{ m_type = SysAnimate32;		m_sType = ENUMSTRING(SysAnimate32);		}
		else if(m_sType.find(ENUMSTRING(SysDateTimePick32))!=std::string::npos)		{ m_type = SysDateTimePick32;	m_sType = ENUMSTRING(SysDateTimePick32);}
		else if(m_sType.find(ENUMSTRING(SysIPAddress32))!=std::string::npos)		{ m_type = SysIPAddress32;		m_sType = ENUMSTRING(SysIPAddress32);	}
		else if(m_sType.find(ENUMSTRING(SysLink))!=std::string::npos)				{ m_type = SysLink;				m_sType = ENUMSTRING(SysLink);			}
		else if(m_sType.find(ENUMSTRING(SysListView32))!=std::string::npos)			{ m_type = SysListView32;		m_sType = ENUMSTRING(SysListView32);	}
		else if(m_sType.find(ENUMSTRING(SysMonthCal32))!=std::string::npos)			{ m_type = SysMonthCal32;		m_sType = ENUMSTRING(SysMonthCal32);	}
		else if(m_sType.find(ENUMSTRING(SysTabControl32))!=std::string::npos)		{ m_type = SysTabControl32;		m_sType = ENUMSTRING(SysTabControl32);	}
		else if(m_sType.find(ENUMSTRING(SysTreeView32))!=std::string::npos)			{ m_type = SysTreeView32;		m_sType = ENUMSTRING(SysTreeView32);	}
		
		// Static Control
		else if(m_sType.find(ENUMSTRING(LTEXT))!=std::string::npos)				{ m_type = LTEXT;				m_sType = ENUMSTRING(LTEXT);			}
		else if(m_sType.find(ENUMSTRING(RTEXT))!=std::string::npos)				{ m_type = RTEXT;				m_sType = ENUMSTRING(RTEXT);			}
		else if(m_sType.find(ENUMSTRING(CTEXT))!=std::string::npos)				{ m_type = CTEXT;				m_sType = ENUMSTRING(CTEXT);			}
		
		// Button Control
		else if(m_sType.find(ENUMSTRING(AUTO3STATE))!=std::string::npos)		{ m_type = AUTO3STATE;			m_sType = ENUMSTRING(AUTO3STATE);		}
		else if(m_sType.find(ENUMSTRING(AUTOCHECKBOX))!=std::string::npos)		{ m_type = AUTOCHECKBOX;		m_sType = ENUMSTRING(AUTOCHECKBOX);		}
		else if(m_sType.find(ENUMSTRING(AUTORADIOBUTTON))!=std::string::npos)	{ m_type = AUTORADIOBUTTON;		m_sType = ENUMSTRING(AUTORADIOBUTTON);	}
		else if(m_sType.find(ENUMSTRING(CHECKBOX))!=std::string::npos)			{ m_type = CHECKBOX;			m_sType = ENUMSTRING(CHECKBOX);			}
		else if(m_sType.find(ENUMSTRING(PUSHBOX))!=std::string::npos)			{ m_type = PUSHBOX;				m_sType = ENUMSTRING(PUSHBOX);			}
		else if(m_sType.find(ENUMSTRING(PUSHBUTTON))!=std::string::npos)		{ m_type = PUSHBUTTON;			m_sType = ENUMSTRING(PUSHBUTTON);		}
		else if(m_sType.find(ENUMSTRING(DEFPUSHBUTTON))!=std::string::npos)		{ m_type = DEFPUSHBUTTON;		m_sType = ENUMSTRING(DEFPUSHBUTTON);	}
		else if(m_sType.find(ENUMSTRING(RADIOBUTTON))!=std::string::npos)		{ m_type = RADIOBUTTON;			m_sType = ENUMSTRING(RADIOBUTTON);		}
		else if(m_sType.find(ENUMSTRING(STATE3))!=std::string::npos)			{ m_type = STATE3;				m_sType = ENUMSTRING(STATE3);			}
		else if(m_sType.find(ENUMSTRING(USERBUTTON))!=std::string::npos)		{ m_type = USERBUTTON;			m_sType = ENUMSTRING(USERBUTTON);		}
		else if(m_sType.find(ENUMSTRING(SPLITBUTTON))!=std::string::npos)		{ m_type = SPLITBUTTON;			m_sType = ENUMSTRING(SPLITBUTTON);		}
		else if(m_sType.find(ENUMSTRING(COMMANDLINK))!=std::string::npos)		{ m_type = COMMANDLINK;			m_sType = ENUMSTRING(COMMANDLINK);		}
		
		// Edit Control
		else if(m_sType.find(ENUMSTRING(EDITTEXT))!=std::string::npos)			{ m_type = EDITTEXT;			m_sType = ENUMSTRING(EDITTEXT);			}
		else if(m_sType.find(ENUMSTRING(BEDIT))!=std::string::npos)				{ m_type = BEDIT;				m_sType = ENUMSTRING(BEDIT);			}
		else if(m_sType.find(ENUMSTRING(HEDIT))!=std::string::npos)				{ m_type = HEDIT;				m_sType = ENUMSTRING(HEDIT);			}
		else if(m_sType.find(ENUMSTRING(IEDIT))!=std::string::npos)				{ m_type = IEDIT;				m_sType = ENUMSTRING(IEDIT);			}
		
		// Combo Control
		else if(m_sType.find(ENUMSTRING(COMBOBOX))!=std::string::npos)			{ m_type = COMBOBOX;			m_sType = ENUMSTRING(COMBOBOX);			}
		
		// GroupBox Control
		else if(m_sType.find(ENUMSTRING(GROUPBOX))!=std::string::npos)			{ m_type = GROUPBOX;			m_sType = ENUMSTRING(GROUPBOX);			}

		// ListBox Control
		else if(m_sType.find(ENUMSTRING(LISTBOX))!=std::string::npos)			{ m_type = LISTBOX;				m_sType = ENUMSTRING(LISTBOX);			}
		
		// Icon Control
		else if(m_sType.find(ENUMSTRING(ICON))!=std::string::npos)				{ m_type = ICON;				m_sType = ENUMSTRING(ICON);				}
		
		// Scrollbar Control
		else if(m_sType.find(ENUMSTRING(SCROLLBAR))!=std::string::npos)			{ m_type = SCROLLBAR;			m_sType = ENUMSTRING(SCROLLBAR);		}

		else												m_type = Inconnu;
	}

	//! Constructeur par copie
	CRcControle::CRcControle(const CRcControle &source)
	{
		m_type = source.m_type;
		m_sType = source.m_sType;
	}

	//! Opérateur =
	CRcControle & CRcControle::operator=(const CRcControle &source)
	{
		m_type = source.m_type;
		m_sType = source.m_sType;

		return *this;
	}

	std::string CRcControle::ToString()
	{
		return m_sType;
	}

	std::string CRcControle::ToString(RcControlType type)
	{
		return CRcControle(type).ToString();
	}

	RcReader::RcControlType CRcControle::ToRcControlType()
	{
		return m_type;
	}

	RcReader::RcControlType CRcControle::ToRcControlType(std::string sType)
	{
		return CRcControle(sType).ToRcControlType();
	}

}
