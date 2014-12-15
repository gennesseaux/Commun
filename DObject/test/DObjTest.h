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
		CDObjTest(unsigned long ulId);
		//! Destructeur
		~CDObjTest(void);

		//! Constructeur par copie.
		CDObjTest(const CDObjTest &source);
		//! Opérateur =
		CDObjTest &operator=(const CDObjTest &source);
		////! Constructeur de déplacement.
		//CDObjTest(CDObjTest&& source);
		////! Opérateur de déplacement
		//CDObjTest &operator=(CDObjTest&& source);

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

	public:
		std::string GetString1();
		bool SetString1(std::string string1);

		std::string GetString2();
		bool SetString2(std::string string2);

		long GetL1() ;
		bool SetL1(long l1);

		long GetL2();
		bool SetL2(long l2);

		unsigned long GetUL3();
		bool SetUL3(unsigned long ul3);

		
		CDObjTestListe* GetPointeurListe(bool bInit = true);


	private:
		// Données membres
		std::string		_string1;
		std::string		_string2;
		long			_l1;
		long			_l2;
		unsigned long	_ul3;

		CDObjTest*		_pointeur;
		CDObjTestListe*	_pointeurListe;
	};



	// Classe CDObjTestListe
	class CDObjTestListe : public CDObjListe<CDObjTest>
	{
	public:
		//! Constructeur
		CDObjTestListe(std::string string);
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


	private:
		std::string _string;
	};

}
