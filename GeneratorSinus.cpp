#include "stdafx.h"
#include "GeneratorSinus.h"
#include <cmath>

GeneratorSinus::GeneratorSinus(std::map<std::string, double> parameters)
{
	this->m_frequency = parameters["sinus_freq"];
	this->m_amplitude = parameters["sinus_amp"];
}

double GeneratorSinus::simulate(int t)
{
	return this->m_amplitude*std::sin((static_cast<double>(t % static_cast<int>(this->m_frequency)) / this->m_frequency) * 6.28);
}