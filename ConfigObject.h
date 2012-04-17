// ---------------------------------------------------------------------------------
// Filename:	ConfigObject.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config
// ---------------------------------------------------------------------------------

#ifndef __CONFIGOBJECT_H__
#define __CONFIGOBJECT_H__

#include "ConfigBase.h"
#include "ConfigParser.h"

#include <tuple>
#include <map>
#include <vector>

/**
 * @class		ConfigObject ConfigObjrct.h
 * @brief		Main class for keeping object settings
 *
 * The main variables are k, polyniomal A,B, stationarity, object name.
 *
 * Exceptions:
 * @see		get_parameters();
 * @see		check_object_stationarity();
 * @see		get_object_name();
 */
class ConfigObject : public ConfigBase, private ConfigParser
{
	typedef std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>> object_details;

	static const int POLYNOMIAL_A = 0;
	static const int POLYNOMIAL_B = 1;

	std::map<std::string, double> m_other_parameters;
	std::map<int,double> m_a_parameters;	// config - container for a - parameters
	std::map<int,double> m_b_parameters;	// config - container for b - parameters

	std::vector<object_details> * m_vector_objects_ptr;	// container for all configs

	private:
		void clear(void);

	public:
		ConfigObject(struct someStruct * state);
		~ConfigObject(void) { this->clear_all(); };
		void parse_line(std::string line);

		/**
		 * Get the size of all objects
		 *
		 * @return		int
		 */
		int get_size() { return m_vector_objects_ptr->size();  };
		std::string get_size(int i);

		void clear_all(void);
};

#endif