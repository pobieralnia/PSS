// ---------------------------------------------------------------------------------
// Filename:	Regulator.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Regulator
// ---------------------------------------------------------------------------------

#ifndef __REGULATOR_H__
#define __REGULATOR_H__

#include "Object.h"

#include <map>
#include <vector>
#include <string>

class SignalBase;

/**
 * @class	Regulator Regulator.
 * @brief	Abstract class Regulator
 *  
 * Interface for regulator object, inherits Object SISO interface
 */
class Regulator : public Object
{
	public:
		virtual double simulate(double objectOutput) = 0;
		virtual ~Regulator(void) {};
		virtual double get_setpoint() = 0;
		virtual void set_setpoint(SignalBase * proces) = 0;
		virtual double get_error() = 0;
		virtual void set_parameters(std::map<std::string, double> & parm) = 0;
		virtual void set_parameters(const std::string & param_name, double value) = 0;
		virtual void get_parameters(std::map<std::string, double> & parm) const = 0;
		virtual Regulator * clone () const = 0;
};

#endif