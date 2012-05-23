// ---------------------------------------------------------------------------------
// Filename:	ConfigRegulator.h
// Author:		Tomasz L.
// Date:		2012-04-22
// ---------------------------------------------------------------------------------

#ifndef __CONFIGREGULATOR_H__
#define __CONFIGREGULATOR_H__

#include "ConfigBase.h"
#include "ConfigParser.h"

#include <vector>
#include <map>

/**
 * @class	ConfigGenerator ConfigGenerator.h
 * @brief	Generator config class
 */
class ConfigRegulator : public ConfigBase, private ConfigParser
{
	std::vector<std::map<std::string,double> > * m_vector_regulator_ptr;
	std::map<std::string, double> m_parameters;

	public:
		ConfigRegulator(struct ConfigStruct & state);
		~ConfigRegulator(void);
		void parse_line(std::string line);
		void clear_all(void);
		int get_size();
		std::string get_size(int i);

	private:
		void clear(void);
};

#endif
