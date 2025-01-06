/*
  ==============================================================================

    ColourSection.h
    Created: 31 Dec 2024 8:50:38am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"
#include "GradientSection.h"

using namespace constants;

class ColourSection : public juce::Component {
public:
	ColourSection(int rowID, ValueTree& masterTree);

	void resized() override;

	void setRowHeight(int _rowHeight);

	int getNumRows();

	int getRequiredHeight();

private:
	int rowHeight = 0;
	int numRows = 6 + 12;// 4 sliders + magic number
	GradientSection gradientSection;
};
