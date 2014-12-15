// DObject_test.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <vld.h>
#include <functional>
#include <memory>

//
#include "DObjTest.h"
#include "Outils/NotificationClientRegistry.h"
#include "DObject/DObjListe.h"

// Linkage automatique avec la lib DObject
#pragma comment(lib, "DObject.lib")

//
using namespace std;
using namespace DObject;


int _tmain(int argc, _TCHAR* argv[])
{
	// Test de notifications
	if (0)
	{
		using namespace Outils;

		enum class Event { Ajouter, Modifier, Supprimer};

		class Liste
		{
		public:
			void OnNotification()					{ trace(_T("   ***  Liste : OnNotification \r\n")); }
			void OnNotificationEvent(Event& event)	{ trace(_T("   ***  Liste : OnNotification Event \r\n")); }
		};

		typedef NotificationClientEventRegistry<Event> Objet;

		// Création des parents
		Liste liste1;	// Observateur (Liste)
		Liste liste2;

		// Création des enfants
		Objet Obj1; // Observable
		Objet Obj2;

		Obj1.registerClient(Event::Ajouter, std::bind(&Liste::OnNotification, liste1));
		Obj1.registerClient(Event::Ajouter, std::bind(&Liste::OnNotification, liste2));
		assert(Obj1.getClientCount(Event::Ajouter) == 2);

		Obj1.registerClient(Event::Modifier, std::bind(&Liste::OnNotification, liste1));
		assert(Obj1.getClientCount(Event::Modifier) == 1);

		Obj2.registerClient(Event::Ajouter, std::bind(&Liste::OnNotificationEvent, liste1, Event::Ajouter));
		Obj2.registerClient(Event::Modifier, std::bind(&Liste::OnNotification, liste1));
		Obj2.registerClient(Event::Modifier, std::bind(&Liste::OnNotification, liste2));
		assert(Obj2.getClientCount(Event::Modifier) == 2);
		Obj2.removeClient(Event::Modifier);
		assert(Obj2.getClientCount(Event::Modifier) == 0);
		assert(Obj2.getClientCount(Event::Ajouter) == 1);


		Obj1.notifyClient(Event::Ajouter);
		Obj1.notifyClient(Event::Modifier);
		Obj1.notifyClient(Event::Supprimer);
		Obj2.notifyClient(Event::Ajouter);
		Obj2.notifyClient(Event::Modifier);
		Obj2.notifyClient(Event::Supprimer);
	}

	if (0)
	{
		using namespace Outils;

		class Liste
		{
		public:
			typedef std::shared_ptr<Liste> Ptr;

		public:
			void OnNotification()					{ trace(_T("   ***  Liste : OnNotification \r\n")); }
		};

		typedef NotificationClientRegistry Objet;
		typedef std::shared_ptr<Objet> ObjetPtr;

		// Création des parents
		Liste::Ptr liste1(new Liste());	// Observateur (Liste)
		Liste::Ptr liste2(new Liste());	// Observateur (Liste)

		// Création des enfants
		ObjetPtr Obj1(new Objet()); // Observable
 		ObjetPtr Obj2(new Objet());

 		Obj1->registerClient(std::bind(&Liste::OnNotification, liste1));
 		Obj1->registerClient(std::bind(&Liste::OnNotification, liste2));
 		assert(Obj1->getClientCount() == 2);


	}


	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("test1");
		CDObjTest* t2 = new CDObjTest(2);	t2->SetString1("test2");
		CDObjTest* t3 = new CDObjTest(3);	t3->SetString1("test3");
		CDObjTest* t4 = new CDObjTest(4);	t4->SetString1("test4");
		CDObjTest* t5 = new CDObjTest(5);	t5->SetString1("test5");
		CDObjTest* t6 = new CDObjTest(6);	t6->SetString1("test6");

		t1->SetPourSupprimer(false);
		t2->SetPourSupprimer(true);
		t2->SetPourSupprimer(false);

		CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
		pListe1->Reserve(5);
		pListe1->Add(t1);
		pListe1->Add(t2);

		assert(pListe1->EstModifier());

		pListe1->Sauver();
		assert(pListe1->EstModifier()==false);


		t1->SetPourSupprimer(true);
		t1->SetPourSupprimer(true);
		t2->SetPourSupprimer(true);
		t1->SetPourSupprimer(false);
		t1->SetPourSupprimer(true);
		t1->SetPourSupprimer(false);

		CDObjTest* pt1 = pListe1->GetAt(0, ObjEtat::Valide);
		CDObjTest* pt2 = pListe1->GetAt(1, ObjEtat::Valide);

		CDObjTest* pf1 = pListe1->GetAt(0, ObjEtat::PourSupprimer);
		CDObjTest* pf2 = pListe1->GetAt(1, ObjEtat::PourSupprimer);

		CDObjTest* pi2 = pListe1->GetFromId(2);
		CDObjTest* pi4 = pListe1->GetFromId(4);

		CDObjTest* pui2 = pListe1->GetFromUUID(t2->GetLPGUID());
		CDObjTest* pui4 = pListe1->GetFromUUID(t4->GetLPGUID());

		CDObjTestListe liste2("liste2");
		liste2.Reserve(5);
		liste2.Add(t3);
		liste2.Add(t4);

		t3->SetModifier(true);

		t3 = (CDObjTest*)t3->Delete();
		t3 = liste2.GetFromId(3);
		assert(liste2.GetCount()==1);
		assert(t3 == nullptr);

		pListe1->Append(*pListe1);
		pListe1->Append(liste2);

		pListe1->InsertAt(3, t4);
		pListe1->InsertAt(3, t5);
		pListe1->InsertAt(8, t6);

		CDObjTest* gp = new CDObjTest(99);	gp->SetString1("Grand père");
		pListe1->AddParent(gp);

		CDObjTestListe liste3("liste3");
		liste3.Add(t4);
		liste3.Copy(*pListe1);
		liste3.Remove(pt1);

		pListe1->SortById();

		delete pListe1;
		delete gp;
	}

	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("test1");

		CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
		pListe1->Add(t1);

		CDObjTestListe* pListe2 = new CDObjTestListe("liste2");
		pListe2->Add(t1);

		pListe1->Verifier();
		pListe1->SetPourSupprimer(true, true);
		pListe1->SetPourSupprimer(false, true);

		delete t1;
		delete pListe1;
		delete pListe2;
	}

	// Tester la suppression d'un obj qui est dans plusieurs listes
	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("test1");		//t1->SetAcquis(true);

		CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
		pListe1->Add(t1);

		CDObjTestListe* pListe2 = new CDObjTestListe("liste2");
		pListe2->Add(t1);

		pListe1->SetPourSupprimer(true, true);
		pListe1->Supprimer();

		assert(pListe1->GetCount() == 0);
		assert(pListe2->GetCount() == 0);

		delete pListe1;
		delete pListe2;
	}

	// Tester la sauvegarde d'un obj qui est dans plusieurs listes
	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("test1");
		CDObjTest* t2 = new CDObjTest(2);	t2->SetString1("test2");
		CDObjTest* t3 = new CDObjTest(3);	t3->SetString1("test3");

		t2->SetPourSupprimer();

		t1->Sauver();
		assert(t1->EstAcquis());

		CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
		pListe1->Add(t1);
		pListe1->Add(t2);
		pListe1->Add(t3);

		CDObjTestListe* pListe2 = new CDObjTestListe("liste2");
		pListe2->Add(t2);

		pListe1->Sauver();
		pListe2->Sauver();


		assert(pListe1->EstAcquis());
		assert(t1->EstAcquis());
		assert(t3->EstAcquis());

		delete pListe1;
		delete pListe2;
	}

	if(1)
	{
		CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");

		auto pObjListe1 = dynamic_cast<CDObjListe<CDObjTest>*>(pListe1);
		assert(pObjListe1);

		CDObjListe<>* pObjListe2 = dynamic_cast<CDObjListe<>*>(pListe1);
		assert(pObjListe2 == NULL);

		IDObjListe* pObjListe3 = dynamic_cast<IDObjListe*>(pListe1);
		assert(pObjListe3);

		delete pListe1;
	}

	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("(t1) Parent");		t1->SetAcquis(true);
		CDObjTest* t2 = new CDObjTest(2);	t2->SetString1("(t2) Enfant 1");	t2->SetAcquis(true);
 	
		t2->AddParent(t1);

		delete t1;
		delete t2;
	}

	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("(t1) Parent");		t1->SetAcquis(true);
		CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");
 	
		pListe1->AddParent(t1);

		delete t1;
		delete pListe1;
	}

	if (1)
	{
		CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1 Parent");
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("(t1) Enfant");		t1->SetAcquis(true);
 	
		t1->AddParent(pListe1);

		delete pListe1;
		delete t1;
	}

	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("(t1) Parent");		t1->SetAcquis(true);
		CDObjTest* t2 = new CDObjTest(2);	t2->SetString1("(t2) Enfant 1");	t2->SetAcquis(true);

 		// 1er test
 		{
 			t2->AddParent(t1);
 			CDObjTest* P1 = t2->GetParent<CDObjTest*>();
 			assert(P1 == t1);
 
 			// Lorsqu'un enfant est modifié, alors le parent doit en être avertis
 			t2->SetString1("(t2) Enfant 1 de Parent");
 
			assert(t2->EstModifier() == true);
			assert(t1->EstModifier() == false);
			assert(t1->SontEnfantsModifier() == true);
 		}
 		t1->Sauver();
 		t2->Sauver();


		CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");
		CDObjTest* t3 = new CDObjTest(3);	t3->SetString1("Enfant 3");		t3->SetAcquis(true);

		// 2eme test
		{
 			pListe1->AddParent(t1);
  			CDObjTest* P1 = pListe1->GetParent<CDObjTest*>();
  			assert(P1 == t1);
 
 			//
 			pListe1->Add(t3);
 			auto PL1 = t3->GetParent<CDObjTestListe*>();
 			auto PL2 = t3->GetParent<CDObjListe<CDObjTest>*>();
			assert(PL1 == pListe1);
 
 			assert(pListe1->EstModifier() == true);
			assert(t1->EstModifier() == false);
			assert(t1->SontEnfantsModifier() == true);
 
 			// Lorsqu'un enfant est modifié, alors le parent doit en être avertis
 			t3->SetString1("Enfant 1 de Liste 1");
 
 			assert(t3->EstModifier() == true);
 			assert(PL1->EstModifier() == true);
			assert(t1->EstModifier() == false);
			assert(t1->SontEnfantsModifier() == true);
		}

		delete t1;
		delete t2;
		delete t3;
		delete pListe1;
	}

	if (1)
	{
		CDObjTest* t1 = new CDObjTest(1);	t1->SetString1("Parent");		t1->SetAcquis(true);
		CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");

		pListe1->AddParent(t1);

		delete pListe1;
		delete t1;
	}


	if (1)
	{
		CDObjTest* gp = new CDObjTest(99);	gp->SetString1("Grand père");	gp->SetAcquis(true);
		CDObjTestListe* pListe = new CDObjTestListe("Liste");
		CDObjTest* e1 = new CDObjTest(3);	e1->SetString1("Enfant 1");		e1->SetAcquis(true);
		CDObjTest* e2 = new CDObjTest(3);	e2->SetString1("Enfant 2");		e2->SetAcquis(true);

		pListe->AddParent(gp);
		pListe->Add(e1);
		pListe->Add(e2);

		assert(gp->EstModifier() == false);
		assert(gp->SontEnfantsModifier() == true);
		assert(pListe->EstModifier() == true);

		delete gp;
		delete pListe;
	}


	return 0;
}

