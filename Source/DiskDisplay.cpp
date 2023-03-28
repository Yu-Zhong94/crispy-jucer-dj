/*
  ==============================================================================

    DiskDisplay.cpp
    Created: 13 Feb 2022 8:01:05am
    Author:  Yu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DiskDisplay.h"

//==============================================================================
DiskDisplay::DiskDisplay() :
                        fileLoaded(false),
                        relative_pos(0.0f)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
}

DiskDisplay::~DiskDisplay()
{
}

void DiskDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    double size = getWidth()> getHeight() ? getHeight() : getWidth();
    Image nullimage, diskimage;
    diskimage = imageFormat.loadFrom(file
        .getCurrentWorkingDirectory()
        .getFullPathName() + "/diskimage.png");
    nullimage = imageFormat.loadFrom(file
        .getCurrentWorkingDirectory()
        .getFullPathName() + "/nullimage.png");

    //if file is loaded, the circle start spining and 
    //paint a disk to the circle

    image = fileLoaded ? diskimage : nullimage;
    image = image.rescaled(size, size);
    AffineTransform transform(
            AffineTransform::translation((float)(getWidth()/2-image.getWidth()/2),
                (float)(getHeight()/2-image.getHeight()/2))
            .followedBy(affineTransform));
    g.drawImageTransformed(image, transform, false);

}


void DiskDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
void DiskDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    DBG("wfd: change received! ");
    repaint();
}
void DiskDisplay::getTransform(double relative_pos)
{
    double ratio = relative_pos * MathConstants<float>::twoPi;
    if (fileLoaded)
    {
        if (ratio != 0)
        {
            affineTransform = affineTransform.rotation(ratio, getWidth()/2, getHeight()/2);
        }
    }
    repaint();
}


void DiskDisplay::fileload(bool loaded)
{
    if (loaded == true)
    {
        fileLoaded = loaded;
        repaint();
    }
}

String DiskDisplay::getFormatName()
{
    return imageFormat.getFormatName();
}
bool DiskDisplay::canUnderstand(InputStream& input)
{
    return imageFormat.canUnderstand(input);
}
bool DiskDisplay::usesFileExtension(const File& possibleFile)
{
    return imageFormat.usesFileExtension(possibleFile);
}
Image DiskDisplay::decodeImage(InputStream& input)
{
    return imageFormat.decodeImage(input);
}
bool DiskDisplay::writeImageToStream(const Image& sourceImage, OutputStream& destStream)
{
    return imageFormat.writeImageToStream(sourceImage, destStream);
}