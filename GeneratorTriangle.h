#ifndef __GENERATORTRIANGLE_H__
#define __GENERATORTRIANGLE_H__

#include "Signal.h"
#include <map>
#include <string>

class GeneratorTraingle : public Signal {

	double m_amplitude;
	double m_output;
	double m_frequence;

	public:
		GeneratorTraingle(std::map<std::string, double> parameters, int start, int stop);
		virtual double simulate(int t);
};
#endif