#pragma once
#include "c:\VST\JUCE530\JUCE\projects\aFilters\Source\Filterz.h"
#include "Filter.h"
#include <map>

class Equalizer:
	public Filter
{
public:
	Equalizer(int Fs);
	~Equalizer();
	void set_biquad(int n, double Fc, double Q, double peakGain);
private:
	std::map<int, int> filter_types = { {0, bq_type_lowshelf}, {1, bq_type_peak}, {2, bq_type_peak}, {3, bq_type_highshelf } };
};

