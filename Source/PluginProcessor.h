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
#include "Filter.h"
#include "Equalizer.h"
#include "LinkedFilter.h"


//==============================================================================
/**
*/
class AFiltersAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AFiltersAudioProcessor();
    virtual ~AFiltersAudioProcessor();

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
	const int number_of_filters = 2;
	AudioProcessorValueTreeState parameters;
	std::vector<FilterBaseClass*> filtereenos;
	std::vector<Equalizer*> eqs1;
	std::vector<Equalizer*> eqs2;
	std::vector<LinkedFilter*> lfs1;
	std::vector<LinkedFilter*> lfs2;

	float tmp;
	float in;
	int Fs = 48000;
	Equalizer Eq1 = Equalizer(Fs);
	Equalizer Eq2 = Equalizer(Fs);
	LinkedFilter LF1 = LinkedFilter(Fs);
	LinkedFilter LF2 = LinkedFilter(Fs);
	FilterBaseClass * filter1;
	FilterBaseClass * filter2;
	MidiHandl mh;
	std::unordered_map<int, String> midi_cc;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AFiltersAudioProcessor)
};
