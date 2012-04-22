// ---------------------------------------------------------------------------------
// Filename:	ConfigGenerator.cpp
// Author:		Tomasz L.
// Date:		2012-04-22
// Package:		Config
// ---------------------------------------------------------------------------------

#include "StdAfx.h"

#include <sstream>

#include "Config.h"
#include "ConfigGenerator.h"


/**
 * Constructor
 * clear all main variables
 * 
 * @param	struct someStruct * state - struct with config variables
 * @return	void
 */
ConfigGenerator::ConfigGenerator(struct someStruct * state)
{
	m_vector_generator_ptr = &state->m_vector_generator;
	this->clear();
}

/**
 * Destructor
 *
 * @return	void
 */
ConfigGenerator::~ConfigGenerator(void)
{
	this->clear_all();
}

/**
 * Clear main config variables
 *
 * @return		void
 */
void ConfigGenerator::clear(void)
{
	this->m_parameters.clear();
}

/**
 * Clear vector of configs
 *
 * @return		void
 */
void ConfigGenerator::clear_all()
{
	this->clear();

	m_vector_generator_ptr->clear();
	m_vector_generator_ptr = NULL;
	delete m_vector_generator_ptr;
}

/**
 * Parse lines to load all main variables in config file
 *
 * @param		string line
 * @return		void
 */
void ConfigGenerator::parse_line(std::string line)
{
	
	if(ConfigParser::regex_end_of_config(line))
	{
		// initialize a tuple and put in vector of configs
		m_vector_generator_ptr->push_back(this->m_parameters);

		// clear main variables
		this->clear();
	}
	else
	{
		// Check what kind of variables are in the line
		ConfigParser::regex_generator_parameter(line, m_parameters);
	}
}

/**
 * Get the string of the size of all generator configs
 *
 * @param		int i - flag
 * @return		string - size of configs
 */
std::string ConfigGenerator::get_size(int i)
{
	std::stringstream ss; //create a stringstream
	ss << m_vector_generator_ptr->size();
	return ss.str(); //return a string with the contents of the stream
}

/**
 * Get the size of all generator configs
 *
 * @return		int
 */
int ConfigGenerator::get_size()
{
	return m_vector_generator_ptr->size(); 
}