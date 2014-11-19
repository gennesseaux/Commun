

// Inclusions
#include "SQLite/TransactionEx.h"

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Assertion.h>


namespace SQLite
{

	// Begins the SQLite TransactionEx
	TransactionEx::TransactionEx(Database& aDatabase)
		: mDatabase(aDatabase)
		, mbCommited(false)
		, m_bTransaction(false)
	{
	}

	// Safely rollback the TransactionEx if it has not been committed.
	TransactionEx::~TransactionEx() noexcept // nothrow
	{
		if (m_bTransaction && mbCommited == false)
		{
			try
			{
				mDatabase.exec("ROLLBACK");
				m_bTransaction = false;
			}
			catch (SQLite::Exception& e)
			{
				SQLITECPP_ASSERT(false, e.what());
			}
		}
	}

	// Begin the Transaction.
	void TransactionEx::begin()
	{
		try
		{
			mDatabase.exec("BEGIN");
			mbCommited = false;
			m_bTransaction = true;
		}
		catch (SQLite::Exception& e)
		{
			throw SQLite::Exception(e.what());
		}
	}

	// Commit the TransactionEx.
	void TransactionEx::commit()
	{
		if (m_bTransaction && mbCommited == false)
		{
			mDatabase.exec("COMMIT");
			mbCommited = true;
			m_bTransaction = false;
		}
		else
		{
			throw SQLite::Exception("Transaction already commited");
		}
	}

	// Rollback the Transaction.
	void TransactionEx::rollback()
	{
		if (m_bTransaction && mbCommited == false)
		{
			mDatabase.exec("ROLLBACK");
			mbCommited = true;
			m_bTransaction = false;
		}
		else
		{
			throw SQLite::Exception("Transaction already commited");
		}
	}

}  // namespace SQLite
