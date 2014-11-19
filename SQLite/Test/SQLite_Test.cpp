// SQLite_Test.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>

#pragma comment(lib,"SQLite.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		SQLite::Database   db("transaction.db", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

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
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}


	return 0;
}

