/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player),
               waveformDisplay(formatManagerToUse, cacheToUse, _player),
               diskDisplay(),
               shouldloop(false), iirInactive(false)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(recButton);
    addAndMakeVisible(pointButton);

    //addAndMakeVisible(rememberButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(iirButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    //addAndMakeVisible(posSlider);
    addAndMakeVisible(iir1);
    addAndMakeVisible(iir2);
    addAndMakeVisible(iir3);
    addAndMakeVisible(iir4);
    addAndMakeVisible(iir5);
    addAndMakeVisible(iir6);
    //addAndMakeVisible(amplitude);
    //addAndMakeVisible(frequency);
    addAndMakeVisible(roomSize);
    addAndMakeVisible(damping);
    addAndMakeVisible(wetLevel);
    addAndMakeVisible(dryLevel);
    addAndMakeVisible(width);
    addAndMakeVisible(freezeMode);

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(diskDisplay);


    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    recButton.addListener(this);
    pointButton.addListener(this);

    loopButton.addListener(this);
    iirButton.addListener(this);
    //rememberButton.addListener(this);
 
    volSlider.addListener(this);
    speedSlider.addListener(this);
    //posSlider.addListener(this);
    iir1.addListener(this);
    iir2.addListener(this);
    iir3.addListener(this);
    iir4.addListener(this);
    iir5.addListener(this);
    iir6.addListener(this);
    //amplitude.addListener(this);
    //frequency.addListener(this);
    roomSize.addListener(this);
    damping.addListener(this);
    wetLevel.addListener(this);
    dryLevel.addListener(this);
    width.addListener(this);
    freezeMode.addListener(this);

    //volumn
    volSlider.setSliderStyle(Slider::Rotary);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volSlider.setRotaryParameters(MathConstants<float>::pi * 1.2f, MathConstants<float>::pi * 2.8f, false);
    volSlider.setPopupDisplayEnabled(true, false, this);
    volSlider.setTextValueSuffix(" db");
    volSlider.setRange(0.0f, 1.0f);
    volSlider.setValue(1.0f);

    //speed up or slow down
    speedSlider.setSliderStyle(Slider::IncDecButtons);
    speedSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    speedSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Horizontal);
    speedSlider.setRange(0.0f, 100.0f, 0.01);
    speedSlider.setValue(1.0f);

    //IIRfilter
    iir1.setSliderStyle(Slider::LinearBar);
    iir1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    iir1.setRange(-50.0f, 50.0f);
    iir1.setValue(1.0f);
    iir1.setColour(Slider::trackColourId, Colours::orange.withAlpha(0.5f));
    
    iir2.setSliderStyle(Slider::LinearBar);
    iir2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    iir2.setRange(-50.0f, 50.0f);
    iir2.setValue(1.0f);
    iir2.setColour(Slider::trackColourId, Colours::orange.withAlpha(0.5f));

    iir3.setSliderStyle(Slider::LinearBar);
    iir3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    iir3.setRange(-50.0f, 50.0f);
    iir3.setValue(1.0f);
    iir3.setColour(Slider::trackColourId, Colours::orange.withAlpha(0.5f));

    iir4.setSliderStyle(Slider::LinearBar);
    iir4.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    iir4.setRange(-50.0f, 50.0f);
    iir4.setValue(0.5f);
    iir4.setColour(Slider::trackColourId, Colours::orange.withAlpha(0.5f));

    iir5.setSliderStyle(Slider::LinearBar);
    iir5.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    iir5.setRange(-50.0f, 50.0f);
    iir5.setValue(1.0f);
    iir5.setColour(Slider::trackColourId, Colours::orange.withAlpha(0.5f));

    iir6.setSliderStyle(Slider::LinearBar);
    iir6.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    iir6.setRange(-50.0f, 50.0f);
    iir6.setValue(1.0f);
    iir6.setColour(Slider::trackColourId, Colours::orange.withAlpha(0.5f));
    //Reverb::Parameters
    roomSize.setSliderStyle(Slider::LinearVertical);
    damping.setSliderStyle(Slider::LinearVertical);
    wetLevel.setSliderStyle(Slider::LinearVertical);
    dryLevel.setSliderStyle(Slider::LinearVertical);
    width.setSliderStyle(Slider::LinearVertical);
    freezeMode.setSliderStyle(Slider::LinearVertical);

    roomSize.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    damping.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    wetLevel.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    dryLevel.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    width.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    freezeMode.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    roomSize.setRange(0.0f, 1.0f);
    roomSize.setValue(0.5f);
    damping.setRange(0.0f, 1.0f);
    damping.setValue(0.5f);
    wetLevel.setRange(0.0f, 1.0f);
    wetLevel.setValue(0.33f);
    dryLevel.setRange(0.0f, 1.0f);
    dryLevel.setValue(0.4f);
    width.setRange(0.0f, 1.0f);
    width.setValue(1.0f);
    freezeMode.setRange(0.0f, 1.0f);
    freezeMode.setValue(0.0f);

    startTimer(500);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.setGradientFill(ColourGradient(Colours::grey, getWidth() / 2, getHeight() / 2,
        getLookAndFeel().findColour(ResizableWindow::backgroundColourId),
        getWidth() / 4, getHeight() / 4, true));
    g.fillRect(0, 0, getWidth(),getHeight());

}

