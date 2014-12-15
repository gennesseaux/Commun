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
//	 R�visions		:	16/7/2014 : 
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
		//! Op�rateur =
		CDObjTest &operator=(const CDObjTest &source);
		////! Constructeur de d�placement.
		//CDObjTest(CDObjTest&& source);
		////! Op�rateur de d�placement
		//CDObjTest &operator=(CDObjTest&& source);

		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CDObjTest &source);

	public:
		//! Initialisation des donn�es membres de la classe
		virtual void InitialiserDonnees();
		//! Initialisation de l'objet
		virtual bool Initialiser();
		//! V�rifie si toutes les donn�es obligatoire pour 
		//! la sauvegarde sont renseign�es
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
		// Donn�es membres
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
		//! Op�rateur =
		CDObjTestListe &operator=(const CDObjTestListe &source);
		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CDObjTestListe &source);

	public:
		//! Initialisation des donn�es membres de la classe
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
