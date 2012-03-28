#include "StdAfx.h"
#include "SaveFile.h"
#include "SaveMysql.h"
#include "Save.h"
#include <string>

SaveBase * Save::createInstance(std::string type)
{
	if      (type == FILE) return new SaveFile;
	else if (type == MYSQL) return new SaveMysql;
	else              return NULL;
}