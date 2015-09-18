
// Inclusions
#include "StdAfx.h"
#include "DObjTest.h"

namespace DObject
{
	//! Constructeur
	CDObjTest::CDObjTest(unsigned long ulId, CDObject* pOwner /*= nullptr*/)  : CDObjBase(ulId,pOwner)
	{
		/* Initialisation des pointeurs. */
		_pointeur1 = nullptr;
		_pointeur2 = nullptr;
		_pointeurListe1 = nullptr;
		_pointeurListe2 = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CDObjTest::~CDObjTest(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CDObjTest::CDObjTest(const CDObjTest &source)
	{
		/* Initialisation des pointeurs. */
		_pointeur1 = nullptr;
		_pointeur2 = nullptr;
		_pointeurListe1 = nullptr;
		_pointeurListe2 = nullptr;

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

	void CDObjTest::ClonnerDonnees(const CDObjTest &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		_string1 = source._string1;

		/* Copie des pointeurs membres de l'objet. */
		delete _pointeur1; _pointeur1 = nullptr;
		if (source._pointeur1)
			_pointeur1 = new CDObjTest(*source._pointeur1);

		delete _pointeur2; _pointeur2 = nullptr;
		if(source._pointeur2)
			_pointeur2 = new CDObjTest(*source._pointeur2);

		delete _pointeurListe1; _pointeurListe1 = nullptr;
		if (source._pointeurListe1)
			_pointeurListe1 = new CDObjTestListe(*source._pointeurListe1);

		delete _pointeurListe2; _pointeurListe2 = nullptr;
		if(source._pointeurListe2)
			_pointeurListe2 = new CDObjTestListe(*source._pointeurListe2);
	}

	void CDObjTest::InitialiserDonnees()
	{
		_string1 = std::string("");

		delete _pointeur1; _pointeur1 = nullptr;
		delete _pointeur2; _pointeur2 = nullptr;
		delete _pointeurListe1; _pointeurListe1 = nullptr;
		delete _pointeurListe2; _pointeurListe2 = nullptr;
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
			if (_pointeur1 && (!_pointeur1->Verifier(sMsg))) return false;
			if (_pointeur2 && (!_pointeur2->Verifier(sMsg))) return false;
			if (_pointeurListe1 && (!_pointeurListe1->Verifier(sMsg))) return false;
			if (_pointeurListe2 && (!_pointeurListe2->Verifier(sMsg))) return false;
		}

		if (!Initialiser())			{ if (sMsg) sMsg->assign("Erreur lors de l'initialisation."); return false; }
		if (_string1.empty())		{ if (sMsg) sMsg->assign("Erreur : _string est vide."); return false; }

		return true;
	}

	bool CDObjTest::Sauver()
	{
		// L'objet n'est pas modifié
		if ( !(DoitEtreSauver() || DoitEtreSupprimer()) ) return true;
		// L'objet est supprimé
		if ( !(PeutEtreSauver() || PeutEtreSupprimer()) ) return false;
		// L'objet est à supprimer
		if ( DoitEtreSupprimer() ) return Supprimer();

		// SaveGuard
		DObjSaveGuard::Start(this);

		// ...
		// Mettre ici le code avant sauvegarde de l'objet
		// ...

		
		// Sauvegarde de _pointeur1
		if(_pointeur1 && !_pointeur1->Sauver())
			return DObjSaveGuard::Error(this);
		// Mise à jour
		//if(_pointeur1) SetXXXX(_pointeur1->GetXXX());
		
		// Sauvegarde de _pointeur2
		if(_pointeur2 && !_pointeur2->Sauver())
			return DObjSaveGuard::Error(this);
		// Mise à jour
		//if(_pointeur2) SetXXXX(_pointeur2->GetXXX());


		// ...
		// Mettre ici le code de sauvegarde de l'objet
		// 
		// En cas d'erreur
		//	{ state.Restore(); return false; }
		// ...

		// ...
		// Mettre ici le code après sauvegarde de l'objet
		// ...


		
		// Sauvegarde de _pointeurListe1
		if(_pointeurListe1 && !_pointeurListe1->Sauver())
			return DObjSaveGuard::Error(this);

		// Sauvegarde de _pointeurListe2
		if(_pointeurListe2 && !_pointeurListe2->Sauver())
			return DObjSaveGuard::Error(this);


		// L'objet est acquis
		SetAcquis();

		return DObjSaveGuard::Sucess(this);
	}

	bool CDObjTest::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return false;
		if (PeutEtreSupprimer() == false) return false;

		// SaveGuard
		DObjSaveGuard::Start(this);

		//
		if(_string1 == "DoNotDelete")
			return DObjSaveGuard::Error(this);

		if(_pointeurListe1)
		{
			_pointeurListe1->SetPourSupprimer(true,true);

			if(!_pointeurListe1->Supprimer())
				return DObject::DObjSaveGuard::Error(this);
		}

		if(_pointeurListe2)
		{
			_pointeurListe2->SetPourSupprimer(true,true);

			if(!_pointeurListe2->Supprimer())
			{
				return DObject::DObjSaveGuard::Error(this);
			}
		}

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

		return DObjSaveGuard::Sucess(this);
	}

	bool CDObjTest::SetString(std::string string)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (_string1 != string)
		{
			// Affectation de la nouvelle valeur.
			_string1 = string;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	std::string CDObjTest::GetString()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string("");

		return _string1;
	}

	CDObjTest* CDObjTest::GetPointeur1()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return nullptr;

		// Si la liste n'existe pas, alosr on la crée. 
		if(_pointeur1 == nullptr)
		{
			_pointeur1 = new CDObjTest(1,this);
		}

		//// 
		//if(_pointeur1 && _pointeur1->GetString1() != "Liste 1 enfant")
		//{
		//	delete _pointeur1; _pointeur1 = nullptr;
		//	return GetPointeur1();
		//}

		return _pointeur1;
	}

