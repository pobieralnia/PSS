// ---------------------------------------------------------------------------------
// Filename:	dbWrapper.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		dbWrapper
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include "dbWrapper.h"

/**
 * Constructor
 * - we set NULL to all main variables for mysql
 * 
 * @return	void
 */
DB_wrapper::DB_wrapper(void)
{
	this->m_conn = NULL;
	this->m_result = NULL;
	this->m_row = NULL;
	this->m_field = NULL;
}

/**
 * Method Disconnet
 * - we try to close mysql connection if there is such as. Next we free mysql result.
 *
 * @return	void
 */
void DB_wrapper::disconnet() const
{
	// Check if connection is open if so than close it
	if(this->m_conn)
	{
		mysql_close(this->m_conn);
	}

	//release result data
	this->free(); 
}

/**
 * Method Free
 * - free mysql resutl if it is needed.
 *
 * @return	void
 */
void DB_wrapper::free(void) const
{
	 // Check if there is a result if so we free it
	 if (this->m_result)
	 {
		mysql_free_result(this->m_result);
	 }
}

/**
 * Method Free
 * - free mysql resutl if it is needed. If connection exists we return bool.
 *
 * @param	bool check - if we want to check or not
 * @return	bool - if connection exists we return True else False
 */
bool DB_wrapper::free(bool check)
{
	 // Check if there is a result if so we free it
	 if (this->m_result)
	 {
		mysql_free_result(this->m_result);
		return true;
	 }

	 return false;
}

/**
 * Fetch all rows in query
 *
 * @return		pointer array
 */
MYSQL_RES * DB_wrapper::get_result(const char * c)
{
	if (this->query(c))
	{
		this->m_result = mysql_store_result(this->m_conn);

		if (this->m_result)
		{
			m_number_fields = mysql_num_fields(this->m_result);
		}
	}

	return this->m_result;
}

/**
 * Execute sql query
 *
 * @param		char
 * @return		bool
 */
bool DB_wrapper::query(const char * c)
{
	// query the database
	if(mysql_query(this->m_conn,c))
	{
		return false;
	}
	else
		return true;

}

/**
 * Row the query result
 *
 * @return		mixed ? string : NULL
 */
MYSQL_ROW DB_wrapper::fetch_row()
{
	this->m_row_counter = 0; // init counter for rows
	return this->m_result ? (this->m_row = mysql_fetch_row(this->m_result)) : NULL;
}


/**
 * Get value of current row
 *
 * @param		int
 * @return		mixed ? string : NULL
 */
const char * DB_wrapper::get_value(int x)
{ 
	if (this->m_result && this->m_row)
	{
		return this->m_row[x] ? this->m_row[x] : "";
	}

	return NULL;
}

/**
 * Get default value
 *
 * @return		mixed ? string : NULL
 */
const char * DB_wrapper::get_value()
{
	return this->get_value(this->m_row_counter++);
}

/**
 * Method num_fields
 * 
 * @return	int - number of fields for result
 */
int DB_wrapper::num_fields()
{
	if (this->m_result)
	{
		return m_number_fields;
	}
	else
		return 0;
}

/**
 * Init mysql connection
 * - connect to database using define variables
 *
 * @return bool
 */
int DB_wrapper::init(void)
{
	 if(this->m_conn) //already connected to another database
		this->disconnet(); //disconnect from that one

	 //initilize the socket
	 this->m_conn = mysql_init(0);

	 //something went wrong with the socket
	 if (!this->m_conn)
	 {
		 printf("Error");
	 }

	 //try connecting to the database  
	 if(!mysql_real_connect(this->m_conn, DB_HOST, DB_USERNAME, DB_PASSWORD, DB_DATABASE, 0, NULL, 0))
	 {
		printf("Error connect");
	 }

	 //successfully connected to the database    
	 return true;  
}

/**
 * Destructor
 * - free the result and close connection if exists
 * 
 * @return	void
 */
DB_wrapper::~DB_wrapper()
{
	this->disconnet();
}

// end of file dbWrapper.cpp