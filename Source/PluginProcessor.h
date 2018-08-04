/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Biquad.h"
#include "MidiHandl.h"
#include <unordered_map>


//==============================================================================
/**
*/
class AFiltersAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AFiltersAudioProcessor();
    ~AFiltersAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
	const int number_of_filters = 8;
	AudioProcessorValueTreeState parameters;
	std::vector<Biquad> filtereenos;
	Biquad lsFilter1 = Biquad();
	Biquad pFilter11 = Biquad();
	Biquad pFilter12 = Biquad();
	Biquad hsFilter1 = Biquad();
	Biquad lsFilter2 = Biquad();
	Biquad pFilter21 = Biquad();
	Biquad pFilter22 = Biquad();
	Biquad hsFilter2 = Biquad();
	float tmp;
	float in;
	MidiHandl mh;
	std::unordered_map<int, String> midi_cc;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AFiltersAudioProcessor)
};
