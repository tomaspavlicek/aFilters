#pragma once
#include "Biquad.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include <complex>
#include "FrequencyVector.h"

#define N 1024
#define filter_order 3
#define M_PI 3.14159265358979323846

enum {
	linked = 1,
	equalizer
};

class Filterz
{
public:
	Filterz(int Fs);
	~Filterz();
	void setMode(int mode);
	void setBiquad(int n, double Fc, double Q, double peakGain);
	float process(float in);
	Path get_spectrum(Rectangle<int> offset);
private:
	FrequencyVector freqVec = FrequencyVector(N, 20, 20000);
	double inv_Fs;
	double spectrum[N] = { 0 };
	const double default_quality = 1 / sqrt(2);
	const double default_attenuation = 0.0;
	double k_2pi__Fs;
	void setDefaults();
	std::map<std::pair<int, int>, std::tuple<int, float, float, float>> default_values;
	const int numberOfBiquads = 4;
	int mode;
	std::vector<Biquad> biquads;
	void compute_spectrum(std::tuple<double, double, double, double, double> coefs);
	std::complex<double> polyval(double *p, int n, std::complex<double> x);
	Point<float> x_tmp;
	Path spectrum_path;
	int gain{ 3 };
	int attenuation = -60;

	int F1;
	int F2;
	float Q;
	int width;
};




