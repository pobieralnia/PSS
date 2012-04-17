// ---------------------------------------------------------------------------------
// Filename:	dbWrapper.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		dbWrapper
// ---------------------------------------------------------------------------------

#ifndef _DBWRAPPER_H_
#define _DBWRAPPER_H_

#include <Windows.h>	// For mysql.h to run on Windows
#ifdef __LCC__ 
#include <winsock.h>	// For windows if __LCC__ is defined (default - winsock.h is included in mysql.h)
#endif 
#include <mysql.h>
#include <string>
#include <iostream>
#include <vector>

#define DB_HOST "localhost"
#define DB_USERNAME "root"
#define DB_PASSWORD ""
#define DB_DATABASE "escard"

/*
 * Filename dbWrapper.h
 * Header for mysql wrapper class
 * 
 * @author	Tomasz L
 * @package dbWrapper
 */
class DB_wrapper
{
	private:
		void disconnet() const;		// Method to disconnet mysql
		bool free(bool check);		// Free memory for current query with bool return

		// Mysql class
		MYSQL *m_conn;
		MYSQL_RES *m_result;
		MYSQL_ROW m_row;
		MYSQL_FIELD *m_field;

		// variables
		int m_number_fields;
		int unsigned m_row_counter;

	public:
		DB_wrapper(void);

		int init(void);		// Init connection
		void free(void) const;		// Free memory for current query
		int num_fields(void);		// Number of fields for the result
		bool query(const char * c);		// Query

		MYSQL_RES * get_result(const char * c);		// Sql query and fetch all records
		MYSQL_ROW fetch_row();		// Fetch row
		const char * get_value(int x);
		const char * get_value();

		~DB_wrapper();
};

#endif