/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 9 Feb 2022 3:05:34pm
    Author:  Yu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");

    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}
void PlaylistComponent::paintRowBackground( Graphics& g,
                                            int rowNumber,
                                            int width,
                                            int height,
                                            bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}
void PlaylistComponent::paintCell(  Graphics& g,
                                    int rowNumber,
                                    int columnId,
                                    int width,
                                    int height,
                                    bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        g.drawText(trackTitles[rowNumber], // we will change this later
            2, 1,
            width - 4, height,
            Justification::centredLeft,
            true);
    }

}

Component* PlaylistComponent::refreshComponentForCell( int rowNumber,
                                                       int columnId,
                                                       bool isRowSelected,
                                                       Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{ "play" };
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            //get my integer, which is the row number convert into a string.
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}
// create a class which inherits from text button, 
// which has two functions, a get IDand a set ID function.
// So when I create the button, I pass an ID on to it that 
// it remembers, and then when I get the button back in the event listener,
// I can just see what the ID was, and I'll know which row it was from 
// and I'll know which track to play.

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());

    std::cout << "PlaylistComponent::buttonClicked" << trackTitles[id]<< std::endl;
}