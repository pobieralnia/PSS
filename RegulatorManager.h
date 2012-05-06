#ifndef __REGULATORMANAGER_H__
#define __REGULATORMANAGER_H__

#include "Regulator.h"
#include "RegulatorP.h"
#include "RegulatorPID.h"
#include "RegulatorGPC.h"

#include <map>
#include <string>
 
/**
 * @class	RegulatorManager RegulatorManager.h
 * @brief	Manager for Regulators
 *
 * Exceptions
 * @see get_prototyp()
 */
class RegulatorManager
{
	public:

		// interface
		static const std::string REGULATOR_P;
		static const std::string REGULATOR_PID;
		static const std::string REGULATOR_GPC;

	public:
		RegulatorManager ();
		~RegulatorManager ();
		Regulator * get_prototyp (const std::string & id) const;
		bool init_prototyp(const std::string & id, Regulator * prototyp);
	private:
		std::map<std::string, Regulator *> m_map;
};
 
#endif