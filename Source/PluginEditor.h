/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Biquad.h"
#include "processing.h"
#include <complex>

#define N 1024
#define NN 3
#define M_PI 3.14159265358979323846

//==============================================================================
/**
*/
class AFiltersAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    AFiltersAudioProcessorEditor (AFiltersAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~AFiltersAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
	void resized() override;
	void draw_spect(Graphics & g, Rectangle<int> bounds, Biquad filter1, Biquad filter2, Biquad filter3, Biquad filter4, Slider * sl11, Slider * sl12, Slider * sl13, Slider * sl21, Slider * sl22, Slider * sl23, Slider * sl31, Slider * sl32, Slider * sl33, Slider * sl41, Slider * sl42, Slider * sl43);

private:
	FreqVec fv = FreqVec(N, 20, 20000);
	Rectangle<int> spect1_offset;
	Rectangle<int> spect2_offset;

	Biquad Filter1 = Biquad();
	Biquad Filter2 = Biquad();
	Biquad Filter3 = Biquad();
	Biquad Filter4 = Biquad();
	Biquad Filter5 = Biquad();
	Biquad Filter6 = Biquad();
	Biquad Filter7 = Biquad();
	Biquad Filter8 = Biquad();

	int tbw = 120;
	int tbh = 60;
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	AudioProcessorValueTreeState& valueTreeState;
    AFiltersAudioProcessor& processor;

	Slider s11;
	Slider s12;
	Slider s13;
	Slider s21;
	Slider s22;
	Slider s23;
	Slider s31;
	Slider s32;
	Slider s33;
	Slider s41;
	Slider s42;
	Slider s43;
	Slider s51;
	Slider s52;
	Slider s53;
	Slider s61;
	Slider s62;
	Slider s63;
	Slider s71;
	Slider s72;
	Slider s73;
	Slider s81;
	Slider s82;
	Slider s83;

	Slider s_cross;
	Slider s_first;
	Slider s_second;
	

	std::unique_ptr<SliderAttachment> sa11;
	std::unique_ptr<SliderAttachment> sa12;
	std::unique_ptr<SliderAttachment> sa13;
	std::unique_ptr<SliderAttachment> sa21;
	std::unique_ptr<SliderAttachment> sa22;
	std::unique_ptr<SliderAttachment> sa23;
	std::unique_ptr<SliderAttachment> sa31;
	std::unique_ptr<SliderAttachment> sa32;
	std::unique_ptr<SliderAttachment> sa33;
	std::unique_ptr<SliderAttachment> sa41;
	std::unique_ptr<SliderAttachment> sa42;
	std::unique_ptr<SliderAttachment> sa43;
	std::unique_ptr<SliderAttachment> sa51;
	std::unique_ptr<SliderAttachment> sa52;
	std::unique_ptr<SliderAttachment> sa53;
	std::unique_ptr<SliderAttachment> sa61;
	std::unique_ptr<SliderAttachment> sa62;
	std::unique_ptr<SliderAttachment> sa63;
	std::unique_ptr<SliderAttachment> sa71;
	std::unique_ptr<SliderAttachment> sa72;
	std::unique_ptr<SliderAttachment> sa73;
	std::unique_ptr<SliderAttachment> sa81;
	std::unique_ptr<SliderAttachment> sa82;
	std::unique_ptr<SliderAttachment> sa83;

	std::unique_ptr<SliderAttachment> sa_cross;
	std::unique_ptr<SliderAttachment> sa_first;
	std::unique_ptr<SliderAttachment> sa_second;


	Rectangle<int> set_filter_bounds(Rectangle<int> area, Slider* s1, Slider* s2, Slider* s3, Slider* s4, Slider* s5, Slider* s6, Slider* s7, Slider* s8, Slider* s9, Slider* s10, Slider* s11, Slider* s12);
	void AFiltersAudioProcessorEditor::setup_slider(Slider *s, const char* sn, std::unique_ptr<SliderAttachment>* sa);
	void AFiltersAudioProcessorEditor::setup_slider2(Slider * s, const char * sn, std::unique_ptr<SliderAttachment>* sa, Slider::SliderStyle slider_style);
	void sliderValueChanged(Slider* slider) override;
    

	//Rectangle<int> spectra1Bounds = Rectangle<int>(0,0,0,0);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AFiltersAudioProcessorEditor)
};
