//	-----------------------------------------------------------------------------
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Ev�nements
//
//	-----------------------------------------------------------------------------
//	 R�visions		:	02/09/2015 : 
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
		//! Notification d'�v�nement
		virtual void OnEvent(DObjEvent& event, CDObject* sender) = 0;

		//! Notification d'�v�nement
		virtual void OnModifier(CDObject* pDObject, CDObject* sender) {};
		//! Notification d'�v�nement
		virtual void OnSauver(CDObject* pDObject, CDObject* sender) {};
		//! Notification d'�v�nement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender) {};
	};
}
