/*
  ==============================================================================

    MusiclibComponent.h
    Created: 9 Feb 2022 3:05:34pm
    Author:  Yu

  ==============================================================================
*/

#pragma once
#include "DeckGUI.h"
#include "MusicTrack.h"
#include "DJAudioPlayer.h"

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory> 
#include <algorithm>

//#include "MainComponent.h"

//==============================================================================
/*
*/
class MusiclibComponent : public juce::Component,
    public juce::TableListBoxModel,
    public Button::Listener,
    public ComboBox::Listener, 
    public TableHeaderComponent::Listener,
    public TextEditor::Listener, 
    public FileDragAndDropTarget,
    public DragAndDropContainer,
    public ComponentListener
{
public:
    MusiclibComponent(DeckGUI *deck1,
        DeckGUI* deck2,
        DJAudioPlayer* player3);

    ~MusiclibComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    //return the number of rows currently in the table
    int getNumRows() override;
    //draw the background behind one of the rows in the table
    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    //draw one of the cells
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;
    //create or update a custom component to go in a cell
    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;
    //Called when the button is clicked.
    void buttonClicked(Button* button) override;
    //Called when a ComboBox has its selected item changed.
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    //write file path to filename.txt and read filepath in constructor
    void setFile(const File& file);
    //Callback to check whether this target is interested in the set of files being offered.
    bool isInterestedInFileDrag(const StringArray& files) override;
    //Callback to indicate that the user has dropped the files onto this component.
    void filesDropped(const StringArray& files, int x, int y) override;
    //allow rows from your table to be dragged-and-dropped
    var getDragSourceDescription(const SparseSet< int >& currentlySelectedRows);
    //virtual function for TableHeaderComponent::Listener Class
    void tableColumnsChanged(TableHeaderComponent* tableHeader) override;
    void tableColumnsResized(TableHeaderComponent* tableHeader) override;
    void tableSortOrderChanged(TableHeaderComponent* tableHeader) override;

private:
    TableListBox tableComponent;
    std::unique_ptr<TableHeaderComponent> header;
    std::vector<MusicTrack*> track;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };
    DeckGUI* deck1;
    DeckGUI* deck2;
    DJAudioPlayer* player3;
    TextButton searchFiles{"SEARCH"};
    TextButton addFiles{"LOAD"};
    TextEditor searchInput{"search"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MusiclibComponent)
};

