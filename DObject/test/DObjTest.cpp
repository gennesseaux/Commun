
// Inclusions
#include "StdAfx.h"
#include "DObjTest.h"

namespace DObject
{
	//! Constructeur
	CDObjTest::CDObjTest(unsigned long ulId)  : CDObjBase(ulId)
	{
		/* Initialisation des pointeurs. */
		_pointeur = nullptr;
		_pointeurListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CDObjTest::~CDObjTest(void)
	{
		RemoveEnfants();

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CDObjTest::CDObjTest(const CDObjTest &source)
	{
		/* Initialisation des pointeurs. */
		_pointeur = nullptr;
		_pointeurListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObjTest & CDObjTest::operator=(const CDObjTest &source)
	{
		/* Clonage des données. */
		if(this != &source)
		{
			ClonnerDonnees(source);
		}

		return *this;
	}

	////! Constructeur de déplacement.
	//CDObjTest::CDObjTest(CDObjTest&& source)
	//{
	//	_string1 = source._string1;
	//	_string2 = source._string2;
	//	_l1 = source._l1;
	//	_l2 = source._l2;
	//	_ul3 = source._ul3;
	//	_pointeur = source._pointeur;
	//	_pointeurListe = source._pointeurListe;

	//	source._string1 = "";
	//	source._string2 = "";
	//	source._l1 = DefLong;
	//	source._l2 = DefLong;
	//	source._ul3 = DefULong;
	//	source._pointeur = nullptr;
	//	source._pointeurListe = nullptr;
	//}

	////! Opérateur de déplacement
	//CDObjTest & CDObjTest::operator=(CDObjTest&& source)
	//{
	//	if(this != &source)
	//	{
	//		_string1 = source._string1;
	//		_string2 = source._string2;
	//		_l1 = source._l1;
	//		_l2 = source._l2;
	//		_ul3 = source._ul3;
	//		_pointeur = source._pointeur;
	//		_pointeurListe = source._pointeurListe;

	//		source._string1 = "";
	//		source._string2 = "";
	//		source._l1 = DefLong;
	//		source._l2 = DefLong;
	//		source._ul3 = DefULong;
	//		source._pointeur = nullptr;
	//		source._pointeurListe = nullptr;
	//	}

	//	return *this;
	//}

	void CDObjTest::ClonnerDonnees(const CDObjTest &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		//_l1 = source._l1;
		//_l2 = source._l2;
		//_ul3 = source._ul3;
		_string1 = source._string1;
		//_string2 = source._string2;

		/* Copie des pointeurs membres de l'objet. */
		if (source._pointeur)
			_pointeur = new CDObjTest(*source._pointeur);

		if (source._pointeurListe)
			_pointeurListe = new CDObjTestListe(*source._pointeurListe);
	}

	void CDObjTest::InitialiserDonnees()
	{
		//_l1 = DefLong;
		//_l2 = DefLong;
		//_ul3 = DefULong;
		_string1 = std::string("");
		//_string2 = std::string("");

		delete _pointeur; _pointeur = nullptr;
		delete _pointeurListe; _pointeurListe = nullptr;
	}

	bool CDObjTest::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// ...
		// Mettre ici le code d'initialisation de l'objet
		// ...


		// L'objet est à présent acqui et initialisé
		SetAcquis();

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	bool CDObjTest::Verifier(std::string* sMsg)
	{
		// Les objets qui dépendent de cette objet ne doivent*
		// pas être vérifiés lors de la création.
		if (!EstNouveau())
		{
			if (_pointeur && (!_pointeur->Verifier(sMsg))) return false;
			if (_pointeurListe && (!_pointeurListe->Verifier(sMsg))) return false;
		}

		if (!Initialiser())			{ if (sMsg) sMsg->assign("Erreur lors de l'initialisation."); return false; }
		if (_string1.empty())		{ if (sMsg) sMsg->assign("Erreur : _string est vide."); return false; }

		return true;
	}

	bool CDObjTest::Sauver()
	{
		if ( !(DoitEtreSauver() || DoitEtreSupprimer()) ) return true;
		if ( !(PeutEtreSauver() || PeutEtreSupprimer()) ) return false;

		// Mémorisation de l'etat de l'objet avant sauvegarde
		CDObjState state(this);

		// ...
		// Mettre ici le code avant sauvegarde de l'objet
		// ...

		// ...
		// Mettre ici le code de sauvegarde de l'objet
		// 
		// En cas d'erreur
		//	{ state.Restore(); return false; }
		// ...

		// ...
		// Mettre ici le code après sauvegarde de l'objet
		// ...


		// L'objet est acquis
		SetAcquis();

		return true;
	}

	bool CDObjTest::Supprimer()
	{
		if (DoitEtreSupprimer() == false) { SetSupprimer(true);  return true; }
		if (PeutEtreSupprimer() == false) { SetSupprimer(false); return false; }

		// Mémorisation de l'etat de l'objet avant sauvegarde
		CDObjState state(this);

		// ...
		// Mettre ici le code avant suppression de l'objet
		// ...

		// ...
		// Mettre ici le code de suppression de l'objet
		// 
		// En cas d'erreur
		//	{ state.Restore(); return false; }
		// ...

		// ...
		// Mettre ici le code après suppression de l'objet
		// ...


		// L'objet est supprimé
		SetSupprimer();

		return true;
	}

	//long CDObjTest::GetL1()
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return DefLong;

	//	return _l1;
	//}

	//bool CDObjTest::SetL1(long l1)
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return false;

	//	// Le champ est modifié uniquement si sa valeur change.
	//	if (_l1 != l1)
	//	{
	//		// Affectation de la nouvelle valeur.
	//		_l1 = l1;

	//		// Marquer l'objet comme modifié.
	//		SetModifier();
	//	}

	//	// Le changement de valeur a réussi.
	//	return true;
	//}

	//long CDObjTest::GetL2()
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return DefLong;

	//	return _l2;
	//}

	//bool CDObjTest::SetL2(long l2)
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return false;

	//	// Le champ est modifié uniquement si sa valeur change.
	//	if (_l2 != l2)
	//	{
	//		// Affectation de la nouvelle valeur.
	//		_l2 = l2;

	//		// Marquer l'objet comme modifié.
	//		SetModifier();
	//	}

	//	// Le changement de valeur a réussi.
	//	return true;
	//}

	//unsigned long CDObjTest::GetUL3()
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return DefLong;

	//	return _ul3;
	//}

	//bool CDObjTest::SetUL3(unsigned long ul3)
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return false;

	//	// Le champ est modifié uniquement si sa valeur change.
	//	if (_ul3 != ul3)
	//	{
	//		// Affectation de la nouvelle valeur.
	//		_ul3 = ul3;

	//		// Marquer l'objet comme modifié.
	//		SetModifier();
	//	}

	//	// Le changement de valeur a réussi.
	//	return true;
	//}

	bool CDObjTest::SetString1(std::string string1)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (_string1 != string1)
		{
			// Affectation de la nouvelle valeur.
			_string1 = string1;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	std::string CDObjTest::GetString1()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string("");

		return _string1;
	}

	//bool CDObjTest::SetString2(std::string string2)
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return false;

	//	// Le champ est modifié uniquement si sa valeur change.
	//	if (_string2 != string2)
	//	{
	//		// Affectation de la nouvelle valeur.
	//		_string2 = string2;

	//		// Marquer l'objet comme modifié.
	//		SetModifier();
	//	}

	//	// Le changement de valeur a réussi.
	//	return true;
	//}

	//std::string CDObjTest::GetString2()
	//{
	//	// L'objet doit être initialisé
	//	if (!Initialiser()) return std::string("");

	//	return _string2;
	//}

	CDObjTestListe* CDObjTest::GetPointeurListe(bool bInit)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return nullptr;

		// Si la liste n'existe pas, alosr on la crée. 
		if (_pointeurListe == nullptr)
		{
			_pointeurListe = new CDObjTestListe("Liste enfant");
			_pointeurListe->AddParent(this);
		//	if (bInit) _pointeurListe->InitialiserAPartirDePrjIdent(m_ulId);
		//}
		//// 
		//else if (_pointeurListe && _pointeurListe->GetPrjIdent() != m_ulId)
		//{
		//	delete _pointeurListe; _pointeurListe = nullptr;
		//	return GetPointeurListe(bInit);
		}

		return _pointeurListe;
	}











	//! Constructeur
	CDObjTestListe::CDObjTestListe(std::string string)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		_string = string;
	}

	//! Destructeur
	CDObjTestListe::~CDObjTestListe(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CDObjTestListe::CDObjTestListe(const CDObjTestListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CDObjTestListe & CDObjTestListe::operator=(const CDObjTestListe &source)
	{
		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CDObjTestListe::ClonnerDonnees(const CDObjTestListe &source)
	{
		/* Initialisation des données. */
		InitialiserDonnees();


		/* Copie des variables membres de l'objet. */
		_string = source._string;

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des données membres de la classe
	void CDObjTestListe::InitialiserDonnees()
	{
		_string = std::string("");
	}

	//! Initialisation de la liste d'objet
	bool CDObjTestListe::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;


		// ...
		// Mettre ici le code d'initialisation de la liste d'objet
		// 
		// Attention : ne pas oublier d'initialiser la taille de la liste
			//	Reserve(123);
		// ...


		// L'objet est acquis
		if (GetCount())
			SetAcquis();

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	//! Verification
	bool CDObjTestListe::Verifier(std::string* sMsg)
	{

		// ...
		// Mettre ici les vérifications de la liste
		// ...

		// Vérifications de base
		return CDObjListe::Verifier(sMsg);
	}

	//! Sauvegarde
	bool CDObjTestListe::Sauver()
	{
		if ( !(DoitEtreSauver() || DoitEtreSupprimer()) ) return true;
		if ( !(PeutEtreSauver() || PeutEtreSupprimer()) ) return false;

		// ...
		// Mettre ici le code avant sauvegarde des objets
		// ...

		// Sauvegarde des objets
		if (!CDObjListe::Sauver())
			return false;

		// ...
		// Mettre ici le code après sauvegarde des objets
		// ...


		// Les objets sont acquis
		SetAcquis();

		return true;
	}

	//! Suppression
	bool CDObjTestListe::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return true;
		if (PeutEtreSupprimer() == false) return false;

		// ...
		// Mettre ici le code avant suppression des objets
		// ...

		// Suppression des objets
		if (!CDObjListe::Supprimer())
			return false;

		// ...
		// Mettre ici le code après suppression des objets
		// ...


		// Les objets sont supprimés
		SetSupprimer();

		return true;
	}

}
