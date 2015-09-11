//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	D�finition des constantes ou m�thodes globales
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	18/6/2014 : 
//	-----------------------------------------------------------------------------

#pragma once

//! Inclusions
#include <algorithm>
#include <cassert>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>


namespace DObject
{
	//! D�finition des valeurs par d�faut utilis�es dans les objets
	#define DefInt		INT_MIN
	#define DefUInt		UINT_MAX
	#define DefLong		LONG_MIN
	#define DefULong	ULONG_MAX

	// Gestion du cache des objets
	// Par d�faut la gestion du cache est activ�e
	static bool _useCache = true;

	// Ev�nements utilis�s entre les objets et les listes
	enum class DObjEvent
	{
		ObjetModifierEvent,				// L'objet est modifi�
		ObjetSauverEvent,				// L'objet est modifi�
		ObjetPourSupprimerEvent,		// L'objet est en attente de suppression
		ObjetSupprimerEvent,			// L'objet est supprim�
	};
}
