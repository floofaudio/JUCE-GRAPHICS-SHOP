#include "MainComponent.h"

using namespace constants;

//==============================================================================
MainComponent::MainComponent(ValueTree& masterTree) : m_masterTree(masterTree)
{
	initMasterTree();

    setSize (900, 700);
	addAndMakeVisible(layers);
	
	m_masterTree.addListener(this);
	
	layers.addLayerListener(this);
	layers.addControlButtonListeners(this);
	addAndMakeVisible(controllersViewport);

	initMenuBar();
}

MainComponent::~MainComponent()
{
	m_masterTree.removeListener(this);
	layers.removeLayerListener(this);
	layers.removeControlButtonListeners(this);
	menuBarComponent.setModel(nullptr);
}
//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
	g.fillAll(Colours::darkgrey);   // clear the background
}

void MainComponent::resized()
{
	auto mainDisplay = Desktop::getInstance().getDisplays().getPrimaryDisplay();
	auto screenHeight = mainDisplay->totalArea.getHeight();
	rowHeight = jmin<int>(static_cast<int>(getHeight() * 0.04f), static_cast<int>(screenHeight * 0.025f));

	auto bounds = getLocalBounds();
	menuBarComponent.setBounds(bounds.removeFromTop(rowHeight));
	bounds.removeFromTop(rowHeight);

	auto sidebarBounds = bounds.removeFromRight(proportionOfWidth(0.3f));

	// set layers bounds
	layers.setRowHeight(rowHeight);
	layers.setBounds(sidebarBounds.removeFromTop(rowHeight*6));
	sidebarBounds.removeFromTop(static_cast<int>(rowHeight * 0.5f));
	
	auto viewedComponentBounds = sidebarBounds.withTrimmedRight(static_cast<int>(sidebarBounds.getWidth() * 0.06f));

	auto* controller = static_cast<ComponentController*>(controllersViewport.getViewedComponent());
	if (controller) {
		controller->setRowHeight(rowHeight);
		
		controllersViewport.getViewedComponent()->setBounds(viewedComponentBounds.withHeight(controller->getRequiredHeight()));
		controllersViewport.setBounds(sidebarBounds);
	}
}

//==============================================================================
void MainComponent::initMasterTree() {
	m_masterTree = ValueTree(MASTER_TREE);
	ValueTree componentsTree = ValueTree(COMPONENTS_TREE);
	m_masterTree.addChild(componentsTree, -1, nullptr);
}

void MainComponent::initMenuBar() {
	addAndMakeVisible(menuBarComponent);
	menuBarComponent.setModel(&menuBarModel);

	menuBarModel.onSaveAs = [this]() {
		saveMasterTreeToFile();
		};

	menuBarModel.onOpen = [this]() {
		resetProject();
		recreateProjectFromMasterTree();
		loadMasterTreeFromFile();
		};
	menuBarModel.onNew = [this]() {
		resetProject();
		recreateProjectFromMasterTree();
		};
	menuBarModel.onAbout = [this]() {
		String version = ProjectInfo::versionString;
		String aboutText =
			"JUCE GRAPHICS SHOP version " + version + "\n" +"Created by Carlos Reiakvam, January 2025.\n\n\n" + LEGAL_INFO;
		juce::AlertWindow::showMessageBoxAsync(
			juce::AlertWindow::InfoIcon,
			"About",
			aboutText);
		};

}
//==============================================================================
void MainComponent::buttonClicked(Button* button) {
	if (button->getComponentID() == ADD_COMPONENT_BUTTON) {
		int layerID = components.size();
		addComponent(layerID);
		addComponentControllers(layerID);
		layers.addLayer(layerID);
		layers.clickLayer(layerID);
	}
	else if (button->getComponentID() == REMOVE_COMPONENT_BUTTON) {
		int layerID = layers.getLastSelectedLayer();
		if (layerID == -1) return;
		layers.removeLayer(layerID);
		deleteComponent(layerID);
	}
	else if (button->getComponentID() == MOVE_COMPONENT_UP_BUTTON) {
		int layerID = layers.getLastSelectedLayer();
		if (layerID == -1) return;
		layers.moveLayerUp(layerID);
	}
	else if (button->getComponentID() == MOVE_COMPONENT_DOWN_BUTTON) {
		int layerID = layers.getLastSelectedLayer();
		if (layerID == -1) return;
		layers.moveLayerDown(layerID);
	}
	else if (button->getComponentID() == DUPLICATE_BUTTON) {
		int layerID = layers.getLastSelectedLayer();
		if (layerID == -1) return;
		int newLayerID = components.size();
		duplicateComponent(layerID, newLayerID);

		// apply the transform properties to the new component
		setComponentBoundsFromTransformTree(newLayerID);

		addComponentControllers(newLayerID);
		layers.addLayer(newLayerID);
		layers.clickLayer(newLayerID);
		repaint();
	}
	else if (button->getComponentID() == EXPORT_BUTTON) {
		int layerID = layers.getLastSelectedLayer();
		if (layerID == -1) return;
		auto* componentByID = getRectangleComponent(layerID);
		if (componentByID != nullptr) {
			String code = componentByID->getPaintMethodAsString();
			showSelectableWindowWithText(code);
		}
	}
	
	setLayerZOrder(layers.getListOrderIDs());
	resized();
}

