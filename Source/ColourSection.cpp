/*
  ==============================================================================

    ColourSection.cpp
    Created: 2 Jan 2025 2:38:20pm
    Author:  carlo

  ==============================================================================
*/

#include "ColourSection.h"


ColourSection::ColourSection(int rowID, ValueTree& gradientTree) : gradientSection(rowID, gradientTree) {
	addAndMakeVisible(gradientSection);
}

void ColourSection::resized() {
	gradientSection.setBounds(getLocalBounds().withHeight(getRequiredHeight()));
}

void ColourSection::setRowHeight(int _rowHeight) {
	rowHeight = _rowHeight;
	gradientSection.setRowHeight(_rowHeight);
}

int ColourSection::getNumRows() {
	return numRows;
}

int ColourSection::getRequiredHeight() {
	return numRows * rowHeight;
}


