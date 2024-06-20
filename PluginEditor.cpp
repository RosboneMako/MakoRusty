/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MakoBiteAudioProcessorEditor::MakoBiteAudioProcessorEditor (MakoBiteAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{    
    //R1.00 Create SLIDER ATTACHMENTS so our parameter vars get adjusted automatically for Get/Set states.
    ParAtt[e_Gain] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "gain", sldKnob[e_Gain]);
    ParAtt[e_NGate] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "ngate", sldKnob[e_NGate]);
    ParAtt[e_Drive] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "drive", sldKnob[e_Drive]);
    ParAtt[e_EQ] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "eq", sldKnob[e_EQ]);
    ParAtt[e_EQ1] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "eq1", sldKnob[e_EQ1]);
    ParAtt[e_EQ2] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "eq2", sldKnob[e_EQ2]);
    ParAtt[e_EQ3] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "eq3", sldKnob[e_EQ3]);
    ParAtt[e_EQ4] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "eq4", sldKnob[e_EQ4]);
    ParAtt[e_EQ5] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "eq5", sldKnob[e_EQ5]);
    ParAtt[e_IR] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "ir", sldKnob[e_IR]);
    ParAtt[e_IRon] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "iron", sldKnob[e_IRon]);
    ParAtt[e_Mono] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "mono", sldKnob[e_Mono]);
    ParAtt[e_Comp] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "comp", sldKnob[e_Comp]);
    ParAtt[e_LoCut] = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "locut", sldKnob[e_LoCut]);
        
    imgBackground = juce::ImageCache::getFromMemory(BinaryData::rustyback_jpg, BinaryData::rustyback_jpgSize);

    //****************************************************************************************
    //R1.00 Add GUI CONTROLS
    //****************************************************************************************
    GUI_Init_Large_Slider(&sldKnob[e_Gain], audioProcessor.Setting[e_Gain],0.0f, 1.0f,.01f,"", 1, 0xFFFF0000);
    GUI_Init_Large_Slider(&sldKnob[e_NGate], audioProcessor.Setting[e_NGate], 0.0f, 1.0f, .01f, "", 1, 0xFFFF0000);
    GUI_Init_Large_Slider(&sldKnob[e_Drive], audioProcessor.Setting[e_Drive], 0.0f, 1.0f, .01f, "", 1, 0xFFFF0000);
    GUI_Init_Large_Slider(&sldKnob[e_Comp], audioProcessor.Setting[e_Comp], 0.0f, 1.0f, .01f, "", 1, 0xFFFF0000);
    GUI_Init_Large_Slider(&sldKnob[e_EQ], audioProcessor.Setting[e_EQ], 0, 10, 1, "", 1, 0xFFFF8000);
    GUI_Init_Large_Slider(&sldKnob[e_EQ1], audioProcessor.Setting[e_EQ1], -12.0f, 12.0f, .1f, "", 2, 0xFFFF8000);
    GUI_Init_Large_Slider(&sldKnob[e_EQ2], audioProcessor.Setting[e_EQ2], -12.0f, 12.0f, .1f, "", 2, 0xFFFF8000);
    GUI_Init_Large_Slider(&sldKnob[e_EQ3], audioProcessor.Setting[e_EQ3], -12.0f, 12.0f, .1f, "", 2, 0xFFFF8000);
    GUI_Init_Large_Slider(&sldKnob[e_EQ4], audioProcessor.Setting[e_EQ4], -12.0f, 12.0f, .1f, "", 2, 0xFFFF8000);
    GUI_Init_Large_Slider(&sldKnob[e_EQ5], audioProcessor.Setting[e_EQ5], -12.0f, 12.0f, .1f, "", 2, 0xFFFF8000);

    GUI_Init_Small_Slider(&sldKnob[e_IR], audioProcessor.Setting[e_IR], 1, 5, 1, "");
    GUI_Init_Small_Slider(&sldKnob[e_IRon], audioProcessor.Setting[e_IRon], 0, 1, 1, "");
    GUI_Init_Small_Slider(&sldKnob[e_Mono], audioProcessor.Setting[e_Mono], 0, 1, 1, "");    
    GUI_Init_Small_Slider(&sldKnob[e_LoCut], audioProcessor.Setting[e_LoCut], 20, 200, 5, "");
        
    //R1.00 Update the Look and Feel (Global colors) so drop down menu is the correct color. 
    getLookAndFeel().setColour(juce::DocumentWindow::backgroundColourId, juce::Colour(32, 32, 32));
    getLookAndFeel().setColour(juce::DocumentWindow::textColourId, juce::Colour(255, 255, 255));
    getLookAndFeel().setColour(juce::DialogWindow::backgroundColourId, juce::Colour(32, 32, 32));
    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colour(0, 0, 0));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour(192, 0, 0));
    getLookAndFeel().setColour(juce::TextButton::buttonOnColourId, juce::Colour(192, 0, 0));
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colour(0, 0, 0));
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colour(0, 0, 0));
    getLookAndFeel().setColour(juce::ListBox::backgroundColourId, juce::Colour(32, 32, 32));
    getLookAndFeel().setColour(juce::Label::backgroundColourId, juce::Colour(32, 32, 32));

    //R1.00 Define our control positions to make drawing easier.
    KNOB_DefinePosition(e_Gain,    50, 50, 40, 40, "Gain"); 
    KNOB_DefinePosition(e_NGate,   50, 100, 40, 40, "Gate");
    
    KNOB_DefinePosition(e_EQ1,    90, 65, 60, 60, UIS_Band1);
    KNOB_DefinePosition(e_EQ2,   150, 65, 60, 60, UIS_Band2);
    KNOB_DefinePosition(e_EQ3,   210, 65, 60, 60, UIS_Band3);
    KNOB_DefinePosition(e_EQ4,   270, 65, 60, 60, UIS_Band4);
    KNOB_DefinePosition(e_EQ5,   330, 65, 60, 60, UIS_Band5);
    KNOB_DefinePosition(e_Drive, 390, 65, 60, 60, "Drive");

    KNOB_DefinePosition(e_Comp, 450, 50, 40, 40, "Comp");
    KNOB_DefinePosition(e_EQ,   450, 100, 40, 40, "EQ Band");

    KNOB_DefinePosition(e_IR,    150, 133, 60, 20, "IR Model");
    KNOB_DefinePosition(e_IRon,  210, 133, 60, 20, "IR On");
    KNOB_DefinePosition(e_Mono,  270, 133, 60, 20, "Stereo/Mono");
    KNOB_DefinePosition(e_LoCut, 330, 133, 60, 20, "Low Cut");

    Knob_Cnt = 14;

    //R1.00 Update our filter text strings.
    Band_SetFilterValues(false);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //R1.00 Set the window size.
    setSize(540, 160);
}