void MainComponent::actionListenerCallback(const String& message) {
	if (message.startsWith(CLICKED_LAYER)) {
		int layerID = message.substring(CLICKED_LAYER.length()).getIntValue();
		setComponentControllersViewedComponent(layerID);
	}
}

void MainComponent::valueTreePropertyChanged(ValueTree& tree, const Identifier& property)	 {
	

	if (tree.getType() == GRADIENT_TREE) {
		auto componentTree = tree.getParent();
		int id = componentTree.getProperty(ID);
		auto* component = components[id];
		var val = tree.getProperty(property);

		component->setGradientProperties(property, val);
		component->repaint();
	}

	else if (tree.getType() == TRANSFORM_TREE) {
		auto componentTree = tree.getParent();
		int id = componentTree.getProperty(ID);
		auto* component = components[id];
		var val = tree.getProperty(property);

		int x = component->getX();
		int y = component->getY();
		int width = component->getWidth();
		int height = component->getHeight();
		int translateY = rowHeight;
		if (property == X) {
			component->setTopLeftPosition(val, y);
		}
		else if (property == Y) {
			component->setTopLeftPosition(x, static_cast<int>(val)+translateY);
		}
		else if (property == WIDTH) {
			component->setSize(val, height);
		}
		else if (property == HEIGHT) {
			component->setSize(width, val);
		}

		component->resized();
		component->repaint();
	}
	else if (tree.getType() == RECTANGLE_TREE) {
		auto componentTree = tree.getParent();
		int id = componentTree.getProperty(ID);
		auto* component = components[id];
		var val = tree.getProperty(property);

		if (property == CORNER) {
			component->setCornerRadius(val);
		}
		component->repaint();

	}

}

//==============================================================================

ValueTree MainComponent::getNewComponentTree(int layerID) {

	// init rectangle tree
	ValueTree rectangleTree(
		RECTANGLE_TREE,
		{
			{IS_ON, true},
			{CORNER, 0},
		});

	// init gradient tree
	ValueTree gradientTree(
		GRADIENT_TREE,
		{
			{IS_ON, true},
			{FROM_X, 0},
			{FROM_Y, 0},
			{STOP1_PERCENT,0},
			{ACTIVE_STOP_1,false},
			{STOP2_PERCENT,0},
			{ACTIVE_STOP_2,false},
			{TO_X, 0},
			{TO_Y, 100},
			{FROM_COLOUR, Colours::black.toString()},
			{TO_COLOUR, Colours::white.toString()}
		});

	// init transform tree
	ValueTree transformTree(
		TRANSFORM_TREE,
		{
			{X, 0},
			{Y, 0},
			{WIDTH, 100},
			{HEIGHT, 100}
		});

	ValueTree componentTree(COMPONENT_TREE);
	componentTree.setProperty(ID, layerID, nullptr);
	componentTree.addChild(gradientTree, -1, nullptr);
	componentTree.addChild(transformTree, -1, nullptr);
	componentTree.addChild(rectangleTree, -1, nullptr);
	return componentTree;
}

