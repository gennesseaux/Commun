#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
#include "DObjTest.h"
#include "Outils/NotificationClientRegistry.h"
#include "DObject/DObjListe.h"

using namespace DObject;
using namespace Outils;

namespace Commun_test
{
	TEST_CLASS(DObject_test)
	{
	public:

		TEST_METHOD(DObjectTest1)
		{

			enum class Event { Ajouter,Modifier,Supprimer };

			class Liste
			{
			public:
				void OnNotification() { trace(_T("   ***  Liste : OnNotification \r\n")); }
				void OnNotificationEvent(Event& event) { trace(_T("   ***  Liste : OnNotification Event \r\n")); }
			};

			typedef NotificationClientEventRegistry<Event> Objet;

			// Création des parents
			Liste liste1;	// Observateur (Liste)
			Liste liste2;

			// Création des enfants
			Objet Obj1; // Observable
			Objet Obj2;

			Obj1.registerClient(Event::Ajouter,std::bind(&Liste::OnNotification,liste1));
			Obj1.registerClient(Event::Ajouter,std::bind(&Liste::OnNotification,liste2));
			assert(Obj1.getClientCount(Event::Ajouter) == 2);

			Obj1.registerClient(Event::Modifier,std::bind(&Liste::OnNotification,liste1));
			assert(Obj1.getClientCount(Event::Modifier) == 1);

			Obj2.registerClient(Event::Ajouter,std::bind(&Liste::OnNotificationEvent,liste1,Event::Ajouter));
			Obj2.registerClient(Event::Modifier,std::bind(&Liste::OnNotification,liste1));
			Obj2.registerClient(Event::Modifier,std::bind(&Liste::OnNotification,liste2));
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

		TEST_METHOD(DObjectTest2)
		{
			using namespace Outils;

			class Liste
			{
			public:
				typedef std::shared_ptr<Liste> Ptr;

			public:
				void OnNotification() { trace(_T("   ***  Liste : OnNotification \r\n")); }
			};

			typedef NotificationClientRegistry Objet;
			typedef std::shared_ptr<Objet> ObjetPtr;

			// Création des parents
			Liste::Ptr liste1(new Liste());	// Observateur (Liste)
			Liste::Ptr liste2(new Liste());	// Observateur (Liste)

			// Création des enfants
			ObjetPtr Obj1(new Objet()); // Observable
			ObjetPtr Obj2(new Objet());

			Obj1->registerClient(std::bind(&Liste::OnNotification,liste1));
			Obj1->registerClient(std::bind(&Liste::OnNotification,liste2));
			assert(Obj1->getClientCount() == 2);
		}

		// Tests de base relation Owner Child : CDObjBase
		TEST_METHOD(DObjectTest3)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("PARENT");
			CDObjTest* t2 = new CDObjTest(2);	t2->SetString("ENFANT 1");
			CDObjTest* t3 = new CDObjTest(3);	t3->SetString("ENFANT 2");

			t2->AddOwner(t1);
			t1->AddChild(t2);
			t1->AddChild(t3);

			assert(t2->GetOwnerCount()==1);
			assert(t1->GetChildCount()==2);

			assert(t1->IsOwner(t2)==true); //oui
			assert(t2->IsChild(t1)==true); //oui

			assert(t2->HasOwner(t1)==true); //oui
			assert(t1->HasChild(t2)==true); //oui

			assert(t1->HasChild(t2)==true); //oui
			assert(t2->HasChild(t1)==false); //non
			assert(t2->HasChild(t3)==false); //non

			CDObjTest* p1 = (CDObjTest*)t2->GetOwner(0);
			assert(p1 == t1);
			CDObjTest* p2 = (CDObjTest*)t1->GetChild(0);
			assert(p2 == t2);
			CDObjTest* p3 = (CDObjTest*)t1->GetChild(1);
			assert(p3 != t2);

			t1->RemoveChild(t3);

			delete t1;
			delete t2;
			delete t3;
		}

		// Tests gestion des évènements entre Owner et Child : CDObjBase
		TEST_METHOD(DObjectTest4)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("PARENT");		t1->SetInitaliser(true);
			CDObjTest* t4 = new CDObjTest(4);	t4->SetString("PARENT 2");		t4->SetInitaliser(true);
			CDObjTest* t2 = new CDObjTest(2);	t2->SetString("ENFANT 1");		t2->SetInitaliser(true);
			CDObjTest* t3 = new CDObjTest(3);	t3->SetString("ENFANT 2");		t3->SetInitaliser(true);

			t2->AddOwner(t1);
			t1->AddChild(t3);
			t3->AddOwner(t4);
			assert(t3->GetOwnerCount()==2);

			t3->notifyClient(DObjEvent::ObjetModifierEvent);
			assert(t1->EstModifier()==false);
			assert(t1->SontEnfantsModifier()==true);
			assert(t4->SontEnfantsModifier()==true);

			t3->notifyClient(DObjEvent::ObjetPourSupprimerEvent);


			delete t1;
			delete t2;
			delete t3;
			delete t4;
		}

