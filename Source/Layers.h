/*
  ==============================================================================

    Layers.h
    Created: 30 Dec 2024 7:09:11am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "LayerListBoxModel.h"

class LayersViewedComponent : public Component {
public:
	LayersViewedComponent() {
		setInterceptsMouseClicks(false, true);

		layersListBox.setModel(&layersListBoxModel);
		addAndMakeVisible(layersListBox);
	}

	void resized() override {
		layersListBox.setBounds(getLocalBounds());
	}

	void addLayer(int layerID) {
		layersListBoxModel.addItem(ListItem{layerID,"Layer "+String(layerID+1)});
		layersListBox.updateContent();
	}

	void removeLayer(int layerID) {
		layersListBoxModel.removeItem(layerID);
		layersListBox.updateContent();
	}

	void removeAllLayers() {
		layersListBoxModel.removeAllItems();
		layersListBox.updateContent();
	}

	void setListBoxRowHeight(int rowHeight) {
		layersListBox.setRowHeight(rowHeight);
	}

	int getNumLayers() {
		return layersListBoxModel.getNumRows();
	}

	void addLayerListener(ActionListener* listener) {
		layersListBoxModel.addActionListener(listener);
	}

	void removeLayerListener(ActionListener* listener) {
		layersListBoxModel.removeActionListener(listener);
	}

	void clickLayer(int layerID) {
		int rowIndex = layersListBoxModel.getRowIndexForLayerID(layerID);
		layersListBox.selectRow(rowIndex);
	}

	int getLastSelectedLayer() {
		return layersListBoxModel.getSelectedLayer(layersListBox.getSelectedRow());
	}

	void moveLayerUp(int layerID) {
		if (layersListBoxModel.moveItemUp(layerID)) {
			layersListBox.updateContent();
			layersListBox.repaint();
			layersListBox.selectRow(layersListBox.getSelectedRow() - 1);
		}
		
	}

	void moveLayerDown(int layerID) {
		if (layersListBoxModel.moveItemDown(layerID)) {
			layersListBox.updateContent();
			layersListBox.repaint();
			layersListBox.selectRow(layersListBox.getSelectedRow() + 1);
		}
	}

	Array<int> getListOrderIds() {
		return layersListBoxModel.getListOrderIds();
	}

private:
	ListBox layersListBox;
	LayerListBoxModel layersListBoxModel;
};

class Layers : public Component{
public:
	Layers() {

		// add header
		 addAndMakeVisible(header);

		// add buttons
		addComponentButton.setButtonText("+");
		addComponentButton.setComponentID(ADD_COMPONENT_BUTTON);
		addAndMakeVisible(addComponentButton);

		deleteComponentButton.setButtonText("-");
		deleteComponentButton.setComponentID(REMOVE_COMPONENT_BUTTON);
		addAndMakeVisible(deleteComponentButton);

		moveUpButton.setButtonText("^");
		moveUpButton.setComponentID(MOVE_COMPONENT_UP_BUTTON);
		addAndMakeVisible(moveUpButton);

		moveDownButton.setButtonText("v");
		moveDownButton.setComponentID(MOVE_COMPONENT_DOWN_BUTTON);
		addAndMakeVisible(moveDownButton);

		duplicateButton.setButtonText("Dupl");
		duplicateButton.setComponentID(DUPLICATE_BUTTON);
		addAndMakeVisible(duplicateButton);

		exportButton.setButtonText("Code");
		exportButton.setComponentID("EXPORT_BUTTON");
		addAndMakeVisible(exportButton);

		layersViewPort.setViewedComponent(&layersViewedComponent);
		addAndMakeVisible(layersViewPort);
	}

	void paint(Graphics& g) override {
		g.fillAll(GREY1);
	}
	
	void resized() override {
		auto bounds = getLocalBounds();

		// Set the bounds of the add component button and the layers viewport
		auto headerBounds = bounds.removeFromTop(rowHeight);
		header.setJustificationType(Justification::centredLeft);
		header.setBounds(headerBounds);

		auto toolBarBounds = bounds.removeFromBottom(rowHeight);
		int btnWidth = toolBarBounds.getWidth() / 6.0f;
		addComponentButton.setBounds(toolBarBounds.removeFromLeft(btnWidth));
		deleteComponentButton.setBounds(toolBarBounds.removeFromLeft(btnWidth));
		moveUpButton.setBounds(toolBarBounds.removeFromLeft(btnWidth));
		moveDownButton.setBounds(toolBarBounds.removeFromLeft(btnWidth));
		duplicateButton.setBounds(toolBarBounds.removeFromLeft(btnWidth));
		exportButton.setBounds(toolBarBounds);
		layersViewPort.setBounds(bounds);
		
		// Set the row height of the list box
		layersViewedComponent.setListBoxRowHeight(rowHeight);
		layersViewedComponent.setBounds(0, addComponentButton.getBottom(), getWidth()-proportionOfWidth(0.05f), rowHeight * layersViewedComponent.getNumLayers());
	}

	void setRowHeight(int _rowHeight) {
		rowHeight = _rowHeight;
	}

	void addLayer(int layerID) {
		layersViewedComponent.addLayer(layerID);
		resized();
		repaint();
	}

	void removeLayer(int layerID) {
		layersViewedComponent.removeLayer(layerID);
		resized();
		repaint();
	}

	void removeAllLayers() {
		layersViewedComponent.removeAllLayers();
		resized();
		repaint();
	}

	TextButton& getAddComponentButton() {
		return addComponentButton;
	}

	void addLayerListener(ActionListener* listener) {
		layersViewedComponent.addLayerListener(listener);
	}

	void removeLayerListener(ActionListener* listener) {
		layersViewedComponent.removeLayerListener(listener);
	}

	void clickLayer(int layerID) {
		layersViewedComponent.clickLayer(layerID);
	}

	int getLastSelectedLayer() {
		if (layersViewedComponent.getNumLayers() <= 0) return -1;
		else return layersViewedComponent.getLastSelectedLayer();
	}

	int getNumLayers() {
		return layersViewedComponent.getNumLayers();
	}

	void addControlButtonListeners(Button::Listener* listener) {
		addComponentButton.addListener(listener);
		deleteComponentButton.addListener(listener);
		moveUpButton.addListener(listener);
		moveDownButton.addListener(listener);
		exportButton.addListener(listener);
		duplicateButton.addListener(listener);
	}

	void removeControlButtonListeners(Button::Listener* listener) {
		addComponentButton.removeListener(listener);
		deleteComponentButton.removeListener(listener);
		moveUpButton.removeListener(listener);
		moveDownButton.removeListener(listener);
		exportButton.removeListener(listener);
		duplicateButton.removeListener(listener);
	}

	void moveLayerUp(int layerID) {
		layersViewedComponent.moveLayerUp(layerID);
	}

	void moveLayerDown(int layerID) {
		layersViewedComponent.moveLayerDown(layerID);
	}

	Array<int> getListOrderIDs() {
		return layersViewedComponent.getListOrderIds();
	}


private:
	int rowHeight = 0;
	Label header{HEADER_LABEL.toString(),"Layers"};
	TextButton addComponentButton;
	TextButton deleteComponentButton;
	TextButton moveUpButton;
	TextButton moveDownButton;
	TextButton duplicateButton;
	TextButton exportButton;
	Viewport layersViewPort;
	LayersViewedComponent layersViewedComponent;
};
