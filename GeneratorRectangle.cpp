#include "stdafx.h"
#include "GeneratorRectangle.h"

GeneratorRectangle::GeneratorRectangle(std::map<std::string, double> parameters)
{
	this->m_frequence = parameters["rectangle_frequence"];
	this->m_amplitude = parameters["rectangle_amplituda"]; 
	this->m_fill = parameters["rectangle_fill"];
}

double GeneratorRectangle::simulate(int t)
{
	 return ((t % static_cast<int>(this->m_frequence)) < (this->m_fill * this->m_frequence)) ? this->m_amplitude : 0;
}