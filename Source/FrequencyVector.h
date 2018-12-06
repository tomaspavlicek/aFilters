#pragma once
#include <vector>
class FrequencyVector {
public:
	FrequencyVector(int vector_size, int min, int max);
	~FrequencyVector();
	std::vector<double> get_p_freq_vec();
	double get_element(int i);
protected:
	std::vector<double> freq_array;
	int arraysize;

};

