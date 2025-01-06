/*
  ==============================================================================

    GradientSection.h
    Created: 31 Dec 2024 8:20:16am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"
#include "SliderWithListener.h"
#include "ButtonWithListener.h"

using namespace constants;

class GradientSection : public juce::Component, public ChangeListener {
public:
	GradientSection(int rowID, ValueTree gradientTree);

	~GradientSection();

	void paint(juce::Graphics& g) override;

	void resized() override; 

	void changeListenerCallback(ChangeBroadcaster* source) override;

	int getNumRows();

	void setRowHeight(int _rowHeight);

private:
	int numRows = 6;
	int rowHeight = 0;
	int m_rowID = 0;
	OwnedArray<SliderWithListener> sliders;
	OwnedArray<Label> sliderLabels;
	OwnedArray<ColourSelector> colourSelectors;
	Label header;
	OwnedArray<ButtonWithListener> activeStopButtons;
	ButtonWithListener isOnButton;
	ValueTree m_gradientTree;
	TabbedComponent tabbedColourSelectors;

};
