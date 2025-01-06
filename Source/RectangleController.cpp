/*
  ==============================================================================

    RectangleController.cpp
    Created: 5 Jan 2025 4:17:31am
    Author:  carlo

  ==============================================================================
*/

#include "RectangleController.h"
RectangleController::RectangleController(int rowID, ValueTree& masterTree) {
	ValueTree componentsTree = masterTree.getChildWithName(COMPONENTS_TREE);
	ValueTree componentTree = componentsTree.getChildWithProperty(ID, rowID);
	ValueTree rectangleTree = componentTree.getChildWithName(RECTANGLE_TREE);

	addAndMakeVisible(isRoundedToggle);

	Array sliderIDs{ CORNER};
	StringArray labelTexts{ "Corner" };
	for (int i = 0; i < sliderIDs.size(); i++) {
		// add labels
		auto* label = new Label();
		label->setText(labelTexts[i], juce::dontSendNotification);
		sliderLabels.add(label);
		addAndMakeVisible(label);

		// get value from tree
		int val = rectangleTree.getProperty(sliderIDs[i]);

		auto* slider = new SliderWithListener(rectangleTree, sliderIDs[i]);
		slider->setRange(0, 100, 1); // represents percentage
		slider->setValue(val);
		slider->setComponentID(sliderIDs[i].toString());
		slider->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		sliders.add(slider);
		addAndMakeVisible(slider);
	}

	addAndMakeVisible(header);
	header.setText("Rectangle", juce::dontSendNotification);
}


void RectangleController::paint(juce::Graphics& g) {
	g.fillAll(GREY1);
}

void RectangleController::resized() {
	auto bounds = getLocalBounds();
	header.setBounds(bounds.removeFromTop(rowHeight));
	int y = bounds.getY();
	int labelWidth = getWidth() * 0.2f;
	for (int i = 0; i < sliders.size(); ++i) {
		sliderLabels[i]->setBounds(0, y, labelWidth, rowHeight);
		sliders[i]->setBounds(labelWidth, y, getWidth() - labelWidth, rowHeight);
		sliders[i]->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, sliders[i]->getWidth() * 0.2f, rowHeight);
		y += rowHeight /*+ 10*/;
	}
}

int RectangleController::getNumRows() {
	return numRows;
}

void RectangleController::setRowHeight(int _rowHeight) {
	rowHeight = _rowHeight;
}

int RectangleController::getRequiredHeight() {
	return numRows * rowHeight;
}