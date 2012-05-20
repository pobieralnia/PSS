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

#include <vector>
#include <deque>
#include <map>
#include <string>

class RegulatorP : public Regulator
{
	private:
		std::deque<double> m_history_U, m_history_Y, m_history_E;	// History for inputs/outputs - new in the front, old in the end
		double m_k;
		double m_w;
		SignalBase * m_proces;

	public:
		RegulatorP(void);
		~RegulatorP(void);
		double simulate(double input);
		double get_error(void);
		void get_error(std::vector<double> & err);
		void set_parameters(std::map<std::string, double> & parm);
		void set_parameters(const std::string & param_name, double value);
		void get_parameters(std::map<std::string, double> & parm) const;
		virtual RegulatorP * clone () const;
		void set_setpoint(SignalBase * proces);
		double get_setpoint();
};

#endif