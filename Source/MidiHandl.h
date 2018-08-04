#pragma once
#include <map>
#include "../JuceLibraryCode/JuceHeader.h"

class MidiHandl
{
public:
	MidiHandl();
	MidiHandl(AudioProcessorValueTreeState *vts);
	void setParam(MidiMessage m);
	~MidiHandl();
private:
	AudioProcessorValueTreeState *parameters;
	std::map<int, juce::StringRef> midiDct = {
		{70, "sl11"},
		{71, "sl12" },
		{72, "sl21"},
		{73, "sl22"},
		{74, "sl23"},
		{75, "sl31"},
		{76, "sl32"},
		{77, "sl33"}
	};
};
