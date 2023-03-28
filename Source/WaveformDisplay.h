/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once
#include "DJAudioPlayer.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener,
                           public Slider::Listener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse ,
                    DJAudioPlayer* player);
    ~WaveformDisplay();

    void paint (Graphics&) override;
    void resized() override;
    //implement this method to receive the callback.
    void changeListenerCallback (ChangeBroadcaster *source) override;
    //Specifies the file that contains the audio file.
    void loadURL(URL audioURL);
    //remember the position of the playhead
    void setPoint(double pos);
    //set the relative position of the playhead
    void setPositionRelative(double pos);
    //Called when the position slider's value is changed.
    void sliderValueChanged(Slider* slider) override;

private:
    //Creates an audio thumbnail
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;
    double point;
    //Creates a slider
    Slider posSlider;
    //Creates a pointer pointing to DJAudioPlayer class
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
//We tell register with the AudioThumbnail as a change listener.This means we will be 
//told when the waveform drawing is complete.We load a file into the AudioThumbnail.
//AudioThumbnail sends us changes as it is drawing the waveform.Each time we receive a change, 
//we call repaint, causing the waveform display to be updated.

//The Timer class allows you to create a separate thread in your application which can 
//run in parallel with the other threads.This thread can be instructed to periodically 
//call a function.
//Timer is create a separate thread in your application.When the timer keeps calling, 
//it will keep calling timerCallback, and what we want to do with Timer is repeatedly 
//call the getand set position.