	CDObjTest* CDObjTest::GetPointeur2()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return nullptr;

		// Si la liste n'existe pas, alosr on la crée. 
		if(_pointeur2 == nullptr)
		{
			_pointeur2 = new CDObjTest(2,this);
		}

		//// 
		//if(_pointeur2 && _pointeur2->GetString1() != "Liste 1 enfant")
		//{
		//	delete _pointeur2; _pointeur2 = nullptr;
		//	return GetPointeur2();
		//}

		return _pointeur2;
	}

	CDObjTestListe* CDObjTest::GetPointeurListe1(bool bInit)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return nullptr;

		// Si la liste n'existe pas, alosr on la crée. 
		if(_pointeurListe1 == nullptr)
		{
			_pointeurListe1 = new CDObjTestListe("Liste 1 enfant",this);
			//if(bInit) _pointeurListe->InitialiserAPartirDePrjIdent(m_ulId);
		}
		// 
		else if(_pointeurListe1 && _pointeurListe1->GetString1() != "Liste 1 enfant")
		{
			delete _pointeurListe1; _pointeurListe1 = nullptr;
			return GetPointeurListe1(bInit);
		}

		return _pointeurListe1;
	}

	CDObjTestListe* CDObjTest::GetPointeurListe2(bool bInit)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return nullptr;

		// Si la liste n'existe pas, alosr on la crée. 
		if(_pointeurListe2 == nullptr)
		{
			_pointeurListe2 = new CDObjTestListe("Liste 2 enfant",this);
			//if(bInit) _pointeurListe2->InitialiserAPartirDePrjIdent(m_ulId);
		}
		// 
		else if(_pointeurListe2 && _pointeurListe2->GetString1() != "Liste 2 enfant")
		{
			delete _pointeurListe2; _pointeurListe2 = nullptr;
			return GetPointeurListe2(bInit);
		}

		return _pointeurListe2;
	}

	void CDObjTest::OnModifier(CDObject* pDObject,CDObject* sender)
	{
		int todo = 0;
	}

	void CDObjTest::OnSauver(CDObject* pDObject,CDObject* sender)
	{
		int todo = 0;
	}

	void CDObjTest::OnSupprimer(CDObject* pDObject,CDObject* sender)
	{
		if(_pointeur1 && _pointeur1==pDObject)					_pointeur1 = nullptr;
		if(_pointeur2 && _pointeur2==pDObject)					_pointeur2 = nullptr;
		if(_pointeurListe1 && _pointeurListe1==pDObject)		_pointeurListe1 = nullptr;
		if(_pointeurListe2 && _pointeurListe2==pDObject)		_pointeurListe2 = nullptr;
		int todo = 0;
	}










	//! Constructeur
	CDObjTestListe::CDObjTestListe(std::string string, CDObject* pOwner /*= nullptr*/) : CDObjListe(pOwner)
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
		if (GetSize())
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
		// L'objet n'est pas modifié
		if ( !(DoitEtreSauver() || DoitEtreSupprimer()) ) return true;
		// L'objet est supprimé
		if ( !(PeutEtreSauver() || PeutEtreSupprimer()) ) return false;
		// L'objet est à supprimer
		if ( DoitEtreSupprimer() ) return Supprimer();
		
		// SaveGuard
		DObjSaveGuard::Start(this);

		// ...
		// Mettre ici le code avant sauvegarde des objets
		// ...

		// Sauvegarde des objets
		if (!CDObjListe::Sauver())
			return DObjSaveGuard::Error(this);

		// ...
		// Mettre ici le code après sauvegarde des objets
		// ...


		// Les objets sont acquis
		SetAcquis();

		return DObjSaveGuard::Sucess(this);
	}

	//! Suppression
	bool CDObjTestListe::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return true;
		if (PeutEtreSupprimer() == false) return false;
		
		// SaveGuard
		DObjSaveGuard::Start(this);

		// ...
		// Mettre ici le code avant suppression des objets
		// ...

		// Suppression des objets
		if (!CDObjListe::Supprimer())
			return DObjSaveGuard::Error(this);

		// ...
		// Mettre ici le code après suppression des objets
		// ...


		// Les objets sont supprimés
		SetSupprimer();

		return DObjSaveGuard::Sucess(this);
	}

	bool CDObjTestListe::SetString1(std::string string)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (_string != string)
		{
			// Affectation de la nouvelle valeur.
			_string = string;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	std::string CDObjTestListe::GetString1()
	{
		return _string;
	}

	void CDObjTestListe::OnModifier(CDObject* pDObject,CDObject* sender)
	{
		int todo = 0;
	}

	void CDObjTestListe::OnSauver(CDObject* pDObject,CDObject* sender)
	{
		int todo = 0;
	}

	void CDObjTestListe::OnSupprimer(CDObject* pDObject,CDObject* sender)
	{
		int todo = 0;
	}

}