MakoBiteAudioProcessorEditor::~MakoBiteAudioProcessorEditor()
{
}

//==============================================================================
void MakoBiteAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    bool UseImage = true;
    juce::ColourGradient ColGrad;

    if (UseImage)
    {
        g.drawImageAt(imgBackground, 0, 0);        
    }
    else
    {
        //R1.00 Draw our GUI.
        //R1.00 Background.
        ColGrad = juce::ColourGradient(juce::Colour(0xFFD0D0D0), 0.0f, 0.0f, juce::Colour(0xFFF0F0F0), 0.0f, 70.0f, false);
        g.setGradientFill(ColGrad);
        g.fillRect(0, 0, 580, 71);
        ColGrad = juce::ColourGradient(juce::Colour(0xFFF0F0F0), 0.0f, 71.0f, juce::Colour(0xFF808080), 0.0f, 160.0f, false);
        g.setGradientFill(ColGrad);
        g.fillRect(0, 71, 580, 90);

        //R1.00 Draw LOGO text.
        g.setColour(juce::Colours::black);
        g.fillRect(120, 0, 300, 40);
        g.setFont(24.0f);
        g.setColour(juce::Colours::white);
        g.drawFittedText("R U S T Y", 120, 0, 300, 18, juce::Justification::centred, 1);
        g.setFont(18.0f);
        g.setColour(juce::Colours::orange);
        g.drawFittedText("M * A * K * O", 120, 20, 300, 15, juce::Justification::centred, 1);       

        g.setColour(juce::Colour(0x80000000));
        g.fillRect(10, 10, 20, 140);
        g.fillRect(510, 10, 20, 140);
                
        g.setColour(juce::Colours::red);
        g.fillEllipse(112, 137, 11, 11);
        g.setColour(juce::Colours::black);
        g.drawEllipse(110, 135, 15, 15, 3);

    }
    
    //R1.00 DRAW TEXT.
    //R1.00 Most of these could be done on the image to speed up painting.
    //R1.00 But the EQ frequencies need to update. So we are doing all the text
    //R1.00 here so the font matches no matter what in the future.
    g.setFont(12.0f);
    g.setColour(juce::Colours::black);
    for (int t = 0; t < Knob_Cnt; t++)
    {
        g.drawFittedText(Knob_Name[t], Knob_Pos[t].x, Knob_Pos[t].y - 10, Knob_Pos[t].sizex, 15, juce::Justification::centred, 1);
    }

    //R1.00 Draw the EQ frequency headers.
    g.drawFittedText(UIS_Band1, Knob_Pos[e_EQ1].x, Knob_Pos[e_EQ1].y - 10, Knob_Pos[e_EQ1].sizex, 15, juce::Justification::centred, 1);
    g.drawFittedText(UIS_Band2, Knob_Pos[e_EQ2].x, Knob_Pos[e_EQ2].y - 10, Knob_Pos[e_EQ2].sizex, 15, juce::Justification::centred, 1);
    g.drawFittedText(UIS_Band3, Knob_Pos[e_EQ3].x, Knob_Pos[e_EQ3].y - 10, Knob_Pos[e_EQ3].sizex, 15, juce::Justification::centred, 1);
    g.drawFittedText(UIS_Band4, Knob_Pos[e_EQ4].x, Knob_Pos[e_EQ4].y - 10, Knob_Pos[e_EQ4].sizex, 15, juce::Justification::centred, 1);
    g.drawFittedText(UIS_Band5, Knob_Pos[e_EQ5].x, Knob_Pos[e_EQ5].y - 10, Knob_Pos[e_EQ5].sizex, 15, juce::Justification::centred, 1);

}

void MakoBiteAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //R1.00 Use RETURN here to have a blank window drawn when creating a GUI image.
    //R1.00 The controls are only visible if thier BOUNDS are defined.
    //return;

    //R1.00 Draw all of the defined KNOBS.
    for (int t = 0; t < Knob_Cnt; t++) sldKnob[t].setBounds(Knob_Pos[t].x, Knob_Pos[t].y, Knob_Pos[t].sizex, Knob_Pos[t].sizey);    
}


//R1.00 Setup the SLIDER control edit values, Text Suffix (if any), UI tick marks, and Indicator Color.
void MakoBiteAudioProcessorEditor::GUI_Init_Large_Slider(juce::Slider* slider, float Val, float Vmin, float Vmax, float Vinterval, juce::String Suffix, int TickStyle, int ThumbColor)
{
    //R1.00 Setup the slider edit parameters.
    slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    slider->setTextValueSuffix(Suffix);
    slider->setRange(Vmin, Vmax, Vinterval);
    slider->setValue(Val);
    slider->addListener(this);
    addAndMakeVisible(slider);

    //R1.00 Override the default Juce drawing routines and use ours.
    slider->setLookAndFeel(&myLookAndFeel);

    //R1.00 Setup the type and colors for the sliders.
    slider->setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider->setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFC08000));
    slider->setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xFF000000));
    slider->setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF000000));
    slider->setColour(juce::Slider::textBoxHighlightColourId, juce::Colour(0xFF804000));
    slider->setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0x00000000));    //R1.00 Make this SEE THRU. Alpha=0.
    slider->setColour(juce::Slider::thumbColourId, juce::Colour(ThumbColor));

    //R1.00 Cheat: We are using this color as a Tick Mark style selector in our drawing function.
    slider->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(TickStyle));
}