		// Tests gestion des évènements entre Owner et Child : CDObjBase
		TEST_METHOD(DObjectTest5)
		{
			CDObjTest* p1 = new CDObjTest(1);	p1->SetString("PARENT 1");		p1->SetInitaliser(true);
			CDObjTest* p2 = new CDObjTest(4);	p2->SetString("PARENT 2");		p2->SetInitaliser(true);
			CDObjTest* e1 = new CDObjTest(2);	e1->SetString("ENFANT 1");		e1->SetInitaliser(true);
			CDObjTest* e2 = new CDObjTest(3);	e2->SetString("ENFANT 2");		e2->SetInitaliser(true);

			e1->AddOwner(p1);
			e1->AddOwner(p2);
			e2->AddOwner(p1);
			e2->AddOwner(p2);

			e1->SetString("Enfant 1");
			assert(e1->EstModifier()==true);
			assert(p1->EstModifier()==false);
			assert(p2->EstModifier()==false);
			assert(p1->SontEnfantsModifier()==true);
			assert(p2->SontEnfantsModifier()==true);

			e2->SetPourSupprimer(true);
			assert(e2->EstModifier()==true);
			assert(p1->EstModifier()==false);
			assert(p2->EstModifier()==false);
			assert(p1->SontEnfantsModifier()==true);
			assert(p2->SontEnfantsModifier()==true);

			p1->SetPourSupprimer(true,true);
			assert(p1->EstPourSupprimer()==true);
			assert(e1->EstPourSupprimer()==true);


			delete p1;
			delete e1;
			delete e2;
			delete p2;
		}

		// Tests de base relation Owner Child : CDObjListe
		TEST_METHOD(DObjectTest6)
		{
			CDObjTestListe* t1 = new CDObjTestListe("PARENT");
			CDObjTestListe* t2 = new CDObjTestListe("ENFANT 1");
			CDObjTestListe* t3 = new CDObjTestListe("ENFANT 2");

			t2->AddOwner(t1);
			t1->AddChild(t2);
			t1->AddChild(t3);

			assert(t2->GetOwnerCount()==1);
			assert(t1->GetChildCount()==2);

			assert(t1->HasChild(t2)==true); //oui
			assert(t2->HasChild(t1)==false); //non
			assert(t2->HasChild(t3)==false); //non

			CDObjTestListe* p1 = (CDObjTestListe*)t2->GetOwner(0);
			assert(p1 == t1);
			CDObjTestListe* p2 = (CDObjTestListe*)t1->GetChild(0);
			assert(p2 == t2);
			CDObjTestListe* p3 = (CDObjTestListe*)t1->GetChild(1);
			assert(p3 != t2);

			t1->RemoveChild(t3);

			delete t1;
			delete t2;
			delete t3;
		}

