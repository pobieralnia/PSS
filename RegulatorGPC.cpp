// ---------------------------------------------------------------------------------
// Filename:	RegulatorGPCh
// Author:		Tomasz L.
// Date:		2012-05-03
// Package:		Regulator
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "RegulatorGPC.h"

/**
 * Constructor - set member variables with defualt values
 *
 * @return		void
 */
RegulatorGPC::RegulatorGPC(void) : m_H(3), m_L(2), m_alpha(0.3), m_ro(0.5), m_rankA(1), m_rankB(0), m_initial_steps(10), m_initial_steps_left(0), m_lambda(0.9),  m_e(0.0)
{
	m_proces = NULL;
	m_identify = NULL;
	m_history_U.push_front(0);
    m_history_Y.push_front(0);
	start_identification();
}

/**
 * Destructor
 *
 * @return		void
 */
RegulatorGPC::~RegulatorGPC(void)
{
}

/**
 * Clone regulator
 *
 * @return new RegulatorP
 */
RegulatorGPC * RegulatorGPC::clone () const
{
    return new RegulatorGPC(*this);
}

/**
 * Simulate
 * 
 * @param		double input
 * @return		double u - control signal
 */
double RegulatorGPC::simulate(double input)
{
	if(m_proces)
	{
		m_w = m_proces->simulate();
		const double y = input;

		m_e = m_w - y;
		m_history_Y.push_front(y);
		m_identify->add_sample(input, m_history_U.front());

		//std::deque<double> A,B;
		//m_poly_A.clear();
		//m_poly_B.clear();

		//A.push_back(-0.6);
		//B.push_back(0.4);

		m_identify->get_polynomial_a(m_poly_A);
		m_identify->get_polynomial_b(m_poly_B);

		// Return disruption
		if (m_initial_steps_left > 0)
		{
			const double u = static_cast<double>(rand())/RAND_MAX*m_w;
			m_history_U.push_front(u);
			m_initial_steps_left--;
			return u;
		}
    
		// Control algorithm
		// ------------------------------------------------------------------------------------------------------
	
		// 1. Calculating h initial conditions equal zero, delay = 0
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 27
		Eigen::VectorXd h(m_H);
		{
			std::map<std::string, double> others;
			others["k"] = 0;
			others["stationary"] = 0;
			others["noise"] = 0;

			ARX ob;
			ob.set_parameters(m_poly_A,m_poly_B,others);
			for(int i=0; i<m_H; i++)
			{
				h[i] = ob.simulate(1.0);
			}
		}

		// 2. Calculating Q:
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 28
		Eigen::MatrixXd Q;
		Q.setZero(m_H, m_L);
		for(int i=0; i<m_H; i++)
		{
			for(int j=0; j<m_L; j++)
			{
				if(i-j<0)
				{
					Q(i,j) = 0;
				}
				else
				{
					Q(i,j) = h[i-j];
				}
			}
		}

		// 3. Calculating w0
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 8
		Eigen::VectorXd w0(m_H);
		w0[0] = (1-m_alpha)*m_w + m_alpha*y;
		for(int i=1; i<m_H; i++)
		{
			w0[i] = (1-m_alpha)*m_w + m_alpha*w0[i-1];
		}
		

		// 4. Calculating q
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 20
		Eigen::VectorXd tmp;
		tmp.setZero(m_L);
		tmp[0] = 1;
		Eigen::MatrixXd mIdentity;
		mIdentity.setIdentity(m_L,m_L);
		Eigen::VectorXd q = (tmp.transpose()
							*((Q.transpose()*Q + m_ro*mIdentity).inverse())
							*Q.transpose()
							).transpose();

		// 5. Calculating y0
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 31
		Eigen::VectorXd y0(m_H);
		{
			ARX ob;
			std::map<std::string, double> others;
			others["k"] = 0;
			others["stationary"] = 0;
			others["noise"] = 0;
			ob.set_parameters(m_poly_A,m_poly_B,others);
			ob.set_initial_state(m_history_U, m_history_Y);
			ob.simulate(m_history_U.front());
			for (int i=0; i<m_H; i++)
			{
				y0[i] = ob.simulate(m_history_U.front());
			}
		}

		// 6. Calculating final control
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 35
		const double du = q.transpose() * (w0-y0);
		const double u = m_history_U.front() + du;

		m_history_U.push_front(u);

		return u;
	}
	else
		return 0.0;
}

/**
 * Set parameters for Regulator
 *
 * @param		std::map<std::string, double> parm
 * @return		void
 */
void RegulatorGPC::set_parameters(std::map<std::string, double> & parm)
{
	// Clear all tmp values
	m_tmp_parameter.clear();

	// Copy values to temporary map
	m_tmp_parameter = parm;

	// Check parameters if they are correct
	try
	{
		if(check_parameters())
		{
			m_H = parm["H"];
			m_L = parm["L"];
			m_alpha = parm["alpha"];
			m_ro = parm["ro"];
			m_rankA = parm["rankA"];
			m_rankB = parm["rankB"];
			m_lambda = parm["lambda"];
		}
     }
	 catch ( std::string & e )
	 {
        throw;
     }

}

