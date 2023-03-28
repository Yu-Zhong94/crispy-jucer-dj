/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource
{
public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    //Base class for objects that can produce a continuous stream of audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    //load file path
    void loadURL(URL audioURL);
    //set audio gain
    void setGain(double gain);
    //set audio speed
    void setSpeed(double ratio);
    //set audio position
    void setPosition(double posInSecs);
    //set relative position of audio
    void setPositionRelative(double pos);
    //return current position of audio
    double getCurrentPosition();
    //set recalling point for audio
    void setpoint(double posInSecs);
    //return recalling point for audio
    void getpoint();
    //set looping for audio
    void setLooping(bool shouldLoop);
    //check whether audio is playing
    bool isPlaying();
    //check whether audio is looping
    bool isLooping();
    //set reverb parameter
    void setParameters(const Reverb::Parameters& newParams);
    //start playing
    void start();
    //stop playing
    void stop();

    /** get the relative position of the playhead */
    double getPositionRelative();
    //set iir coefficients for iir filter
    void setCoefficients(const IIRCoefficients& newCoefficients);
    //set iir inactive
    void makeInactive();

private:
    bool fileloaded;
    double positionRelative;
    TimeSliceThread thread{ "audio file preview" };
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;

    //Creates an AudioTransportSource
    AudioTransportSource transportSource;
    //Creates a ResamplingAudioSource for a given input source.
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
    //Creates a ReverbAudioSource for a given input source.
    ReverbAudioSource reverbSource { &transportSource, false};
    //Creates a IIRFilterAudioSource for a given input source.
    IIRFilterAudioSource IIRFilterSource{ &transportSource, false };
};

