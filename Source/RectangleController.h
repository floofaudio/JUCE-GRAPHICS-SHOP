/*
  ==============================================================================

    RectangleController.h
    Created: 5 Jan 2025 4:16:11am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include "Utils.h"
#include "SliderWithListener.h"

using namespace constants;

class RectangleController : public juce::Component {
public:
	RectangleController(int rowID, ValueTree& masterTree);

	void paint(juce::Graphics& g) override;

	void resized() override;

	int getNumRows();

	void setRowHeight(int _rowHeight);

	int getRowHeight() { return rowHeight; }

	int getRequiredHeight();

private:
	int numRows = 2;
	int numSliders = 1;
	int rowHeight = 0;
	OwnedArray<SliderWithListener> sliders;
	OwnedArray<Label> sliderLabels;
	ToggleButton isRoundedToggle;
	Label header;

};
