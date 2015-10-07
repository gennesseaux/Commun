
#pragma once

// Inclusions
#include <windows.h>
#include <assert.h>

// Inclusions STL
#include <string>
#include <sstream>
#include <memory>

// Inclusions
#include <Outils/StringTools.h>
#include <Outils/StreamSupport.h>
#include <Outils/VariantStream.h>

// Inclusions
#include <SQLiteCpp/Database.h>
#include <SQLite/TransactionEx.h>

namespace SQLite
{

	class CSQLiteSource
	{
	public:
		// Constructeur
		CSQLiteSource();
		// Destructeur
		~CSQLiteSource();


		// Retourne le pointeur sur la base de donn�e en cours d'utilisation
		SQLite::Database*			GetDataBase();
		// Transactions
		SQLite::TransactionEx*		GetTransaction();

		// Cr�ation d'une base de donn�es par d�faut
		SQLite::Database*			New(std::string sFileName = "");
		// Ouverture d'une base de donn�es
		SQLite::Database*			Open(std::string sFileName);
		// Ouverture de la base de donn�e active
		SQLite::Database*			Open();
		// d�place la base de donn�es
		SQLite::Database*			SaveAs(std::string sFileName);
		// Fermeture de la base de donn�e active
		bool						Close();

		//
		virtual void Init() {};

	public:
		//! Constructeur par copie
		CSQLiteSource(const CSQLiteSource&) = delete;
		CSQLiteSource(CSQLiteSource&&) = delete;
		//! Op�rateur =
		CSQLiteSource& operator = (const CSQLiteSource&) = delete;
		CSQLiteSource& CSQLiteSource::operator=(CSQLiteSource&&) = delete;

	private:
		std::string				m_sDataBaseFilename;
		SQLite::Database*		m_pDatabase;
		SQLite::TransactionEx*	m_pTransaction;
	};

	// Fonctions d'aide � la cr�ation de requ�te
	inline std::string ToQuery(std::string sString)
	{
		if(sString.length()==0)
			return "null";

		// "?", "?NNN", ":VVV", "@VVV" or "$VVV"
		if(StringTools::starts_with(sString,"?") || StringTools::starts_with(sString,":") || StringTools::starts_with(sString,"@") || StringTools::starts_with(sString,"$"))
			return sString;

		std::ostringstream toQuery;
		toQuery << "'" << sString << "'";
		return toQuery.str();
	}
	inline std::string ToQuery(unsigned long ul, unsigned long null = ULONG_MAX)
	{
		if(ul==null)
			return "null";
		return std::to_string(ul);
	}
	inline void ToBlob(_variant_t& value,BLOB& blob)
	{
		WriteVariantToBlob(value,blob);
	}
	inline void ToVariant(BLOB& blob,const VARTYPE vtSrc,_variant_t& value)
	{
		ReadVariantFromBlob(blob,value);
	}


	class AutoTransaction
	{
	public:
		// Constructeur
		AutoTransaction(SQLite::TransactionEx* pTransaction);
		// Destructeur
		~AutoTransaction();

		// Commit
		void commit();
		// Rollback
		void rollback();

	public:
		// Constructeur
		AutoTransaction() = delete;
		//! Constructeur par copie
		AutoTransaction(const AutoTransaction&) = delete;
		AutoTransaction(AutoTransaction&&) = delete;
		//! Op�rateur =
		AutoTransaction& operator = (const AutoTransaction&) = delete;
		AutoTransaction& AutoTransaction::operator=(AutoTransaction&&) = delete;

	private:
		SQLite::TransactionEx* _pTransaction = nullptr;
		bool _bAutoTransaction = true;
	};

	
	// D�but d'une transaction automatique
	#define __TRANSACTION_AUTO_DEBUT__(pTransaction) \
 		SQLite::AutoTransaction _Autotransaction(pTransaction);

	// fin d'une transaction automatique avec annulation de la transaction
	#define __TRANSACTION_AUTO_ANNULE__	\
 		_Autotransaction.rollback();

	// fin d'une transaction automatique avec validation de la transaction
	#define __TRANSACTION_AUTO_VALIDE__	\
 		_Autotransaction.commit();
}
