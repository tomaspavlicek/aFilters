#include "Equalizer.h"
#include "Biquad.h"


Equalizer::Equalizer(int Fs):FilterBaseClass(Fs)
{
	this->numberOfBiquads = 4;
	init_biquads(numberOfBiquads);
}

Equalizer::~Equalizer()
{
}

void Equalizer::set_filter(int n, double Fc, double Q, double peakGain)
{
	if (n >= this->numberOfBiquads)
	{
		throw ("'n' must be lower than '%s'", this->numberOfBiquads);
	}
	biquads[n].setBiquad(this->filter_types[n], Fc * this->inv_Fs, Q, peakGain);
}

void Equalizer::set_sliders(Slider* s1, Slider* s2, Slider* s3, Slider* s4, Slider* s5, Slider* s6, Slider* s7, Slider* s8, Slider* s9, Slider* s10, Slider* s11, Slider* s12)
{
	set_slider(s4);
	set_slider(s5);
	set_slider(s6);
	set_slider(s7);
	set_slider(s8);
	set_slider(s9);
	set_slider(s10);
	set_slider(s11);
	set_slider(s12);
}

void Equalizer::set_slider(Slider* s) 
{
	s->setAlpha(1.0);
	s->setEnabled(true);
}