// ---------------------------------------------------------------------------------
// Filename:	setpointGenerator.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		setpointGenerator
// ---------------------------------------------------------------------------------

public class setpointGenerator
{
	bool m_enable_sinus, m_enable_step

    struct {
        double amplitude, frequency;
    } sinus;

	struct {
        double amplitude, frequency;
    } triangle;

    struct {
        double value;
        int time;
    } step;

	struct {
        double amplitude, frequency, fill;
    } rectangle;

	int m_time;

	public:
		setpointGenerator(void);
		virtual ~setpointGenerator(void);

		double get_value() const;
		void update();
};