ValueTree MainComponent::getComponentTree(int layerID) {
	return m_masterTree.getChildWithName(COMPONENTS_TREE).getChildWithProperty(ID, layerID);
}

void MainComponent::saveMasterTreeToFile()
{
	if (auto xml = m_masterTree.createXml())
	{
		auto sharedXml = std::make_shared<juce::XmlElement>(*xml);

		fileChooser = std::make_unique<juce::FileChooser>(
			"Save Master Tree as XML",
			juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),
			"*.xml");

		fileChooser->launchAsync(juce::FileBrowserComponent::saveMode, [this, sharedXml](const juce::FileChooser& chooser) {
			juce::File selectedFile = chooser.getResult();

			if (selectedFile != juce::File{})
			{
				if (selectedFile.existsAsFile() || selectedFile.create())
				{
					selectedFile.replaceWithText(sharedXml->toString());
					juce::AlertWindow::showMessageBoxAsync(
						juce::AlertWindow::InfoIcon,
						"Save Successful",
						"Master Tree saved to: " + selectedFile.getFullPathName()
					);
				}
				else
				{
					juce::AlertWindow::showMessageBoxAsync(
						juce::AlertWindow::WarningIcon,
						"Save Failed",
						"Unable to create or write to the selected file."
					);
				}
			}
			else
			{
				juce::AlertWindow::showMessageBoxAsync(
					juce::AlertWindow::InfoIcon,
					"Save Canceled",
					"No file was selected."
				);
			}
			});
	}
	else
	{
		juce::AlertWindow::showMessageBoxAsync(
			juce::AlertWindow::WarningIcon,
			"Save Failed",
			"Unable to create XML representation of the master tree."
		);
	}
}

void MainComponent::loadMasterTreeFromFile()
{
	fileChooser = std::make_unique<juce::FileChooser>(
		"Load Master Tree from XML",
		juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),
		"*.xml");

	fileChooser->launchAsync(juce::FileBrowserComponent::openMode, [this](const juce::FileChooser& chooser) {
		juce::Logger::writeToLog("FileChooser Callback Invoked");
		juce::File selectedFile = chooser.getResult();

		if (selectedFile != juce::File{})
		{
			if (selectedFile.existsAsFile())
			{
				auto xml = juce::XmlDocument::parse(selectedFile);

				if (xml.get() != nullptr)
				{
					m_masterTree = ValueTree::fromXml(*xml);
					recreateProjectFromMasterTree();
					juce::AlertWindow::showMessageBoxAsync(
						juce::AlertWindow::InfoIcon,
						"Load Successful",
						"Master Tree loaded from: " + selectedFile.getFullPathName()
					);
				}
				else
				{
					juce::AlertWindow::showMessageBoxAsync(
						juce::AlertWindow::WarningIcon,
						"Load Failed",
						"Unable to parse the selected file as XML."
					);
				}
			}
			else
			{
				juce::AlertWindow::showMessageBoxAsync(
					juce::AlertWindow::WarningIcon,
					"Load Failed",
					"The selected file does not exist."
				);
			}
		}
		else
		{
			juce::AlertWindow::showMessageBoxAsync(
				juce::AlertWindow::InfoIcon,
				"Load Canceled",
				"No file was selected."
			);
		}
		});
}

void MainComponent::resetProject() {
	// remove all components
	for (int i = components.size(); --i >= 0;)
	{
		deleteComponent(i);
	}

	// remove all controllers
	for (int i = controllers.size(); --i >= 0;)
	{
		controllers.remove(i);
	}

	// remove all layers
	layers.removeAllLayers();

	initMasterTree();
}

void MainComponent::recreateProjectFromMasterTree() {
	// add components from loaded file
	auto componentsTree = m_masterTree.getChildWithName(COMPONENTS_TREE);
	int nComponents = componentsTree.getNumChildren();
	for (int i = 0; i < nComponents; i++) {
		auto componentTree = componentsTree.getChild(i);
		int layerID = componentTree.getProperty(ID);
		createComponentFromTree(layerID);
		addComponentControllers(layerID);
		layers.addLayer(layerID);
	}

	// set the last selected layer
	layers.clickLayer(components.size() - 1);
	setLayerZOrder(layers.getListOrderIDs());
	resized();
}
//==============================================================================

