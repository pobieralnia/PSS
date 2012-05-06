#include "StdAfx.h"
#include "Identification.h"
#include <iostream>
#include <algorithm>

using namespace std;
/**
 * Constructor - set variables with initial data
 *
 * @return		void
 */
Identification::Identification() : m_rankA(1), m_rankB(0), m_lambda(0.9), m_delay(1), m_delta_min(0.00001), m_delta_max(100)
{
	m_history_poly_A.push_front(0.0);
	m_history_poly_B.push_front(0.0);
	m_loaded_flag = false;
	m_loaded_flag_identity = false;
}

/**
 * Destructor
 * 
 * @return		void
 */
Identification::~Identification(void)
{
}

/**
 * Set parameters for identification
 *
 * @return		void
 */
void Identification::set_parameters(int rA, int rB, double l, double delta_min, double delta_max)
{
	if(m_loaded_flag == false)
	{
		if(rA > 0 || rB > 0 || l > 0 || l < 1 || delta_min > 0 || delta_max < 1000000)
		{
			m_rankA = rA;
			m_rankB = rB;
			m_lambda = l;
			m_delta_min = delta_min;
			m_delta_max = delta_max;

			m_loaded_flag = true;
			m_loaded_flag_identity = true;
		}
		else
			throw std::string("Parametry siê nie zgadzaj¹ nic nie zosta³o zmienione");
	}
	else
		throw std::string("Parametry za³adowane nale¿y zresetowaæ identyfikacje");
}

/**
 * Identify - prepare vectors and matrix for identification
 * There are to flags which are checked every time we call method
 * m_loaded_flag - for checking if method set_parameters() was called
 * m_loaded_flag_identity - for checking if identify() was called
 *
 * @return		void
 */
void Identification::identify()
{
	if(m_loaded_flag == true || m_loaded_flag_identity == false)
	{
		m_Q.setZero(m_rankB+1 + m_rankA);
		m_Fi.setZero(m_rankB+1 + m_rankA);
		m_P.setIdentity(m_rankB+1 + m_rankA, m_rankB+1 + m_rankA);
		m_P *= 1000;

		m_IM.setIdentity(m_rankB+1 + m_rankA,m_rankB+1 + m_rankA);
		m_history_U.resize(m_rankB+1 + m_delay);
		m_history_Y.resize(m_rankA);

		m_loaded_flag_identity = true;
	}
	else
		throw std::string("Parametry za³adowane nale¿y zresetowaæ identyfikacje");

}

/**
 * Identify polynomial by given sample of output and control signal
 *
 * @param		double y - output
 * @param		double u - control signal
 */
void Identification::add_sample(double y, double u)
{
	if(m_loaded_flag == true && m_loaded_flag_identity == true)
	{
		m_history_U.push_front(u);
		m_history_U.pop_back();

		calculating_fi();
		calculating_pi(y);
		calculating_covariance_matrix();
		minimizing_quality_pointer();

		m_history_Y.push_front(y);
		m_history_Y.pop_back();

		// update history for polynomials
		update_history();
	}
}

/**
 * Minimazing quality pointer
 * dr. Dariusz Bismor - PSS [32.5], [32.6]
 * 
 * @return		void
 */
void Identification::minimizing_quality_pointer()
{
	Eigen::VectorXd k = m_P * m_Fi;
	m_Q = m_Q + k*m_epsilon;
}

/**
 * Calculating covariance matrix for RMNK
 * dr. Dariusz Bismor - PSS [32.1], [32.13], [32.16]
 * 
 * @return		void
 */
void Identification::calculating_covariance_matrix()
{
	const double q = (m_delta_max - m_delta_min) / m_delta_max;
	const double r = m_delta_min;
	m_P = q * m_P + r * m_IM;
}

/**
 * Calculating Fi
 * dr. Dariusz Bismor - PSS [32.3]
 *
 * @return		void
 */
void Identification::calculating_fi()
{
	std::deque<double>::iterator itr = m_history_U.begin();
	advance(itr, m_delay);
	int i = 0;
	for( ; itr != m_history_U.end() ; itr++, i++)
	{
		m_Fi[i] = *itr;
	}

	for(std::deque<double>::iterator it = m_history_Y.begin() ; it != m_history_Y.end() ; it++, i++)
	{
		m_Fi[i] = -(*it);
	}
}

/**
 * Calculating Pi
 * dr. Dariusz Bismor - PSS [32.8]
 *
 * @param		double y - output from regulation loop
 * @return		void
 */
void Identification::calculating_pi(double y)
{
	m_epsilon = y - m_Q.dot(m_Fi);
	m_P = (1.0 / m_lambda) * (  m_P - ((m_P * m_Fi * m_Fi.transpose() * m_P) / (m_lambda + m_Fi.transpose() * m_P * m_Fi)) );
}

/**
 * Update history for polynomial A and B - new inputs in the front of polynomials
 *
 * @return		void
 */
void Identification::update_history(void)
{
	int i = 0;
	for(; i<m_rankB+1 ; i++)			m_history_poly_B.push_front(m_Q[i]);

	for(; i<m_rankB+1+m_rankA ; i++)	m_history_poly_A.push_front(m_Q[i]);
}

/**
 * Get identified polynomial a
 *
 * @param		std::deque<double> & poly
 * @return		void
 */
void Identification::get_polynomial_a(std::deque<double> & poly)
{
	std::deque<double> tmp_polyA(m_rankA);
	for(int i = 0; i < m_rankA; i++)
		tmp_polyA.push_front(m_history_poly_A[i]);
	
	poly = tmp_polyA;
}

/**
 * Get identified polynomial b
 *
 * @param		std::deque<double> & poly
 * @return		void
 */
void Identification::get_polynomial_b(std::deque<double> & poly)
{
	std::deque<double> tmp_polyB(m_rankB+1);
	for(int i = 0; i < m_rankB+1; i++)
		tmp_polyB.push_front(m_history_poly_B[i]);
	
	poly = tmp_polyB;
}