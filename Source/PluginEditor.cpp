/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#pragma once
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <complex>
#include <math.h>
#include <iostream>
#include "processing.h"



//==============================================================================
AFiltersAudioProcessorEditor::AFiltersAudioProcessorEditor (AFiltersAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	
	
	setup_slider2(&s_cross, "s_cross", &sa_cross, Slider::LinearVertical);
	setup_slider2(&s_first, "s_first", &sa_first, Slider::LinearVertical);
	setup_slider2(&s_second, "s_second", &sa_second, Slider::LinearVertical);
	setup_slider(&s11, "sl11", &sa11);
	setup_slider(&s12, "sl12", &sa12);
	setup_slider(&s13, "sl13", &sa13);
	setup_slider(&s21, "sl21", &sa21);
	setup_slider(&s22, "sl22", &sa22);
	setup_slider(&s23, "sl23", &sa23);
	setup_slider(&s31, "sl31", &sa31);
	setup_slider(&s32, "sl32", &sa32);
	setup_slider(&s33, "sl33", &sa33);
	setup_slider(&s41, "sl41", &sa41);
	setup_slider(&s42, "sl42", &sa42);
	setup_slider(&s43, "sl43", &sa43);
	setup_slider(&s51, "sl51", &sa51);
	setup_slider(&s52, "sl52", &sa52);
	setup_slider(&s53, "sl53", &sa53);
	setup_slider(&s61, "sl61", &sa61);
	setup_slider(&s62, "sl62", &sa62);
	setup_slider(&s63, "sl63", &sa63);
	setup_slider(&s71, "sl71", &sa71);
	setup_slider(&s72, "sl72", &sa72);
	setup_slider(&s73, "sl73", &sa73);
	setup_slider(&s81, "sl81", &sa81);
	setup_slider(&s82, "sl82", &sa82);
	setup_slider(&s83, "sl83", &sa83);

	addAndMakeVisible(&s11);
	addAndMakeVisible(&s12);
	addAndMakeVisible(&s13);
	addAndMakeVisible(&s21);
	addAndMakeVisible(&s22);
	addAndMakeVisible(&s23);
	addAndMakeVisible(&s31);
	addAndMakeVisible(&s32);
	addAndMakeVisible(&s33);
	addAndMakeVisible(&s41);
	addAndMakeVisible(&s42);
	addAndMakeVisible(&s43);
	addAndMakeVisible(&s51);
	addAndMakeVisible(&s52);
	addAndMakeVisible(&s53);
	addAndMakeVisible(&s61);
	addAndMakeVisible(&s62);
	addAndMakeVisible(&s63);
	addAndMakeVisible(&s71);
	addAndMakeVisible(&s72);
	addAndMakeVisible(&s73);
	addAndMakeVisible(&s81);
	addAndMakeVisible(&s82);
	addAndMakeVisible(&s83);
	addAndMakeVisible(&s_cross);
	addAndMakeVisible(&s_first);
	addAndMakeVisible(&s_second);
	setSize(1800, 800);
	setResizable(true, true);
}

AFiltersAudioProcessorEditor::~AFiltersAudioProcessorEditor()
{

}

//==============================================================================
void AFiltersAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::black);
	g.setColour(Colours::cyan);
	draw_spect(g, spect1_offset, Filter1, Filter2, Filter3, Filter4, &s11, &s12, &s13, &s21, &s22, &s23, &s31, &s32, &s33, &s41, &s42, &s43);
	draw_spect(g, spect2_offset, Filter5, Filter6, Filter7, Filter8, &s51, &s52, &s53, &s61, &s62, &s63, &s71, &s72, &s73, &s81, &s82, &s83);

}

void AFiltersAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();
	auto weight_slider_width = area.getWidth() / 15;
	s_cross.setBounds(area.removeFromLeft(weight_slider_width));
	auto weight_sliders_area = area.removeFromLeft(weight_slider_width);
	s_first.setBounds(weight_sliders_area.removeFromTop(weight_sliders_area.getHeight() / 2));
	s_second.setBounds(weight_sliders_area);
	spect1_offset = set_filter_bounds(area.removeFromTop(area.getHeight() / 2), &s11, &s12, &s13, &s21, &s22, &s23, &s31, &s32, &s33, &s41, &s42, &s43);
	spect2_offset = set_filter_bounds(area, &s51, &s52, &s53, &s61, &s62, &s63, &s71, &s72, &s73, &s81, &s82, &s83);
	
}

