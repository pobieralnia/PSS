// ---------------------------------------------------------------------------------
// Filename:	SaveBase.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Save
// ---------------------------------------------------------------------------------

#ifndef __SAVEBASE_H__
#define __SAVEBASE_H__

#include <string>

/**
 * @class		SaveBase SaveBase.h
 * @brief		Abstract class for saving files
 * @date		2012-02-28
 * @author		Tomasz L
 */
class SaveBase
{
	public:
		virtual void save_online(std::string line) = 0;
		virtual bool open() = 0;
		virtual void close() = 0;
		virtual ~SaveBase() {};
};

#endif