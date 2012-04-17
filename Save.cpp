// ---------------------------------------------------------------------------------
// Filename:	Save.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Save
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "SaveFile.h"
#include "SaveMysql.h"
#include "Save.h"

#include <iostream>
#include <string>

const std::string Save::FILE = "file";
const std::string Save::MYSQL = "mysql";

Save::Save(void)
{
	this->m_drivers.clear();
	this->m_drivers.push_back(FILE);
	this->m_drivers.push_back(MYSQL);
}

SaveBase * Save::createInstance(std::string type)
{
	if      (type == FILE)	return new SaveFile;
	else if (type == MYSQL) return new SaveMysql;
	else					return NULL;
}

void Save::show_available_methods()
{
	std::cout << FILE << std::endl;
	std::cout << MYSQL << std::endl;
}