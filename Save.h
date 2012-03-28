// ---------------------------------------------------------------------------------
// Filename:	Save.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Save
// ---------------------------------------------------------------------------------

#ifndef __SAVE_H__
#define __SAVE_H__

#include "SaveBase.h"
#include "SaveFile.h"
#include "SaveMysql.h"
#include <string>
#include <vector>

/**
 * @class		Save Save.h
 * @brief		Fabric pattern for saving values to file or mysql
 *
 * Usage:
 *  Save * object = new Save();
 *	object->show_available_methods();
 *
 *	SaveBase * File = object->createInstance("file");
 *
 *	cout << File->open() << endl;
 *	File->save_online("asddasd");
 *
 *	delete File;
 *	delete object;
 *
 */
class Save
{
	static const std::string FILE;
	static const std::string MYSQL;
	std::vector<std::string> m_drivers;

	public:
		SaveBase * createInstance(std::string type);
		Save(void);
		~Save(void) {};

		void show_available_methods();

		/**
		 * Get available drivers in vector
		 *
		 * @return		vector<string>
		 */
		std::vector<std::string> get_available_methods() { return this->m_drivers; };

	private:
		Save (const Save &);		// disable default copy
		Save & operator = (const Save &);		// disable default copy
};

#endif