void MainComponent::addComponent(int layerID) {
	auto componentTree = getNewComponentTree(layerID);
	m_masterTree.getChildWithName(COMPONENTS_TREE).addChild(std::move(componentTree), -1, nullptr);

	auto* newComponent = new RectangleComponent(layerID, componentTree);
	components.add(newComponent);
	newComponent->setBounds(0, rowHeight, 100, 100);
	addAndMakeVisible(newComponent);
}

void MainComponent::createComponentFromTree(int layerID) {
	auto componentTree = getComponentTree(layerID);
	auto* newComponent = new RectangleComponent(layerID, componentTree);
	components.add(newComponent);
	newComponent->setBounds(0, rowHeight, 100, 100);
	addAndMakeVisible(newComponent);
	repaint();
}

void MainComponent::duplicateComponent(int fromLayerID, int toLayerID) {
	auto fromComponentTree = getComponentTree(fromLayerID);
	auto newTree = getNewComponentTree(toLayerID);
	newTree.copyPropertiesAndChildrenFrom(fromComponentTree, nullptr);
	newTree.setProperty(ID, toLayerID, nullptr);
	m_masterTree.getChildWithName(COMPONENTS_TREE).addChild(newTree,-1,nullptr);
	createComponentFromTree(toLayerID);
}

void MainComponent::deleteComponent(int layerID) {
	auto componentTree = getComponentTree(layerID);
	m_masterTree.getChildWithName(COMPONENTS_TREE).removeChild(componentTree, nullptr);
	auto* component = components[layerID];
	components.removeObject(component);
	removeChildComponent(component);
}

RectangleComponent* MainComponent::getRectangleComponent(int layerID) {
	for (auto* component : components) {
		if (component->getLayerID() == layerID) {
			return component;
		}
	}
	return nullptr;
}

//==============================================================================

void MainComponent::addComponentControllers(int layerID) {
	auto componentTree = getComponentTree(layerID);
	auto gradientTree = componentTree.getChildWithName(GRADIENT_TREE);
	
	auto* newController = new ComponentController(layerID, m_masterTree,gradientTree,ControllerType::RectangleControllerType);
	controllers.add(newController);

	// add the controller to the viewport
	controllersViewport.setViewedComponent(controllers.getLast(), false);
}

void MainComponent::setComponentControllersViewedComponent(int layerID) {
	controllersViewport.setViewedComponent(controllers[layerID], false);
	resized();
}

void MainComponent::setLayerZOrder(Array<int> layerIDs) {
	for (int i = 0; i < layerIDs.size(); i++) {
		auto* component = components[layerIDs[i]];
		component->toBack();
	}
}

void MainComponent::showSelectableWindowWithText(const juce::String& multilineText)
{
	class SelectableTextWindow : public juce::DocumentWindow
	{
	public:
		SelectableTextWindow(const juce::String& title, const juce::String& text)
			: juce::DocumentWindow(title, juce::Colours::lightgrey, juce::DocumentWindow::closeButton)
		{
			auto* textBox = new juce::TextEditor();
			textBox->setMultiLine(true);
			textBox->setReadOnly(true);
			textBox->setText(text);
			textBox->setCaretVisible(false);
			textBox->setBounds(0, 0, 600, 300);

			setUsingNativeTitleBar(true);
			setContentOwned(textBox, true);
			centreWithSize(600, 300);
			setVisible(true);
		}

		void closeButtonPressed() override
		{
			// Delete this window when it is closed
			delete this;
		}
	};

	// Create the window dynamically
	new SelectableTextWindow("CODE", multilineText);
}

void MainComponent::setComponentBoundsFromTransformTree(int layerID) {
	auto transformTree = getComponentTree(layerID).getChildWithName(TRANSFORM_TREE);

	if (transformTree.isValid())
	{
		int x = transformTree.getProperty("X", 0);
		int y = transformTree.getProperty("Y", 0);
		y += rowHeight; // adjust for menu bar on tops
		int width = transformTree.getProperty("WIDTH", 100);
		int height = transformTree.getProperty("HEIGHT", 100);

		getRectangleComponent(layerID)->setBounds(x, y, width, height);;
	}
}
