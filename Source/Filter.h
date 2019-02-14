#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Biquad.h"
#include <complex>
#include "FrequencyVector.h"

#define spectrum_length 1024
#define filter_order 3
#define M_PI 3.14159265358979323846

class FilterBaseClass
{
public:
	FilterBaseClass(int Fs);
	virtual ~FilterBaseClass() = 0;
	float process(float in);
	Path get_spectrum(Rectangle<int> offset);
	//virtual int get_number_of_biquads();
    //virtual void set_biquad(int n, double Fc, double Q, double peakGain);
	virtual void set_filter(int n, double Fc, double Q, double peakGain) = 0;
	virtual void set_sliders(Slider* s1, Slider* s2, Slider* s3, Slider* s4, Slider* s5, Slider* s6, Slider* s7, Slider* s8, Slider* s9, Slider* s10, Slider* s11, Slider* s12) = 0;
	//virtual KnobSettings get_knob_settings();
protected:
	std::vector<Biquad> biquads;
	int numberOfBiquads;

	void init_biquads(int numberOfBiquads);
	void compute_spectrum(std::tuple<double, double, double, double, double> coefs, double * spectrum);
	std::complex<double> polyval(double *p, int n, std::complex<double> x);
	int Fs;
	double inv_Fs;
	double k_2pi__Fs;
	FrequencyVector freqVec;
	const int gain = 5;
	std::complex<double> ci = std::complex<double>(0, 1);
	Point<float> point;
	Path spectrum_path;
};