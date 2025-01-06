/*
  ==============================================================================

    ColourSection.cpp
    Created: 2 Jan 2025 2:38:20pm
    Author:  carlo

  ==============================================================================
*/

#include "ColourSection.h"


ColourSection::ColourSection(int rowID, ValueTree& gradientTree) : gradientSection(rowID, gradientTree) {
	//if (componentTree.isValid()) DBG("COMPO");
	//ValueTree componentsTree = masterTree.getChildWithName(COMPONENTS_TREE);
	//ValueTree componentTree = componentsTree.getChildWithProperty(ID, rowID);
	//int nChildren = componentTree.getNumChildren();
	//DBG("num children from ColourSelector: " + String(nChildren));

	//ValueTree& gradientTree = componentTree.getChildWithName(GRADIENT_TREE);
	//DBG("num props gradient section: " + String(gradientTree.getNumProperties()));
	addAndMakeVisible(gradientSection);
}

void ColourSection::resized() {
	//tabbedComponent.setBounds(getLocalBounds().withHeight(getRequiredHeight()));
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


