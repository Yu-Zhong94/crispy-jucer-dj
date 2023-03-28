/*
==============================================================================

DJAudioPlayer.cpp
Created: 13 Mar 2020 4:22:22pm
Author:  matthew

==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) 
: formatManager(_formatManager), positionRelative(0.0f),fileloaded(false)
{
}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    //toneGeneratorSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
    reverbSource.getNextAudioBlock(bufferToFill);
    //toneGeneratorSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
    //toneGeneratorSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {       
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, 
true)); 
        
        transportSource.setSource(newSource.get(), 0, &thread, reader->sampleRate);
        readerSource.reset(newSource.release());
        DBG("player : file loaded");
        fileloaded = true;
    }
}
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        DBG("DJAudioPlayer::setGain gain should be between 0 and 1" );
    }
    else {
        transportSource.setGain(gain);
    }
}
void DJAudioPlayer::setSpeed(double ratio)
{
  if (ratio <= 0 || ratio > 100.0)
    {
      DBG("DJAudioPlayer::setSpeed ratio should be between 0 and 100");
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double positionRelative)
{
     if (positionRelative < 0 || positionRelative > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative positionRelative should be between 0 and 1" << std::endl;
    }
    else {
        double pos = transportSource.getLengthInSeconds() * positionRelative;
        setPosition(pos);
    }
}


void DJAudioPlayer::start()
{
    transportSource.start();
    DBG("player : file start");
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
    DBG("player : file stop");
}

double DJAudioPlayer::getPositionRelative() 
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
double DJAudioPlayer::getCurrentPosition()
{
    return transportSource.getCurrentPosition();
}
void DJAudioPlayer::setLooping(bool shouldLoop)
{
    if (fileloaded)
    {
        if (shouldLoop)
        {
            readerSource->setLooping(true);
            DBG("DJAudioPlayer::setLooping");
        }
        else
        {
            readerSource->setLooping(false);
        }
    }
    else {
        DBG("file isn't loaded.");
    }
}
bool DJAudioPlayer::isLooping()
{
    return transportSource.isLooping();
}
bool DJAudioPlayer::isPlaying()
{
    return transportSource.isPlaying();
}
void DJAudioPlayer::setParameters(const Reverb::Parameters& newParams)
{
    reverbSource.setParameters(newParams);
}


void DJAudioPlayer::setpoint(double pos)
{
    //remember this passing value
    positionRelative = pos;
    //draw this value on disk or waveform
}

void DJAudioPlayer::getpoint()
{
    transportSource.setPosition(positionRelative);
}
void DJAudioPlayer::setCoefficients(const IIRCoefficients& newCoefficients)
{
    IIRFilterSource.setCoefficients(newCoefficients);
}
void DJAudioPlayer::makeInactive()
{
    IIRFilterSource.makeInactive();
}
//void DJAudioPlayer::setAmplitude(float newAmplitude)
//{
//    toneGeneratorSource.setAmplitude(newAmplitude);
//}
//
//void DJAudioPlayer::setFrequency(double newFrequencyHz)
//{
//    toneGeneratorSource.setFrequency(newFrequencyHz);
//}