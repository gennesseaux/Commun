//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	19/12/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include <string>

namespace RcReader
{

	//
	enum RcControlType : unsigned int
	{
		// Generic Control (recensés à ce jour 08/01/2015)
		/*CONTROL,*/
		Button,MfcButton,MfcColorButton,MfcEditBrowse,MfcFontComboBox,MfcLink,MfcMaskedEdit,MfcMenuButton,
		MfcPropertyGrid,MfcShellList,MfcVSListBox,msctls_netaddress,msctls_progress32,msctls_trackbar32,
		RichEdit20W,Static,SysAnimate32,SysDateTimePick32,SysIPAddress32,SysLink,SysListView32,SysMonthCal32,
		SysTabControl32,SysTreeView32,

		// Static Control
		LTEXT, RTEXT, CTEXT,

		// Button Control
		AUTO3STATE, AUTOCHECKBOX, AUTORADIOBUTTON, CHECKBOX, PUSHBOX, PUSHBUTTON, DEFPUSHBUTTON, RADIOBUTTON,
		STATE3, USERBUTTON, SPLITBUTTON, COMMANDLINK,

		// Edit Control
		EDITTEXT, BEDIT, HEDIT, IEDIT,

		// Combo Control
		COMBOBOX,

		// GroupBox Control
		GROUPBOX,

		// ListBox Control
		LISTBOX,
		
		// Icon Control
		ICON,

		// Scrollbar Control
		SCROLLBAR,

		// Compteur et type inconnu
		Count, Inconnu
	};

	class CRcControle
	{
	public:
 		//! Constructeur
 		CRcControle();
		// Constructeur
		CRcControle(RcControlType type);
		// Constructeur
		CRcControle(std::string sType);
		// Destructeur
		~CRcControle() = default;

		//! Constructeur par copie
		CRcControle(const CRcControle &source);														
		//! Opérateur =
		CRcControle &operator=(const CRcControle &source);

	public:
		std::string ToString();
		static std::string ToString(RcControlType type);

		RcControlType ToRcControlType();
		static RcControlType ToRcControlType(std::string sType);

	protected:
		RcControlType	m_type;
		std::string		m_sType;
	};
}
