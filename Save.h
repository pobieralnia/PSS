// ---------------------------------------------------------------------------------
// Filename:	SaveBase.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Save
// ---------------------------------------------------------------------------------

#ifndef __SAVE_H__
#define __SAVE_H__

#define FILE  "file"
#define MYSQL "mysql"

#include "SaveBase.h"
#include "SaveFile.h"
#include "SaveMysql.h"
#include <string>

class Save
{
	public:
		SaveBase * createInstance(std::string type);
		Save(void) {};
		~Save(void) {};

		// project in progress
		void show_available_methods() {};
		void get_available_methods() {};
};

#endif