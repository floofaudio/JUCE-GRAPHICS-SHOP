#pragma once

#include <JuceHeader.h>
#include "Layers.h"
#include "ComponentController.h"
#include "RectangleComponent.h"
#include "MainMenuBarModel.h"
#include "Utils.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component, public ValueTree::Listener, public Button::Listener, public ActionListener
{
public:
    //==============================================================================
    MainComponent(ValueTree& masterTree);
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void addComponent(int layerID);
	RectangleComponent* getRectangleComponent(int layerID);
    void addComponentControllers(int layerID);
	void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
	void buttonClicked(Button* button) override;
    void actionListenerCallback(const String& message) override;
    void saveMasterTreeToFile();
    void loadMasterTreeFromFile();
    void recreateProjectFromMasterTree();
	void resetProject();
    void createComponentFromTree(int layerID);
private:
    void initMenuBar();
    void initMasterTree();
	ValueTree getNewComponentTree(int layerID);
    ValueTree getComponentTree(int id);
	void setComponentControllersViewedComponent(int id);
    void deleteComponent(int layerID);
    void setLayerZOrder(Array<int> layerIDs);
    void showSelectableWindowWithText(const juce::String& multilineText);
	void duplicateComponent(int fromLayerID, int toLayerID);
	void setComponentBoundsFromTransformTree(int layerID);
	ComponentController& getControllerForLayerID(int layerID);


private:
    //==============================================================================
	int currentLayerID = 0;
	int rowHeight = 0;
    Layers layers;
    OwnedArray <RectangleComponent> components;
    //Array <std::shared_ptr<ComponentController>> controllers;
    OwnedArray <ComponentController> controllers;
	//Component componentControllersViewedComponent;
    Viewport controllersViewport;
    ValueTree& m_masterTree;
	MenuBarComponent menuBarComponent;
	MainMenuBarModel menuBarModel;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
