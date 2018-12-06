#include "Equalizer.h"
#include "Biquad.h"


Equalizer::Equalizer(int Fs):Filter(Fs)
{
	numberOfBiquads = 4;
	init_biquads(numberOfBiquads);
}

Equalizer::~Equalizer()
{
}

void Equalizer::set_biquad(int n, double Fc, double Q, double peakGain)
{
	if (n >= numberOfBiquads)
	{
		throw ("'n' must be lower than '%s'", numberOfBiquads);
	}
	biquads[n].setBiquad(filter_types[n], Fc * this->inv_Fs, Q, peakGain);
}