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
	NormalisableRange<double> gnr = NormalisableRange<double>(-15.0f, 15.0f, 0.01f);
	NormalisableRange<double> fnr = NormalisableRange<double>(20.0f, 20000.0f, 1.0f, 0.2, false);
	NormalisableRange<double> qnr = NormalisableRange<double>(0.1f, 100.0f, 0.01f, 0.2, false);
	s1->setNormalisableRange(gnr);
	s2->setNormalisableRange(fnr);
	s3->setNormalisableRange(qnr);
	s4->setNormalisableRange(gnr);
	s5->setNormalisableRange(fnr);
	s6->setNormalisableRange(qnr);
	s7->setNormalisableRange(gnr);
	s8->setNormalisableRange(fnr);
	s9->setNormalisableRange(qnr);
	s10->setNormalisableRange(gnr);
	s11->setNormalisableRange(fnr);
	s12->setNormalisableRange(qnr);

	set_slider(s1);
	set_slider(s2);
	set_slider(s3);
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