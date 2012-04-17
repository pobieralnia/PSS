// ---------------------------------------------------------------------------------
// Filename:	ConfigStruct.h
// Author:		Tomasz L.
// Date:		2012-04-12
// Package:		Config
// ---------------------------------------------------------------------------------

#ifndef __CONFIGSTRUCT_H__
#define __CONFIGSTRUCT_H__

#include <string>
#include <map>
#include <tuple>
#include <vector>

/**
 * @struct	ConfigStruct ConfigStruct.h
 * @brief	Structure for all main configs
 */
struct someStruct {
		std::vector<std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>>> m_vector_objects;
		std::vector<std::map<std::string,double>> m_vector_regulator;
		std::vector<std::map<std::string,double>> m_vector_generator;
	};

#endif