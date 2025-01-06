/*
  ==============================================================================

    ButtonWithListener.h
    Created: 2 Jan 2025 3:36:29pm
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ButtonWithListener : public juce::ToggleButton, public juce::Button::Listener
{
public:
    ButtonWithListener(juce::ValueTree tree, juce::Identifier propertyID)
        : valueTree(tree), property(propertyID)
    {
        addListener(this);
    }

    ~ButtonWithListener()
    {
        removeListener(this);
    }

	void buttonClicked(juce::Button* button) override
	{
		if (button == this)
		{
			// Update the ValueTree when button value changes
			valueTree.setProperty(property, button->getToggleState(), nullptr);
		}
	}

private:
    juce::ValueTree valueTree;
    juce::Identifier property;
};
