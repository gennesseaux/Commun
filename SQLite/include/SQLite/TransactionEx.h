
#pragma once

#include <SQLiteCpp/Transaction.h>

namespace SQLite
{
	// Forward declaration
	class Database;

	/**
	* @brief RAII encapsulation of a SQLite Transaction.
	*
	* A Transaction is a way to group multiple SQL statements into an atomic secured operation;
	* either it succeeds, with all the changes committed to the database file,
	* or if it fails, all the changes are rolled back to the initial state.
	*
	* Resource Acquisition Is Initialization (RAII) means that the Transaction
	* begins in the constructor and is rollbacked in the destructor, so that there is
	* no need to worry about memory management or the validity of the underlying SQLite Connection.
	*
	* This method also offers big performances improvements compared to individually executed statements.
	*
	* Thread-safety: a Transaction object shall not be shared by multiple threads, because :
	* 1) in the SQLite "Thread Safe" mode, "SQLite can be safely used by multiple threads
	*    provided that no single database connection is used simultaneously in two or more threads."
	* 2) the SQLite "Serialized" mode is not supported by SQLiteC++,
	*    because of the way it shares the underling SQLite precompiled statement
	*    in a custom shared pointer (See the inner class "Statement::Ptr").
	*/
	class TransactionEx
	{
	public:
		/**
		 * @brief Begins the SQLite TransactionEx
		 *
		 * @param[in] aDatabase the SQLite Database Connection
		 *
		 * Exception is thrown in case of error, then the TransactionEx is NOT initiated.
		 */
		explicit TransactionEx(Database& aDatabase);

		/**
		 * @brief Safely rollback the TransactionEx if it has not been committed.
		 */
		virtual ~TransactionEx() noexcept; // nothrow

		/**
		* @brief Begin the Transaction.
		*/
		void begin();

		/**
		* @brief Commit the Transaction.
		*/
		void commit();

		/**
		* @brief Rollback the Transaction.
		*/
		void rollback();

		/**
		* @brief .
		*/
		bool IsTransactionActive() const { return m_bTransaction; };

	private:
		// TransactionEx must be non-copyable
		TransactionEx(const TransactionEx&);
		TransactionEx& operator=(const TransactionEx&);

	private:
		Database&   mDatabase;			//!< Reference to the SQLite Database Connection
		bool        mbCommited;			//!< True when commit has been called
		bool		m_bTransaction;
	};


}  // namespace SQLite
