/*
  ==============================================================================

    MainMenuBarModel.cpp
    Created: 5 Jan 2025 11:56:06am
    Author:  carlo

  ==============================================================================
*/

#include "MainMenuBarModel.h"
#include "MainComponent.h"


MainMenuBarModel::MainMenuBarModel() {};

StringArray MainMenuBarModel::getMenuBarNames()  {
	const char* const names[] = { "File", "Help", nullptr };
	return StringArray(names);
}

PopupMenu MainMenuBarModel::getMenuForIndex(int menuIndex, const String& menuName)  {
	PopupMenu menu;
	if (menuIndex == 0) {
		menu.addItem(MenuID::New, "New");
		menu.addItem(MenuID::Open, "Open");
		menu.addItem(MenuID::SaveAs, "Save As");
		menu.addSeparator();
		menu.addItem(MenuID::Quit, "Quit");
	}
	else if (menuIndex == 1) {
		menu.addItem(MenuID::About, "About");
	}
	return menu;
}

void MainMenuBarModel::menuItemSelected(int menuItemID, int topLevelMenuIndex)  {
	if (menuItemID == MenuID::SaveAs) {
		onSaveAs(); // Call the Save As callback
	}
	else if (menuItemID == MenuID::Open) {
		onOpen(); // Call the Open callback
	}
	else if (menuItemID == MenuID::New) {
		onNew(); // Call the New callback
	}
	else if (menuItemID == MenuID::About) {
		onAbout(); // Call the About callback
	}
	else if (menuItemID == MenuID::Quit) {
		JUCEApplication::getInstance()->systemRequestedQuit();
	}
}