/*
  ==============================================================================

    MusiclibComponent.cpp
    Created: 9 Feb 2022 3:05:34pm
    Author:  Yu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusiclibComponent.h"

//==============================================================================
MusiclibComponent::MusiclibComponent(DeckGUI* _deck1,
    DeckGUI* _deck2,
    DJAudioPlayer* _player3) :
    deck1(_deck1),
    deck2(_deck2),
    player3(_player3)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    std::unique_ptr<TableHeaderComponent> sethead(new TableHeaderComponent());
    header = std::move(sethead);
    header->addColumn("ID", 1, 50);
    header->addColumn("Track Title", 2, 300);
    header->addColumn("Track Length", 3, 200);
    header->addColumn("", 4, 250);

    header->setColumnVisible(1, true);
    header->setSortColumnId(1, false);
    header->addListener(this);
    tableComponent.setHeader(std::move(header));

    tableComponent.addComponentListener(this);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);

    searchInput.setTextToShowWhenEmpty("Search", Colours::white);
    searchInput.setPopupMenuEnabled(true);
    searchInput.addListener(this);
    addAndMakeVisible(searchInput);

    searchFiles.addListener(this);
    addAndMakeVisible(searchFiles);

    addFiles.addListener(this);
    addAndMakeVisible(addFiles);

    std::string filename;
    std::ifstream readFile("filename.txt");
    // Use a while loop together with the getline() 
    // function to read the file line by line
    while (std::getline(readFile, filename)) {
        // Output the text from the file
        if (filename.size() != NULL)
        {
            int key = getNumRows();
            ++key;
            MusicTrack* metaSource = new MusicTrack{ File(filename) ,key };
            //DBG("key:"<< key);
            track.push_back(metaSource);
        }
    }
    readFile.close();
}

MusiclibComponent::~MusiclibComponent()
{
}

void MusiclibComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("MusiclibComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void MusiclibComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() / 5;
    double colW = getWidth() / 5;
    tableComponent.setBounds(0, rowH, getWidth(), 4 * rowH);
    searchInput.setBounds(colW * 2, 0, colW * 1.8, rowH);
    searchFiles.setBounds(4 * colW, 0, colW , rowH);
    addFiles.setBounds(0, 0, colW, rowH);
}

int MusiclibComponent::getNumRows()
{
    return track.size();
}
void MusiclibComponent::paintRowBackground(Graphics& g,
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


Component* MusiclibComponent::refreshComponentForCell(int rowNumber,
                                                    int columnId,
                                                    bool isRowSelected,
                                                    Component* existingComponentToUpdate)
{
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            ComboBox *box = new ComboBox{ "choose deck" };
            box->setText("choose deck");
            String id{ String(rowNumber) };
            box->setComponentID(id);
            box->addItem("Load Left Deck", 1);
            box->addItem("Load Right Deck", 2);
            box->addItem("Start (default)", 3);
            box->addItem("Stop (default)", 4);
            //box->setSelectedId(3);
            box->addListener(this);
            existingComponentToUpdate = box;
        }
    }
    if (columnId == 5)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton *btn = new TextButton{ "play" };
            DBG("rowNumber: "<<rowNumber);
            String id{String (rowNumber)};
            //String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            //get my integer, which is the row number convert into a string.
            btn->addListener(this); 
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}
void MusiclibComponent::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    int playerid = comboBoxThatHasChanged->getSelectedId();
    int id = std::stoi(comboBoxThatHasChanged->getComponentID().toStdString());
    if (playerid == 1)
    {
        deck1->filesDropped(track[id]->getFile().getFullPathName(), 1, 1);
    }
    if (playerid == 2)
    {
        deck2->filesDropped(track[id]->getFile().getFullPathName(), 1, 1);
    }
    if (playerid == 3)
    {
        player3->loadURL(URL(track[id]->getFile()));
        player3->start();
    }
    if (playerid == 4)
    {
        player3->stop();
    }
}
void MusiclibComponent::buttonClicked(Button* button)
{
    if (button == &addFiles)
    {
        DBG("MusiclibComponent::buttonClicked addfiles");
        FileChooser chooser{ "Select files..." };
        if (chooser.browseForMultipleFilesOrDirectories())
        {
            int key = getNumRows();
            for each (File i in chooser.getResults())
            {
                setFile(i);
                ++key;
                MusicTrack* metaSource = new MusicTrack{ i ,key };
                track.push_back(metaSource);
            }
            tableComponent.updateContent();
        }
    }
    if (button == &searchFiles)
    {
        String music = searchInput.getTextValue().getValue();
        if (music.containsNonWhitespaceChars())
        {
            for (size_t i = 0; i < track.size(); i++)
            {
                if (track[i]->getFilename().containsIgnoreCase(music))
                {
                    //DBG("find track:" << track[i]->fileid << track[i]->getFilename());
                    track.insert(track.begin(), track.at(i));
                    track.erase(track.begin()+i+1);
                    break;
                }
            }
            tableComponent.repaint();
        }
    }
    //if (button->getComponentID().length())
    //{
    //    int id = std::stoi(button->getComponentID().toStdString());
    //    DBG("play track:" << id);
    //    if (box->getSelectedItemIndex() == 1)
    //    {
    //        player1->loadURL(URL(track[id]->getfile));
    //        player1->start();
    //    }
    //    if (box->getSelectedItemIndex() == 2)
    //    {
    //        player2->loadURL(URL(track[id]->getfile));
    //        player2->start();
    //    }
    //    if (box->getSelectedItemIndex() == 3)
    //    {
    //        player3->loadURL(URL(track[id]->getfile));
    //        player3->start();
    //    }
    //}
}

void MusiclibComponent::paintCell(Graphics& g,
                                int rowNumber,
                                int columnId,
                                int width,
                                int height,
                                bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
        {
            g.drawText(String(track[rowNumber]->getFileid()), // we will change this later
                2, 1,
                width - 4, height,
                Justification::centredLeft,
                true);
        }
        if (columnId == 2)
        {
            g.drawText(track[rowNumber]->getFilename(), // we will change this later
                2, 1,
                width - 4, height,
                Justification::centredLeft,
                true);
        }
        if (columnId == 3)
        {
            g.drawText(track[rowNumber]->getFilelength(), // we will change this later
                2, 2,
                width - 4, height,
                Justification::centredLeft,
                true);
        }
    }
}

bool MusiclibComponent::isInterestedInFileDrag(const StringArray& files)
{
    DBG("DeckGUI::isInterestedInFileDrag");
    return true;
}

void MusiclibComponent::filesDropped(const StringArray& files, int x, int y)
{
    DBG("DeckGUI::filesDropped");
    if (files.size() != 0)
    {
        int key = getNumRows();
        for each (String i in files)
        {
            setFile(File(i));
            ++key;
            MusicTrack* metaSource = new MusicTrack{ File(i) ,key};
            track.push_back(metaSource);
        }
        tableComponent.updateContent();
    }
}

var MusiclibComponent::getDragSourceDescription(const SparseSet< int >& selectedRows)
{
// for our drag description, we'll just make a comma-separated list of the selected row
// numbers - this will be picked up by the drag target and displayed in its box.
    File filename = track[tableComponent.getSelectedRow()]->getFile();
    return filename.getFullPathName();
}

void MusiclibComponent::setFile(const File& file)
{
    std::fstream fs;
    fs.open("filename.txt", std::fstream::out | std::fstream::app);
    if (fs.is_open())
    {
        fs << file.getFullPathName() << "\n";
        fs.close();
    }
}
 // This is overloaded from TableListBoxModel, 
 // and tells us that the user has clicked a table header
 // to change the sort order.

void MusiclibComponent::tableColumnsChanged(TableHeaderComponent* tableHeader)
{
    tableComponent.tableSortOrderChanged(tableHeader);
}
void MusiclibComponent::tableColumnsResized(TableHeaderComponent* tableHeader)
{
    tableComponent.tableColumnsResized(tableHeader);
}
void MusiclibComponent::tableSortOrderChanged(TableHeaderComponent* tableHeader)
{
    DBG("tableSortOrderChanged  "<< tableHeader->getSortColumnId());

    if (tableHeader->isSortedForwards())
    {
        DBG("tableSortOrderChanged :sortedForwards");
        if (tableHeader->getSortColumnId() == 1)
        {
            std::sort(track.begin(), track.end(),
                [](MusicTrack* id1, MusicTrack* id2)
                {
                    int num1 = id1->getFileid();
                    int num2 = id2->getFileid();
                    return (num1 < num2);
                });
        }
        if (tableHeader->getSortColumnId() == 2)
        {
            std::sort(track.begin(), track.end(),
                [](MusicTrack* id1, MusicTrack* id2)
                {
                    String num1 = id1->getFilename();
                    String num2 = id2->getFilename();
                    return (num1 < num2);
                });
        }
        if (tableHeader->getSortColumnId() == 3)
        {
            std::sort(track.begin(), track.end(),
                [](MusicTrack* id1, MusicTrack* id2)
                {
                    double num1 = id1->getTimelength();
                    double num2 = id2->getTimelength();
                    return (num1 < num2);
                });
        }

    }else
    {
        DBG("tableSortOrderChanged: sortedBackwards");
        if (tableHeader->getSortColumnId() == 1)
        {
            std::sort(track.begin(), track.end(),
                [](MusicTrack* id1, MusicTrack* id2)
                {
                    int num1 = id1->getFileid();
                    int num2 = id2->getFileid();
                    return (num1 > num2);
                });
        }
        if (tableHeader->getSortColumnId() == 2)
        {
            std::sort(track.begin(), track.end(),
                [](MusicTrack* id1, MusicTrack* id2)
                {
                    String num1 = id1->getFilename();
                    String num2 = id2->getFilename();
                    return (num1 > num2);
                });
        }
        if (tableHeader->getSortColumnId() == 3)
        {
            std::sort(track.begin(), track.end(),
                [](MusicTrack* id1, MusicTrack* id2)
                {
                    double num1 = id1->getTimelength();
                    double num2 = id2->getTimelength();
                    return (num1 > num2);
                });
        }
    }
}
