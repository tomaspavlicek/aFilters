#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Biquad.h"
#include <complex>
#include "FrequencyVector.h"

#define spectrum_length 1024
#define filter_order 3
#define M_PI 3.14159265358979323846

class Filter
{
public:
	Filter(int Fs);
	float process(float in);
	Path get_spectrum(Rectangle<int> offset);
	//virtual void set_biquad(int n, double Fc, double Q, double peakGain);
protected:
	std::vector<Biquad> biquads;
	int numberOfBiquads;

	void init_biquads(int numberOfBiquads);
	void compute_spectrum(std::tuple<double, double, double, double, double> coefs, double * spectrum);
	std::complex<double> polyval(double *p, int n, std::complex<double> x);
	double inv_Fs;
	double k_2pi__Fs;
	FrequencyVector freqVec;
	//double spectrum[spectrum_length] = { 0 };  // TODO - zbavit se tohoto a vykreslit spectrum
	const int gain = 5;
	std::complex<double> ci = std::complex<double>(0, 1);
	Point<float> point;
	Path spectrum_path;
};