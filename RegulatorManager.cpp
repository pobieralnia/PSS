#include "StdAfx.h"
#include "RegulatorManager.h"

#include <algorithm>

namespace {
    class DestObiektFun {
    public:
        void operator() (std::pair<std::string, Regulator *> w) {
            delete w.second;
        }
    };
}

// Interface for Regulator P
const std::string RegulatorManager::REGULATOR_P = "P";

// Interface for Regulator PID
const std::string RegulatorManager::REGULATOR_PID = "PID";

// Interface for Regulator GPC
const std::string RegulatorManager::REGULATOR_GPC = "GPC";

/**
 * Constructor - initialize new Regulator
 *
 * @see		rejestrujPrototyp()
 * @return	bool
 */
RegulatorManager::RegulatorManager ()
{
    this->init_prototyp(REGULATOR_P, new RegulatorP());
	this->init_prototyp(REGULATOR_PID, new RegulatorPID());
	this->init_prototyp(REGULATOR_GPC, new RegulatorGPC());
}

/**
 * Destructor - delete all pointers
 *
 * @return	void
 */
RegulatorManager::~RegulatorManager()
{
    std::for_each(m_map.begin(), m_map.end(), DestObiektFun());
}

/**
 * Init prototyp - add new prototyp to map
 *
 * @param	const std::string & id
 * @param	Regulator * prototyp
 * @return	bool
 */
bool RegulatorManager::init_prototyp(const std::string & id, Regulator * prototyp)
{
    if (m_map.count(id) == 0)
	{
        m_map[id] = prototyp;
        return true;
    }
	else
        return false;
}

/**
 * Create new clone for regaultor
 *
 * @param	const std::string & id
 * @return	void
 */
Regulator * RegulatorManager::get_prototyp(const std::string & id) const
{
    if (m_map.count(id) != 0)
        return m_map.find(id)->second->clone();
    else
        throw std::exception (std::string("Nie znaleziono prototypu o identyfikatorze ").append(id).c_str());
}