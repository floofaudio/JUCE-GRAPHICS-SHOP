/*
==============================================================================

GradientSection.cpp
Created: 2 Jan 2025 2:41:48pm
Author:  carlo

==============================================================================
*/

#include "GradientSection.h"

GradientSection::GradientSection(int rowID, ValueTree gradientTree) : m_gradientTree(gradientTree), m_rowID(rowID), tabbedColourSelectors(TabbedButtonBar::Orientation::TabsAtTop), isOnButton(gradientTree,IS_ON) {

	addAndMakeVisible(isOnButton);
	isOnButton.setToggleState(gradientTree.getProperty(IS_ON),dontSendNotification);

	Array sliderIDs{ FROM_X,FROM_Y,STOP1_PERCENT,STOP2_PERCENT,TO_X,TO_Y };
	Array<float> rangeEnds{ 100.0f,100.0f,100.0f,100.0f,500.0f,500.0f};
	for (int i = 0; i < sliderIDs.size(); i++) {
		// add labels
		auto* label = new Label();
		label->setText(sliderIDs[i].toString(), juce::dontSendNotification);
		sliderLabels.add(label);
		addAndMakeVisible(label);

		// get value from tree
		int val = gradientTree.getProperty(sliderIDs[i]);

		// add sliders
		auto* slider = new SliderWithListener(gradientTree, Identifier{ sliderIDs[i] });
		slider->setRange(0.0f, rangeEnds[i], 1);
		slider->setValue(val);
		slider->setComponentID(sliderIDs[i].toString());
		slider->setName(sliderIDs[i].toString());
		slider->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		//slider->addListener(this);
		sliders.add(slider);
		addAndMakeVisible(slider);
	}

	addAndMakeVisible(tabbedColourSelectors);
	StringArray colourSelectorNames{ "From", "Stop 1", "Stop 2","To"};
	Array<Identifier> csIDs{FROM_COLOUR,STOP1_COLOUR,STOP2_COLOUR,TO_COLOUR};
	for (int i = 0; i < 4; i++) {
		ColourSelector* cs = new ColourSelector(ColourSelector::editableColour | ColourSelector::showColourAtTop | ColourSelector::showSliders | ColourSelector::showColourspace | ColourSelector::showAlphaChannel);
		cs->setColour(ColourSelector::ColourIds::backgroundColourId, GREY1);
		cs->setComponentID(csIDs[i].toString());
		colourSelectors.add(std::move(cs));
		colourSelectors[i]->addChangeListener(this);
		tabbedColourSelectors.addTab(colourSelectorNames[i], Colours::aliceblue, colourSelectors[i], false);
	}

	addAndMakeVisible(header);
	header.setText("Gradient", juce::dontSendNotification);

	Array activeButtonIds{ ACTIVE_STOP_1,ACTIVE_STOP_2 };
	for (int i = 0; i < 2; i++) {
		activeStopButtons.add(new ButtonWithListener(m_gradientTree, activeButtonIds[i]));
		//activeStopButtons[i]->setButtonText("_");
		activeStopButtons[i]->setToggleState(m_gradientTree.getProperty(activeButtonIds[i]), dontSendNotification);
		addAndMakeVisible(activeStopButtons[i]);
	}
}

GradientSection::~GradientSection() {
	for (auto cs : colourSelectors) {
		cs->removeChangeListener(this);
	}
}

void GradientSection::paint(juce::Graphics& g) {
	g.fillAll(GREY1);
}

void GradientSection::resized()  {
	auto bounds = getLocalBounds();
	int labelWidth = getWidth() * 0.2f;
	auto headerBounds = bounds.removeFromTop(rowHeight);
	isOnButton.setBounds(headerBounds.removeFromLeft(labelWidth/2.0f));
	header.setBounds(headerBounds.removeFromLeft(proportionOfWidth(0.5f)));

	for (int i = 0; i < sliders.size(); ++i) {
		auto rowBounds = bounds.removeFromTop(rowHeight);

		if (sliders[i]->getComponentID() == STOP1_PERCENT.toString()) {
			activeStopButtons[0]->setBounds(rowBounds.removeFromRight(labelWidth / 2.0f));
		}
		else if (sliders[i]->getComponentID() == STOP2_PERCENT.toString()) {
			activeStopButtons[1]->setBounds(rowBounds.removeFromRight(labelWidth / 2.0f));
		}
		else {
			rowBounds.removeFromRight(labelWidth / 2.0f);
		}

		sliderLabels[i]->setBounds(rowBounds.removeFromLeft(labelWidth));

		sliders[i]->setBounds(rowBounds);
		sliders[i]->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, labelWidth, rowHeight);
	}
	tabbedColourSelectors.setBounds(bounds);
}

void GradientSection::changeListenerCallback(ChangeBroadcaster* source) {
	if (source == colourSelectors[0]) {
		m_gradientTree.setProperty(FROM_COLOUR, colourSelectors[0]->getCurrentColour().toString(), nullptr);
	}
	else if (source == colourSelectors[1]) {
		m_gradientTree.setProperty(STOP1_COLOUR, colourSelectors[1]->getCurrentColour().toString(), nullptr);
	}
	else if (source == colourSelectors[2]) {
		m_gradientTree.setProperty(STOP2_COLOUR, colourSelectors[2]->getCurrentColour().toString(), nullptr);
	}
	else if (source == colourSelectors[3]) {
		m_gradientTree.setProperty(TO_COLOUR, colourSelectors[3]->getCurrentColour().toString(), nullptr);
	}
}

int GradientSection::getNumRows() {
	return numRows;
}

void GradientSection::setRowHeight(int _rowHeight) {
	rowHeight = _rowHeight;
}

