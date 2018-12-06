#include "FrequencyVector.h"

FrequencyVector::FrequencyVector(int vector_size, int min, int max) {
	double lmin = log10(min);
	double step = double(log10(max) - lmin) / double(vector_size - 1);
	freq_array.push_back(min);
	for (size_t i = 1; i < vector_size - 1; i++)
	{
		freq_array.push_back(pow(10, (lmin + i*step)));
	}
	freq_array.push_back(max);
}

std::vector<double> FrequencyVector::get_p_freq_vec()
{
	return this->freq_array;
}

double FrequencyVector::get_element(int i)
{
	return this->freq_array.at(i);
}


FrequencyVector::~FrequencyVector()
{
}