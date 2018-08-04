#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Biquad.h"
#include "PluginEditor.h"

class FilterPanel: 
{
public:
	FilterPanel::FilterPanel(AudioProcessorValueTreeState& valueTreeState, AFiltersAudioProcessorEditor ape);
	~FilterPanel();
private:
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	void addSlider(Slider& s, const char* sn, AudioProcessorValueTreeState& valueTreeState);
	void sliderValueChanged(Slider* slider) override;

	//AFiltersAudioProcessorEditor *ape;
	//AudioProcessorValueTreeState vts;

	const int sl_width = 100;
	const int sl_height = 30;



	/*std::unique_ptr<SliderAttachment> sl11a;
	std::unique_ptr<SliderAttachment> sl12a;
	std::unique_ptr<SliderAttachment> sl13a;
	std::unique_ptr<SliderAttachment> sl21a;
	std::unique_ptr<SliderAttachment> sl22a;
	std::unique_ptr<SliderAttachment> sl23a;
	std::unique_ptr<SliderAttachment> sl31a;
	std::unique_ptr<SliderAttachment> sl32a;
	std::unique_ptr<SliderAttachment> sl33a;
	std::unique_ptr<SliderAttachment> sl41a;
	std::unique_ptr<SliderAttachment> sl42a;
	std::unique_ptr<SliderAttachment> sl43a;*/

	Biquad *Filter1 = new Biquad();
	Biquad *Filter2 = new Biquad();
	Biquad *Filter3 = new Biquad();
	Biquad *Filter4 = new Biquad();

	std::tuple<double, double, double, double, double> coefs1;
	std::tuple<double, double, double, double, double> coefs2;
	std::tuple<double, double, double, double, double> coefs3;
	std::tuple<double, double, double, double, double> coefs4;
};
