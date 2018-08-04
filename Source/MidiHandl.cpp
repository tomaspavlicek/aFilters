#include "midiHandl.h"

MidiHandl::MidiHandl()
{
}

MidiHandl::MidiHandl(AudioProcessorValueTreeState *vts)
{
	this->parameters = vts;
}

void MidiHandl::setParam(MidiMessage m)
{
	if (m.isController())
	{
		int n = m.getControllerNumber();
		if (midiDct.find(n) != midiDct.end()) 
		{
			parameters->getParameter(midiDct.at(n))->setValueNotifyingHost(float(m.getControllerValue()) / 127);
		}
	}
}


MidiHandl::~MidiHandl()
{
}
