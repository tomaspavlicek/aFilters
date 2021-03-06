#include "LinkedFilter.h"



LinkedFilter::LinkedFilter(int Fs):FilterBaseClass(Fs)
{
	this->numberOfBiquads = 2;
	init_biquads(numberOfBiquads);
}


LinkedFilter::~LinkedFilter()
{
}

void LinkedFilter::set_filter(int n, double freq, double Q, double width)
{
	if (n == 0) {
		f2 = freq * width;
		if (f2 >= this->Fs__2) {
			f2 = this->Fs__2-1;
		}
		biquads[0].setBiquad(this->filter_types[0], freq * this->inv_Fs, Q, -3);
		biquads[1].setBiquad(this->filter_types[1], f2 * this->inv_Fs, Q, -3);
	}
}

void LinkedFilter::set_sliders(Slider* s1, Slider* s2, Slider* s3, Slider* s4, Slider* s5, Slider* s6, Slider* s7, Slider* s8, Slider* s9, Slider* s10, Slider* s11, Slider* s12)
{
	s1->setNormalisableRange(NormalisableRange<double>(2.0f, 5.0f, 0.001f, 0.2, false));
	s1->setAlpha(1.0);
	s1->setEnabled(true);

	s2->setAlpha(1.0);
	s2->setEnabled(true);

	s3->setAlpha(1.0);
	s3->setEnabled(true);

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

void LinkedFilter::set_slider(Slider* s)
{
	s->setAlpha(0.5);
	s->setEnabled(false);
}