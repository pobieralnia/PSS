// ---------------------------------------------------------------------------------
// Filename:	ConfigObject.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config
// ---------------------------------------------------------------------------------

#include "stdafx.h"

#include <string>
#include <sstream>
#include <tuple>
#include <map>
#include <iostream>

#include "Config.h"
#include "ConfigObject.h"

ConfigObject::ConfigObject(struct someStruct * state)
{
	m_vector_objects_ptr = &state->m_vector_objects;
	this->clear();
}

/**
 * Init - filled main variables with default data
 *
 * @return		void
 */
void ConfigObject::clear(void)
{
	this->m_other_parameters.clear();
	this->m_a_parameters.clear();
	this->m_b_parameters.clear();
}

/**
 * Clear config vector
 *
 * @return		void
 */
void ConfigObject::clear_all()
{
	this->clear();

	m_vector_objects_ptr->clear();
	m_vector_objects_ptr = NULL;
	delete m_vector_objects_ptr;
}

/**
 * Parse lines to load all main variables in config file
 *
 * @param		string line
 * @return		void
 */
void ConfigObject::parse_line(std::string line)
{
	// Clean values
	double m_tmp_parm_val = 0;
	int m_tmp_parm_key = 0;
	int m_tmp_da = 0;
	int m_tmp_db = 0;
	double m_tmp_k = 0;

	// Check what kind of variables are in the line
	if(ConfigParser::regex_a_parameter(line, &m_tmp_parm_val, &m_tmp_parm_key))
	{
		this->m_a_parameters[m_tmp_parm_key] = m_tmp_parm_val;
	}
	else if(ConfigParser::regex_b_parameter(line, &m_tmp_parm_val, &m_tmp_parm_key))
	{
		this->m_b_parameters[m_tmp_parm_key] = m_tmp_parm_val; // number
	}
	else if(ConfigParser::regex_stationary(line))
	{
		this->m_other_parameters["stationary"] = 1;
	}
	else if(ConfigParser::regex_k(line, &m_tmp_k))
	{
		this->m_other_parameters["k"] = m_tmp_k;
	}
	else if(ConfigParser::regex_da(line, &m_tmp_da))
	{
		this->m_other_parameters["da"] = m_tmp_da;
	}
	else if(ConfigParser::regex_db(line, &m_tmp_db))
	{
		this->m_other_parameters["db"] = m_tmp_db;
	}
	else if(ConfigParser::regex_end_of_config(line))
	{
		// initialize a tuple and put in vector of configs
		m_vector_objects_ptr->push_back(make_tuple(this->m_b_parameters, this->m_a_parameters, this->m_other_parameters));

		// clear main variables
		this->clear();
	}
}

/**
 * Get the string of all configs
 *
 * @param		int i - flag
 * @return		string - size of configs
 */
std::string ConfigObject::get_size(int i)
{
	std::stringstream ss; //create a stringstream
	ss << m_vector_objects_ptr->size();
	return ss.str(); //return a string with the contents of the stream
}