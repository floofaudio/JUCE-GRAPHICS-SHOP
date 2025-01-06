/*
  ==============================================================================

    Utils.h
    Created: 31 Dec 2024 2:35:28am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace constants {
	// general constants
	const Identifier HEADER_LABEL = "HEADER_LABEL";

	// rectangle controller constants
	const Identifier CORNER = "CORNER";
	const Identifier IS_ROUNDED = "IS_ROUNDED";


	// layer constants
	const String ADD_COMPONENT_BUTTON = "ADD_COMPONENT_BUTTON";
	const String REMOVE_COMPONENT_BUTTON = "REMOVE_COMPONENT_BUTTON";
	const String MOVE_COMPONENT_UP_BUTTON = "MOVE_COMPONENT_UP_BUTTON";
	const String MOVE_COMPONENT_DOWN_BUTTON = "MOVE_COMPONENT_DOWN_BUTTON";
	const String EXPORT_BUTTON = "EXPORT_BUTTON";

	// gradient contstants
	const Identifier FROM_COLOUR = "FROM_COLOUR";
	const Identifier TO_COLOUR = "TO_COLOUR";
	const Identifier STOP1_PERCENT = "STOP1_PERCENT";
	const Identifier STOP2_PERCENT = "STOP2_PERCENT";
	const Identifier STOP1_COLOUR = "STOP1_COLOUR";
	const Identifier STOP2_COLOUR = "STOP2_COLOUR";
	const Identifier FROM_X = "FROM_X";
	const Identifier FROM_Y = "FROM_Y";
	const Identifier TO_X = "TO_X";
	const Identifier TO_Y = "TO_Y";
	const Identifier ACTIVE_STOP_1 = "ACTIVE_STOP_1";
	const Identifier ACTIVE_STOP_2 = "ACTIVE_STOP_2";

	// transform constants
	const Identifier X = "X";
	const Identifier Y = "Y";
	const Identifier WIDTH = "WIDTH";
	const Identifier HEIGHT = "HEIGHT";

	// tree constants
	const Identifier ID("ID");
	const Identifier IS_ON("IS_ON");
	const Identifier MASTER_TREE("MASTER_TREE");
	const Identifier COMPONENTS_TREE("COMPONENTS_TREE");
	const Identifier COMPONENT_TREE("COMPONENT_TREE");
	const Identifier GRADIENT_TREE("GRADIENT_TREE");
	const Identifier RECTANGLE_TREE("RECTANGLE_TREE");
	const Identifier TRANSFORM_TREE("TRANSFORM_TREE");

	// action message constants
	const String CLICKED_LAYER = "CLICKED_LAYER";

	// colours
	const Colour GREY1 = Colours::black.withBrightness(0.25f);
	const Colour COLOUR_BUTTON_NORMAL = Colours::black.withBrightness(0.3f);
	const Colour COLOUR_BUTTON_DOWN = Colours::lightblue.withAlpha(0.5f);

	const String LEGAL_INFO = juce::CharPointer_UTF8("This project is licensed under Creative Commons Attribution-NonCommercial 4.0 International.\n"
		"\n"
		"You are free to:\n"
		"Share \xe2\x80\x94 copy and redistribute the material in any medium or format Adapt \xe2\x80\x94 remix, transform, and bui"
		"ld upon the material The licensor cannot revoke these freedoms as long as you follow the license ter"
		"ms.\n"
		"\n"
		"Under the following terms:\n"
		"\n- Attribution \xe2\x80\x94 You must give appropriate credit , provide a link to the license, and indicate if chan"
		"ges were made . You may do so in any reasonable manner, but not in any way that suggests the licenso"
		"r endorses you or your use.\n"
		"\n- NonCommercial \xe2\x80\x94 You may not use the material for commercial purposes . No additional restrictions \xe2\x80\x94 "
		"You may not apply legal terms or technological measures that legally restrict others from doing anyt"
		"hing the license permits.");
}

struct ListItem
{
	int id;
	String text;
	// anything else you might need
};

enum ControllerType {
	RectangleControllerType,
	EllipseControllerType
};