		// Tests gestion des évènements entre Owner et Child : CDObjListe
		TEST_METHOD(DObjectTest7)
		{
			CDObjTestListe* t1 = new CDObjTestListe("PARENT");
			CDObjTestListe* t4 = new CDObjTestListe("PARENT 2");
			CDObjTestListe* t2 = new CDObjTestListe("ENFANT 1");
			CDObjTestListe* t3 = new CDObjTestListe("ENFANT 2");

			t2->AddOwner(t1);
			t1->AddChild(t3);
			t3->AddOwner(t4);
			assert(t3->GetOwnerCount()==2);

			t3->notifyClient(DObjEvent::ObjetModifierEvent);
			assert(t1->EstModifier()==false);
			assert(t1->SontEnfantsModifier()==true);
			assert(t4->SontEnfantsModifier()==true);

			t3->notifyClient(DObjEvent::ObjetPourSupprimerEvent);


			delete t1;
			delete t2;
			delete t3;
			delete t4;
		}

		// Tests gestion des évènements entre Owner et Child : CDObjListe
		TEST_METHOD(DObjectTest8)
		{
			CDObjTestListe* p1 = new CDObjTestListe("PARENT");
			CDObjTestListe* p2 = new CDObjTestListe("PARENT 2");
			CDObjTestListe* e1 = new CDObjTestListe("ENFANT 1");
			CDObjTestListe* e2 = new CDObjTestListe("ENFANT 2");

			e1->AddOwner(p1);
			e1->AddOwner(p2);
			e2->AddOwner(p1);
			e2->AddOwner(p2);

			e1->SetString1("Enfant 1");
			assert(e1->EstModifier()==true);
			assert(p1->EstModifier()==false);
			assert(p2->EstModifier()==false);
			assert(p1->SontEnfantsModifier()==true);
			assert(p2->SontEnfantsModifier()==true);

			e2->SetPourSupprimer(true);
			assert(e2->EstModifier()==true);
			assert(p1->EstModifier()==false);
			assert(p2->EstModifier()==false);
			assert(p1->SontEnfantsModifier()==true);
			assert(p2->SontEnfantsModifier()==true);

			p2->SetPourSupprimer(true,true);
			assert(p2->EstModifier()==true);
			assert(p2->SontEnfantsModifier()==true);
			assert(e1->EstModifier()==true);
			assert(e2->EstModifier()==true);
			assert(p2->EstPourSupprimer()==true);
			assert(e1->EstPourSupprimer()==true);
			assert(e2->EstPourSupprimer()==true);

			delete p1;
			delete e1;
			delete e2;
			delete p2;
		}

		// Tests gestion des évènements entre Owner et Child : CDObjBase et CDObjListe
		TEST_METHOD(DObjectTest9)
		{
			CDObjTestListe* p1 = new CDObjTestListe("PARENT");
			CDObjTestListe* e1 = new CDObjTestListe("ENFANT 1");
			CDObjTestListe* e2 = new CDObjTestListe("ENFANT 2");

			e1->AddOwner(p1);
			e2->AddOwner(p1);

			p1->SetPourSupprimer(true,true);
			assert(p1->EstModifier()==true);
			assert(p1->SontEnfantsModifier()==true);
			assert(e1->EstModifier()==true);
			assert(e2->EstModifier()==true);
			assert(p1->EstPourSupprimer()==true);
			assert(e1->EstPourSupprimer()==true);
			assert(e2->EstPourSupprimer()==true);

			delete p1;
			delete e1;
			delete e2;
		}

