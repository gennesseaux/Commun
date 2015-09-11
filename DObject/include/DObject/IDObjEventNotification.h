//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Evènements
//
//	-----------------------------------------------------------------------------
//	 Révisions		:	02/09/2015 : 
//	-----------------------------------------------------------------------------

#pragma once

// Inclusions
#include "DObject/DObjGlobal.h"

namespace DObject
{
	class CDObject;

	class IDObjEventNotification
	{
	public:
		//! Notification d'évènement
		virtual void OnEvent(DObjEvent& event, CDObject* sender) = 0;

		//! Notification d'évènement
		virtual void OnModifier(CDObject* pDObject, CDObject* sender) {};
		//! Notification d'évènement
		virtual void OnSauver(CDObject* pDObject, CDObject* sender) {};
		//! Notification d'évènement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender) {};
	};
}
