/*
  ==============================================================================

    LayerListBoxModel.h
    Created: 31 Dec 2024 12:51:31am
    Author:  carlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"


using namespace constants;

class LayerListBoxModel : public juce::ListBoxModel, public ActionBroadcaster
{
public:
    LayerListBoxModel(){}

    // Returns the total number of rows in the list
    int getNumRows() override
    {
        return static_cast<int>(items.size());
    }

    // Called to paint each row of the list
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool isSelected) override
    {
        g.fillAll(COLOUR_BUTTON_NORMAL);
        if (isSelected) {
            g.fillAll(COLOUR_BUTTON_DOWN); // Highlight selected rows
        }

        // e.g. Draw the text
        if (rowNumber >= 0 && rowNumber < (int)items.size())
        {
            g.setColour(Colours::white);
            g.drawFittedText(items[rowNumber].text,
                4, 0, width - 8, height,
                Justification::centredLeft, 1);
        }

    }

    // Handle row selection
    void listBoxItemClicked(int row, const juce::MouseEvent&) override
    {
        // get item
		lastSelectedRow = items[row].id;
		sendActionMessage(CLICKED_LAYER + juce::String(lastSelectedRow));
        juce::Logger::outputDebugString("Clicked on row with id" + juce::String(lastSelectedRow));
    }

    void addItem(ListItem newItem)
    {
        items.insert(items.begin(), newItem);
    }

	void removeItem(int id)
	{
		for (int i = 0; i < items.size(); i++) {
			if (items[i].id == id) {
				items.erase(items.begin() + i);
				break;
			}
		}
	}

    int getSelectedLayer(int rowIndex) {
		return items[rowIndex].id;
    }

    int getRowIndexForLayerID(int layerID) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].id == layerID) {
                return i;
            }
        }
        return 0;
    }

    bool moveItemUp(int layerID) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i].id == layerID) {
				if (i > 0) {
					std::swap(items[i], items[i - 1]);
                    DBG("swap up");
                    return true;
				}
				break;
			}
		}
        return false;
    }

    bool moveItemDown(int layerID) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].id == layerID) {
                if (i < items.size() - 1) {
                    std::swap(items[i], items[i + 1]);
					DBG("swap down");
                    return true;
                }
                break;
            }
        }
        return false;
        
    }

    Array<int> getListOrderIds() {
		Array<int> listOrderIds;
		for (int i = 0; i < items.size(); ++i) {
			int id = items[i].id;
			listOrderIds.add(id);
		}
		return listOrderIds;
    }

	void removeAllItems() {
		items.clear();
	}

private:
	int lastSelectedRow = 0;
    std::vector<ListItem> items;
};