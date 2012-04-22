#ifndef __GENERATORSINUS_H__
#define __GENERATORSINUS_H__

#include "Signal.h"
#include <map>
#include <string>

class GeneratorSinus : public Signal {

	double m_frequency;
	double m_amplitude;

	public:
		GeneratorSinus(std::map<std::string, double> parameters);
		virtual double simulate(int t);
};
#endif