void MakoBiteAudioProcessorEditor::GUI_Init_Small_Slider(juce::Slider* slider, float Val, float Vmin, float Vmax, float Vinterval, juce::String Suffix)
{
    //R1.00 Setup the slider edit parameters.
    slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    slider->setRange(Vmin, Vmax, Vinterval);
    slider->setTextValueSuffix(Suffix);
    slider->setValue(Val);
    slider->addListener(this);
    addAndMakeVisible(slider);

    //R1.00 Setup the type and colors for the sliders.
    slider->setSliderStyle(juce::Slider::LinearHorizontal);
    slider->setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFA0A0A0));
    slider->setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xFF202020));
    slider->setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF000000));
    slider->setColour(juce::Slider::textBoxHighlightColourId, juce::Colour(0xFF404040));
    slider->setColour(juce::Slider::trackColourId, juce::Colour(0xFF404040));
    slider->setColour(juce::Slider::backgroundColourId, juce::Colour(0xFF000000));
    slider->setColour(juce::Slider::thumbColourId, juce::Colour(0xFFE02020));
}

void MakoBiteAudioProcessorEditor::KNOB_DefinePosition(int idx,float x, float y, float sizex, float sizey, juce::String name)
{
    Knob_Pos[idx].x = x;
    Knob_Pos[idx].y = y;
    Knob_Pos[idx].sizex = sizex;
    Knob_Pos[idx].sizey = sizey;
    Knob_Name[idx] = name;
}

/*
void MakoBiteAudioProcessorEditor::updateToggleState(juce::Button* button, juce::String name)
{
    auto state = button->getToggleState();
    bool Butt_On = state ? true : false;

}
*/

void MakoBiteAudioProcessorEditor::Setting_UpdateProcessor(int SettingType)
{
    //R1.00 Set flags here that let the PROCESSOR know it needs to update settings.
    //R1.00 If we are changing settings in CODE, we dont want to update the proc until all done changing.
    if (audioProcessor.SettingsType != 100)
    {
        audioProcessor.SettingsType = SettingType;
        audioProcessor.SettingsChanged = true;  //R1.00 We need to update settings in processor.
    }
}


void MakoBiteAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{   
    //R1.00 Catch the EQ BAND change here so we can update the UI and frequencies.
    if (slider == &sldKnob[e_EQ])
    {   
        audioProcessor.Setting[e_EQ] = float(sldKnob[e_EQ].getValue());
        Band_SetFilterValues(true);
        audioProcessor.SettingsChanged += 1;        
        return; 
    }

    //R1.00 When a slider is adjusted, this func gets called. Capture the new edits and flag
    //R1.00 the processor when it needs to recalc things.
    //R1.00 Check which slider has been adjusted.
    for (int t = 0; t < Knob_Cnt; t++)
    {
        if (slider == &sldKnob[t])
        {            
            //R1.00 Update the actual processor variable being edited.
            audioProcessor.Setting[t] = float(sldKnob[t].getValue());

            //R1.00 We need to update settings in processor.
            //R1.00 Increment changed var to be sure every change gets made. Changed var is decremented in processor.
            audioProcessor.SettingsChanged += 1;

            //R1.00 We have captured the correct slider change, exit this function.
            return;
        }
    }
    
    return;
}

