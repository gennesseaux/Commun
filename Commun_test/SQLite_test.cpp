#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include <SQLite/SQLiteSource.h>


namespace Commun_test
{
	TEST_CLASS(SQLite_test)
	{
	public:

		TEST_METHOD(SQLiteTest1)
		{
			try
			{
				SQLite::Database   db("transaction.db",SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

				db.exec("DROP TABLE IF EXISTS test");

				// Begin transaction
				SQLite::Transaction transaction(db);

				db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT)");

				int nb = db.exec("INSERT INTO test (value) VALUES ('test')");
				std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

				nb = db.exec("INSERT INTO test (value) VALUES (\"test2\")");
				std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

				nb = db.exec("INSERT INTO test (value) VALUES (\"test3\")");
				std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

				// Commit transaction
				transaction.commit();
			}
			catch(std::exception& e)
			{
				std::cout << "exception: " << e.what() << std::endl;
			}
		}

		TEST_METHOD(SQLiteSource1)
		{
			// Création d'une nouvelle base
			SQLite::CSQLiteSource sqlite;
			sqlite.New();

			// Début  de la transaction
			SQLite::AutoTransaction trans(sqlite.GetTransaction());

			//
			sqlite.GetDataBase()->exec("DROP TABLE IF EXISTS test");
			sqlite.GetDataBase()->exec("CREATE TABLE test (id INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT)");

			// Fin de la transaction
			trans.rollback();

			// fermeture de la base
			sqlite.Close();
		}

		TEST_METHOD(SQLiteSource2)
		{
			// Création d'une nouvelle base
			SQLite::CSQLiteSource sqlite;
			sqlite.Open();
			sqlite.Close();
		}

	};
}