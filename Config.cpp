// ---------------------------------------------------------------------------------
// Filename:	Config.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config,ConfigParser
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include <string>
#include <tuple>
#include <sstream>
#include "Config.h"


/**
 * Init - filled main variables with default data
 *
 * @return		void
 */
void Config::clear(void)
{
	this->m_stationary = 0;
	this->m_a_parameters.clear();
	this->m_b_parameters.clear();
}

/**
 * Clear config vector
 *
 * @return		void
 */
void Config::clear_vector_config()
{
	this->clear();
	this->m_config_loaded = false;
	this->m_vector_configs.clear();
}

/**
 * Set new config - config have never been used, addtionaly main variables are cleared
 *
 * @return		void
 */
void Config::set_config(void)
{
	this->m_config_loaded = true;
}

/**
 * Parse lines to load all main variables in config file
 *
 * @param		string line
 * @return		void
 */
void Config::parse_file(std::string line)
{

	// check if not empty
	if(!line.empty())
	{
		// Clean values
		m_tmp_parm_val = 0;
		m_tmp_parm_key = 0;
		m_tmp_parm_object.clear();

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
			this->m_stationary = 1;
		}
		else if(ConfigParser::regex_object_name(line, m_tmp_parm_object))
		{
			this->m_object_name = m_tmp_parm_object;
		}
		else if(ConfigParser::regex_end_of_config(line))
		{
			 // initialize a tuple and put in vector of configs
			 m_vector_configs.push_back(make_tuple(this->m_object_name, this->m_b_parameters, this->m_a_parameters, this->m_stationary));

			 // clear main variables
			 this->clear();
		}
	}
}


/**
 * Get the string of all configs
 *
 * @param		int i - flag
 * @return		string - size of configs
 */
std::string Config::get_size_of_configs(int i)
{
	std::stringstream ss; //create a stringstream
	ss << m_vector_configs.size();
	return ss.str(); //return a string with the contents of the stream
}

/**
 * Get a or b parameters for current object
 *
 * @param		map parm - passed by reference
 * @param		int object
 * @param		int parameter - 1 for a parameters - 2 for b parameters
 * @return		void
 */
void Config::get_parameters(std::map<int, int> & parm, int object, int parameter)
{
	if(this->get_size_of_configs() > abs(object))
	{
		// todo - enum, albo rozbiæ to na dwie funkcje ?
		if(parameter == 1)
			parm = std::get<1>(this->m_vector_configs[abs(object)]);
		else	
			parm = std::get<2>(this->m_vector_configs[abs(object)]);
	}
	else
	{
		throw "Nie mo¿na pobraæ parametrów obiektu";
	}
}

/**
 * Check if current object is stationar
 *
 * @param		int object
 * @return		bool
 */
bool Config::check_object_stationarity(int object)
{
	if(this->get_size_of_configs() > abs(object))
	{
		return std::get<3>(this->m_vector_configs[abs(object)]) & 1;
	}
	else
	{
		throw "Nie mo¿na pobraæ parametru obiektu - domyœlnie -> false";
	}

	return false;
}

/**
 * Get object name
 *
 * @param		int object
 * @return		string
 */
std::string Config::get_object_name(int object)
{
	if(this->get_size_of_configs() > abs(object))
	{
		return std::get<0>(this->m_vector_configs[abs(object)]);
	}
	else
	{
		throw "Nie mo¿na pobraæ parametru obiektu - domyœlnie -> No name";
	}

	return "No name";
}