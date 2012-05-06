// ---------------------------------------------------------------------------------
// Filename:	ConfigRegulator.cpp
// Author:		Tomasz L.
// Date:		2012-04-22
// Package:		Config
// ---------------------------------------------------------------------------------

#include "StdAfx.h"

#include <sstream>

#include "Config.h"
#include "ConfigRegulator.h"


/**
 * Constructor -clear all main variables
 * 
 * @param	struct someStruct * state - struct with config variables
 * @return	void
 */
ConfigRegulator::ConfigRegulator(struct someStruct & state)
{
	m_vector_regulator_ptr = &state.m_vector_regulator;
	this->clear();
}

/**
 * Destructor
 *
 * @return	void
 */
ConfigRegulator::~ConfigRegulator(void)
{
	this->clear_all();

	m_vector_regulator_ptr = NULL;
	delete m_vector_regulator_ptr;
}

/**
 * Clear main config variables
 *
 * @return		void
 */
void ConfigRegulator::clear(void)
{
	this->m_parameters.clear();
}

/**
 * Clear vector of configs
 *
 * @return		void
 */
void ConfigRegulator::clear_all()
{
	this->clear();
	m_vector_regulator_ptr->clear();
}

/**
 * Parse lines to load all main variables in config file
 *
 * @param		string line
 * @return		void
 */
void ConfigRegulator::parse_line(std::string line)
{
	if(ConfigParser::regex_end_of_config(line))
	{
		// initialize a tuple and put in vector of configs
		m_vector_regulator_ptr->push_back(this->m_parameters);

		// clear main variables
		this->clear();
	}
	else
	{
		// Check what kind of variables are in the line
		ConfigParser::regex_regulator_parameter(line, m_parameters);
	}
}

/**
 * Get the string of the size of all generator configs
 *
 * @param		int i - flag
 * @return		string - size of configs
 */
std::string ConfigRegulator::get_size(int i)
{
	std::stringstream ss; //create a stringstream
	ss << m_vector_regulator_ptr->size();
	return ss.str(); //return a string with the contents of the stream
}

/**
 * Get the size of all generator configs
 *
 * @return		int
 */
int ConfigRegulator::get_size()
{
	return m_vector_regulator_ptr->size(); 
}