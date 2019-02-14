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




//==============================================================================
AFiltersAudioProcessorEditor::AFiltersAudioProcessorEditor (AFiltersAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	
	
	setup_slider(&s_cross, "s_cross", &sa_cross, Slider::LinearVertical);
	setup_slider(&s_first, "s_first", &sa_first, Slider::LinearVertical);
	setup_slider(&s_second, "s_second", &sa_second, Slider::LinearVertical);
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
	setupFilterTypeCB(&filterTypeCB1);
	setupFilterTypeCB(&filterTypeCB2);
	filterTypeLabel1.setText(filterTypeCB1.getText(), sendNotificationAsync);
	filterTypeLabel2.setText(filterTypeCB2.getText(), sendNotificationAsync);
	filterTypeButt1.setButtonText("Apply");
	filterTypeButt2.setButtonText("Apply");
	filterTypeButt1.onClick = [this] { buttonClicked(&filterTypeButt1); };
	filterTypeButt2.onClick = [this] { buttonClicked(&filterTypeButt2); };

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
	addAndMakeVisible(&filterTypeLabel1);
	addAndMakeVisible(&filterTypeLabel2);
	addAndMakeVisible(&filterTypeCB1);
	addAndMakeVisible(&filterTypeCB2);
	addAndMakeVisible(&filterTypeButt1);
	addAndMakeVisible(&filterTypeButt2);

	setSize(1800, 800);
	setResizable(true, true);
	
	filter1 = &Eq1;
	filter2 = &Eq2;
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
	draw_spect(g, spect1_offset, filter1, &s11, &s12, &s13, &s21, &s22, &s23, &s31, &s32, &s33, &s41, &s42, &s43);
	draw_spect(g, spect2_offset, filter2, &s51, &s52, &s53, &s61, &s62, &s63, &s71, &s72, &s73, &s81, &s82, &s83);

}

void AFiltersAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();
	auto weight_slider_width = area.getWidth() / 15;
	auto xarea = area.removeFromLeft(weight_slider_width);
	filterTypeLabel1.setBounds(xarea.removeFromTop(tbh));
	filterTypeCB1.setBounds(xarea.removeFromTop(tbh));
	filterTypeButt1.setBounds(xarea.removeFromTop(tbh));
	s_cross.setBounds(xarea.removeFromTop(xarea.getHeight()-3*tbh));
	filterTypeButt2.setBounds(xarea.removeFromTop(tbh));
	filterTypeCB2.setBounds(xarea.removeFromTop(tbh));
	filterTypeLabel2.setBounds(xarea);
	auto weight_sliders_area = area.removeFromLeft(weight_slider_width);
	s_first.setBounds(weight_sliders_area.removeFromTop(weight_sliders_area.getHeight() / 2));
	s_second.setBounds(weight_sliders_area);
	spect1_offset = set_filter_bounds(area.removeFromTop(area.getHeight() / 2), &s11, &s12, &s13, &s21, &s22, &s23, &s31, &s32, &s33, &s41, &s42, &s43);
	spect2_offset = set_filter_bounds(area, &s51, &s52, &s53, &s61, &s62, &s63, &s71, &s72, &s73, &s81, &s82, &s83);
	
}

void AFiltersAudioProcessorEditor::draw_spect(Graphics& g, Rectangle<int> bounds, FilterBaseClass * filterz, Slider* sl11, Slider* sl12, Slider* sl13, Slider* sl21, Slider* sl22, Slider* sl23, Slider* sl31, Slider* sl32, Slider* sl33, Slider* sl41, Slider* sl42, Slider* sl43)
{
	filterz->set_filter(0, sl12->getValue(), sl13->getValue(), sl11->getValue());
	filterz->set_filter(1, sl22->getValue(), sl23->getValue(), sl21->getValue());
	filterz->set_filter(2, sl32->getValue(), sl33->getValue(), sl31->getValue());
	filterz->set_filter(3, sl42->getValue(), sl43->getValue(), sl41->getValue());
	g.strokePath(filterz->get_spectrum(bounds), PathStrokeType(4));
}

void AFiltersAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	repaint();
}

void AFiltersAudioProcessorEditor::buttonClicked(Button * butt)
{
	if (butt == &filterTypeButt1 && fabs(1.0 - s_cross.getValue()) < 0.0001)
	{
		filterTypeLabel1.setText(filterTypeCB1.getText(), sendNotificationAsync);
		setFilterTypes();
	}

	if (butt == &filterTypeButt2 && s_cross.getValue() < 0.0001)
	{
		filterTypeLabel2.setText(filterTypeCB2.getText(), sendNotificationAsync);
		setFilterTypes();
	}
	repaint();
	
}

void AFiltersAudioProcessorEditor::setFilterTypes()
{

	if (filterTypeCB1.getSelectedItemIndex() == 1) {
		filter1 = &LF1;
	} else {
		filter1 = &Eq1;
	}
	filter1->set_sliders(&s11, &s12, &s13, &s21, &s22, &s23, &s31, &s32, &s33, &s41, &s42, &s43);
	if (filterTypeCB2.getSelectedItemIndex() == 1) {
		filter2 = &LF2;
	}
	else {
		filter2 = &Eq2;
		
	}
	filter2->set_sliders(&s51, &s52, &s53, &s61, &s62, &s63, &s71, &s72, &s73, &s81, &s82, &s83);
}


void AFiltersAudioProcessorEditor::setupFilterTypeCB(ComboBox* comboBox)
{
	comboBox->addItem("Equalizer", 1);
	comboBox->addItem("Linked", 2);
	comboBox->setSelectedId(1);
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


void AFiltersAudioProcessorEditor::setup_slider(Slider *s, const char* sn, std::unique_ptr<SliderAttachment>* sa, Slider::SliderStyle slider_style)
{
	sa->reset(new SliderAttachment(this->valueTreeState, sn, *s));
	s->setSliderStyle(slider_style);
	s->setTextBoxStyle(Slider::TextBoxBelow, true, tbw, tbh);
	s->addListener(this);
}
