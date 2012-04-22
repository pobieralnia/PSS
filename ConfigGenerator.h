// ---------------------------------------------------------------------------------
// Filename:	ConfigGenerator.h
// Author:		Tomasz L.
// Date:		2012-04-22
// ---------------------------------------------------------------------------------

#ifndef __CONFIGGENERATOR_H__
#define __CONFIGGENERATOR_H__

#include "ConfigBase.h"
#include "ConfigParser.h"

#include <vector>
#include <map>

/**
 * @class	ConfigGenerator ConfigGenerator.h
 * @brief	Generator config class
 * @date	2012-04-04
 */
class ConfigGenerator : public ConfigBase, private ConfigParser
{
	std::vector<std::map<std::string,double> > * m_vector_generator_ptr;
	std::map<std::string, double> m_parameters;

	public:
		ConfigGenerator(struct someStruct * state);
		~ConfigGenerator(void);
		void parse_line(std::string line);
		void clear_all(void);
		int get_size();
		std::string get_size(int i);

	private:
		void clear(void);
};

#endif
