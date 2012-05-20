// ---------------------------------------------------------------------------------
// Filename:	SaveMysql.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Save
// ---------------------------------------------------------------------------------

#ifndef __SAVEMYSQL_H__
#define __SAVEMYSQL_H__

#include "SaveBase.h"

class SaveMysql : public SaveBase
{
	public:
		void save_online(std::string line) {};
		void save_online(double line) {};
		bool open() { return true; };
		void close() {};
};

#endif

