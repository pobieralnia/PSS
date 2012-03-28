// ---------------------------------------------------------------------------------
// Filename:	SaveBase.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Save
// ---------------------------------------------------------------------------------

#ifndef __SAVEFILE_H__
#define __SAVEFILE_H__

#include "SaveBase.h"

class SaveFile : public SaveBase
{
	public:
		void save_online(std::string line) {};
		void save_static() {};
};

#endif

