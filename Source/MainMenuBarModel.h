/*
  ==============================================================================

    MainMenuBarModel.h
    Created: 3 Jan 2025 11:30:28am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <functional> // Include for std::function

enum MenuID {
	New = 1,
	Open,
	SaveAs,
	Quit,
	About
};

class MainMenuBarModel : public MenuBarModel
{
public:
	MainMenuBarModel();

	StringArray getMenuBarNames() override;
	
	PopupMenu getMenuForIndex(int menuIndex, const String& menuName) override;
	
	void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	std::function<void()> onSaveAs;
	std::function<void()> onOpen;
	std::function<void()> onNew;
	std::function<void()> onAbout;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainMenuBarModel)
};