void AFiltersAudioProcessorEditor::draw_spect(Graphics& g, Rectangle<int> bounds, Biquad filter1, Biquad filter2, Biquad filter3, Biquad filter4, Slider* sl11, Slider* sl12, Slider* sl13, Slider* sl21, Slider* sl22, Slider* sl23, Slider* sl31, Slider* sl32, Slider* sl33, Slider* sl41, Slider* sl42, Slider* sl43)
{
	const int Fs = 48000;
	const float Fs_inv = 1 / Fs;
	double spect1[N] = { 0 };

	filter1.setBiquad(bq_type_lowshelf, sl12->getValue() * Fs_inv, sl13->getValue(), sl11->getValue());
	compute_spectrum(spect1, fv.get_p_freq_vec(), filter1.getCoefs());
	filter2.setBiquad(bq_type_peak, sl22->getValue() * Fs_inv, sl23->getValue(), sl21->getValue());
	compute_spectrum(spect1, fv.get_p_freq_vec(), filter2.getCoefs());
	filter3.setBiquad(bq_type_peak, sl32->getValue() * Fs_inv, sl33->getValue(), sl31->getValue());
	compute_spectrum(spect1, fv.get_p_freq_vec(), filter3.getCoefs());
	filter4.setBiquad(bq_type_highshelf, sl42->getValue() * Fs_inv, sl43->getValue(), sl41->getValue());
	compute_spectrum(spect1, fv.get_p_freq_vec(), filter4.getCoefs());


	float x = bounds.getTopLeft().getX();
	float y = bounds.getCentre().getY();
	Point<float> x_tmp;
	Path spectrum1;
	int gain{ 3 };
	spectrum1.startNewSubPath(x , y + gain * spect1[0]);
	for (size_t i = 1; i < N; i++) {
		x_tmp.setX(x + i);
		x_tmp.setY(y + gain * spect1[i]);
		spectrum1.lineTo(x_tmp);
	}
	g.strokePath(spectrum1, PathStrokeType(4));
}

void AFiltersAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	
	repaint();
}

Rectangle<int> AFiltersAudioProcessorEditor::set_filter_bounds(Rectangle<int> area, Slider* s1, Slider* s2, Slider* s3, Slider* s4, Slider* s5, Slider* s6, Slider* s7, Slider* s8, Slider* s9, Slider* s10, Slider* s11, Slider* s12)
{
	int slider_size = area.getHeight()/3;
	Rectangle<int> s1_block = area.removeFromLeft(slider_size);
	s1->setBounds(s1_block.removeFromTop(slider_size));
	s2->setBounds(s1_block.removeFromTop(slider_size));
	s3->setBounds(s1_block.removeFromTop(slider_size));
	Rectangle<int> s2_block = area.removeFromLeft(slider_size);
	s4->setBounds(s2_block.removeFromTop(slider_size));
	s5->setBounds(s2_block.removeFromTop(slider_size));
	s6->setBounds(s2_block.removeFromTop(slider_size));
	Rectangle<int> s3_block = area.removeFromLeft(slider_size);
	s7->setBounds(s3_block.removeFromTop(slider_size));
	s8->setBounds(s3_block.removeFromTop(slider_size));
	s9->setBounds(s3_block.removeFromTop(slider_size));
	Rectangle<int> s4_block = area.removeFromLeft(slider_size);
	s10->setBounds(s4_block.removeFromTop(slider_size));
	s11->setBounds(s4_block.removeFromTop(slider_size));
	s12->setBounds(s4_block.removeFromTop(slider_size));
	return area;
}

void AFiltersAudioProcessorEditor::setup_slider(Slider *s, const char* sn, std::unique_ptr<SliderAttachment>* sa)
{
	sa->reset(new SliderAttachment(this->valueTreeState, sn, *s));
	s->setSliderStyle(Slider::RotaryVerticalDrag);
	s->setTextBoxStyle(Slider::TextBoxBelow, true, tbw, tbh);
	s->addListener(this);
}

void AFiltersAudioProcessorEditor::setup_slider2(Slider *s, const char* sn, std::unique_ptr<SliderAttachment>* sa, Slider::SliderStyle slider_style)
{
	sa->reset(new SliderAttachment(this->valueTreeState, sn, *s));
	s->setSliderStyle(slider_style);
	s->setTextBoxStyle(Slider::TextBoxBelow, true, tbw, tbh);
	s->addListener(this);
}