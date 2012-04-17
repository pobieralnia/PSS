#ifndef __GENERATORRECTANGLE_H__
#define __GENERATORRECTANGLE_H__

#include "Signal.h"
#include <map>
#include <string>

class GeneratorRectangle : public Signal {

	double m_amplitude;
	double m_output;
	double m_fill;
	double m_frequence;

	public:
		GeneratorRectangle(std::map<std::string, double> parameters, int start, int stop);
		virtual double simulate(int t);
};
#endif