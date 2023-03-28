/*
  ==============================================================================

    DiskDisplay.h
    Created: 13 Feb 2022 8:01:05am
    Author:  Yu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/* a circle can be dragged to set speed of the player, 
it starts spining right after the player is started, and vice versa.
it changed the circle looks to a disk once the disk is loaded.
*/
class DiskDisplay  : public juce::Component,
                     public ChangeListener,
                     public ImageFileFormat
{
public:
    DiskDisplay();
    ~DiskDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    //implement this method to receive the callback.
    void changeListenerCallback(ChangeBroadcaster* source) override;
    //set fileloaded situation
    void fileload(bool loaded);
    //set speed of circle
    void getTransform(double relative_pos);

    //ImageFileFormat override function
    String getFormatName()override;
    bool canUnderstand(InputStream& input)override;
    bool usesFileExtension(const File& possibleFile)override;
    Image decodeImage(InputStream& input)override;
    bool writeImageToStream(const Image& sourceImage, OutputStream& destStream)override;

    

private:
    //reading and writing PNG files
    PNGImageFormat imageFormat;
    bool fileLoaded;
    Image image;
    File file;
    double relative_pos;
    //Creates an identity transform
    AffineTransform affineTransform;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiskDisplay)
};
