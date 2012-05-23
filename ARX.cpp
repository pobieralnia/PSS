// ---------------------------------------------------------------------------------
// Filename:	ARX.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ARX	
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include <numeric>
#include <deque>
#include "ARX.h"

/**
 * Constructor - fill variables with default data
 *
 * @return		void
 */
ARX::ARX(void)
{
	this->clear();

	this->m_A.push_back(-0.6);
	this->m_B.push_back(0.4);
	this->m_delay = 1;
	this->m_stat = 0;
	this->m_noise = 0.0;

}
/**
 * Simulate ARX object with current input value
 *
 * @param		double input
 * @return		double output
 */
double ARX::simulate(double input)
{
    // Change size if polynolmials were changed (depands if object is stationary)
    this->update_sample_size();

    // Removes the last element
    this->m_U.pop_back();

	// Add input to the front
    this->m_U.push_front(input);

    // Cut u and catch delay (k)
	std::deque<double>::iterator tmp_u_begin = m_U.begin();
    advance(tmp_u_begin, this->m_delay);

    const double b_u = inner_product(
										this->m_B.begin(),
										this->m_B.end(),
										tmp_u_begin, 
										0.0
									);
	

	const double a_y = inner_product(
										this->m_A.begin(),
										this->m_A.end(),
										this->m_Y.begin(), 
										0.0
									);

    const double e = static_cast<double>(0.1 * input * m_noise);
	const double output = -a_y + b_u + e;

	// Removes the last element
	this->m_Y.pop_back();

	// Add output to the front
	this->m_Y.push_front(output);

    return output;
	
}

/**
 * Set initial state for inputs and outputs
 *
 * @param		deque u_init - inputs
 * @param		deque y_init - outputs
 * @return		void
 */
void ARX::set_initial_state(const std::deque<double> u_init, const std::deque<double> y_init)
{
	size_t i;

	// fill init inputs with values
    for(i = 0; (i < u_init.size()) && (i < this->m_U.size()); i++)		this->m_U[i] = u_init[i];

	// rest if left fill with zeros
    for(; i < this->m_U.size(); i++)		this->m_U[i] = 0;

	// fill init outputs with values
    for(i = 0; (i < y_init.size()) && (i < this->m_Y.size()); i++)		this->m_Y[i] = y_init[i];

	// rest if left fill with zeros
    for(; i < this->m_Y.size(); i++)		this->m_Y[i] = 0;
    
}

/**
 * Update size of inputs and outputs (u,y)
 *
 * @see			simulate()
 * @return		void
 */
void ARX::update_sample_size()
{
	// outputs
    const int max_y = this->m_A.size() - this->m_Y.size();
    if (max_y > 0)		this->m_Y.resize(max_y,0);
    
	// inputs
    const int max_u = this->m_B.size() + this->m_delay - this->m_U.size();
    if (max_u > 0)		this->m_U.resize(max_u,0);
}

/**
 * Clear deque variables for ARX object
 *
 * @return		void
 */
void ARX::clear()
{
	this->m_A.clear();
	this->m_B.clear();
}

/**
 * Set arx parameters
 *
 * @param		std::deque<double> A - polynomial A
 * @param		std::deque<double> B - polynomial B
 * @param		std::map<std::string, double> others
 * @return		void
 */
void ARX::set_parameters(std::deque<double> A, std::deque<double> B, std::map<std::string, double> others)
{
	this->clear();

	this->m_A = A;
	this->m_B = B;
	this->m_delay = others["k"];
	this->m_stat = others["stationary"];
	this->m_noise = others["noise"];

	this->update_sample_size();
}

/**
 * Get arx parameters
 *
 * @param		std::deque<double> A - polynomial A
 * @param		std::deque<double> B - polynomial B
 * @param		std::map<std::string, double> others
 * @return		void
 */
void ARX::get_parameters(std::deque<double> & A, std::deque<double> & B, std::map<std::string, double> & others) const
{
	A = m_A;
	B = m_B;
	others["k"] = m_delay;
	others["stationary"] = m_stat;
	others["noise"] = m_noise;
}