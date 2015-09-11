//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Définition des constantes ou méthodes globales
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	18/6/2014 : 
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
	//! Définition des valeurs par défaut utilisées dans les objets
	#define DefInt		INT_MIN
	#define DefUInt		UINT_MAX
	#define DefLong		LONG_MIN
	#define DefULong	ULONG_MAX

	// Gestion du cache des objets
	// Par défaut la gestion du cache est activée
	static bool _useCache = true;

	// Evènements utilisés entre les objets et les listes
	enum class DObjEvent
	{
		ObjetModifierEvent,				// L'objet est modifié
		ObjetSauverEvent,				// L'objet est modifié
		ObjetPourSupprimerEvent,		// L'objet est en attente de suppression
		ObjetSupprimerEvent,			// L'objet est supprimé
	};
}
