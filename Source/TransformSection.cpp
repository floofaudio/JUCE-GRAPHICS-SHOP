/*
  ==============================================================================

    TransformSection.cpp
    Created: 2 Jan 2025 3:13:23pm
    Author:  carlo

  ==============================================================================
*/

#include "TransformSection.h"

TransformSection::TransformSection(int rowID, ValueTree& masterTree) {
	ValueTree componentsTree = masterTree.getChildWithName(COMPONENTS_TREE);
	ValueTree componentTree = componentsTree.getChildWithProperty(ID, rowID);
	ValueTree transformTree = componentTree.getChildWithName(TRANSFORM_TREE);

	//StringArray sliderIDs = StringArray{ X,Y,WIDTH,HEIGHT };
	Array sliderIDs{ X,Y,WIDTH,HEIGHT };
	for (int i = 0; i < sliderIDs.size(); i++) {
		// add labels
		auto* label = new Label();
		label->setText(sliderIDs[i].toString(), juce::dontSendNotification);
		sliderLabels.add(label);
		addAndMakeVisible(label);

		// get value from tree
		int val = transformTree.getProperty(sliderIDs[i]);

		auto* slider = new SliderWithListener(transformTree, sliderIDs[i]);
		slider->setRange(0, 1500, 1);
		slider->setValue(val);
		slider->setComponentID(sliderIDs[i].toString());
		slider->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		sliders.add(slider);
		addAndMakeVisible(slider);
	}

	addAndMakeVisible(header);
	header.setText("Transform", juce::dontSendNotification);
}


void TransformSection::paint(juce::Graphics& g) {
	g.fillAll(GREY1);
}

void TransformSection::resized() {
	float w = static_cast<float>(getWidth());
	auto bounds = getLocalBounds();
	header.setBounds(bounds.removeFromTop(rowHeight));
	int y = bounds.getY();
	int labelWidth = static_cast<int>(w * 0.2f);
	for (int i = 0; i < sliders.size(); ++i) {
		sliderLabels[i]->setBounds(0, y, labelWidth, rowHeight);
		sliders[i]->setBounds(labelWidth, y, static_cast<int>(w - labelWidth), rowHeight);
		sliders[i]->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, static_cast<int>(sliders[i]->getWidth() * 0.2f), rowHeight);
		y += rowHeight /*+ 10*/;
	}
}

int TransformSection::getNumRows() {
	return numRows;
}

void TransformSection::setRowHeight(int _rowHeight) {
	rowHeight = _rowHeight;
}

int TransformSection::getRequiredHeight() {
	return numRows * rowHeight;
}