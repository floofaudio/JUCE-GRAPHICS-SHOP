/*
  ==============================================================================

    TransformSection.h
    Created: 31 Dec 2024 8:04:21am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"
#include "SliderWithListener.h"

using namespace constants;

class TransformSection : public juce::Component {
public:
	TransformSection(int rowID, ValueTree& masterTree);

	void paint(juce::Graphics& g) override;

	void resized() override;

	int getNumRows();

	void setRowHeight(int _rowHeight);

	int getRowHeight() { return rowHeight; }

	int getRequiredHeight();

private:
	int numRows = 5;
	int numSliders = 4;
	int rowHeight = 0;
	OwnedArray<SliderWithListener> sliders;
	OwnedArray<Label> sliderLabels;
	Label header;

};
