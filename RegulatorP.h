// ---------------------------------------------------------------------------------
// Filename:	Regulator.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		RegulatorP
// ---------------------------------------------------------------------------------

#ifndef __REGULATORP_H__
#define __REGULATORP_H__

#include "Regulator.h"
#include "Signal.h"

/**
 * @class	RegulatorP	RegulatorP.h
 * @brief	Implements regulator P
 *
 * Class simulate behevior for P controller
 */
class RegulatorP : public Regulator
{
	private:
		double m_k;
		double m_w;
		double m_e;
		SignalBase * m_proces;

	public:
		RegulatorP(void);
		~RegulatorP(void);
		double simulate(double input);
		double get_error(void);
		void set_parameters(std::map<std::string, double> & parm);
		void set_parameters(const std::string & param_name, double value);
		void get_parameters(std::map<std::string, double> & parm) const;
		virtual RegulatorP * clone () const;
		void set_setpoint(SignalBase * proces);
		double get_setpoint();
};

#endif