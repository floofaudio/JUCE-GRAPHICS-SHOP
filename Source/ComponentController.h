/*
  ==============================================================================

    ComponentControllers.h
    Created: 30 Dec 2024 7:23:13am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"
#include "TransformSection.h"
#include "ColourSection.h"
#include "RectangleController.h"

using namespace constants;


class ComponentController : public juce::Component {
public:
	ComponentController(int rowID, ValueTree& masterTree, ValueTree& gradientTree, ControllerType controllerType);
	~ComponentController();

	void resized() override;
	
	void setRowHeight(int _rowHeight);
	
	int getRequiredHeight();

private:
	int rowHeight = 0;
	ControllerType controllerType = ControllerType::RectangleControllerType;
	TransformSection transformSection;
	ColourSection colourSection;
	RectangleController rectangleController;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ComponentController)
};
