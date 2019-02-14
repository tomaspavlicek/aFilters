#pragma once
#include "c:\VST\JUCE530\JUCE\projects\aFilters\Source\Filterz.h"
#include "Filter.h"
#include <map>

class Equalizer:
	public FilterBaseClass
{
public:
	Equalizer(int Fs);
	~Equalizer();
	void set_filter(int n, double Fc, double Q, double peakGain);
	void set_sliders(Slider* s1, Slider* s2, Slider* s3, Slider* s4, Slider* s5, Slider* s6, Slider* s7, Slider* s8, Slider* s9, Slider* s10, Slider* s11, Slider* s12);
	void set_slider(Slider* s1);
private:
	std::map<int, int> filter_types = { {0, bq_type_lowshelf}, {1, bq_type_peak}, {2, bq_type_peak}, {3, bq_type_highshelf } };
};

