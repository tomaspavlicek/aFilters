#include "Filter.h"

Filter::Filter(int Fs):freqVec(spectrum_length, 20, 20000)
{
	this->inv_Fs = 1.0 / Fs;
	this->k_2pi__Fs = 2 * M_PI * this->inv_Fs;
}

float Filter::process(float in)
{
	for (size_t n = 0; n < numberOfBiquads; n++)
	{
		in = biquads[n].process(in);
	}
	return in;
}

void Filter::init_biquads(int numberOfBiquads)
{
	for (size_t i = 0; i < numberOfBiquads; i++)
	{
		this->biquads.push_back(Biquad());
	}
}



Path Filter::get_spectrum(Rectangle<int> offset)
{
	double spectrum[spectrum_length] = { 0 }; // TODO change to vector
	for (size_t n = 0; n < numberOfBiquads; n++)
	{
		this->compute_spectrum(this->biquads[n].getCoefs(), spectrum);
	}
	float x = offset.getTopLeft().getX();
	float y = offset.getCentre().getY();
	spectrum_path.startNewSubPath(x, y + gain * spectrum[0]);
	for (size_t i = 1; i < spectrum_length; i++) {
		this->point.setX(x + i);
		this->point.setY(y + gain * spectrum[i]);
		spectrum_path.lineTo(this->point);
	}
	return spectrum_path;
}

void Filter::compute_spectrum(std::tuple<double, double, double, double, double> coefs, double * spectrum) {
	double num[filter_order] = { std::get<2>(coefs),std::get<3>(coefs), std::get<4>(coefs) };
	double den[filter_order] = { 1, std::get<0>(coefs), std::get<1>(coefs) };
	//this->spectrum[spectrum_length] = { 0 };
	for (size_t i = 0; i < spectrum_length; i++)
	{
		spectrum[i] += -20 * log10(std::abs(this->polyval(num, filter_order, std::exp(ci * this->k_2pi__Fs * this->freqVec.get_element(i))) / polyval(den, filter_order, std::exp(ci * k_2pi__Fs * this->freqVec.get_element(i)))));
	}
}

std::complex<double> Filter::polyval(double *p, int n, std::complex<double> x)
{
	if (n < 1) {
		throw ("filter order must be higher than 0 ", numberOfBiquads);
	}
	std::complex<double> y = p[0];
	for (size_t i = 1; i < n; i++)
	{
		y = x * y + p[i];
	}
	return y;
}