void MakoBiteAudioProcessorEditor::Band_SetFilterValues(bool ForcePaint)
{
    int EQ_Mode = int(audioProcessor.Setting[e_EQ]);

    //R1.01 Define the user selected EQ mode.
    switch (EQ_Mode)
    {
    default:
    {
        audioProcessor.Band1_Freq = 150.0f;
        audioProcessor.Band2_Freq = 300.0f;
        audioProcessor.Band3_Freq = 750.0f;
        audioProcessor.Band4_Freq = 1500.0f;
        audioProcessor.Band5_Freq = 3000.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = 1.414f;
        break;
    }
    case 1:
    {
        audioProcessor.Band1_Freq = 150.0f;
        audioProcessor.Band2_Freq = 450.0f;
        audioProcessor.Band3_Freq = 900.0f;
        audioProcessor.Band4_Freq = 1800.0f;
        audioProcessor.Band5_Freq = 3500.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = 1.414f;
        break;
    }
    case 2:
    {
        audioProcessor.Band1_Freq = 80.0f;
        audioProcessor.Band2_Freq = 220.0f;
        audioProcessor.Band3_Freq = 750.0f;
        audioProcessor.Band4_Freq = 2200.0f;
        audioProcessor.Band5_Freq = 6000.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = 1.414f;
        break;
    }
    case 3:
    {
        audioProcessor.Band1_Freq = 80.0f;
        audioProcessor.Band2_Freq = 350.0f;
        audioProcessor.Band3_Freq = 900.0f;
        audioProcessor.Band4_Freq = 1500.0f;
        audioProcessor.Band5_Freq = 3000.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = 1.414f;
        break;
    }
    case 4:
    {
        audioProcessor.Band1_Freq = 100.0f;
        audioProcessor.Band2_Freq = 400.0f;
        audioProcessor.Band3_Freq = 800.0f;
        audioProcessor.Band4_Freq = 1600.0f;
        audioProcessor.Band5_Freq = 3200.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = 1.414f;
        break;
    }
    case 5:
    {
        audioProcessor.Band1_Freq = 120.0f;
        audioProcessor.Band2_Freq = 330.0f;
        audioProcessor.Band3_Freq = 660.0f;
        audioProcessor.Band4_Freq = 1320.0f;
        audioProcessor.Band5_Freq = 2500.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = .707f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = .707f;
        break;
    }
    case 6:
    {
        audioProcessor.Band1_Freq = 150.0f;
        audioProcessor.Band2_Freq = 500.0f;
        audioProcessor.Band3_Freq = 900.0f;
        audioProcessor.Band4_Freq = 1800.0f;
        audioProcessor.Band5_Freq = 5000.0f;
        audioProcessor.Band1_Q = 1.414f;
        audioProcessor.Band2_Q = .707f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = .707f;
        break;
    }
    case 7:
    {
        audioProcessor.Band1_Freq = 80.0f;
        audioProcessor.Band2_Freq = 300.0f;
        audioProcessor.Band3_Freq = 650.0f;
        audioProcessor.Band4_Freq = 1500.0f;
        audioProcessor.Band5_Freq = 5000.0f;
        audioProcessor.Band1_Q = 1.414f;
        audioProcessor.Band2_Q = .707f;
        audioProcessor.Band3_Q = 2.00f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = .707f;
        break;
    }
    case 8:
    {
        audioProcessor.Band1_Freq = 100.0f;
        audioProcessor.Band2_Freq = 400.0f;
        audioProcessor.Band3_Freq = 800.0f;
        audioProcessor.Band4_Freq = 1500.0f;
        audioProcessor.Band5_Freq = 5000.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = .707f;
        audioProcessor.Band3_Q = 1.414f;
        audioProcessor.Band4_Q = 2.00f;
        audioProcessor.Band5_Q = .35f;
        break;
    }
    case 9:
    {
        audioProcessor.Band1_Freq = 80.0f;
        audioProcessor.Band2_Freq = 500.0f;
        audioProcessor.Band3_Freq = 1000.0f;
        audioProcessor.Band4_Freq = 2000.0f;
        audioProcessor.Band5_Freq = 5000.0f;
        audioProcessor.Band1_Q = .707f;
        audioProcessor.Band2_Q = 1.414f;
        audioProcessor.Band3_Q = .707f;
        audioProcessor.Band4_Q = .707f;
        audioProcessor.Band5_Q = .350f;
        break;
    }
    case 10:
    {
        audioProcessor.Band1_Freq = 80.0f;
        audioProcessor.Band2_Freq = 250.0f;
        audioProcessor.Band3_Freq = 750.0f;
        audioProcessor.Band4_Freq = 1800.0f;
        audioProcessor.Band5_Freq = 5000.0f;
        audioProcessor.Band1_Q = 2.000f;
        audioProcessor.Band2_Q = .707f;
        audioProcessor.Band3_Q = 2.00f;
        audioProcessor.Band4_Q = 1.414f;
        audioProcessor.Band5_Q = .350f;
        break;
    }

    }

    //R1.00 Create formatted strings for our UI.
    UIS_Band1 = std::to_string(int(audioProcessor.Band1_Freq));
    UIS_Band2 = std::to_string(int(audioProcessor.Band2_Freq));
    UIS_Band3 = std::to_string(int(audioProcessor.Band3_Freq));
    UIS_Band4 = std::to_string(int(audioProcessor.Band4_Freq));
    UIS_Band5 = std::to_string(int(audioProcessor.Band5_Freq));

    //R1.01 We changed some stuff so refresh the screen/UI.
    if (ForcePaint) repaint();

}
