/*
  ==============================================================================

    SliderWithListener.h
    Created: 2 Jan 2025 1:37:28am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SliderWithListener : public juce::Slider, public juce::Slider::Listener
{
public:
    SliderWithListener(juce::ValueTree tree, juce::Identifier propertyID)
        : valueTree(tree), property(propertyID)
    {
        //setVelocityBasedMode(true);
        setSliderSnapsToMousePosition(false);
        setVelocityModeParameters(0.9,0.1, 0.0,true,ModifierKeys::shiftModifier);
        addListener(this);
    }

	~SliderWithListener()
	{
		removeListener(this);
	}

    void sliderValueChanged(juce::Slider* slider) override
    {
        if (slider == this)
        {
            // Update the ValueTree when slider value changes
            valueTree.setProperty(property, slider->getValue(), nullptr);
        }
    }

private:
    juce::ValueTree valueTree;
    juce::Identifier property;
};