/**
 * Set one parameter for Regulator
 *
 * @param		const std::string & param_name
 * @param		double value
 * @return		void
 */
void RegulatorGPC::set_parameters(const std::string & param_name, double value)
{
	// Clear all tmp values
	m_tmp_parameter.clear();

	m_tmp_parameter["H"] = m_H;
	m_tmp_parameter["L"] = m_L;
	m_tmp_parameter["alpha"] = m_alpha;
	m_tmp_parameter["lambda"] = m_lambda;
	m_tmp_parameter["rankA"] = m_rankA;
	m_tmp_parameter["rankB"] = m_rankB;
	m_tmp_parameter["ro"] = m_ro;

	if(param_name == "H")
		m_tmp_parameter["H"] = value;
	else if(param_name == "L")
		m_tmp_parameter["L"] = value;
	else if(param_name == "alpha")
		m_tmp_parameter["alpha"] = value;
	else if(param_name == "lambda")
		m_tmp_parameter["lambda"] = value;
	else if(param_name == "rankA")
		m_tmp_parameter["rankA"] = value;
	else if(param_name == "rankB")
		m_tmp_parameter["rankB"] = value;
	else if(param_name == "rankB")
		m_tmp_parameter["rankB"] = value;
	else if(param_name == "ro")
		m_tmp_parameter["ro"] = value;

	// Check parameters if they are correct
	try
	{
		if(check_parameters())
		{
			// TODO Bezsens nie mam pomys³u jak tego nie dublowac
			if(param_name == "H")
				m_H = value;
			else if(param_name == "L")
				m_L = value;
			else if(param_name == "alpha")
				m_alpha = value;
			else if(param_name == "lambda")
				m_lambda = value;
			else if(param_name == "rankA")
				m_rankA = value;
			else if(param_name == "rankB")
				m_rankB = value;
			else if(param_name == "ro")
				m_ro = value;
		}
	}
	catch (std::string & e)
	{
		throw; // rethrow exception
	}
}

/**
 * Get parameters from Regulator
 *
 * @param		std::map<std::string, double> parm
 * @return		void
 */
void RegulatorGPC::get_parameters(std::map<std::string, double> & parm) const
{
	parm["H"] = m_H;
    parm["L"] =  m_L;
    parm["alpha"] = m_alpha;
    parm["lambda"] = m_lambda;
    parm["ro"] = m_ro;
	parm["rankA"] = m_rankA;
	parm["rankB"] = m_rankB;
}

/** 
 * Get error for current simulation regulation
 *
 * @return	double
 */
double RegulatorGPC::get_error()
{
	return m_e;
}

/**
 * Get set point value
 *
 * @return		double
 */
double RegulatorGPC::get_setpoint()
{
	return m_w;
}


/**
 * Set setpoint
 *
 * @param		SignalBase * proces - signal generator
 * @return		void
 */
void RegulatorGPC::set_setpoint(SignalBase * proces)
{
	m_proces = proces;
}

/**
 * Check parameters if they are correct with model
 *
 * @return		bool
 */
bool RegulatorGPC::check_parameters()
{
	// All parameters have to be positive 
	for(std::map<std::string,double>::iterator itr = m_tmp_parameter.begin(); itr != m_tmp_parameter.end(); itr++)
	{
		if(itr->second < 0)
		{
			throw std::string("Parametry musz¹ byæ dodatnie");
			return false;
		}
	}

	if(m_tmp_parameter["H"] < 1 || m_tmp_parameter["H"] > 1000)
	{
		throw std::string("Parametr H mniejszy od 1 lub wiêkszy od 1000");
		return false;
	}
	else if(m_tmp_parameter["L"] < 1)
	{
		throw std::string("Parametr L mniejszy od 1");
		return false;
	}
	else if(m_tmp_parameter["alpha"] < 0 || m_tmp_parameter["alpha"] > 1)
	{
		throw std::string("Alpha spoza przedzia³u 0,1");
		return false;
	}
	else if(m_tmp_parameter["ro"] < 0 || m_tmp_parameter["ro"] > 1)
	{
		throw std::string("Ro spoza przedzia³u 0,1");
		return false;
	}
	else if(m_tmp_parameter["ro"] < 0 || m_tmp_parameter["ro"] > 1)
	{
		throw std::string("Ro spoza przedzia³u 0,1");
		return false;
	}
	else if(m_tmp_parameter["rankA"] < 1)
	{
		throw std::string("Rozmiar Wielomianu A");
		return false;
	}
	else if(m_tmp_parameter["rankB"] < 0)
	{
		throw std::string("Rozmiar Wielomianu B");
		return false;
	}
	else if(m_tmp_parameter["lambda"] < 0 || m_tmp_parameter["lambda"] > 1)
	{
		throw std::string("Lambda spoza przedzia³u 0,1");
		return false;
	}

	return true;
}

/**
 * Start identifaction with default initial data
 *
 * @return		void
 */
void RegulatorGPC::start_identification()
{
	m_identify = new Identification;
	m_identify->set_parameters(m_rankA,m_rankB,m_lambda,0.00001,100);
	m_identify->identify();
	m_initial_steps_left = 1;
}