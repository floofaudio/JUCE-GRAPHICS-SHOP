/*
  ==============================================================================

    RectangleComponent.h
    Created: 2 Jan 2025 5:28:14pm
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"

using namespace constants;

struct Gradient {
	bool isOn = false;
	bool isStop1Active = false;
	bool isStop2Active = false;
	float fromX = 0;
	float fromY = 0;
	float stop1Percent = 0;
	float stop2Percent = 0;
	float toX = 100;
	float toY = 100;
	Colour fromColour = Colours::black;
	Colour toColour = Colours:: white;
	Colour stop1Colour = Colours::blue;
	Colour stop2Colour = Colours::green;
};

class RectangleComponent : public Component
{
public:
	RectangleComponent(int _layerID, ValueTree& componentTree) {
		// init gradients array
		layerID = _layerID;
		getProperties().set(ID, layerID);

		for (int i = 0; i < 4; i++) {
			auto gradientTree = componentTree.getChildWithName(GRADIENT_TREE);
			bool isOn = gradientTree.getProperty(IS_ON);
			bool isStop1Active = gradientTree.getProperty(ACTIVE_STOP_1);
			bool isStop2Active = gradientTree.getProperty(ACTIVE_STOP_2);
			float fromX = gradientTree.getProperty(FROM_X);
			float fromY = gradientTree.getProperty(FROM_Y);
			float stop1Percent = gradientTree.getProperty(STOP1_PERCENT);
			float stop2Percent = gradientTree.getProperty(STOP2_PERCENT);
			float toX = gradientTree.getProperty(TO_X);
			float toY = gradientTree.getProperty(TO_Y);
			auto fromColour = Colour::fromString(gradientTree.getProperty(FROM_COLOUR).toString());
			auto toColour = Colour::fromString(gradientTree.getProperty(TO_COLOUR).toString());
			auto stop1Colour = Colour::fromString(gradientTree.getProperty(STOP1_COLOUR).toString());
			auto stop2Colour = Colour::fromString(gradientTree.getProperty(STOP2_COLOUR).toString());
			gradient = Gradient{ isOn,isStop1Active,isStop2Active, fromX, fromY, stop1Percent,stop2Percent, toX, toY, fromColour, toColour, stop1Colour,stop2Colour };
		}
	}

	void paint(Graphics& g) override{
		float w = static_cast<float>(getWidth());
		float h = static_cast<float>(getHeight());
		if (gradient.isOn) {
			ColourGradient colourGradient(
				gradient.fromColour, 
				gradient.fromX * 0.01f * w,
				gradient.fromY * 0.01f * h,
				gradient.toColour, 
				gradient.toX*0.01f * w, 
				gradient.toY*0.01f*h, false
			);

			if (gradient.isStop1Active) {
				colourGradient.addColour(gradient.stop1Percent * 0.01f, gradient.stop1Colour);
			}
			if (gradient.isStop2Active) {
				colourGradient.addColour(gradient.stop2Percent * 0.01f, gradient.stop2Colour);
			}

			g.setGradientFill(colourGradient);
			g.fillRoundedRectangle(0, 0, w, h, cornerSize);
		}
	}

	void setGradientProperties( Identifier id, var value) {
		if (id == IS_ON) {
			gradient.isOn = value;
		}
		else if (id == FROM_X) {
			gradient.fromX = value;
		}
		else if (id == FROM_Y) {
			gradient.fromY = value;
		}
		else if (id == TO_X) {
			gradient.toX = value;
		}
		else if (id == TO_Y) {
			gradient.toY = value;
		}
		else if (id == FROM_COLOUR) {
			gradient.fromColour = Colour::fromString(value.toString());
		}
		else if (id == TO_COLOUR) {
			gradient.toColour = Colour::fromString(value.toString());
		}
		else if (id == STOP1_PERCENT) {
			gradient.stop1Percent = value;
		}
		else if (id == STOP2_PERCENT) {
			gradient.stop2Percent = value;
		}
		else if (id == STOP1_COLOUR) {
			gradient.stop1Colour = Colour::fromString(value.toString());
		}
		else if (id == STOP2_COLOUR) {
			gradient.stop2Colour = Colour::fromString(value.toString());
		}
		else if (id == ACTIVE_STOP_1) {
			gradient.isStop1Active = value;
		}
		else if (id == ACTIVE_STOP_2) {
			gradient.isStop2Active = value;
		}

		
		repaint();
	}

	void updateGradients() {
		gradient.fromX = getX() + gradient.fromX * 0.01f * getWidth();
		gradient.fromY = getY() + gradient.fromY;
		gradient.toX = getX() + gradient.toX * 0.01f * getWidth();
		gradient.toY = getY() + gradient.toY * 0.01f * getHeight();
		repaint();
	}

	void setCornerRadius(int _cornerSize) {
		cornerSize = _cornerSize;
		repaint();
	}

	String getPaintMethodAsString()
	{
		String code;

		// Start the method definition
		code << "void paint(Graphics& g) override {\n";

		if (!gradient.isOn)
		{
			code << "    // Gradient is off, nothing to paint\n";
			code << "}\n"; // Close the function early
			return code;    // Return here since there's no painting needed
		}

		// Create the ColourGradient
		code << "    ColourGradient colourGradient(\n";
		code << "        Colours::" << gradient.fromColour.toString() << ",\n";
		code << "        " << juce::String::formatted("%.2ff * getWidth(),\n", gradient.fromX * 0.01f);
		code << "        " << juce::String::formatted("%.2ff * getHeight(),\n", gradient.fromY * 0.01f);
		code << "        Colours::" << gradient.toColour.toString() << ",\n";
		code << "        " << juce::String::formatted("%.2ff * getWidth(),\n", gradient.toX * 0.01f);
		code << "        " << juce::String::formatted("%.2ff * getHeight(),\n", gradient.toY * 0.01f);
		code << "        false\n";
		code << "    );\n";

		// Add gradient stops if active
		if (gradient.isStop1Active)
		{
			code << "    colourGradient.addColour("
				<< juce::String::formatted("%.2f", gradient.stop1Percent * 0.01f)
				<< "f, Colours::" << gradient.stop1Colour.toString() << ");\n";
		}

		if (gradient.isStop2Active)
		{
			code << "    colourGradient.addColour("
				<< juce::String::formatted("%.2f", gradient.stop2Percent * 0.01f)
				<< "f, Colours::" << gradient.stop2Colour.toString() << ");\n";
		}

		// Set the gradient fill and draw the rounded rectangle
		code << "    g.setGradientFill(colourGradient);\n";
		code << "    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), cornerSize);\n";

		// Close the method
		code << "}\n";

		return code;
	}

	int getLayerID() {
		return layerID;
	}

private: 
	int layerID = 0;
	int cornerSize = 0;
	Gradient gradient;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RectangleComponent);
};
