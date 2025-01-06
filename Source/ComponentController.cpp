/*
  ==============================================================================

    ComponentController.cpp
    Created: 2 Jan 2025 2:33:05pm
    Author:  carlo

  ==============================================================================
*/

#include "ComponentController.h"

	ComponentController::ComponentController(int rowID, ValueTree& masterTree, ValueTree& gradientTree, ControllerType _controllerType) : transformSection(rowID, masterTree), colourSection(rowID, gradientTree), rectangleController(rowID,masterTree) {
		addAndMakeVisible(transformSection);
		addAndMakeVisible(colourSection);

		controllerType = _controllerType;
		if (controllerType == ControllerType::RectangleControllerType)
		{
			addAndMakeVisible(rectangleController);
		}
	}

	ComponentController::~ComponentController() {}


	void ComponentController::resized() {
		auto bounds = getLocalBounds();
		if (controllerType == RectangleControllerType)
		{
			rectangleController.setBounds(bounds.removeFromTop(rectangleController.getRequiredHeight()));
			bounds.removeFromTop(transformSection.getRowHeight() * 0.5f);
		}
		transformSection.setBounds(bounds.removeFromTop(transformSection.getRequiredHeight()));
		bounds.removeFromTop(transformSection.getRowHeight()*0.5f);
		colourSection.setBounds(bounds.removeFromTop(jmin<int>(colourSection.getRequiredHeight(),bounds.getHeight())));
	}


	void ComponentController::setRowHeight(int _rowHeight) {
		rowHeight = _rowHeight;
		transformSection.setRowHeight(_rowHeight);
		colourSection.setRowHeight(_rowHeight);
		if (controllerType == RectangleControllerType)
		{
			rectangleController.setRowHeight(_rowHeight);
		}
	}

	int ComponentController::getRequiredHeight() {
		if (controllerType == RectangleControllerType) {
			return transformSection.getRequiredHeight() + colourSection.getRequiredHeight() + rectangleController.getRequiredHeight() + rowHeight;
		}
		else {
			return transformSection.getRequiredHeight() + colourSection.getRequiredHeight() + rowHeight*0.5f;
		}
	}
