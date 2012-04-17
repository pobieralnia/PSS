#ifndef __GENERATORSTEP_H__
#define __GENERATORSTEP_H__

#include "Signal.h"
#include <map>
#include <string>

class GeneratorStep : public Signal {

	double m_value;
	int m_time;

	public:
		GeneratorStep(std::map<std::string, double> parameters, int start, int stop);
		virtual double simulate(int t);
};
#endif