		// Tests gestion des évènements entre Owner et Child : CDObjListe et CDObjBase
		TEST_METHOD(DObjectTest10)
		{
			CDObjTestListe* p1 = new CDObjTestListe("PARENT 1");
			CDObjTestListe* p2 = new CDObjTestListe("PARENT 2");
			CDObjTest* e1 = new CDObjTest(2);	e1->SetString("ENFANT 1");		e1->SetInitaliser(true);
			CDObjTest* e2 = new CDObjTest(3);	e2->SetString("ENFANT 2");		e2->SetInitaliser(true);
			CDObjTest* e3 = new CDObjTest(3);	e3->SetString("ENFANT 3");		e3->SetInitaliser(true);

			p1->Add(e1);
			p1->Add(e2);

			p2->Add(e1);
			p2->Add(e3);

			assert(p1->EstModifier()==true);
			assert(p1->GetChildCount()==2);
			assert(p2->GetChildCount()==2);
			assert(e1->GetOwnerCount()==2);
			assert(e2->GetOwnerCount()==1);

			p1->SetPourSupprimer(true,true);
			assert(p1->EstModifier()==true);
			assert(p1->SontEnfantsModifier()==true);
			assert(e1->EstModifier()==true);
			assert(e2->EstModifier()==true);
			assert(p1->EstPourSupprimer()==true);
			assert(e1->EstPourSupprimer()==true);
			assert(e2->EstPourSupprimer()==true);

			e2 = p1->RemoveAt(1);	// doit faire un delete de e2
			e1 = p2->RemoveAt(0);	// Ne doit PAS faire de delete de e1
			e3 = p2->Remove(e3);	// doit faire un delete de e3

			assert(p1->GetChildCount()==1);
			assert(p2->GetChildCount()==0);
			assert(e1->GetOwnerCount()==1);
			assert(e2==nullptr);
			assert(e3==nullptr);

			assert(e1 == p2->Remove(e1));	// Ne doit PAS faire de delete de e1 car E& n'est plus dans p2

			e1->m_bAutoDeleteFromList = false;

			delete p1;
			delete p2;
			delete e1;
			delete e2;
			delete e3;
		}

		// Tests divers
		TEST_METHOD(DObjectTest11)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("test1");		t1->SetInitaliser(true);
			CDObjTest* t2 = new CDObjTest(2);	t2->SetString("test2");		t2->SetInitaliser(true);
			CDObjTest* t3 = new CDObjTest(3);	t3->SetString("test3");		t3->SetInitaliser(true);
			CDObjTest* t4 = new CDObjTest(4);	t4->SetString("test4");		t4->SetInitaliser(true);
			CDObjTest* t5 = new CDObjTest(5);	t5->SetString("test5");		t5->SetInitaliser(true);
			CDObjTest* t6 = new CDObjTest(6);	t6->SetString("test6");		t6->SetInitaliser(true);

			t1->SetPourSupprimer(false);
			t2->SetPourSupprimer(true);
			t2->SetPourSupprimer(false);
			assert(t1->EstPourSupprimer()==false);
			assert(t2->EstPourSupprimer()==false);
			assert(t1->EstModifier()==false);
			assert(t2->EstModifier()==true);

			CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
			pListe1->Reserve(5);
			pListe1->Add(t1);
			pListe1->Add(t2);

			assert(pListe1->EstModifier()==true);

			pListe1->Sauver();
			assert(pListe1->EstModifier()==false);


			t1->SetPourSupprimer(true);
			t1->SetPourSupprimer(true);
			t2->SetPourSupprimer(true);
			t1->SetPourSupprimer(false);
			t1->SetPourSupprimer(true);
			t1->SetPourSupprimer(false);

			CDObjTest* pt1 = pListe1->GetAt(0,ObjEtat::Valide);
			CDObjTest* pt2 = pListe1->GetAt(1,ObjEtat::Valide);

			CDObjTest* pf1 = pListe1->GetAt(0,ObjEtat::PourSupprimer);
			CDObjTest* pf2 = pListe1->GetAt(1,ObjEtat::PourSupprimer);

			CDObjTest* pi2 = pListe1->GetFromId(2);
			CDObjTest* pi4 = pListe1->GetFromId(4);

