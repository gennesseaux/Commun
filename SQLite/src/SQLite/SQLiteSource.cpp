
// Inclusions
#include "SQLite/SQLiteSource.h"

// Inclusions
#include <stdio.h>
#include <fstream>

//
using namespace SQLite;

//
#define BUFSIZE 32767
static std::string m_sTempFilename;

// Temp folder
std::string tempFolder()
{
	DWORD dwBufSize = BUFSIZE;
	TCHAR lpPathBuffer[BUFSIZE];

	// Get the temp path.
	GetTempPath(dwBufSize,lpPathBuffer);

	std::wstring wpath(&lpPathBuffer[0]); //convert to wstring
	std::string path(wpath.begin(), wpath.end()); //and convert to string.

	return path;
}

// Temp file
std::string tempFile()
{
	DWORD dwBufSize = BUFSIZE;
	TCHAR lpPathBuffer[BUFSIZE];
	TCHAR szTempName[BUFSIZE];

	// Get the temp path.
	GetTempPath(dwBufSize,lpPathBuffer);

	// Create a temporary file.
	GetTempFileName(lpPathBuffer, // directory for tmp files
					L"NEW", // temp file name prefix
					0, // create unique name
					szTempName); // buffer for the name

	std::wstring wfile(&szTempName[0]); //convert to wstring
	std::string file(wfile.begin(), wfile.end()); //and convert to string.

	return file;
}




// Constructeur
CSQLiteSource::CSQLiteSource() : m_pDatabase(nullptr), m_pTransaction(nullptr)
{
}

// Destructeur
CSQLiteSource::~CSQLiteSource()
{
	delete m_pTransaction;	m_pTransaction = nullptr;
	delete m_pDatabase;		m_pDatabase = nullptr;

	if(!m_sTempFilename.empty() && std::ifstream(m_sTempFilename))
		std::remove(m_sTempFilename.c_str());
}

// Retourne le pointeur sur la base de donnée en cours d'utilisation
SQLite::Database* CSQLiteSource::GetDataBase()
{
	return m_pDatabase ? m_pDatabase : New();
}

// Transactions
SQLite::TransactionEx* CSQLiteSource::GetTransaction()
{
	return m_pTransaction;
}

// Création d'une base de données par défaut
SQLite::Database* CSQLiteSource::New()
{
	// Chemin de la base de données par défaut
	if(m_sDataBaseFilename.empty())
	{
		m_sTempFilename = tempFile();
		m_sDataBaseFilename = m_sTempFilename;
	}

	// Suppression du pointeur vers la base de donnée
	if (m_pDatabase)
	{
		delete m_pTransaction;	m_pTransaction = nullptr;
		delete m_pDatabase;		m_pDatabase = nullptr;
	}

	// Suppression de la base par défaut si elle existe
	if(std::ifstream(m_sDataBaseFilename))
		std::remove(m_sDataBaseFilename.c_str());

	// Ouverture de la base de donnée par défaut
	return Open(m_sDataBaseFilename);
}

// Ouverture d'une base de données
SQLite::Database* CSQLiteSource::Open(std::string sFileName)
{
	//
	if(sFileName.empty()) return New();

	// Chemin de la base de données
	m_sDataBaseFilename = sFileName;

	// Initialisation de la base de données
	if (m_pDatabase == nullptr)
	{
		try
		{
			m_pDatabase = new SQLite::Database(m_sDataBaseFilename, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		}
		catch (...)
		{
			return nullptr;
		}
	}

	// Si la base de données ne correspond pas au nom alors on ouvre la base de données demandée
	if (m_pDatabase && m_pDatabase->getFilename().compare(m_sDataBaseFilename)!=0)
	{
		delete m_pTransaction;	m_pTransaction = nullptr;
		delete m_pDatabase;		m_pDatabase = nullptr;

		return Open(sFileName);
	}

	// Initialisation des transactions
	delete m_pTransaction; m_pTransaction = new TransactionEx(*m_pDatabase);

	//
	Init();

	return m_pDatabase;
}

Database* CSQLiteSource::Open()
{
	return Open(m_sDataBaseFilename);
}

bool CSQLiteSource::Close()
{
	if(m_pTransaction && m_pTransaction->IsTransactionActive())
		return false;

	if(m_pDatabase)
	{
		delete m_pTransaction;	m_pTransaction = nullptr;
		delete m_pDatabase;		m_pDatabase = nullptr;
	}

	return true;
}

// déplace la base de données
SQLite::Database* CSQLiteSource::SaveAs(std::string sFileName)
{
	// Chemin de la base de données 
	if (m_sDataBaseFilename.compare(sFileName) == 0)
		return m_pDatabase;

	// Initialisation de la base de données par défaut
	if (m_pDatabase == nullptr)
		return nullptr;

	// Suppression du pointeur sur la base opur éviter toute violation d'accès
	delete m_pTransaction;	m_pTransaction = nullptr;
	delete m_pDatabase;		m_pDatabase = nullptr;

	// Suppression de la base si elle existe
	if(std::ifstream(sFileName))
		std::remove(sFileName.c_str());

	// Déplacement du fichier
	std::ifstream ifs(m_sDataBaseFilename,std::ios::in | std::ios::binary);
	std::ofstream ofs(sFileName,std::ios::out | std::ios::binary);
	ofs << ifs.rdbuf();

	// Ouverture de la base déplacée
	return Open(sFileName);
}








// Constructeur
AutoTransaction::AutoTransaction(CSQLiteSource* pSqlite)
{
	_pSqlite = pSqlite;

	if(_pSqlite->GetTransaction()->IsTransactionActive())
		_bAutoTransaction = false;
	if(_bAutoTransaction)
		_pSqlite->GetTransaction()->begin();
}

// Destructeur
AutoTransaction::~AutoTransaction()
{
	if(_bAutoTransaction && _pSqlite->GetTransaction()->IsTransactionActive())
		rollback();

	_pSqlite = nullptr;
}

// Commit
void AutoTransaction::commit()
{
	if (_bAutoTransaction)
	{
		_pSqlite->GetTransaction()->commit();
		_bAutoTransaction = false;
	}
}

// Rollback
void AutoTransaction::rollback()
{
	if (_bAutoTransaction)
	{
		_pSqlite->GetTransaction()->rollback();
		_bAutoTransaction = false;
	}
}
