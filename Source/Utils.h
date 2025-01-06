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

	const String LEGAL_INFO = "This application is licensed under the GNU Affero General Public License v3.0 (AGPL-3.0)"
		"\nThis means: You are free to use, modify, and distribute this application, as long as any modificatio"
		"ns or derived works are also made available under the AGPL-3.0 license.\n";
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