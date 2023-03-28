/*
  ==============================================================================

    MusicTrack.cpp
    Created: 14 Feb 2022 1:00:18am
    Author:  Yu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicTrack.h"

//==============================================================================
//MusicTrack::MusicTrack( AudioFormatManager& _formatManager)
//    : getfile(File()), fileid(0),
//    filename(String()),filelength(String()),
//    formatManager(_formatManager)
//{
//    //formatManager = _formatManager;
//}
MusicTrack::MusicTrack(const File& _file, const int& _id)
        : getfile(_file),fileid(_id), timelength(0.0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    auto* reader = formatManager.createReaderFor(getfile);
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
            true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        filename = getfile.getFileNameWithoutExtension();
        timelength = transportSource.getLengthInSeconds();
        filelength = secondToDate((int)transportSource.getLengthInSeconds());
        readerSource.reset(newSource.release());
    }
}

MusicTrack::~MusicTrack()
{
}

String MusicTrack::secondToDate(int result) 
{
    String length;
    String h = String(floor(result / 3600));
    String m = String(floor((result / 60 % 60)));
    String s = String(floor((result % 60)));
    if (h == "0")
    {
        length = m + ":" + s;
        if (m == "0")
        {
            length = "0:" + s;
        }
    }
    else
    {
        length = h + ":" + m + ":" + s;
    }
    return length;
}
void MusicTrack::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void MusicTrack::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}
void MusicTrack::releaseResources()
{
    transportSource.releaseResources();
}
void MusicTrack::start()
{
    transportSource.start();
}
void MusicTrack::stop()
{
    transportSource.stop();
}
bool MusicTrack::isPlaying()
{
    return transportSource.isPlaying();
}
//void MusicTrack::setAudio(const File& file)
//{
//    AudioFormatManager formatManager;
//    formatManager.registerBasicFormats();
//    auto* reader = formatManager.createReaderFor(file);
//    if (reader != nullptr) // good file!
//    {
//        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
//            true));
//        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
//        //filename = file.getFileNameWithoutExtension();
//        //filelength = secondToDate((int)transportSource.getLengthInSeconds());
//        readerSource.reset(newSource.release());
//    }
//}

File MusicTrack::getFile()
{
    return getfile;
}
String MusicTrack::getFilename() 
{
    return filename;
}
String MusicTrack::getFilelength() 
{
    return filelength;
}
int MusicTrack::getFileid() 
{
    return fileid;
}
double MusicTrack::getTimelength()
{
    return timelength;
}