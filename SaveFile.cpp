#include "stdafx.h"
#include "SaveFile.h"
#include <fstream>
#include <ctime>

/**
 * Constructor
 *
 * @return		void
 */
SaveFile::SaveFile(void)
{
	// if File is open close it
	if(this->m_open_flag)		this->m_FILE.close();	

	// set flag to close
	this->m_open_flag = false;

	// clear file name
	this->m_name_file = "example.txt";

	// set default flag
	this->m_flag_saving = FLAG_WRITE_TO_FIRST_LINE;
}

/** Flag for saving input data to file from last line */
bool SaveFile::FLAG_WRITE_TO_END = false;

/** Flag for saving input data to file from line */
bool SaveFile::FLAG_WRITE_TO_FIRST_LINE = true;

/**
 * Open file to do operation on it
 *
 * @return		bool
 */
bool SaveFile::open()
{
	// if File is open close it
	if(this->m_open_flag)		this->m_FILE.close();	

	this->m_FILE.open(this->m_name_file, this->m_flag_saving);

	// Check if File was open properly
	if (this->m_FILE.is_open())
	{
		this->m_open_flag = true;
		return true;
	}

	return false;
}

/**
 * Save one string to file
 *
 * @param		string line
 * @return		void
 */
void SaveFile::save_online(std::string line)
{
	// If open save to file
	if(this->m_open_flag)
	{
		// Time
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		this->m_FILE << asctime(timeinfo) << line << "\r\n";
	}
}


/**
 * Close file
 *
 * @return		void
 */
void SaveFile::close()
{
	// if File is open close it
	if(this->m_open_flag)		this->m_FILE.close();
}

/**
 * Set name for file to open
 *
 * @param		string name
 * @return		void
 */
void SaveFile::set_name_for_file(std::string name)
{
	this->m_name_file = name;
}

/**
 * Function allows to save current data to file - map, vector or string
 *
 * @param		T data - container or string
 * @return		void
 */
template <typename T>
void SaveFile::save_static(T data)
{
	// If open save to file
	if(this->m_open_flag)
	{
		// Time
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		if( typeid(data).name() == "vector" || typeid(data).name() == "map" )
		{
			for( auto ii=data.begin(); ii!=data.end(); ++ii)
				this->m_FILE << asctime(timeinfo) << *ii << "\r\n";
		}
		elseif(typeid(data).name() == "string")	
			this->m_FILE << asctime(timeinfo) << data << "\r\n";
	}
};

/**
 * Write data from last line
 * 
 * @return		void
 */
void SaveFile::write_from_end()
{
	this->m_flag_saving = FLAG_WRITE_TO_END;
}

/**
 * Write data from last line
 * 
 * @return		void
 */
void SaveFile::write_from_begging()
{
	this->m_flag_saving = FLAG_WRITE_TO_FIRST_LINE;
}