			CDObjTest* pui2 = pListe1->GetFromUUID(t2->GetLPGUID());
			CDObjTest* pui4 = pListe1->GetFromUUID(t4->GetLPGUID());

			CDObjTestListe liste2("liste2");
			liste2.Reserve(5);
			liste2.Add(t3);
			liste2.Add(t4);
			liste2.Add(t5);

			t3->SetModifier(true);

			t3 = (CDObjTest*)t3->Delete();
			t3 = liste2.GetFromId(3);
			assert(liste2.GetCount()==2);
			assert(t3 == nullptr);

			delete t4;
			assert(liste2.GetCount()==1);

			pListe1->Append(*pListe1);
			pListe1->Append(liste2);

			t4 = new CDObjTest(4);	t4->SetString("test4");		t4->SetInitaliser(true);

			pListe1->InsertAt(3,t4);
			pListe1->InsertAt(3,t5);
			pListe1->InsertAt(8,t6);

			CDObjTest* gp = new CDObjTest(99);	gp->SetString("Grand père");
			pListe1->AddOwner(gp);

			CDObjTestListe liste3("liste3");
			liste3.Add(t4);
			liste3.Copy(*pListe1);
			liste3.Remove(pt1);

			pListe1->SortById();

			delete pListe1;
			delete gp;
		}

		TEST_METHOD(DObjectTest12)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("test1");

			CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
			pListe1->Add(t1);

			CDObjTestListe* pListe2 = new CDObjTestListe("liste2");
			pListe2->Add(t1);

			pListe1->Verifier();
			pListe1->SetPourSupprimer(true,true);
			pListe1->SetPourSupprimer(false,true);

			delete t1;
			delete pListe1;
			delete pListe2;
		}

		// Tester la suppression d'un obj qui est dans plusieurs listes
		TEST_METHOD(DObjectTest13)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("test1");		//t1->SetAcquis(true);

			CDObjTestListe* pListe1 = new CDObjTestListe("liste1");
			pListe1->Add(t1);

			CDObjTestListe* pListe2 = new CDObjTestListe("liste2");
			pListe2->Add(t1);

			pListe1->SetPourSupprimer(true,true);
			if(pListe1->Supprimer())
				pListe1 = nullptr;

			//assert(pListe1->GetCount() == 0);
			assert(pListe2->GetCount() == 0);

			delete pListe1;
			delete pListe2;
		}

		// Tester la sauvegarde d'un obj qui est dans plusieurs listes
		TEST_METHOD(DObjectTest14)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("test1");
			CDObjTest* t2 = new CDObjTest(2);	t2->SetString("test2");
			CDObjTest* t3 = new CDObjTest(3);	t3->SetString("test3");

			t2->SetAcquis();
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

		TEST_METHOD(DObjectTest15)
		{
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");

			auto pObjListe1 = dynamic_cast<CDObjListe<CDObjTest>*>(pListe1);
			assert(pObjListe1);

			CDObjListe<>* pObjListe2 = dynamic_cast<CDObjListe<>*>(pListe1);
			assert(pObjListe2 == NULL);

			delete pListe1;
		}

		TEST_METHOD(DObjectTest16)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Parent");		t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(2);	t2->SetString("(t2) Enfant 1");	t2->SetAcquis(true);

			t2->AddOwner(t1);

			delete t1;
			delete t2;
		}

		TEST_METHOD(DObjectTest17)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Parent");		t1->SetAcquis(true);
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");

			pListe1->AddOwner(t1);

			delete t1;
			delete pListe1;
		}

		TEST_METHOD(DObjectTest18)
		{
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1 Parent");
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Enfant");		t1->SetAcquis(true);

			t1->AddOwner(pListe1);

			delete pListe1;
			delete t1;
		}

		TEST_METHOD(DObjectTest19)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Parent");		t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(2);	t2->SetString("(t2) Enfant 1");	t2->SetAcquis(true);

			// 1er test
			{
				t2->AddOwner(t1);
				CDObjTest* P1 = (CDObjTest*)t2->GetOwner();
				assert(P1 == t1);

				// Lorsqu'un enfant est modifié, alors le parent doit en être avertis
				t2->SetString("(t2) Enfant 1 de Parent");

				assert(t2->EstModifier() == true);
				assert(t1->EstModifier() == false);
				assert(t1->SontEnfantsModifier() == true);
			}
			t1->Sauver();
			t2->Sauver();


			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");
			CDObjTest* t3 = new CDObjTest(3);	t3->SetString("Enfant 3");		t3->SetAcquis(true);

			// 2eme test
			{
				pListe1->AddOwner(t1);
				CDObjTest* P1 = (CDObjTest*)pListe1->GetOwner();
				assert(P1 == t1);

				//
				pListe1->Add(t3);
				auto PL1 = (CDObjTestListe*)t3->GetOwner();
				auto PL2 = t3->GetOwner();
				assert(PL1 == pListe1);

				assert(pListe1->EstModifier() == true);
				assert(t1->EstModifier() == false);
				assert(t1->SontEnfantsModifier() == true);

				// Lorsqu'un enfant est modifié, alors le parent doit en être avertis
				t3->SetString("Enfant 1 de Liste 1");

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

		TEST_METHOD(DObjectTest20)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("Parent");		t1->SetAcquis(true);
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");

			pListe1->AddOwner(t1);

			delete pListe1;
			delete t1;
		}

		TEST_METHOD(DObjectTest21)
		{
			CDObjTest* gp = new CDObjTest(99);	gp->SetString("Grand père");	gp->SetAcquis(true);
			CDObjTestListe* pListe = new CDObjTestListe("Liste");
			CDObjTest* e1 = new CDObjTest(3);	e1->SetString("Enfant 1");		e1->SetAcquis(true);
			CDObjTest* e2 = new CDObjTest(3);	e2->SetString("Enfant 2");		e2->SetAcquis(true);

			pListe->AddOwner(gp);
			pListe->Add(e1);
			pListe->Add(e2);

			assert(gp->EstModifier() == false);
			assert(gp->SontEnfantsModifier() == true);
			assert(pListe->EstModifier() == true);

			delete gp;
			delete pListe;
		}

		TEST_METHOD(DObjectTest22)
		{
			CDObjTest* parent = new CDObjTest(1);	parent->SetString("Parent");
			CDObjTest* enfant = new CDObjTest(2);	enfant->SetString("Enfant");

			parent->GetPointeurListe1()->Add(enfant);
			enfant->AddOwner(parent);


			delete enfant;
			delete parent;
		}

		TEST_METHOD(DObjectTest23)
		{
			CDObjTest* parent = new CDObjTest(1);	parent->SetString("Parent");
			CDObjTest* enfant1 = new CDObjTest(2);	enfant1->SetString("Enfant 1");
			CDObjTest* enfant2 = new CDObjTest(2);	enfant2->SetString("Enfant 2");
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1");
			CDObjTestListe* pListe2 = new CDObjTestListe("Liste 2");

			// Cas 1
			enfant1->AddOwner(parent);
			enfant1->SetPourSupprimer(true);
			if(enfant1->Supprimer())
				enfant1 = nullptr;

			// Cas 2
			pListe1->Add(enfant2);
			pListe1->AddOwner(parent);
			pListe1->SetPourSupprimer(true);
			pListe1->Supprimer();
			delete pListe1;
			pListe1 = nullptr;
			enfant2 = nullptr;

			// Cas 3
			enfant1 = new CDObjTest(2);	enfant1->SetString("Enfant 1");
			pListe1 = new CDObjTestListe("Liste Parent");

			enfant1->AddOwner(pListe1);
			enfant1->SetPourSupprimer(true);
			if(enfant1->Supprimer())
				enfant1 = nullptr;

			// Cas 4
			delete pListe1; pListe1 = new CDObjTestListe("Parent");
			delete pListe2; pListe2 = new CDObjTestListe("Enfant");

			pListe2->AddOwner(pListe1);
			pListe2->SetPourSupprimer(true);
			pListe2->Supprimer();
			delete pListe2;
			pListe2 = nullptr;

			// Cas 5
			delete parent; parent = new CDObjTest(1);	parent->SetString("Parent");
			delete pListe1; pListe1 = new CDObjTestListe("Liste Parent");
			delete enfant1; enfant1 = new CDObjTest(2);	enfant1->SetString("Enfant 1");

			enfant1->AddOwner(parent);
			enfant1->AddOwner(pListe1);
			enfant1->SetPourSupprimer(true);
			if(enfant1->Supprimer())
				enfant1 = nullptr;

			delete parent; parent = nullptr;
			delete enfant1; enfant1 = nullptr;
			delete enfant2; enfant2 = nullptr;
			delete pListe1; pListe1 = nullptr;
			delete pListe2; pListe2 = nullptr;
		}

		TEST_METHOD(DObjectTest24)
		{
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1 Parent");
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Enfant");		t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(1);	t2->SetString("(t2) Enfant");		t2->SetAcquis(true);

			pListe1->Add(t1);
			pListe1->Add(t2);

			assert(pListe1->GetCount()==2);
			assert(pListe1->GetCount(ObjEtat::Valide)==2);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==0);

			t2->SetPourSupprimer(true);
			assert(pListe1->GetCount()==2);
			assert(pListe1->GetCount(ObjEtat::Valide)==1);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==1);

			pListe1->Sauver();
			assert(pListe1->GetCount()==1);
			assert(pListe1->GetCount(ObjEtat::Valide)==1);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==0);

			delete pListe1;
		}

		TEST_METHOD(DObjectTest25)
		{
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1 Parent");
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Enfant");		t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(1);	t2->SetString("DoNotDelete");		t2->SetAcquis(true);

			pListe1->Add(t1);
			pListe1->Add(t2);

			t2->SetPourSupprimer(true);

			pListe1->Sauver();
			assert(pListe1->GetCount()==2);
			assert(pListe1->GetCount(ObjEtat::Valide)==1);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==1);

			delete pListe1;
		}

		TEST_METHOD(DObjectTest26)
		{
			CDObjTestListe* pListe1 = new CDObjTestListe("Liste 1 Parent");
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("(t1) Enfant");		t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(1);	t2->SetString("DoNotDelete");		t2->SetAcquis(true);

			pListe1->Add(t1);
			pListe1->Add(t2);

			t1->SetPourSupprimer(true);
			t2->SetPourSupprimer(true);

			bool bSauv = pListe1->Sauver();
			assert(bSauv==false);
			assert(pListe1->GetCount()==2);
			assert(pListe1->GetCount(ObjEtat::Valide)==0);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==2);

			delete pListe1;
		}

		TEST_METHOD(DObjectTest27)
		{
			CDObjTest* p1 = new CDObjTest(1);	p1->SetString("(p1) Parent");		p1->SetAcquis(true);
			CDObjTest* e1 = p1->GetPointeur1(); e1->SetString("(e1) Enfant");		e1->SetAcquis(true);
			CDObjTest* e2 = p1->GetPointeur2(); e2->SetString("DoNotDelete");		e2->SetAcquis(true);

			e1->SetPourSupprimer(true);
			e2->SetPourSupprimer(true);
			bool bSav = p1->Sauver();

			assert(bSav==false);
			assert(p1->GetChildCount()==2);
			assert(e1->EstPourSupprimer()==true);
			assert(e2->EstPourSupprimer()==true);

			e2->SetString("(e2) Enfant");
			bSav = p1->Sauver();
			assert(bSav==true);
			assert(p1->GetChildCount()==0);

			delete p1;
		}

		TEST_METHOD(DObjectTest28)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("Parent");			t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(1);	t2->SetString("(t2) Enfant");		t2->SetAcquis(true);
			CDObjTest* t3 = new CDObjTest(1);	t3->SetString("(t3) Enfant");		t3->SetAcquis(true);
			CDObjTest* t4 = new CDObjTest(1);	t4->SetString("DoNotDelete");		t4->SetAcquis(true);

			CDObjTestListe* pListe1 = t1->GetPointeurListe1();
			pListe1->Add(t2);
			CDObjTestListe* pListe2 = t1->GetPointeurListe2();
			pListe2->Add(t3);
			pListe2->Add(t4);

			t2->SetPourSupprimer(true);
			assert(pListe1->GetCount()==1);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==1);

			t3->SetPourSupprimer(true);
			t4->SetPourSupprimer(true);
			assert(pListe2->GetCount()==2);
			assert(pListe2->GetCount(ObjEtat::PourSupprimer)==2);

			bool bSauv = t1->Sauver();
			assert(bSauv==false);
			assert(pListe1->GetCount()==1);
			assert(pListe1->GetCount(ObjEtat::PourSupprimer)==1);
			assert(pListe2->GetCount()==2);
			assert(pListe2->GetCount(ObjEtat::PourSupprimer)==2);

			delete t1;
		}

		TEST_METHOD(DObjectTest29)
		{
			CDObjTest* t1 = new CDObjTest(1);	t1->SetString("Parent");			t1->SetAcquis(true);
			CDObjTest* t2 = new CDObjTest(1);	t2->SetString("(t2) Enfant");		t2->SetAcquis(true);
			t2->AddOwner(t1);

			Assert::IsTrue(t2->GetOwnerCount()==1);
			Assert::IsTrue(t1->GetChildCount()==1);

			CDObjTest c1 = CDObjTest(*t1);
			Assert::IsTrue(t1->GetChildCount()==1);
			Assert::IsTrue(c1.GetChildCount()==1);
			Assert::IsTrue(t2->GetOwnerCount()==2);
			Assert::IsTrue(c1.GetId()==t1->GetId());
			Assert::IsTrue(c1.GetLPGUID()->Data1==t1->GetLPGUID()->Data1);
			Assert::IsTrue(c1.GetLPGUID()->Data2==t1->GetLPGUID()->Data2);
			Assert::IsTrue(c1.GetLPGUID()->Data3==t1->GetLPGUID()->Data3);
			// Pas de tests sur Data4 car unsigned char
			//Assert::IsTrue(c1.GetLPGUID()->Data4==t1->GetLPGUID()->Data4);

			CDObjTest c2 = CDObjTest(*t2);
			Assert::IsTrue(c2.GetOwnerCount()==2);
			Assert::IsTrue(c1.GetId()==t1->GetId());
			Assert::IsTrue(c2.GetId()==t2->GetId());
			Assert::IsTrue(c2.GetLPGUID()->Data1==t2->GetLPGUID()->Data1);
			Assert::IsTrue(c2.GetLPGUID()->Data2==t2->GetLPGUID()->Data2);
			Assert::IsTrue(c2.GetLPGUID()->Data3==t2->GetLPGUID()->Data3);
			// Pas de tests sur Data4 car unsigned char
			//Assert::IsTrue(c2.GetLPGUID()->Data4==t2->GetLPGUID()->Data4);

			delete t1;
			delete t2;
		}

		TEST_METHOD(DObjectTest30)
		{
			CDObjTest* p1 = new CDObjTest(1);	p1->SetString("Parent");			p1->SetAcquis(true);
			CDObjTest* e1 = new CDObjTest(1);	e1->SetString("(e1) Enfant");		e1->SetAcquis(true);

			p1->GetPointeurListe1()->Add(e1);

			p1->SetPourSupprimer(true);
			if(p1->Supprimer())
				p1 = nullptr;

			delete p1;
		}
	};
}