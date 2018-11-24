/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MidiHandl.h"

//==============================================================================
AFiltersAudioProcessor::AFiltersAudioProcessor()
	: parameters(*this, nullptr),
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	NormalisableRange<float> slr = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);
	NormalisableRange<float> gnr = NormalisableRange<float>(-15.0f, 15.0f, 0.01f);
	NormalisableRange<float> fnr = NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2, false);
	NormalisableRange<float> qnr = NormalisableRange<float>(0.1f, 100.0f, 0.01f, 0.2, false);

	parameters.createAndAddParameter("s_cross", "Cross", "", slr, 0.5, nullptr, nullptr);
	parameters.createAndAddParameter("s_first", "Att", "", slr, 1.0, nullptr, nullptr);
	parameters.createAndAddParameter("s_second", "Att", "", slr, 1.0, nullptr, nullptr);

	parameters.createAndAddParameter("sl11", "Sl11", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl21", "Sl21", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl31", "Sl31", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl41", "Sl41", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl51", "Sl51", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl61", "Sl61", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl71", "Sl71", " dB", gnr, 0.0, nullptr, nullptr);
	parameters.createAndAddParameter("sl81", "Sl81", " dB", gnr, 0.0, nullptr, nullptr);

	parameters.createAndAddParameter("sl12", "Sl12", " Hz", fnr, 200, nullptr, nullptr);
	parameters.createAndAddParameter("sl22", "Sl22", " Hz", fnr, 1000, nullptr, nullptr);
	parameters.createAndAddParameter("sl32", "Sl32", " Hz", fnr, 5000, nullptr, nullptr);
	parameters.createAndAddParameter("sl42", "Sl42", " Hz", fnr, 10000, nullptr, nullptr);
	parameters.createAndAddParameter("sl52", "Sl52", " Hz", fnr, 200, nullptr, nullptr);
	parameters.createAndAddParameter("sl62", "Sl62", " Hz", fnr, 1000, nullptr, nullptr);
	parameters.createAndAddParameter("sl72", "Sl72", " Hz", fnr, 5000, nullptr, nullptr);
	parameters.createAndAddParameter("sl82", "Sl82", " Hz", fnr, 10000, nullptr, nullptr);

	parameters.createAndAddParameter("sl13", "Sl13", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl23", "Sl23", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl33", "Sl33", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl43", "Sl43", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl53", "Sl53", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl63", "Sl63", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl73", "Sl73", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.createAndAddParameter("sl83", "Sl83", "", qnr, 1 / sqrt(2), nullptr, nullptr);
	parameters.state = ValueTree(Identifier("aFiltersVT"));

	mh = MidiHandl(&parameters);
	midi_cc[76] = "sl11";
	midi_cc[77] = "sl12";


	for (size_t i = 0; i < getTotalNumInputChannels(); i++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			filtereenos.push_back(Biquad());
		}
	}


}

AFiltersAudioProcessor::~AFiltersAudioProcessor()
{
}

//==============================================================================
const String AFiltersAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AFiltersAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AFiltersAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AFiltersAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AFiltersAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AFiltersAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AFiltersAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AFiltersAudioProcessor::setCurrentProgram (int index)
{
}

const String AFiltersAudioProcessor::getProgramName (int index)
{
    return {};
}

void AFiltersAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AFiltersAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AFiltersAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AFiltersAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AFiltersAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	// midi
	int time;
	MidiMessage m;
	const float den = 1.0 / 127;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		if (m.isController())
		{
			if (midi_cc.find(m.getControllerNumber()) != midi_cc.end())
			{
				parameters.getParameter(midi_cc[m.getControllerNumber()])->setValue(m.getControllerValue() * den);
			}
		}
	}
	const int Fs = getSampleRate();
	for (size_t i = 0; i < getNumInputChannels(); i++)
	{
		int filter_offset = i* number_of_filters;
		filtereenos[filter_offset].setBiquad(bq_type_lowshelf, *parameters.getRawParameterValue("sl12") / Fs, *parameters.getRawParameterValue("sl13"), *parameters.getRawParameterValue("sl11"));
		filtereenos[filter_offset + 1].setBiquad(bq_type_peak, *parameters.getRawParameterValue("sl22") / Fs, *parameters.getRawParameterValue("sl23"), *parameters.getRawParameterValue("sl21"));
		filtereenos[filter_offset + 2].setBiquad(bq_type_peak, *parameters.getRawParameterValue("sl32") / Fs, *parameters.getRawParameterValue("sl33"), *parameters.getRawParameterValue("sl31"));
		filtereenos[filter_offset + 3].setBiquad(bq_type_highshelf, *parameters.getRawParameterValue("sl42") / Fs, *parameters.getRawParameterValue("sl43"), *parameters.getRawParameterValue("sl41"));
		filtereenos[filter_offset + 4].setBiquad(bq_type_lowshelf, *parameters.getRawParameterValue("sl52") / Fs, *parameters.getRawParameterValue("sl53"), *parameters.getRawParameterValue("sl51"));
		filtereenos[filter_offset + 5].setBiquad(bq_type_peak, *parameters.getRawParameterValue("sl62") / Fs, *parameters.getRawParameterValue("sl63"), *parameters.getRawParameterValue("sl61"));
		filtereenos[filter_offset + 6].setBiquad(bq_type_peak, *parameters.getRawParameterValue("sl72") / Fs, *parameters.getRawParameterValue("sl73"), *parameters.getRawParameterValue("sl71"));
		filtereenos[filter_offset + 7].setBiquad(bq_type_highpass, *parameters.getRawParameterValue("sl82") / Fs, *parameters.getRawParameterValue("sl83"), *parameters.getRawParameterValue("sl81"));
	}
	float fw1 = *parameters.getRawParameterValue("s_first");
	float fw2 = *parameters.getRawParameterValue("s_second");
	float xf = *parameters.getRawParameterValue("s_cross");
	float wetf1 = fw1 * xf * 0.25;  // 0.25 is weight of each  paralel sos system (4 sos per filter)
	float wetf2 = fw2 * (1 - xf) * 0.25;
	float dry = 1 - xf * fw1 + xf * fw2 - fw2;

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		int filter_offset = channel * number_of_filters;
        //auto* channelData = buffer.getWritePointer (channel);
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
			in = buffer.getSample(channel, sample);
			tmp = dry * in;
			tmp += wetf1 * filtereenos[filter_offset].process(in);
			tmp += wetf1 * filtereenos[filter_offset + 1].process(in);
			tmp += wetf1 * filtereenos[filter_offset + 2].process(in);
			tmp += wetf1 * filtereenos[filter_offset + 3].process(in);
			tmp += wetf2 * filtereenos[filter_offset + 4].process(in);
			tmp += wetf2 * filtereenos[filter_offset + 5].process(in);
			tmp += wetf2 * filtereenos[filter_offset + 6].process(in);
			tmp += wetf2 * filtereenos[filter_offset + 7].process(in);
			buffer.setSample(channel, sample, tmp);
		}
        
    }
}

//==============================================================================
bool AFiltersAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AFiltersAudioProcessor::createEditor()
{
    return new AFiltersAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void AFiltersAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void AFiltersAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AFiltersAudioProcessor();
}