void DeckGUI::resized()
{
    double rowH = getHeight() / 16; 
    double colW = getWidth() / 9;
    playButton.setBounds(0, 0, colW * 2, rowH);
    stopButton.setBounds(0, rowH, colW * 2, rowH);
    loopButton.setBounds(0, rowH * 2, colW * 2, rowH);

    waveformDisplay.setBounds(colW * 2, 0, 7 * colW, rowH * 3);
    diskDisplay.setBounds(2.5 * colW, rowH * 3, 5.5 * colW, rowH * 10);
    volSlider.setBounds(0, rowH * 3, 2*colW, rowH * 3);

    iir1.setBounds(0, rowH * 6, 2 * colW, rowH);
    iir2.setBounds(0, rowH * 7, 2 * colW, rowH);
    iir3.setBounds(0, rowH * 8, 2 * colW, rowH);
    iir4.setBounds(0, rowH * 9, 2 * colW, rowH);
    iir5.setBounds(0, rowH * 10, 2 * colW, rowH);
    iir6.setBounds(0, rowH * 11, 2 * colW, rowH);
    iirButton.setBounds(0, rowH * 12, 2 * colW, rowH);
    //posSlider.setBounds(0, rowH * 9, 2*colW, rowH * 3);
    
    loadButton.setBounds(0, rowH * 13, colW, rowH);
    recButton.setBounds(0, rowH * 14, colW, rowH);
    pointButton.setBounds(0, rowH * 15, colW, rowH);

    //amplitude.setBounds(colW * 1, rowH * 13, colW, rowH * 3);
    //frequency.setBounds(colW * 2, rowH * 13, colW, rowH * 3);
    speedSlider.setBounds(colW*1.5, rowH * 13, colW*1.5, rowH*2);

    roomSize.setBounds(colW*3, rowH * 13, colW, rowH * 3);
    damping.setBounds(colW*4, rowH * 13, colW, rowH * 3);
    wetLevel.setBounds(colW*5, rowH * 13, colW, rowH * 3);
    dryLevel.setBounds(colW*6, rowH * 13, colW, rowH * 3);
    width.setBounds(colW*7, rowH * 13, colW, rowH * 3);
    freezeMode.setBounds(colW*8, rowH * 13, colW, rowH * 3);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        DBG("Play button was clicked");
        player->start();

    }
    if (button == &stopButton)
    {
        DBG("Stop button was clicked ");
        player->stop();
    }
    if (button == &loadButton)
    {
        FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()});
            diskDisplay.fileload(true);
            if (shouldloop)
            {
                player->setLooping(true);
            }
            else
            {
                player->setLooping(false);
            }
        }
    }
    //set iir
    if (button == &iirButton)
    {
        iirInactive = button->getToggleState();
    }
    //set loop
    if (button == &loopButton)
    {
        shouldloop = button->getToggleState();
        
        if (shouldloop)
        {
            player->setLooping(true);
        }
        else
        {
            player->setLooping(false);
        }
    }
    //set a point to recall
    if (button == &recButton)
    {
        player->getpoint();
    }
    if (button == &pointButton)
    {
        player->setpoint(player->getCurrentPosition());
        waveformDisplay.setPoint(player->getPositionRelative());
    }

}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    //if (slider == &amplitude)
    //{
    //    player->setAmplitude(slider->getValue());
    //}
    //if (slider == &frequency)
    //{
    //    player->setFrequency(slider->getValue());
    //}
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (iirInactive == false)
    {
        if (slider == &iir1 || slider == &iir2 || slider == &iir3 || slider == &iir4 || slider == &iir5 || slider == &iir6)
        {
            player->setCoefficients(IIRCoefficients(iir1.getValue(), iir2.getValue(), iir3.getValue(),
                                    iir4.getValue(), iir5.getValue(), iir6.getValue()));
        }
    }
    else
    {
        player->makeInactive();
    }

    //if (slider == &posSlider)
    //{
    //    player->setPositionRelative(slider->getValue());
    //}
    if (slider == &roomSize)
    {
        newParams.roomSize = slider->getValue();
        player->setParameters(newParams);
    }
    if (slider == &damping)
    {
        newParams.damping = slider->getValue();
        player->setParameters(newParams);
    }
    if (slider == &wetLevel)
    {
        newParams.wetLevel = slider->getValue();
        player->setParameters(newParams);
    }
    if (slider == &dryLevel)
    {
        newParams.dryLevel = slider->getValue();
        player->setParameters(newParams);
    }
    if (slider == &width)
    {
        newParams.width = slider->getValue();
        player->setParameters(newParams);
    }
    if (slider == &freezeMode)
    {
        newParams.freezeMode = slider->getValue();
        player->setParameters(newParams);
    }
}


bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
    DBG("DeckGUI::isInterestedInFileDrag");
    return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
    DBG("DeckGUI::filesDropped");
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{ File{files[0]} });
    diskDisplay.fileload(true);
    if (shouldloop)
    {
        player->setLooping(true);
    }
    else
    {
        player->setLooping(false);
    }
  }
}

bool DeckGUI::isInterestedInDragSource(const SourceDetails& dragSourceDetails)
{
    return true;
}
void DeckGUI::itemDropped(const SourceDetails& dragSourceDetails)
{
    filesDropped(dragSourceDetails.description.toString(), 1, 1);

}

void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
    diskDisplay.getTransform(
        player->getPositionRelative());
    //posSlider.setValue(player->getPositionRelative());
}
    

