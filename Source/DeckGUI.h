/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "DiskDisplay.h"
//#include "MusiclibComponent.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public Slider::SliderLayout,
                   public FileDragAndDropTarget, 
                   public DragAndDropTarget,
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse);
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;
    /** implement FileDragAndDropTarget */
    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 
    /** implement DragAndDropTarget, get items from music library component */
    bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;
    void itemDropped(const SourceDetails& dragSourceDetails)override;
    /** implement Timer */
    void timerCallback() override; 

private:
    //buttons
    TextButton playButton{ "PLAY" },
        stopButton{ "STOP" },
        loadButton{ "LOAD" },
        recButton{ "REC" },
        pointButton{ "*" };
    //loop button
    ToggleButton loopButton{ "LOOP" };
    bool shouldloop;

    //volslider and speedslider
    Slider volSlider; 
    Slider speedSlider;

    //reverb parameter
    Slider roomSize;
    Slider damping;
    Slider wetLevel;
    Slider dryLevel;
    Slider width;
    Slider freezeMode;
    Reverb::Parameters newParams;

    //iir parameter
    Slider iir1;
    Slider iir2;
    Slider iir3;
    Slider iir4;
    Slider iir5;
    Slider iir6;
    bool iirInactive;
    ToggleButton iirButton{ "IIR Disabled" };
    //create a waveformDisplay
    WaveformDisplay waveformDisplay;
    //create a diskDisplay
    DiskDisplay diskDisplay;
    //create a pointer pointing to DJAudioPlayer
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
