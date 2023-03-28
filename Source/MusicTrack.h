/*
  ==============================================================================

    MusicTrack.h
    Created: 14 Feb 2022 1:00:18am
    Author:  Yu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <iostream>
#include <fstream>

//==============================================================================
/*
*/

class MusicTrack : public juce::Component, 
                   public AudioSource
{
public:
    MusicTrack(const File& file, const int & id);
    ~MusicTrack() override;
    //Base class for objects that can produce a continuous stream of audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //void setAudio(const File& file);
    //play audio in music lib
    void start();
    //stop audio in music lib
    void stop();
    //check whether audio is playing
    bool isPlaying();
    //return file path
    File getFile();
    //return file id
    int getFileid();
    //return file name
    String getFilename();
    //return file length
    double getTimelength();
    //translate seconds to certain format file length
    String secondToDate(int result);
    //return certain format file length
    String getFilelength();

private:
    File getfile;
    int fileid;
    String filelength;
    double timelength;
    String filename;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
};
