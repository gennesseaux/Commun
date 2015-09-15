///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	DObjTest.h
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de test
//
//	-----------------------------------------------------------------------
//	 Révisions		:	16/7/2014 : 
//	-----------------------------------------------------------------------
//*/

#pragma once

// Inclusions
#include "DObject/DObjBase.h"
#include "DObject/DObjListe.h"


namespace DObject
{
	class CDObjTestListe;

	// Classe CDObjTest
	class CDObjTest : public CDObjBase
	{
	public:
		//! Constructeur
		CDObjTest(unsigned long ulId, CDObject* pOwner = nullptr);
		//! Destructeur
		~CDObjTest(void);

		//! Constructeur par copie.
		CDObjTest(const CDObjTest &source);
		//! Opérateur =
		CDObjTest &operator=(const CDObjTest &source);

		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CDObjTest &source);

	public:
		//! Initialisation des données membres de la classe
		virtual void InitialiserDonnees();
		//! Initialisation de l'objet
		virtual bool Initialiser();
		//! Vérifie si toutes les données obligatoire pour 
		//! la sauvegarde sont renseignées
		virtual bool Verifier(std::string* = NULL);
		//! Sauvegarde de l'objet
		virtual bool Sauver();
		//! Suppression de l'objet
		virtual bool Supprimer();

	// Gestion des évènements
	public:
		//! Notification d'évènement
		virtual void OnModifier(CDObject* pDObject, CDObject* sender);
		//! Notification d'évènement
		virtual void OnSauver(CDObject* pDObject, CDObject* sender);
		//! Notification d'évènement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender);

	// Accesseurs
	public:
		std::string GetString();
		bool SetString(std::string string1);

		
		CDObjTest* GetPointeur1();
		CDObjTest* GetPointeur2();
		
		CDObjTestListe* GetPointeurListe1(bool bInit = true);
		CDObjTestListe* GetPointeurListe2(bool bInit = true);


	private:
		// Données membres
		std::string		_string1;

		CDObjTest*		_pointeur1;
		CDObjTest*		_pointeur2;
		CDObjTestListe*	_pointeurListe1;
		CDObjTestListe*	_pointeurListe2;
	};



	// Classe CDObjTestListe
	class CDObjTestListe : public CDObjListe<CDObjTest>
	{
	public:
		//! Constructeur
		CDObjTestListe(std::string string, CDObject* pOwner = nullptr);
		//! Destructeur
		~CDObjTestListe(void);

		//! Constructeur par copie.
		CDObjTestListe(const CDObjTestListe &source);
		//! Opérateur =
		CDObjTestListe &operator=(const CDObjTestListe &source);
		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CDObjTestListe &source);

	public:
		//! Initialisation des données membres de la classe
		virtual void InitialiserDonnees();
		//! Initialisation de la liste d'objet
		virtual bool Initialiser();
		//! Verification
		virtual bool Verifier(std::string* sMsg = NULL);
		//! Sauvegarde
		virtual bool Sauver();
		//! Suppression
		virtual bool Supprimer();

	// Gestion des évènements
	public:
		//! Notification d'évènement
		virtual void OnModifier(CDObject* pDObject, CDObject* sender);
		//! Notification d'évènement
		virtual void OnSauver(CDObject* pDObject, CDObject* sender);
		//! Notification d'évènement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender);

	// Accesseurs
	public:
		std::string GetString1();
		bool SetString1(std::string string1);


	private:
		std::string _string;
	};

}
