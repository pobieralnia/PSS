// ---------------------------------------------------------------------------------
// Filename:	SaveFile.h
// Author:		Tomasz L.
// Date:		2012-03-28
// Package:		Save
// ---------------------------------------------------------------------------------

#ifndef __SAVEFILE_H__
#define __SAVEFILE_H__

#include <fstream>
#include <typeinfo>

#include "SaveBase.h"

/**
 * @class		SaveFile SaveFile.h
 * @brief		Class allows to save data to file with set name
 * @author		Tomasz L
 * @date		2012-03-28
 *
 * Driver for saving to file. Allows save map,vector or string statically (one call), or allows save ex. in loop save_online() a string
 */
class SaveFile : public SaveBase
{

	bool m_open_flag;
	std::ofstream m_FILE;
	std::string m_name_file;

	public:
		SaveFile(void);
		void save_online(std::string line);
		void close();

		template <typename T>
		void save_static(T data);

		bool open();
		void set_name_for_file(std::string name);
		~SaveFile() { this->m_FILE.close(); };

	private:
		SaveFile (const SaveFile &);		// disable default copy
		SaveFile & operator = (const SaveFile &);		// disable default copy
};

#endif

