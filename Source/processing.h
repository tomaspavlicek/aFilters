#ifndef __PROCESSING__
#define __PROCESSING__

#include <tuple>
#include <complex>
#include <vector>

void compute_spectrum(double *p, std::vector<double> fv, std::tuple<double, double, double, double, double> coefs);
std::complex<double> polyval(double *p, int n, std::complex<double> x);
class FreqVec {
public:
	FreqVec(int vector_size, int min, int max);
	std::vector<double> get_p_freq_vec();
protected:
	std::vector<double> freq_array;
	int arraysize;

};

#endif // !__PROCESSING__

