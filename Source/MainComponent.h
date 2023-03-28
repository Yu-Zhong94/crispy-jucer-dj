/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MusiclibComponent.h"



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    //A base class for writing audio apps that stream from the audio i/o devices. 
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 
    //initialize default player in music library
    DJAudioPlayer player3{ formatManager };
    //initialize left deck
    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1 {&player1, formatManager, thumbCache};
    //initialize right deck
    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2 {&player2, formatManager, thumbCache} ;
    //initialize musiclibComponent, connect deckGUI and another player to musiclibComponent
    MusiclibComponent musiclibComponent{ &deckGUI1, &deckGUI2, &player3 };
    //mix audio source
    MixerAudioSource mixerSource; 


    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


//JUCE audio classes are required to play audio
//AudioFormatReader ¨C this is used to do the low - level audio file reading.
//AudioFormatReaderSource ¨C this wraps the AudioFormatReader and converts it into an AudioSource.
//AudioFormatManager ¨C this is used to create parsers for known audio formats.
//TransportSource ¨C this wraps the AudioFormatReaderSourceand provides higher level audio playback controls.
