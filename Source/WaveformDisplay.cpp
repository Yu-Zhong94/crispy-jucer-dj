/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse,
                                 DJAudioPlayer* _player) :
                                 player(_player),
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0),point(0)
                          
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

  audioThumb.addChangeListener(this);

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::orange);
    if(fileLoaded)
    {
      audioThumb.drawChannels(g, 
        getLocalBounds(), 
        0, 
        audioThumb.getTotalLength(), 
        1.0f
      );
      addAndMakeVisible(posSlider);
      posSlider.addListener(this);
      posSlider.setSliderStyle(Slider::LinearBar);
      posSlider.setRange(0, audioThumb.getTotalLength(),1);
      posSlider.setColour(Slider::trackColourId, Colours::lightgreen.withAlpha(0.5f));
      posSlider.setValue(position * audioThumb.getTotalLength());
      posSlider.setTextValueSuffix(" s");
      posSlider.setTextBoxIsEditable(false);
     
      //g.setColour(Colours::lightgreen);
      //g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else 
    {
      g.setFont (20.0f);
      g.drawText ("File not loaded...", getLocalBounds(),
                  Justification::centred, true);   // draw some placeholder text
    }
    g.setColour(Colours::red);
    g.drawLine(point * getWidth(), 0, point * getWidth(), getHeight());

}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    posSlider.setBounds(getLocalBounds());
}

void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  //double filelength = audioThumb.getTotalLength();
  if (fileLoaded)
  {
    std::cout << "wfd: loaded! " << std::endl;
    repaint();
  }
  else {
    std::cout << "wfd: not loaded! " << std::endl;
  }
}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;
    repaint();
}
void WaveformDisplay::sliderValueChanged(Slider* slider)
{
    if (slider == &posSlider)
    {
        player->setPosition(slider->getValue());
    }
    
}
void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position && pos > 0 )
  {
    position = pos;
    repaint();
  }
}
void WaveformDisplay::setPoint(double pos)
{
    point = pos;
    repaint();
}


