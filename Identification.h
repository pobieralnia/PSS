// ---------------------------------------------------------------------------------
// Filename:	Identification.h
// Author:		Tomasz L.
// Date:		2012-05-03
// Package:		Identification
// ---------------------------------------------------------------------------------

#ifndef __IDENTIFICATION_H__
#define __IDENTIFICATION_H__

#include <deque>
#include "Eigen/Dense"

/**
 * @class	Identification	Identification.h
 * @brief	Class identification for ARX model
 *
 * By outputs and control signal class indentify polynomials A and B for ARX object
 *
 * Exceptions:
 * @see	set_parameters(int rA, int rB, double l, double delta_min, double delta_max)
 * @see	identify()
 */
class Identification
{
	private:
		int m_rankA, m_rankB; // rank of polynomial
		int m_delay;
		double m_epsilon;
		double m_lambda;
		double m_delta_min, m_delta_max;
		std::deque<double> m_history_U,m_history_Y;
		bool m_loaded_flag_identity;	/*< flag for setting all matrix and vectors */
		bool m_loaded_flag;		/*< flag for loading parameters to use only once */
		std::deque<double> m_history_poly_A, m_history_poly_B;
		Eigen::VectorXd m_Q, m_Fi;
		Eigen::MatrixXd m_P, m_IM;
	public:
		Identification(void);
		~Identification(void);
		void add_sample(double y, double u);
		void set_parameters(int rA, int rB, double l, double delta_min, double delta_max);
		void identify(void);
		void get_polynomial_a(std::deque<double> & poly);
		void get_polynomial_b(std::deque<double> & poly);
	private:
		void update_history(void);
		void calculating_fi(void);
		void calculating_changeable_weights(void);
		void calculating_pi(double y);
		void calculating_covariance_matrix(void);
		void minimizing_quality_pointer(void);
};

#endif